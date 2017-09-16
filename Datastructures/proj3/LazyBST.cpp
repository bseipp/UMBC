#include "LazyBST.h"
#include <iostream>

using std::cout;
using std::endl;

LazyBST::LazyBST()
{
	this->root = NULL;
}

LazyBST::LazyBST(const LazyBST& other)
{
	Node * copyNode = other.root;
	this->preOrderInsertion(copyNode, this->root);
}

void LazyBST::preOrderInsertion(Node * &copyNode, Node * &currentNode) {
	if (copyNode == NULL)
		currentNode = NULL;
	else {
		currentNode = new Node(copyNode->value);
		this->preOrderInsertion(copyNode->left, currentNode->left);
		this->preOrderInsertion(copyNode->right, currentNode->right);
		currentNode->resizeCurrentNode();
	}
}

void LazyBST::deleteNode(Node* currentNode)
{
	if (currentNode->left != NULL)
		this->deleteNode(currentNode->left);

	if (currentNode->right != NULL)
		this->deleteNode(currentNode->right);

	currentNode->left = NULL;
	currentNode->right = NULL;
	currentNode->value = 0;
	currentNode->height = 0;
	currentNode->size = 0;

	delete currentNode;
}

LazyBST::~LazyBST()
{
	if (this->root != NULL)
		this->deleteNode(this->root);
}

const LazyBST& LazyBST::operator= (const LazyBST& rhs)
{
	if (this->root != NULL)
		this->deleteNode(this->root);
	
	Node * copyNode = rhs.root;
	this->preOrderInsertion(copyNode, this->root);

	return *this;
}

bool LazyBST::remove(int key) {
	return this->remove(key, this->root);
}

bool LazyBST::remove(const int &key, Node * &currentNode) {
	bool result;

	if (currentNode == NULL)
		return false;

	// Check if this tree needs to be rebalanced
	if (currentNode->checkForRebalance()) {
		currentNode->rebalance(currentNode);
	}

	if (currentNode->value > key)
		result = this->remove(key, currentNode->left);
	else if (currentNode->value < key)
		result = this->remove(key, currentNode->right);
	else if (currentNode->left != NULL && currentNode->right != NULL) {
		currentNode->value = currentNode->findMin(currentNode->right)->value;
		result = this->remove(currentNode->value, currentNode->right);
	}
	else {
		Node * temp = currentNode;
		currentNode = currentNode->left != NULL ? currentNode->left : currentNode->right;
		result = true;
		delete temp;
	}

	if (currentNode != NULL) 
		currentNode->resizeCurrentNode();

	return result;
}

LazyBST::Node* LazyBST::Node::findMin(Node * currentNode) {
	while (currentNode->left != NULL) {
		currentNode = currentNode->left;
	}
	return currentNode;
}

void LazyBST::insert(int key)
{
	this->insert(key, this->root);
}

void LazyBST::insert(const int &key, Node * &currentNode) {
	//check if new tree
	if (currentNode == NULL) {
		// If there are no nodes on the tree, add this to the tree
		this->root = new Node(key);
		return;
	}

	// Check if this tree needs to be rebalanced
	if (currentNode->checkForRebalance()) {
		currentNode->rebalance(currentNode);
	}

	//move to correct area of tree, either left right or do nothing
	if (currentNode->value > key)
	{
		if (currentNode->left != NULL) {
			insert(key, currentNode->left);
		}
		else {
			currentNode->left = new Node(key);
		}
	}
	else if (currentNode->value < key)
	{
		if (currentNode->right != NULL) {
			insert(key, currentNode->right);
		}
		else {
			currentNode->right = new Node(key);
		}
	}
	currentNode->resizeCurrentNode();
}

void LazyBST::inorder() {
	inorder(this->root);
}

void LazyBST::inorder(Node * currentNode) {
	if (currentNode == NULL)
		return;

	cout << "(";
	if (currentNode->left != NULL) {
		inorder(currentNode->left);
	}
	cout << currentNode->value << ":" << currentNode->height << ":" << currentNode->size;
	if (currentNode->right != NULL) {
		inorder(currentNode->right);
	}
	cout << ")";
}

void LazyBST::Node::resizeCurrentNode() {
	int leftHeight = 0;
	int rightHeight = 0;
	int leftSize = 0;
	int rightSize = 0;
	int heightIncrement = 0;

	// Set left subtree height
	if (this->left != NULL) {
		leftHeight = this->left->height;
		leftSize = this->left->size;
	}

	if (this->right != NULL) {
		rightHeight = this->right->height;
		rightSize = this->right->size;
	}

	// Check if this is a leaf node
	if (this->left != NULL || this->right != NULL) {
		heightIncrement = 1;
	}

	// Resize height of currentNode
	if (leftHeight > rightHeight) {
		this->height = leftHeight + heightIncrement;
	}
	else {
		this->height = rightHeight + heightIncrement;
	}
	// Add a node to the size of the tree
	this->size = leftSize + rightSize + 1;
}

void LazyBST::Node::rebalance(Node * &currentNode) {
	Node** sortedTreeArray = new Node*[this->size];
	this->inOrderTraversal(sortedTreeArray, 0, this);
	currentNode = this->sortedArrayToBST(sortedTreeArray, this->size);
	delete[] sortedTreeArray;
}

LazyBST::Node* LazyBST::Node::sortedArrayToBST(Node** sortedTreeArray, int size) {
	if (sortedTreeArray == NULL)
		return NULL;

	return buildBST(sortedTreeArray, 0, size - 1);
}

LazyBST::Node* LazyBST::Node::buildBST(Node** sortedTreeArray, int start, int end) {
	if (start > end) {
		return NULL;
	}

	int mid = (end - start) % 2 != 0 ? start + (end - start) / 2 + 1 : start + (end - start) / 2;
	Node* root = sortedTreeArray[mid];

	root->left = buildBST(sortedTreeArray, start, mid - 1);
	root->right = buildBST(sortedTreeArray, mid + 1, end);

	root->resizeCurrentNode();

	return root;
}

int LazyBST::Node::inOrderTraversal(Node** sortedTreeArray, int index, Node * currentNode) {
	if (currentNode->left != NULL) {
		index = this->inOrderTraversal(sortedTreeArray, index, currentNode->left);
	}

	sortedTreeArray[index] = currentNode;

	if (currentNode->right != NULL) {
		index++;
		index = this->inOrderTraversal(sortedTreeArray, index, currentNode->right);
		return index;
	}

	return index + 1;
}

bool LazyBST::find(int key) {
	return this->find(key, this->root);
}

bool LazyBST::find(const int &key, Node * currentNode) {
	if (currentNode == NULL)
		return false;
	else if (currentNode->value > key)
		return this->find(key, currentNode->left);
	else if (currentNode->value < key)
		return this->find(key, currentNode->right);
	else
		return true;
}

bool LazyBST::locate(const char *position, int& key) {
	bool found = false;
	Node * currentNode = this->root;
	int letter = 0;

	while (found == false && currentNode != NULL) {
		if (position[letter] == 'L')
			currentNode = currentNode->left;
		else if (position[letter] == 'R')
			currentNode = currentNode->right;
		else if (position[letter] == NULL) {
			key = currentNode->value;
			found = true;
		}
		letter++;
	}
	return found;
}

LazyBST::Node* LazyBST::getRoot() {
	return this->root;
}

bool LazyBST::Node::checkForRebalance() {
	if (this == NULL) {
		return false;
	}

	int leftSize = 0;
	int rightSize = 0;

	// Set left subtree height
	if (this->left != NULL)
		leftSize = this->left->size;

	if (this->right != NULL)
		rightSize = this->right->size;

	//otherwise check if this tree needs to be rebalanced
	if (this->height > 3) {
		if (leftSize >= (2 * rightSize) || rightSize >= (2 * leftSize)) {
			// If height of current tree is greater than 3, and the left or right height 
			// is twice the size of the sibling tree, rebalance the tree 
			return true;
		}
	}
	return false;
}

LazyBST::Node::Node(int value, Node *left, Node *right, int height, int size) {
	this->value = value;
	this->left = left;
	this->right = right;
	this->height = height;
	this->size = size;
}

