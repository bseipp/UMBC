#include <vector>
#include <iostream>

using namespace std;

class StackEmpty
{
private:
  string SEM_Exception;

public: 
  StackEmpty(string str)
  {
    SEM_Exception = str;
  }

  string GetMessage()
  {
    return SEM_Exception;
  }
};

class StackFull
{
private:
  string SFM_Exception;
  int SFM_ExceptionValue;

public:
  StackFull(string str, int i)
  {
    SFM_ExceptionValue = i;
    SFM_Exception = str;
  }
  
  string GetMessage()
  {
    return SFM_Exception;
  }

  int GetValue()
  {
    return SFM_ExceptionValue;
  }
};



class InvalidSize
{
private: 
  string ISM_Exception;

public:
  InvalidSize(string str)
  {
    ISM_Exception = str;
  }

  string GetMessage()
  {
    return ISM_Exception;
  }
};

class IntStack
{
public:
  // MaxSize should be an unsigned int, but for the sake of example...
  IntStack(int MaxSize)
  {
    if(MaxSize < 0)
      {
	throw InvalidSize("Cannot create a negative size stack");
      }
		
    data.resize(MaxSize);
    cur_index = 0;
  }

  void push(int new_data)
  {
    if(cur_index == data.size())
      {
	throw StackFull("Push to full stack", new_data);
      }
    else
      {
	data.at(cur_index) = new_data;
	cur_index++;
      }
  }

  int pop()
  {
    if(cur_index == 0)
      {
	throw StackEmpty("Pop from empty stack");
      }
    else
      {
	// pop off the int and return it
	cur_index--;
	return data.at(cur_index);
      }
  }

private:
  vector<int> data;
  unsigned int cur_index;
};

int main()
{
  try {
    // Testing Constructor
    IntStack c_test(-10);
    
    c_test.push(3);
    c_test.push(4);
    c_test.pop();
    c_test.pop();
    
  }
  catch (InvalidSize &e){
    cerr << e.GetMessage() << endl;
  }

  try {
    // Testing push
    IntStack push_test(5);
    
    for(unsigned int i = 0; i < 7; i++) {
    push_test.push(i);
    }
  }
  catch (StackFull &e) {
    cerr << e.GetMessage() << endl;
  }

  try {    
    // Testing pop
    IntStack pop_test(2);
    
    pop_test.push(1);
    pop_test.push(2);
    pop_test.pop();
    pop_test.pop();
    pop_test.pop();
  }
  catch (StackEmpty &e) {
    cerr << e.GetMessage() << endl;
  }

    cout << "Completed!" << endl;
}
