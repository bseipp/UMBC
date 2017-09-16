#include "Graph.h"
#include <iostream>

Graph::Graph(int n)
{
	this->m_size = n;
	this->m_adjLists = new AdjListNode*[this->m_size];

       	for (int i = 0; i < this->m_size; i++)
	  	this->m_adjLists[i] = NULL;
}

Graph::Graph(const Graph& G)
{
	this->m_size = G.m_size;
	this->m_adjLists = new AdjListNode*[this->m_size];

	for (int i = 0; i < this->m_size; i++) {
		this->m_adjLists[i] = NULL;

		AdjListNode* temp = G.m_adjLists[i];
		while (temp != NULL) {
			AdjListNode* nNode = new AdjListNode(temp->m_vertex, NULL);
			nNode->next = this->m_adjLists[i];
			this->m_adjLists[i] = nNode;
			temp = temp->next;
		}
	}
}

Graph::~Graph()
{
	AdjListNode** tempNodePtr = this->m_adjLists;
	this->m_adjLists = NULL;
	
	for (int i = 0; i < this->m_size; i++) {
		while (tempNodePtr[i] != NULL) {
			AdjListNode* temp = tempNodePtr[i];
			tempNodePtr[i] = tempNodePtr[i]->next;
			delete temp;
		}
	}
	if (tempNodePtr[0] != NULL) {
		delete[] tempNodePtr;
	}
}

const Graph& Graph::operator= (const Graph& rhs)
{
	//delete old graph data
	this->~Graph();
	
	this->m_size = rhs.m_size;
	this->m_adjLists = new AdjListNode*[this->m_size];

	//assign each edge from the rhs to the lhs
	for (int i = 0; i < this->m_size; i++) {
		this->m_adjLists[i] = NULL;

		AdjListNode* temp = rhs.m_adjLists[i];
		while (temp != NULL) {
			AdjListNode* nNode = new AdjListNode(temp->m_vertex, NULL);
			nNode->next = this->m_adjLists[i];
			this->m_adjLists[i] = nNode;
			temp = temp->next;
		}
	}

	return *this;
}


int Graph::size()
{
	return this->m_size;
}

void Graph::addEdge(int u, int v)
{
	try
	{
		//Check if either vertex is not on the graph
		if (u >= this->m_size || v >= this->m_size)
			throw std::out_of_range("Edge verticies out of range.");

		//create and add a node of value v to index u
		AdjListNode* uNode = new AdjListNode(v, NULL);

		if (this->m_adjLists[u] == NULL) {
			this->m_adjLists[u] = uNode;
		}
		else {
			uNode->next = this->m_adjLists[u];
			this->m_adjLists[u] = uNode;
		} 

		//create and add a node of value u to index v
		AdjListNode* vNode = new AdjListNode(u, NULL);

		if (this->m_adjLists[v] == NULL) {
			this->m_adjLists[v] = vNode;
		}
		else {
			vNode->next = this->m_adjLists[v];
			this->m_adjLists[v] = vNode;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Graph::dump()
{
	std::cout << "Dump out graph(size = " << this->m_size << ") :" << std::endl;
	//hit each vertex
	for (int i = 0; i < this->m_size; i++) {
		std::cout << " [ " << i << " ] : ";

		AdjListNode* temp = this->m_adjLists[i];
		//rotate through each edge and print it
		while (temp != NULL) {
			std::cout << temp->m_vertex;
			std::cout << " --> ";
			temp = temp->next;
		}

		//stick null at the end of the dump for each vertex
		std::cout << "NULL" << std::endl;
	}
}


Graph::EgIterator::EgIterator(Graph *Gptr, bool isEnd)
{
	this->m_Gptr = Gptr;

	//check if there is no graph associated
	if (this->m_Gptr == NULL) {
		this->m_where = NULL;
		this->m_source = 0;
	}
	//check if this is the end iterator, if not...
	else if (isEnd == false) {
	  this->m_source = 0;
	  //move to the first node in the list
	  while (this->m_Gptr->m_adjLists[this->m_source] == NULL){
	    this->m_source++;
	  }
	  this->m_where = this->m_Gptr->m_adjLists[this->m_source];
	}
	//otherwise create end iterator
	else {
		this->m_where = NULL;
		//set source to the size of the graph, since that is not a real vertex
		this->m_source = m_Gptr->m_size;
	}
}

bool Graph::EgIterator::operator!= (const EgIterator& rhs)
{
	//if this source is the same as the rhs source, we know they are equal to each other if the gptrs match
	if (this->m_source == rhs.m_source && this->m_Gptr == rhs.m_Gptr)
		return false;
	return true;
}

void Graph::EgIterator::operator++(int dummy)
{
	bool stillLookingForNode = true;

	//keep moving along verticies until you hit a valid node or the nodes are exhausted
	while (this->m_source < this->m_Gptr->m_size && stillLookingForNode) {
		this->m_where = this->m_where->next;

		//advance along nodes until you hit null or a valid node
		if (this->m_where == NULL) {
			this->m_source++;
			if (this->m_source < this->m_Gptr->m_size)
				this->m_where = this->m_Gptr->m_adjLists[this->m_source];
		}

		if (this->m_where != NULL && this->m_source < this->m_where->m_vertex)
			stillLookingForNode = false;
	}
}

std::pair<int, int> Graph::EgIterator::operator*()
{
	try
	{
		//verify we are able to dereference
		if (this->m_source >= this->m_Gptr->m_size)
			throw std::out_of_range("m_source >= m_Gptr->m_size");
		else if (this->m_where == NULL)
			throw std::out_of_range("m_where == NULL");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return std::pair<int, int>(this->m_source, this->m_where->m_vertex);
}


Graph::EgIterator Graph::egBegin()
{
	EgIterator eBegin = EgIterator(this, false);

	return eBegin;
}

Graph::EgIterator Graph::egEnd()
{
	EgIterator eEnd = EgIterator(this, true);

	return eEnd;
}


Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd)
{
	this->m_Gptr = Gptr;
	this->m_source = v;

	//if this isn't the end iterator
	if (isEnd == false && this->m_Gptr != NULL)
		this->m_where = this->m_Gptr->m_adjLists[this->m_source];
	else
		this->m_where = NULL;
}

bool Graph::NbIterator::operator!= (const NbIterator& rhs)
{
	if (this->m_where == rhs.m_where)
		return false;
	return true;
}

void Graph::NbIterator::operator++(int dummy)
{
	try {
		//Make sure we aren't on a NULL position
		if (this->m_where == NULL)
			throw std::out_of_range("Unable to advance NbIterator, m_where is NULL");

		//move to next node
		this->m_where = this->m_where->next;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}	
}

int Graph::NbIterator::operator*()
{
	try {
		//if we are not on a null ptr, return the vertex
		if (this->m_where == NULL)
			throw std::out_of_range("Unable to dereference NbIterator, m_where is NULL");

		return this->m_where->m_vertex;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}


Graph::NbIterator Graph::nbBegin(int v)
{
	try {
		//if a valid vertex is provided, return the new iterator set to that vertex
		if (v >= this->m_size)
			throw std::out_of_range("Cannot create NbIterator->begin at that vertex, it is not on the graph");

		NbIterator nBegin = NbIterator(this, v, false);

		return nBegin;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

Graph::NbIterator Graph::nbEnd(int v)
{

	try {
		//if a valid vertex is provided, return the new iterator set to that vertex
		if (v >= this->m_size)
			throw std::out_of_range("Cannot create NbIterator->end at that vertex, it is not on the graph");

		NbIterator nEnd = NbIterator(this, v, true);

		return nEnd;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}


Graph::AdjListNode::AdjListNode(int v, AdjListNode *ptr)
{
	this->m_vertex = v;
	this->next = ptr;
}

