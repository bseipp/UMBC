// File: LazyBST.h
//
// CMSC 341 Spring 2017
//
// Header file for LazyBST class
//

#ifndef _LAZYBST_H_
#define _LAZYBST_H_

#include <stdexcept>   // for throwing out_of_range exceptions

#include <utility>     // for pair template


class LazyBST {

	class Node;   // forward inner class declaration

public:

	// LazyBST constructor
	LazyBST();

	// LazyBST copy constructor
	LazyBST(const LazyBST& other);

	// LazyBST destructor
	~LazyBST();

	void deleteNode(Node* currentNode);

	//  deallocate memory used by the host object and then make deep copy of rhs
	const LazyBST& operator=(const LazyBST& rhs);

	// insert new value into tree bootstrap
	void insert(int key);

	void insert(const int &key, Node * &currentNode);

	bool remove(int key);

	bool remove(const int &key, Node * &currentNode);

	bool find(int key);

	bool find(const int &key, Node * currentNode);

	// Performs an inorder walk of the LazyBST and at each node, prints out the key followed by a : 
	// followed by the height of the node followed by another : 
	// followed by the size of the subtree rooted at that node.
	// Print an open parenthesis before visiting the left subtree and a close parenthesis after visiting the right subtree. 
	// Nothing should be printed when inorder() is called on an empty tree, not even parentheses
	void inorder();

	void inorder(Node * currentNode);

	void preOrderInsertion(Node * &copyNode, Node * &currentNode);


	// Returns whether there is a node in a position of the LazyBST and stores the key in the reference parameter. 
	// The position is given by a constant C string, where a character 'L' indicates left and a character 'R' indicates right. 
	// The locate() function must have the signature
	// For example:
	// A call to locate("LRL",key) should return true and store 26 in key.
	// A call to locate("RRLR",key) should return true and store 75 in key.
	// A call to locate("RLR",key) should return false and not make any changes to key since there is not a node in that position. Note: locate() must not abort and must not throw an exception in this situation.
	// A call to locate("",key) should return true and store 41 in key, since the empty string indicates the root of tree. 
	bool locate(const char *position, int& key);

	Node* getRoot();


private:
	Node * root;

	class Node {
		// let all LazyBST class have access
		friend class LazyBST;

	private:
		// construct a node 
		Node(int value = 0, Node *left = NULL, Node *right = NULL, int height = 0, int size = 1);

		int height;
		int size;

		int value;    // Holds value of the node
		Node * left;  // left Node
		Node * right;  // left Node

		void rebalance(Node * &currentNode);

		void resizeCurrentNode();

		bool checkForRebalance();

		LazyBST::Node* findMin(Node * currentNode);

		int inOrderTraversal(Node** sortedTreeArray, int index, Node * currentNode);

		LazyBST::Node* sortedArrayToBST(Node** sortedTreeArray, int size);

		LazyBST::Node* buildBST(Node** sortedTreeArray, int start, int end);
	};
};

#endif