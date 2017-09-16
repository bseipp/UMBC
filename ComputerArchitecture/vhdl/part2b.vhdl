-- part2a_start.vhdl   VHDL '93 version using entities from WORK library
--              basic five stage pipeline of MIPS architecture
--              The 411 course pipeline has the same five stages
--              IF Instruction Fetch includes PC and instruction memory
--              ID Instruction Decode and registers
--              EX Execution including the ALU Arithmetic Logic Unit
--              MEM data Memory
--              WB Write Back into registers
--
--              The signal naming convention uses the stage as a prefix
--              WORK library needs entities and architectures for
--              add32  and  bshift.
--
-- This self contained VHDL file defines:
--     a package declaration and body that defines functions and memory
--     a 32 bit and a 5 bit register entity with clock and clear inputs
--     an instruction memory entity and behavioral architecture
--     a data memory entity and behavioral architecture
--     a general register entity and behavioral architecture
--     multiplexer entities and behavioral architectures
--     equal comparator entities and circuit architectures
--     an incomplete ALU entity and schematic architecture

--     a top level entity, part2b, test bench
--     the architecture, schematic layout of the top level entity
--     the signals for interconnecting the entities
--     a clock generator process
--     the entities connected with signals (port maps)
--     a memory read process that reads "part2b.abs"
--     a print process that shows the registers in the pipeline each clock

library IEEE;
use IEEE.std_logic_1164.all;

package util_pkg is
  function to_integer(sig : std_logic_vector) return integer;

  -- main memory, a process reads a file to load memory
  subtype word is std_logic_vector(31 downto 0);
  type mem_array is array(integer range <>) of word;
  shared variable memory: mem_array(0 to 4095);  -- max 12 bit addresses

  -- general register memory
  type reg_mem_type is array (natural range <>) of word;
  shared variable reg_mem : reg_mem_type(0 to 31) := (others =>(others =>'0'));
end package util_pkg;

package body util_pkg is
  function to_integer(sig : std_logic_vector) return integer is
    variable num : integer := 0;  -- descending sig as integer
  begin
    for i in sig'range loop
      if sig(i)='1' then
        num := num*2+1;
      else
        num := num*2;
      end if;
    end loop;  -- i
    return num;
  end function to_integer;
end package body util_pkg;

library IEEE;
use IEEE.std_logic_1164.all;

entity register_32 is
  port(clk    : in  std_logic;
       clear  : in  std_logic;
       input  : in  std_logic_vector (31 downto 0);
       output : out std_logic_vector (31 downto 0) );
end entity register_32;

architecture behavior of register_32 is
begin  -- behavior
  reg_32: process(clk, clear)
          begin
            if clear='1' then  -- only once
              output <= (others=>'0');
            elsif clk'event and clk='1' then
              output <= input after 250 ps;
            end if;
          end process reg_32;
end architecture behavior;  -- of register_32

library IEEE;
use IEEE.std_logic_1164.all;

entity register_5 is
  port(clk    : in  std_logic;
       clear  : in  std_logic;
       input  : in  std_logic_vector (4 downto 0);
       output : out std_logic_vector (4 downto 0) );
end entity register_5;

architecture behavior of register_5 is
begin  -- behavior
  reg_5: process(clk, clear)
         begin
           if clear='1' then  -- only once
             output <= (others=>'0');
           elsif clk'event and clk='1' then
             output <= input after 250 ps;
           end if;
         end process reg_5;
end architecture behavior;  -- of register_5


library IEEE;
use IEEE.std_logic_1164.all;
use WORK.util_pkg.all;

entity instruction_memory is
  port(clear : in  std_logic;
       addr  : in  std_logic_vector (31 downto 0);
       inst  : out std_logic_vector (31 downto 0));
end entity instruction_memory;

architecture behavior of instruction_memory is
begin  -- behavior
  inst_mem: process(addr, clear) 
              variable word_addr : natural;  -- byte addr/4
            begin
              if clear='1' then  -- total machine clear  
                inst <= x"00000000";
              else -- normal operation
                word_addr := to_integer(addr(13 downto 2)); -- crop to 12 bits
                inst <= memory(word_addr) after 250 ps;
              end if;
            end process inst_mem;
end architecture behavior;  -- of instruction_memory


library IEEE;
use IEEE.std_logic_1164.all;
use WORK.util_pkg.all;

entity data_memory is
  port(address      : in  std_logic_vector (31 downto 0);
       write_data   : in  std_logic_vector (31 downto 0);
       read_enable  : in  std_logic;  -- from address
       write_enable : in  std_logic;  -- rising clock and enable
       write_clk    : in  std_logic;  -- required to write
       read_data    : out std_logic_vector (31 downto 0));
end entity data_memory;

architecture behavior of data_memory is
begin  -- behavior
  data_mem: process(address, write_clk)
              variable word_addr : natural;  -- byte addr/4
            begin
              if write_enable='1' and write_clk='1' then
                word_addr := to_integer(address(13 downto 2));  -- 12 bits
                memory(word_addr) := write_data;  -- write main memory
                read_data <= write_data;  -- just something to output
              elsif read_enable='1' then
                word_addr := to_integer(address(13 downto 2));  -- 12 bits
                read_data <= memory(word_addr) after 250 ps;  -- read memory
              else
                read_data <= x"00000000";  -- just to clean up printout
              end if;
            end process data_mem;
end architecture behavior;  -- of data_memory


library IEEE;
use IEEE.std_logic_1164.all;
use WORK.util_pkg.all;

entity registers is
  port(read_reg_1   : in  std_logic_vector (4 downto 0); -- address
       read_reg_2   : in  std_logic_vector (4 downto 0); -- address
       write_reg    : in  std_logic_vector (4 downto 0); -- address
       write_data   : in  std_logic_vector (31 downto 0);
       write_enable : in  std_logic;  -- rising clock and enable
       write_clk    : in  std_logic;  -- required to write
       read_data_1  : out std_logic_vector (31 downto 0);
       read_data_2  : out std_logic_vector (31 downto 0));
end entity registers;

architecture behavior of registers is
begin  -- behavior
  reg: process(read_reg_1, read_reg_2, write_clk)
         variable reg_addr : natural;
       begin
         if write_enable='1' and write_clk'active and write_clk='1' then
           reg_addr := to_integer(write_reg);
           if reg_addr/=0 then           -- can not change register zero
             reg_mem(reg_addr) := write_data;
           end if;
         end if;
         read_data_1 <= reg_mem(to_integer(read_reg_1));
         read_data_2 <= reg_mem(to_integer(read_reg_2));
         -- signals updated after process exits
       end process reg;
end architecture behavior;  -- of registers

library IEEE;
use IEEE.std_logic_1164.all;

entity mux_32 is
  port(in0    : in  std_logic_vector (31 downto 0);
       in1    : in  std_logic_vector (31 downto 0);
       ctl    : in  std_logic;
       result : out std_logic_vector (31 downto 0));
end entity mux_32;

architecture behavior of mux_32 is 
begin  -- behavior -- no process needed with concurrent statements
  result <= in1 when ctl='1' else in0 after 250 ps;
end architecture behavior;  -- of mux_32

library IEEE;
use IEEE.std_logic_1164.all;
entity mux32_3 is
  port(in0    : in  std_logic_vector (31 downto 0);
       in1    : in  std_logic_vector (31 downto 0);
       in2    : in  std_logic_vector (31 downto 0);
       ct1    : in  std_logic;          -- pass in1(has priority)
       ct2    : in  std_logic;          -- pass in2
       result : out std_logic_vector (31 downto 0));
end entity mux32_3;

architecture behavior of mux32_3 is 
begin  -- behavior -- no process needed with concurrent statements
  result <= in1 when ct1='1' else in2 when ct2='1' else in0 after 50 ps;
end architecture behavior;  -- of mux32_3

library IEEE;
use IEEE.std_logic_1164.all;
entity mux32_6 is
  port(in0    : in  std_logic_vector (31 downto 0);
       in1    : in  std_logic_vector (31 downto 0);
       in2    : in  std_logic_vector (31 downto 0);
       in3    : in  std_logic_vector (31 downto 0);
       in4    : in  std_logic_vector (31 downto 0);
       in5    : in  std_logic_vector (31 downto 0);
       ct1    : in  std_logic;          -- pass in1(has priority)
       ct2    : in  std_logic;          -- pass in2
       ct3    : in  std_logic;          -- pass in3
       ct4    : in  std_logic;          -- pass in4
       ct5    : in  std_logic;          -- pass in5
       result : out std_logic_vector (31 downto 0));
end entity mux32_6;

architecture behavior of mux32_6 is
begin  -- behavior -- no process needed with concurrent statements
  result <= in1 when ct1='1'  else in2 when ct2='1' else
            in3 when ct3='1'  else in4 when ct4='1' else
            in5 when ct5='1' else in0 after 50 ps;
end architecture behavior;  -- of mux32_6

library IEEE;
use IEEE.std_logic_1164.all;

entity mux_5 is
  port(in0    : in  std_logic_vector (4 downto 0);
       in1    : in  std_logic_vector (4 downto 0);
       ctl    : in  std_logic;
       result : out std_logic_vector (4 downto 0));
end entity mux_5;

architecture behavior of mux_5 is 
begin  -- behavior -- no process needed with concurrent statements
  result <= in1 when ctl='1' else in0 after 250 ps;
end architecture behavior;  -- of mux_5

library IEEE;
use IEEE.std_logic_1164.all;

entity equal32 is --  a 32-bit compare
  port(inst  : in  std_logic_vector(31 downto 0);
       test  : in  std_logic_vector(31 downto 0);
       equal : out std_logic);
end entity equal32;

architecture circuits of equal32 is
  signal temp : std_logic_vector(0 to 32) := (others=>'1');
begin  -- circuits
  t1: for I in 0 to 31 generate
        temp(I+1) <= (inst(I) xnor test(I)) and temp(I);
      end generate t1;
  equal <= temp(32);
end architecture circuits;  -- of equal32

library IEEE;
use IEEE.std_logic_1164.all;

entity equal6 is -- basically a 6-bit op code compare
  port(inst  : in  std_logic_vector(5 downto 0);
       test  : in  std_logic_vector(5 downto 0);
       equal : out std_logic);
end entity equal6;

architecture circuits of equal6 is
  signal temp : std_logic_vector(0 to 6) := (others=>'1');
begin  -- circuits
  t1: for I in 0 to 5 generate
        temp(I+1) <= (inst(I) xnor test(I)) and temp(I);
      end generate t1;
  equal <= temp(6);
end architecture circuits;  -- of equal6

library IEEE;
use IEEE.std_logic_1164.all;

entity equal5 is -- basically a 5-bit register number compare
  port(inst  : in  std_logic_vector(4 downto 0);
       test  : in  std_logic_vector(4 downto 0);
       equal : out std_logic);
end entity equal5;

architecture circuits of equal5 is
  signal temp : std_logic_vector(0 to 5) := (others=>'1');
begin  -- circuits
  t1: for I in 0 to 4 generate
        temp(I+1) <= (inst(I) xnor test(I)) and temp(I);
      end generate t1;
  equal <= temp(5);
end architecture circuits;  -- of equal5


library IEEE;
use IEEE.std_logic_1164.all;

entity alu_32 is
  port(inA    : in  std_logic_vector (31 downto 0);
       inB    : in  std_logic_vector (31 downto 0);
       inst   : in  std_logic_vector (31 downto 0);
       result : out std_logic_vector (31 downto 0));
end entity alu_32;

architecture schematic of alu_32 is 
  signal cin       : std_logic := '0';
  signal cout      : std_logic;
  signal RRop      : std_logic;
  signal orop      : std_logic;
  signal orop_and  : std_logic;
  signal andop     : std_logic;
  signal andop_and : std_logic;
  signal S_sel     : std_logic;
  signal mulop      : std_logic;
  signal mulop_and  : std_logic;
  signal divop      : std_logic;
  signal divop_and  : std_logic;
  signal subop: std_logic;
  signal subop_and: std_logic;
  signal sllop: std_logic;
  signal sllop_and: std_logic;
  signal srlop: std_logic;
  signal srlop_and: std_logic;
  signal cmplop: std_logic;
  signal cmplop_and: std_logic;

  signal srlop_and_or_sllop_and: std_logic;
  signal subop_and_or_cmplop_and: std_logic;
  signal notinB: std_logic_vector(31 downto 0);
  signal resultM: std_logic_vector(31 downto 0);
  
  signal aresult : std_logic_vector (31 downto 0);
  signal bresult : std_logic_vector (31 downto 0);
  signal orresult : std_logic_vector (31 downto 0);
  signal andresult : std_logic_vector (31 downto 0);
  signal mulresult : std_logic_vector (31 downto 0);
  signal divquo    : std_logic_vector (15 downto 0);
  signal divquo32  : std_logic_vector (31 downto 0);
  signal divrem    : std_logic_vector (15 downto 0);
  signal divrem32  : std_logic_vector (31 downto 0);
  signal z16       : std_logic_vector (15 downto 0) := "0000000000000000";
  
begin  -- schematic
  ORR : entity WORK.equal6 port map(inst(31 downto 26), "000000", RRop);
  Oor:  entity WORK.equal6 port map(inst(5 downto 0), "001101", orop);
  Omul: entity WORK.equal6 port map(inst(5 downto 0), "011011", mulop);
  Odiv: entity WORK.equal6 port map(inst(5 downto 0), "011000", divop);
  Osub : entity WORK.equal6 port map(inst(5 downto 0), "100010",subop);
  Oand: entity WORK.equal6 port map(inst(5 downto 0), "001010", andop);
  Osll: entity WORK.equal6 port map(inst(5 downto 0), "000010", sllop);
  Osrl: entity WORK.equal6 port map(inst(5 downto 0), "000011", srlop);
  Ocmpl: entity WORK.equal6 port map(inst(5 downto 0), "001011", cmplop);


  srlop_and_or_sllop_and <= srlop_and or sllop_and;
  orop_and  <=orop and RRop;
  mulop_and <=mulop and RRop;
  divop_and <=divop and RRop;
  subop_and <=subop and RRop;
  andop_and <=andop and RRop;
 
  srlop_and_or_sllop_and <= srlop_and or sllop_and;
  subop_and_or_cmplop_and <= subop_and or cmplop_and;
  notinB <= not inB;

  sllop_and <=sllop and RRop;
  srlop_and <=srlop and RRop;
  cmplop_and <=cmplop and Rrop;
  S_sel <= srlop_and_or_sllop_and;
-----------------------------------------------------------------------------mux 32!
 
  adder: entity WORK.add32 port map(a    => inA,
                                    b => resultM,
                                    cin  => subop_and,
                                    sum  => aresult,
                                    cout => cout);


  and_result: andresult <= inA and inB;
  or_result: orresult <= inA or inB;
  
  Mux_B: entity WORK.mux_32 port map(inB, notinB, subop_and_or_cmplop_and, resultM);

   bshifter: entity WORK.bshift port map(left => sllop,
                                    logical => '1',
                                    shift => inst(10 downto 6),
                                    input => inB,
                                    output => bresult);


  Mul:  entity WORK.pmul8 port map(inA(7 downto 0),
                                   inB(7 downto 0),
                                   mulresult(15 downto 0));

  Div:  entity WORK.divcas16 port map(inA(31 downto 0),
                                      inB(15 downto 0),
                                      divquo(15 downto 0),
                                      divrem(15 downto 0));

  divquo32 <= z16&divquo;
  divrem32 <= z16&divrem;   -- not used yet

  Omux: entity WORK.mux32_6 port map(in0=>aresult,
                                     in1=>bresult,
                                     in2=>andresult,
                                     in3=>orresult,
                                     in4=>mulresult,
                                     in5=>divquo32,
                                     ct1=>S_sel,
                                     ct2=>andop_and,
                                     ct3=>orop_and,
                                     ct4=>mulop_and,
                                     ct5=>divop_and,
                                     result=>result);
end architecture schematic;  -- of alu_32


entity part2b is  -- test bench
end part2b;

library STD;
use STD.textio.all;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_textio.all;
use WORK.util_pkg.all;

architecture schematic of part2b is -- top level connection of entities
  
  -- signals used in top level architecture (the interconnections)
  
  subtype word_32 is std_logic_vector(31 downto 0);  -- data and inst
  subtype word_6 is std_logic_vector(5 downto 0);    -- op codes
  subtype word_5 is std_logic_vector(4 downto 0);    -- register numbers
  
  signal zero_32 : word_32 := (others=>'0');     -- 32 bits of zero
  signal zero    : std_logic := '0';             -- one bit zero
  signal four_32 : word_32 := x"00000004";       -- four

  signal lwop    : word_6 := "100011";     -- lw op code
  signal RRop    : word_6 := "000000";     -- RR op code
  
  signal clear   : std_logic := '1';       -- one shot clear
  signal clk     : std_logic := '1';       -- master clock
  signal clk_bar : std_logic := '0';       -- complement of master clock
  signal counter : integer := 0;           -- master clock counter,raising edge
  
  signal PC_next        : word_32;            -- next value of PC 
  signal PC             : word_32;            -- Program Counter
  signal inst           : word_32;            -- instruction fetched
  
  signal ID_IR          : word_32;            -- ID Instruction Register
  signal ID_read_data_1 : word_32;            -- ID Register read data 1
  signal ID_read_data_2 : word_32;            -- ID Register read data 2
  signal ID_sign_ext    : word_32;            -- ID sign extension
  signal RegDst         : std_logic := '0';   -- ID register destination ctl
  signal ID_rd          : word_5;             -- ID register destination
  alias  ID_addr        : std_logic_vector(15 downto 0) is ID_IR(15 downto 0);
  
  signal EX_IR          : word_32;            -- EX Instruction Register
  signal EX_A           : word_32;            -- EX data A
  signal EX_B           : word_32;            -- EX data B
  signal EX_C           : word_32;            -- EX data C
  signal EX_rd          : word_5;             -- EX register destination
  signal EX_aluB        : word_32;            -- EX into ALU B
  signal ALUSrc         : std_logic := '1';   -- EX ALU B side source control
  signal EX_result      : word_32;            -- EX ALU output
  
  signal MEM_IR         : word_32;            -- MEM Inst Register
  signal MEM_addr       : word_32;            -- MEM address
  signal MEM_data       : word_32;            -- MEM write data
  signal MEM_read_data  : word_32;            -- MEM read data
  signal MEM_rd         : word_5;             -- MEM register destination
  signal MEMRead        : std_logic := '1';   -- MEM enable read
  signal MEMWrite       : std_logic := '0';   -- MEM enable write
  
  signal WB_IR          : word_32;            -- WB Instruction Register
  signal WB_read        : word_32;            -- WB read data
  signal WB_pass        : word_32;            -- WB pass data
  signal WB_rd          : word_5;             -- WB register destination
  signal WB_rd_zero     : std_logic;          -- WB_rd is zero, no value
  signal MemtoReg       : std_logic := '1';   -- WB mux control
  signal WB_result      : word_32;            -- WB mux output
  signal WB_write_enb   : std_logic := '1';   -- WB enable register write
  signal WB_lwop        : std_logic;          -- Have a LW in WB stage
  signal result1: std_logic;
  signal WB_RRop: std_logic;
  signal WB_addiop: std_logic;

  signal AFMA, AFMA1, AFMA2, AFMA3 : std_logic;
  signal BFMA, BFMA1, BFMA2, BFMA3 : std_logic;
  signal AFWB, AFWB1, AFWB2, AFWB3 : std_logic;
  signal BFWB, BFWB1, BFWB2, BFWB3 : std_logic;
  signal OneF, OneF1, OneF2, OneF3 : std_logic;
  signal TwoF, TwoF1, TwoF2, TwoF3 : std_logic;
  signal jump : std_logic;
  signal beq : std_logic;
  signal sw : std_logic;
  signal equal32SigA, equal32SigB : std_logic_vector(31 downto 0);
  signal equal32ResultSig :std_logic;
  signal beq_and_equal32ResultSig : std_logic;
  signal resultPCAdd : std_logic;
  signal shifterPCRegAdderResult, mux32_3aResult, mux32_3bResult : std_logic_vector(31 downto 0);
  signal PCP : std_logic_vector(31 downto 0);
  signal ctlOrSig : std_logic;
  signal shifted2, jump_Addr : std_logic_vector(31 downto 0);
  signal beq_and_equal32ResSig : std_logic;
  signal PC_next2 : word_32;
  signal old_ID_rd : word_5;
  signal EX_BB : std_logic_vector(31 downto 0);
  
  signal slw1, slw2, slw3, slw4, slw5, slw6, stall_lw : std_logic;
  signal slwlw1, slwlw2, slwlw3, slwlw4, slwlw5, slwlw6, stall_lwlw : std_logic;
  signal smem1, smem2, smem3, smem4, smem5, smem6, stall_mem : std_logic;
  signal sbeq1, sbeq2, sbeq3, sbeq4, sbeq5, sbeq6, stall_beq : std_logic;
  signal slw3a, slw3b, slwlw3a, slwlw3b, smem3a, smem3b, sbeq3a, sbeq3b : std_logic;
  signal stall : std_logic;
  signal sclk : std_logic;
  signal ID_IR_muxed : word_32;
  signal nop         : word_32 := x"00000000";

  alias ID_reg1 : word_5 is ID_IR(25 downto 21);
  alias ID_reg2 : word_5 is ID_IR(20 downto 16);
  alias MEM_OP  : word_6 is MEM_IR(31 downto 26);
  alias ID_OP   : word_6 is ID_IR(31 downto 26);
  alias EX_OP   : word_6 is EX_IR(31 downto 26);
  alias EX_reg1 : word_5 is EX_IR(25 downto 21);
  alias EX_reg2 : word_5 is EX_IR(20 downto 16);
    
begin  -- schematic of part2b, top level architecture and test bench

  -- First Stall : stall_lw
  eq40:  entity WORK.equal6 port map (EX_OP, "100011", slw1);
  eq41:  entity WORK.equal5 port map (EX_rd, "00000", slw2);
  eq42:  entity WORK.equal5 port map (ID_reg1, EX_rd, slw3a);
  eq43:  entity WORK.equal5 port map (ID_reg2, EX_rd, slw3b);
  slw3 <= slw3a or slw3b;
  eq44:  entity WORK.equal6 port map (ID_OP, "100011", slw4);
  eq45:  entity WORK.equal6 port map (ID_OP, "000111", slw5);
  eq46:  entity WORK.equal6 port map (ID_OP, "000010", slw6);
  stall_lw <= slw1 and not slw2 and slw3 and not slw4 and not slw5 and not slw6;
  
  -- Second Stall : stall_lwlw
  eq47:  entity WORK.equal6 port map (EX_OP, "100011", slwlw1);
  eq48:  entity WORK.equal5 port map (EX_rd, "00000", slwlw2);
  eq49:  entity WORK.equal6 port map (ID_OP, "100011", slwlw3a);
  eq50:  entity WORK.equal6 port map (ID_OP, "000111", slwlw3b);
  slwlw3 <= slwlw3a or slwlw3b;
  eq51:  entity WORK.equal5 port map (ID_reg1, EX_rd, slwlw4);
  stall_lwlw <= slwlw1 and not slwlw2 and slwlw3 and slwlw4;

  -- Third Stall : stall_mem
  eq52:  entity WORK.equal6 port map (ID_OP, "011111", smem1);
  eq53:  entity WORK.equal5 port map (MEM_rd, "00000", smem2);
  eq54:  entity WORK.equal6 port map (MEM_OP, "100011", smem4);
  eq55:  entity WORK.equal5 port map (ID_reg1, MEM_rd, smem3a);
  eq56:  entity WORK.equal5 port map (ID_reg2, MEM_rd, smem3b);
  smem3 <= smem3a or smem3b;
  stall_mem <= smem1 and not smem2 and smem3 and smem4;

  -- Fourth Stall : stall_beq
  eq57:  entity WORK.equal6 port map (ID_OP, "011111", sbeq1);
  eq58:  entity WORK.equal5 port map (EX_rd, "00000", sbeq2);
  eq59:  entity WORK.equal5 port map (ID_reg1, EX_rd, sbeq3a);
  eq60:  entity WORK.equal5 port map (ID_reg2, EX_rd, sbeq3b);
  sbeq3 <= sbeq3a or sbeq3b;
  stall_beq <= sbeq1 and not sbeq2 and sbeq3;

  stall <= stall_lw or stall_lwlw or stall_mem or stall_beq;

  sclk <= clk or stall;
  
  clock_gen: process(clk, clear)  -- clock generator and one shot clear signal
             begin
               if clear='1' then -- happens only once
                 clear <= '0' after 200 ps;
               elsif clear='0' then     -- avoid time zero glitch
                 clk <= not clk after 5 ns;  -- 10 ns period
               end if;
             end process clock_gen;

             clk_bar <= not clk;               -- for split phase registers


             
  eq17 : entity WORK.equal5 port map (EX_IR(25 downto 21), MEM_rd, AFMA1);
  eq18:  entity WORK.equal5 port map (MEM_rd, "00000", AFMA2);
  eq19:  entity WORK.equal6 port map (MEM_IR(31 downto 26), "100011", AFMA3);
  AFMA <= AFMA1 and not AFMA2 and not AFMA3;

  eq20 : entity WORK.equal5 port map (EX_IR(25 downto 21), WB_rd, AFWB1);
  eq21:  entity WORK.equal5 port map (WB_rd, "00000", AFWB2);
--  eq22:  entity WORK.equal5 port map (MEM_IR(31 downto 26), "100011", AFWB3);
  AFWB <= AFWB1 and not AFWB2; --and not AFMA3;

             
  eq22 : entity WORK.equal5 port map (EX_IR(20 downto 16), MEM_rd, BFMA1);
  eq23 : entity WORK.equal5 port map (MEM_rd, "00000", BFMA2);
  eq24 :  entity WORK.equal6 port map (MEM_IR(31 downto 26), "100011", BFMA3);
  BFMA <= BFMA1 and not BFMA2 and not BFMA3;

  eq25 : entity WORK.equal5 port map (EX_IR(20 downto 16), WB_rd, BFWB1);
  eq26 :  entity WORK.equal5 port map (WB_rd, "00000", BFWB2);
--  eq22:  entity WORK.equal5 port map (MEM_IR(31 downto 26), "100011", AFWB3);
  BFWB <= BFWB1 and not BFWB2; --and not AFMA3;

             
  eq27 : entity WORK.equal5 port map (ID_IR(25 downto 21), MEM_rd, OneF1);
  eq28 : entity WORK.equal5 port map (MEM_rd, "00000", OneF2);
  eq29 :  entity WORK.equal6 port map (MEM_IR(31 downto 26), "100011", OneF3);
  OneF <= OneF1 and not OneF2 and not OneF3;

  eq30 : entity WORK.equal5 port map (ID_IR(25 downto 21), MEM_rd, TwoF1);
  eq31 : entity WORK.equal5 port map (MEM_rd, "00000", TwoF2);
  eq32 :  entity WORK.equal6 port map (MEM_IR(31 downto 26), "100011", TwoF3);
  TwoF <= TwoF1 and not TwoF2 and not TwoF3;


             
             
-- IF, Instruction Fetch pipeline stage
  PC_reg:    entity WORK.register_32 port map(sclk, clear, PC_next, PC);
  PC_incr:   entity WORK.add32 port map(PC, four_32, zero, PC_next2, open);
  inst_mem:  entity WORK.instruction_memory port map(clear, PC, inst);

-- ID, Instruction Decode and register stack pipeline stage
  ID_IR_reg: entity WORK.register_32 port map(sclk, clear, inst, ID_IR);
  ID_regs:   entity WORK.registers port map(
                                read_reg_1   => ID_IR(25 downto 21),
                                read_reg_2   => ID_IR(20 downto 16),
                                write_reg    => WB_rd,
                                write_data   => WB_result,
                                write_enable => WB_write_enb,
                                write_clk    => clk_bar,
                                read_data_1  => ID_read_data_1,
                                read_data_2  => ID_read_data_2);

Reg_Dest: entity WORK.equal6 port map(ID_IR(31 downto 26), "000000", RegDst);
 
 ID_mux_rd: entity WORK.mux_5 port map(in0    => ID_IR(20 downto 16),
                                        in1    => ID_IR(15 downto 11),
                                        ctl    => RegDst,
                                        result => old_ID_rd);
             ID_sign_ext(15 downto 0) <= ID_addr;  -- just wiring
             ID_sign_ext(31 downto 16) <= (others => ID_IR(15));

             
  jumpEntity: entity WORK.equal6 port map(inst => ID_IR(31 downto 26),
                                          test => "000010",
                                          equal => jump);
             
  beqEntity: entity WORK.equal6 port map(inst => ID_IR(31 downto 26),
                                          test => "011111",
                                          equal => beq);
             
  swEntity: entity WORK.equal6 port map(inst => ID_IR(31 downto 26),
                                          test => "101011",
                                          equal => sw);

  ctlOrSig <= jump or beq or sw or stall;           
             
  ID_mux_rd2: entity WORK.mux_5 port map(in0 => old_ID_rd,
                                         in1 => "00000",
                                         ctl => ctlOrSig,
                                         result => ID_rd);

  ID_mux_equal32A: entity WORK.mux_32 port map(in0 => ID_read_data_1,
                                              in1 => MEM_addr,
                                              ctl => OneF,
                                              result => equal32SigA);

  ID_mux_equal32B: entity WORK.mux_32 port map(in0 => ID_read_data_2,
                                              in1 => MEM_addr,
                                              ctl => TwoF,
                                              result => equal32SigB);

  ID_equal32: entity WORK.equal32 port map(inst => equal32SigA,
                                           test => equal32SigB,
                                           equal => equal32ResultSig);

  shifted2 <= ID_sign_ext(29 downto 0) & "00";

  beq_and_equal32ResSig <= beq and equal32ResultSig;

  pcp_reg: entity WORK.register_32 port map(sclk, clear, PC_next2, PCP);

  shifteerPCregAdder : entity WORK.add32 port map(shifted2, PCP, zero, shifterPCRegAdderResult, open);

  jump_addr <= PCP(31 downto 28) & ID_IR(25 downto 0) & "00";

  mux32_3PC_next: entity WORK.mux32_3 port map(in0 => PC_next2,
                                               in1 => jump_addr,
                                               in2 => shifterPCRegAdderResult,
                                               ct1 => jump,
                                               ct2 => beq_and_equal32ResSig,
                                               result => PC_next);

  stall_mux: entity WORK.mux_32 port map (in0 => ID_IR,
                                           in1 => nop,
                                           ctl => stall,
                                           result => ID_IR_muxed);
             
  EX_IR_reg: entity WORK.register_32 port map(clk, clear, ID_IR_muxed, EX_IR);
  EX_A_reg : entity WORK.register_32 port map(clk, clear, ID_read_data_1,EX_A);
  EX_B_reg : entity WORK.register_32 port map(clk, clear, ID_read_data_2,EX_B);
  EX_C_reg : entity WORK.register_32 port map(clk, clear, ID_sign_ext, EX_C);
  EX_rd_reg: entity WORK.register_5  port map(clk, clear, ID_rd, EX_rd);

  EQUAL6 : entity WORK.equal6 port map (EX_IR(31 downto 26),
                                        "000000",
                                        result1);

             ALUSrc <= not result1;

  Omux32_3a : entity WORK.mux32_3 port map(in0 => EX_A,
                                          in1 => MEM_addr,
                                          in2 => WB_result,
                                          ct1 => AFMA,
                                          ct2 => AFWB,
                                          result => mux32_3aResult);

  Omux32_3b : entity WORK.mux32_3 port map(in0 => EX_B,
                                          in1 => MEM_addr,
                                          in2 => WB_result,
                                          ct1 => BFMA,
                                          ct2 => BFWB,
                                          result => mux32_3bResult);

  EX_BB <= mux32_3bResult;
             
  EX_mux1  : entity WORK.mux_32 port map(in0    => mux32_3bResult,
                                         in1    => EX_C,
                                         ctl    => ALUSrc,
                                         result => EX_aluB );

  ALU      : entity WORK.alu_32 port map(inA   => mux32_3aResult,
                                         inB   => EX_aluB,
                                         inst  => EX_IR,
                                         result=> EX_result);

-- MEM Data Memory pipeline stage
  MEM_IR_reg  : entity WORK.register_32 port map(clk, clear, EX_IR, MEM_IR);
  MEM_addr_reg: entity WORK.register_32 port map(clk, clear, EX_result,
                                                 MEM_addr);
  MEM_data_reg: entity WORK.register_32 port map(clk, clear, EX_BB, MEM_data);
  MEM_rd_reg  : entity WORK.register_5  port map(clk, clear, EX_rd, MEM_rd);

  MEM_lw      : entity WORK.equal6 port map(MEM_IR(31 downto 26), lwop,
                                            MEMRead);

   MEM_sw      : entity WORK.equal6 port map(MEM_IR(31 downto 26), "101011", MEMWrite);
  data_mem    : entity WORK.data_memory port map(address     => MEM_addr,
                                                 write_data  => MEM_data,
                                                 read_enable => MEMRead,
                                                 write_enable=> MEMWrite,
                                                 write_clk   => clk_bar,
                                                 read_data   => MEM_read_data);
             
 


-- WB, Write Back pipeline stage
  WB_IR_reg  : entity WORK.register_32 port map(clk, clear, MEM_IR, WB_IR);
  WB_read_reg: entity WORK.register_32 port map(clk, clear, MEM_read_data,
                                                WB_read);
  WB_pass_reg: entity WORK.register_32 port map(clk, clear, MEM_addr, WB_pass);
  WB_rd_reg  : entity WORK.register_5  port map(clk, clear, MEM_rd, WB_rd);
  decode_mt  : entity WORK.equal6 port map(WB_IR(31 downto 26), lwop, WB_lwop);
             MemtoReg <= WB_lwop;

  WBrrop: entity WORK.equal6 port map( WB_IR(31 downto 26),"000000", WB_RRop);
  WBaddiop: entity WORK.equal6 port map(WB_IR(31 downto 26),"000111",WB_addiop);
  compare_rd : entity WORK.equal5 port map(WB_rd, "00000", WB_rd_zero);
               WB_write_enb <= (not WB_rd_zero) and
                               (WB_lwop or WB_RRop or WB_addiop );  --  or WB_RRop or WB_addiop ???

  WB_mux     : entity WORK.mux_32 port map(in0    => WB_pass,
                                           in1    => WB_read,
                                           ctl    => MemtoReg,
                                           result => WB_result );
    
  loadmem: process    -- read part2b.abs into shared memory array
             file my_input : TEXT open READ_MODE is "part2b.abs";  -- hex data
             variable good : boolean := true;
             variable my_line : LINE;
             variable my_input_line : LINE;
             variable loc : std_logic_vector(31 downto 0);  -- read from file
             variable val : std_logic_vector(31 downto 0);  -- read from file
             variable word_addr : natural;  -- byte addr/4
           begin
             write(my_line, string'
                   ("---PC--- --inst--  loadmem process input .abs file"));
             writeline(output, my_line);
             while good loop
               exit when endfile(my_input);
               readline(my_input, my_input_line);
               my_line := new string'(my_input_line.all);  -- for printing
               writeline(output, my_line); -- writing clears my_line
               hread(my_input_line, loc, good);
               exit when not good;
               hread(my_input_line, val, good);
               exit when not good;
               word_addr := to_integer(loc(13 downto 2)); -- crop to 12 bits
               memory(word_addr) := val;  -- write main memory
             end loop;
             write(my_line, string'("loadmem ended. memory loaded"));
             writeline(output, my_line);
             wait; -- run once. do not keep restarting process
           end process loadmem;
           
  printout:  process -- used to show pipeline, registers and memory
               variable my_line : LINE;   -- not part of working circuit
             begin
               wait for 9.5 ns;         -- just before rising clock
               write(my_line, string'("clock "));
               write(my_line, counter);
               write(my_line, string'("  inst="));
               hwrite(my_line, inst);
               write(my_line, string'("  PC   ="));
               hwrite(my_line, PC);
               write(my_line, string'(" PCnext="));
               hwrite(my_line, PC_next);
               writeline(output, my_line);
               write(my_line, string'("ID  stage  IR="));
               hwrite(my_line, ID_IR);
               if (WB_write_enb='1') and (WB_rd/="00000") then
                 write(my_line, string'("  write="));
                 hwrite(my_line, WB_result);
                 write(my_line, string'("  into ="));
                 hwrite(my_line, "000000000000000000000000000"&WB_rd);
               else
                 write(my_line, string'("                "));
                 write(my_line, string'("                "));
               end if;
               write(my_line, string'("                "));
               write(my_line, string'(" rd="));
               write(my_line, ID_rd);
               writeline(output, my_line);

               write(my_line, string'("EX  stage  IR="));
               hwrite(my_line, EX_IR);
               write(my_line, string'("  EX_A ="));
               hwrite(my_line, EX_A);
               write(my_line, string'("  EX_B ="));
               hwrite(my_line, EX_B);
               write(my_line, string'("  EX_C ="));
               hwrite(my_line, EX_C);
               write(my_line, string'(" rd="));
               write(my_line, EX_rd);
               writeline(output, my_line);
               write(my_line, string'("EX  stage"));
               write(my_line, string'("             "));
               write(my_line, string'("EX_aluB="));
               hwrite(my_line, EX_aluB);
               write(my_line, string'(" EX_res="));
               hwrite(my_line, EX_result);
               writeline(output, my_line);
               write(my_line, string'("MEM stage  IR="));
               hwrite(my_line, MEM_IR);
               write(my_line, string'("  addr ="));
               hwrite(my_line, MEM_addr);
               write(my_line, string'("  data ="));
               hwrite(my_line, MEM_data);
               if MEMread='1' then
                 write(my_line, string'("  read ="));
                 hwrite(my_line, MEM_read_data);
               elsif MEMWrite='1' then
                 write(my_line, string'("  wrote="));
                 hwrite(my_line, MEM_data);
               else
                 write(my_line, string'("                "));
               end if;
               write(my_line, string'(" rd="));
               write(my_line, MEM_rd);
               writeline(output, my_line);
               write(my_line, string'("WB  stage  IR="));
               hwrite(my_line, WB_IR);
               write(my_line, string'("  read ="));
               hwrite(my_line, WB_read);
               write(my_line, string'("  pass ="));
               hwrite(my_line, WB_pass);
               write(my_line, string'(" result="));
               hwrite(my_line, WB_result);
               write(my_line, string'(" rd="));
               write(my_line, WB_rd);
               writeline(output, my_line);
               write(my_line, string'("control RegDst="));
               write(my_line, RegDst);
               write(my_line, string'("  ALUSrc="));
               write(my_line, ALUSrc);
               write(my_line, string'("  MemtoReg="));
               write(my_line, MemtoReg);
               write(my_line, string'("  MEMRead="));
               write(my_line, MEMRead);
               write(my_line, string'("  MEMWrite="));
               write(my_line, MEMWrite);
               write(my_line, string'("  WB_write_enb="));
               write(my_line, WB_write_enb);
               writeline(output, my_line);

               -- registers
               write(my_line, string'("reg 0-7 "));
               for I in 0 to 7 loop
                 hwrite(my_line, reg_mem(I));
                 write(my_line, string'(" "));            
               end loop;  -- I
               writeline(output, my_line);
               write(my_line, string'("   8-15 "));
               for I in 8 to 15 loop
                 hwrite(my_line, reg_mem(I));
                 write(my_line, string'(" "));            
               end loop;  -- I
               writeline(output, my_line);
               write(my_line, string'("  16-23 "));
               for I in 16 to 23 loop
                 hwrite(my_line, reg_mem(I));
                 write(my_line, string'(" "));            
               end loop;  -- I
               writeline(output, my_line);
                 
               -- RAM memory
               write(my_line, string'("RAM 70- "));
               for I in 28 to 35 loop  -- word at hex 70 byte address
                 hwrite(my_line, memory(I));
                 write(my_line, string'(" "));
               end loop;
               writeline(output, my_line);

               writeline(output, my_line);  -- blank line
               counter <= counter+1;
               wait for 0.5 ns;         -- rest of 10 ns clock period
             end process printout;

end architecture schematic; -- of part2b_start
