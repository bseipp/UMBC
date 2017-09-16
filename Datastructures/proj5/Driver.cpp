// File: driver.cpp
//
// Insertions triggers incremental rehashing
// Further insertions make us give up on 
// rehashing and consolidate items into a single
// hash table.
//

#include <iostream>
#include <cstdlib>
using namespace std;

#include "HashTable.h"


int main() {
	HashTable T(107);

	T.insert("undulation");     //  9
	T.insert("impertinent");    // 10
	T.insert("maladies");       // 10 -> 11
	T.insert("dominions");	// 12

	T.insert("waspish");        // 52
	T.insert("wildebeest");     // 52 -> 53
	T.insert("reaction");       // 52 -> 54

	T.insert("pawns");          // 43
	T.insert("vacuously");      // 43 -> 44
	T.insert("firth");          // 43 -> 45
	T.insert("manipulator");    // 43 -> 46
	T.insert("dreariness");     // 43 -> 47

	T.insert("insanity");       // 105
	T.insert("enthronement");   // 105 -> 106
	T.insert("falsifiers");     // 105 -> 0
	T.insert("ignominious");    // 105 -> 1
	T.insert("mummified");      // 105 -> 2

	T.insert("tributes");	// 21
	T.insert("skulduggery");	// 22
	T.insert("convulse");	// 23
	T.insert("frothed");	// 24
	T.insert("horrify");	// 25
	T.insert("blackmailers");	// 26
	T.insert("defenestrated");	// 27
	T.insert("garrison");	// 23 -> 28
	T.insert("lidless");	// 22 -> 29
	T.insert("eye");            // 21 -> 30, should trigger inc. rehash


	cout << "----------------------------------------------------\n";
	cout << "Hash table after rehash triggered\n";
	cout << "----------------------------------------------------\n";
	T.dump();
	cout << "----------------------------------------------------\n";

	cout << "\n\nDo some insertions to make long linear probe sequence in the second table.\n\n";

	T.insert("wildcat");        // 18 (new table)
	T.insert("weightlessness"); // 69 (new table)
	T.insert("sorceress");      // 33 (new table)
	T.insert("enchantress");    // 33 (new table) really.
	T.insert("witchery");       // 67 -> 68 (new table)
	T.insert("heliosphere");    // 67 -> 72 (new table)
	T.insert("obstruct");       // 67 -> 73 (new table)

	cout << "----------------------------------------------------\n";
	cout << "Hash table insertions.\n";
	cout << "----------------------------------------------------\n";
	T.dump();
	cout << "----------------------------------------------------\n";

	cout << "\n\nOne more insertion in slot 67 should make us give up on rehashing.\n\n";
	T.insert("peripatetic");    // 67 -> 77 (new table)

	cout << "----------------------------------------------------\n";
	cout << "Hash table giving up on rehashing.\n";
	cout << "----------------------------------------------------\n";
	T.dump();
	cout << "----------------------------------------------------\n";

	HashTable S(T);
	cout << "----------------------------------------------------\n";
	cout << "Hash table S\n";
	cout << "----------------------------------------------------\n";
	S.dump();
	cout << "------------------------S---------------------------\n";


	HashTable H(107);
	H = S;
	cout << "----------------------------------------------------\n";
	cout << "Hash table H\n";
	cout << "----------------------------------------------------\n";
	H.dump();
	cout << "------------------------H---------------------------\n";

	T.insert("undulation");     //  9
	T.insert("impertinent");    // 10
	T.insert("maladies");       // 10 -> 11
	T.insert("dominions");	// 12

	T.insert("waspish");        // 52
	T.insert("wildebeest");     // 52 -> 53
	T.insert("reaction");       // 52 -> 54

	T.insert("pawns");          // 43
	T.insert("vacuously");      // 43 -> 44
	T.insert("firth");          // 43 -> 45
	T.insert("manipulator");    // 43 -> 46
	T.insert("dreariness");     // 43 -> 47

	T.insert("insanity");       // 105
	T.insert("enthronement");   // 105 -> 106
	T.insert("falsifiers");     // 105 -> 0
	T.insert("ignominious");    // 105 -> 1
	T.insert("mummified");      // 105 -> 2

	T.insert("tributes");	// 21
	T.insert("skulduggery");	// 22
	T.insert("convulse");	// 23
	T.insert("frothed");	// 24
	T.insert("horrify");	// 25
	T.insert("blackmailers");	// 26
	T.insert("defenestrated");	// 27
	T.insert("garrison");	// 23 -> 28
	T.insert("lidless");	// 22 -> 29

	cout << "----------------------------------------------------\n";
	cout << "Original hash table\n";
	cout << "----------------------------------------------------\n";
	T.dump();
	cout << "----------------------------------------------------\n";

	cout << "\n\nInserting \"eye\" should trigger rehash\n\n";
	T.insert("eye");            // 21 -> 30, should trigger inc. rehash


	cout << "----------------------------------------------------\n";
	cout << "Hash table after rehash triggered\n";
	cout << "----------------------------------------------------\n";
	T.dump();
	cout << "----------------------------------------------------\n";

	cout << "\n\nSearch for \"manipulator\" should move cluster in slots 43-47.\n\n";
	T.find("manipulator");            // 21 -> 30, should trigger inc. rehash

	cout << "----------------------------------------------------\n";
	cout << "Hash table after cluster 43-47 moved.\n";
	cout << "----------------------------------------------------\n";
	T.dump();
	cout << "----------------------------------------------------\n";

	cout << "\n\nDo some finds, inserts and removes\n\n";

	const char *str;
	char *ptr;

	if (T.find(str = "zip")) {
		cout << "Found " << str << endl;
	}
	else {
		cout << "Did not find " << str << endl;
	}

	if (T.find(str = "spaceflight")) {
		cout << "Found " << str << endl;
	}
	else {
		cout << "Did not find " << str << endl;
	}

	if (T.find(str = "frothed")) {
		cout << "Found " << str << endl;
	}
	else {
		cout << "Did not find " << str << endl;
	}

	T.insert("wildcat");        // 18 (new table)
	T.insert("weightlessness"); // 69 (new table)
	T.insert("sorceress");      // 33 (new table)
	T.insert("enchantress");    // 33 (new table) really.


	cout << "----------------------------------------------------\n";
	cout << "Hash table after more insertions.\n";
	cout << "----------------------------------------------------\n";
	T.dump();
	cout << "----------------------------------------------------\n";

	cout << "\n\nA find on \"ignominious\" + 1 more operation should cause the tables to consolidate down to one table. \n\n";

	if (T.find(str = "ignominious")) {
		cout << "Found " << str << endl;
	}
	else {
		cout << "Did not find " << str << endl;
	}

	if (T.find(str = "reaction")) {
		cout << "Found " << str << endl;
	}
	else {
		cout << "Did not find " << str << endl;
	}


	cout << "----------------------------------------------------\n";
	cout << "Hash table after wrap up.\n";
	cout << "----------------------------------------------------\n";
	T.dump();
	cout << "----------------------------------------------------\n";

	T.remove("insanity");       // 105
	T.remove("enthronement");   // 105 -> 106
	T.remove("falsifiers");     // 105 -> 0
	T.remove("ignominious");    // 105 -> 1
	T.remove("mummified");      // 105 -> 2

	T.remove("tributes");	// 21
	T.remove("skulduggery");	// 22
	T.remove("convulse");	// 23
	T.remove("frothed");	// 24
	T.remove("horrify");	// 25
	T.remove("blackmailers");	// 26
	T.remove("defenestrated");	// 27
	T.remove("garrison");	// 23 -> 28
	T.remove("lidless");	// 22 -> 29

	cout << "----------------------------------------------------\n";
	cout << "Hash table after removes.\n";
	cout << "----------------------------------------------------\n";
	T.dump();
	cout << "----------------------------------------------------\n";

	return 0;
}
