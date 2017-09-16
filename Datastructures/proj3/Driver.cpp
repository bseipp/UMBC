// File: Driver.cpp
//
// Tests file
//
#include <iostream>
#include <stdexcept>
using namespace std;

#include "LazyBST.h"

const int depthLimit = 30;

bool sanityCheck(LazyBST& T, char pos[], int depth, int& key, int& height, int& size, bool report = true) {

	int leftKey, rightKey;
	int leftHeight = -1, rightHeight = -1;
	int leftSize = 0, rightSize = 0;
	bool hasLeft, hasRight;


	// Try to catch bad BST with cycles
	//
	if (depth >= depthLimit) {
		throw out_of_range("Depth limit reached. Something looks wrong!\n");
	}


	// Is does current position have a node?
	//
	if (!T.locate(pos, key)) return false;


	// Add extra '\0' so pos string can be extended
	//
	pos[depth + 1] = '\0';


	// Recursively checks left subtree.
	//
	pos[depth] = 'L';
	hasLeft = sanityCheck(T, pos, depth + 1, leftKey, leftHeight, leftSize, report);


	// Recursively checks right subtree.
	//
	pos[depth] = 'R';
	hasRight = sanityCheck(T, pos, depth + 1, rightKey, rightHeight, rightSize, report);


	pos[depth] = '\0';  // restores pos[]


						// Compute current node's height and size
						//
	height = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
	size = 1 + leftSize + rightSize;


	// Check key ordering for left child
	//
	if (hasLeft && leftKey >= key) {
		cerr << "\nIn position " << pos
			<< " (key=" << key << ",height=" << height << ",size=" << size << ")"
			<< " left child's key not less than current node's key:"
			<< leftKey << " " << key << endl;
	}


	// Check key ordering for right child
	//
	if (hasRight && rightKey <= key) {
		cerr << "\nIn position " << pos
			<< " (key=" << key << ",height=" << height << ",size=" << size << ")"
			<< " right child's key not greater than current node's key:"
			<< rightKey << " " << key << endl;
	}


	// Check relative sizes of left and right subtrees.
	// Note: leftSize == 2* rightSize (or vice versa) is not an error
	//    because it is up to the next insert or remove to fix.
	//
	if (height > 3) {
		if (leftSize > 2 * rightSize) {
			cerr << "\nIn position " << pos
				<< " (key=" << key << ",height=" << height << ",size=" << size << ")"
				<< " left subtree too big: "
				<< leftSize << " " << rightSize << endl;
		}
		if (rightSize > 2 * leftSize) {
			cerr << "\nIn position " << pos
				<< " (key=" << key << ",height=" << height << ",size=" << size << ")"
				<< " right subtree too big: "
				<< leftSize << " " << rightSize << endl;
		}

	}


	// Give stats for current node, if so desired.
	//

	if (report) {
		cout << "\n Node report on position " << pos << " :" << endl;
		cout << "   key = " << key
			<< "   height = " << height
			<< "   size = " << size
			<< endl;

		if (hasLeft) {
			cout << "   left child key = " << leftKey << endl;
		}
		else {
			cout << "   no left child\n";
		}

		if (hasRight) {
			cout << "   right child key = " << rightKey << endl;
		}
		else {
			cout << "   no right child\n";
		}
	}

	return true;

}

int main() {

	LazyBST T;

	// add a bunch of numbers
	//
	T.insert(70);
	T.insert(30);
	T.insert(110);
	T.insert(40);
	T.insert(20);
	T.insert(41);
	T.insert(31);
	T.insert(32);
	T.insert(33);
	T.insert(19);
	T.insert(34);
	T.insert(15);
	T.insert(14);
	T.insert(38);
	T.insert(81);
	T.insert(95);
	T.insert(43);
	T.insert(17);

	T.inorder(); cout << endl;

	char pos[depthLimit];
	pos[0] = '\0';
	int key, height, size;

	// Do check
	//
	cout << "First a small test...\n";
	sanityCheck(T, pos, 0, key, height, size);
	cout << "\n\nSmall tree has root with key=" << key
		<< ", height=" << height
		<< ", size=" << size
		<< endl;

	cout << endl << endl;
	cout << "Now a big test...\n";

	LazyBST T2;

	for (int i = 1000; i<1500; i++) {
		T2.insert(i);
	}
	for (int i = 250; i<900; i++) {
		T2.insert(i);
	}
	for (int i = 3000; i>1600; i--) {
		T2.insert(i);
	}
	for (int i = 3500; i<6000; i++) {
		T2.insert(i);
	}

	sanityCheck(T2, pos, 0, key, height, size, false);
	cout << "\n\nBig tree has root with key=" << key
		<< ", height=" << height
		<< ", size=" << size
		<< endl;

	cout << endl << endl;

	LazyBST T3;

	T3.insert(70);
	T3.inorder(); cout << endl;

	T3.insert(30);
	T3.inorder(); cout << endl;

	T3.insert(110);

	T3.inorder(); cout << endl;

	cout << "\n\n***** Insert 40 *****\n";
	T3.insert(40);
	T3.inorder(); cout << endl;

	cout << "\n\n***** Insert 20 *****\n";
	T3.insert(20);
	T3.inorder(); cout << endl;

	cout << "\n\n***** Insert 41 *****\n";
	T3.insert(41);
	T3.inorder(); cout << endl;

	cout << "\n\n***** Insert 31 *****\n";
	T3.insert(31);
	T3.inorder(); cout << endl;

	cout << "\n\n***** Insert 32 *****\n";
	T3.insert(32);
	T3.inorder(); cout << endl;

	cout << "\n\n***** Insert 33 *****\n";
	T3.insert(33);
	T3.inorder(); cout << endl;

	cout << "\n\n***** Insert 19 *****\n";
	T3.insert(19);
	T3.inorder(); cout << endl;

	cout << "\n\n***** Insert 34 *****\n";
	T3.insert(34);
	T3.inorder(); cout << endl;

	cout << "\n\n***** Insert 15 *****\n";
	T3.insert(15);
	T3.inorder(); cout << endl;

	cout << "\n\n***** Insert 14 *****\n";
	T3.insert(14);
	T3.inorder(); cout << endl;

	cout << "\n\n***** Create T2, copy T *****\n";
	LazyBST T4(T3);
	cout << "\n\n***** T, &T = 0x" << &T3 << ", &root = 0x" << T3.getRoot() << " *****\n";
	T3.inorder(); cout << endl;
	cout << "\n\n***** T, &T2 = 0x" << &T4 << ", &root = 0x" << T4.getRoot() << " *****\n";
	T4.inorder(); cout << endl;

	cout << "\n\n***** Insert 99, T2 *****\n";
	T4.insert(99);
	T4.inorder(); cout << endl;

	cout << "\n\n***** Insert 22, T2 *****\n";
	T4.insert(22);
	T4.inorder(); cout << endl;

	cout << "\n\n***** Insert 7, T2 *****\n";
	T4.insert(7);
	T4.inorder(); cout << endl;

	cout << "\n\n***** T = T2 *****\n";
	T3 = T4;
	cout << "\n\n***** T, &T = 0x" << &T3 << ", &root = 0x" << T3.getRoot() << " *****\n";
	T3.inorder(); cout << endl;
	cout << "\n\n***** T, &T2 = 0x" << &T4 << ", &root = 0x" << T4.getRoot() << " *****\n";
	T4.inorder(); cout << endl;

	cout << "\n\n***** Locate LLR *****\n";
	key = 0;
	cout << "Located = " << T4.locate("LLR", key) << ", key = " << key << endl;

	cout << "\n\n***** Locate root *****\n";
	key = 0;
	cout << "Located = " << T4.locate("", key) << ", key = " << key << endl;

	cout << "\n\n***** Locate LLLLLLLLL *****\n";
	key = 0;
	cout << "Located = " << T4.locate("LLLLLLLLL", key) << endl;

	LazyBST T5;

	T5.insert(14);

	T5.insert(7);
	T5.insert(3); T5.insert(1); T5.insert(4);
	T5.insert(10); T5.insert(9); T5.insert(12);

	T5.insert(25);
	T5.insert(18); T5.insert(15); T5.insert(21);
	T5.insert(32); T5.insert(29); T5.insert(44);

	//   T5.dump() ;
	T5.inorder(); cout << endl;

	int n, answer;


	n = 3;
	cout << "Find " << n << endl;
	if (T5.find(n)) {
		cout << "found = " << n << endl;
	}
	else {
		cout << "did not find = " << n << endl;
	}
	cout << endl;


	n = 4;
	cout << "Find " << n << endl;
	if (T5.find(n)) {
		cout << "found = " << n << endl;
	}
	else {
		cout << "did not find = " << n << endl;
	}
	cout << endl;


	n = 29;
	cout << "Find " << n << endl;
	if (T5.find(n)) {
		cout << "found = " << n << endl;
	}
	else {
		cout << "did not find = " << n << endl;
	}
	cout << endl;


	n = 39;
	cout << "Find " << n << endl;
	if (T5.find(n)) {
		cout << "found = " << n << endl;
	}
	else {
		cout << "did not find = " << n << endl;
	}
	cout << endl;


	n = 301;
	cout << "Find " << n << endl;
	if (T5.find(n)) {
		cout << "found = " << n << endl;
	}
	else {
		cout << "did not find = " << n << endl;
	}
	cout << endl;


	// Checking remove...

	n = 21;
	cout << "Remove " << n << endl;
	if (T5.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T5.inorder(); cout << endl;

	n = 18;
	cout << "Remove " << n << endl;
	if (T5.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T5.inorder(); cout << endl;

	n = 7;
	cout << "Remove " << n << endl;
	if (T5.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T5.inorder(); cout << endl;

	n = 13;
	cout << "Remove " << n << endl;
	if (T5.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T5.inorder(); cout << endl;

	n = 29;
	cout << "Remove " << n << endl;
	if (T5.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T5.inorder(); cout << endl;

	n = 32;
	cout << "Remove " << n << endl;
	if (T5.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T5.inorder(); cout << endl;

	n = 14;
	cout << "Remove " << n << endl;
	if (T5.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T5.inorder(); cout << endl;

	LazyBST T6;

	T6.insert(14);

	T6.insert(7);
	T6.insert(25);

	T6.insert(3); T6.insert(32);
	T6.insert(9); T6.insert(18);

	// Inserting duplicates

	T6.insert(3); T6.insert(32);
	T6.insert(9); T6.insert(18);

	T6.insert(1); T6.insert(44);
	T6.insert(12); T6.insert(15);
	T6.insert(4); T6.insert(29);
	T6.insert(10); T6.insert(21);

	T6.inorder(); cout << endl;

	cout << "removing ..." << endl;

	n = 14; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 12; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 7; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 25; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 3; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 29; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 32; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 15; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;


	// Removing items that do not exist
	cout << endl;
	n = 19; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 101; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = -32; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	cout << endl;

	n = 18; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 21; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 10; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 9; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 1; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 44; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;
	n = 4; cout << "removing " << n << endl; T6.remove(n); T6.inorder(); cout << endl;

	return 0;

}
