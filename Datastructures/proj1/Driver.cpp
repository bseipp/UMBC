// File: Driver.cpp
//
// CMSC 341 Spring 2017
// Project 1 
//
// Driver Program which tests my code
//

#include <iostream>
#include <utility>
using namespace std;

#include "Graph.h"

int main() {
	//create a new Graph
	Graph* Gptr = new Graph(5);

	// add some edges
	Gptr->addEdge(1, 2);
	Gptr->addEdge(2, 3);
	Gptr->addEdge(0, 1);
	Gptr->addEdge(2, 4);

	cout << "Test 1: Added Four edges, 0: 1 Edge, 1: 2 Edges, 2: 2 Edges, 3: 1 Edge, 4: 1 Edges" << endl;
	// dump out data structure
	Gptr->dump();
	
	//add edges where the large index is first
	Gptr->addEdge(4, 1);
	Gptr->addEdge(2, 0);
	Gptr->addEdge(4, 3);

	cout << "Test 2: Added Three edges, 0: 2 Edge, 1: 3 Edges, 2: 3 Edges, 3: 2 Edge, 4: 3 Edges" << endl;
	// dump out data structure
	Gptr->dump();

	// make a copy using copy constructor
	Graph* Gptr2 = new Graph(*Gptr);
	cout << "Test 3: Copy Graph 1 using copy constructor, should match exactly" << endl;
	Gptr2->dump();

	// get rid off original graph
	// check if new graph is still there
	delete Gptr;
	cout << "Test 4: Delete Graph 1 and dump graph 2, should still exist" << endl;
	Gptr2->dump();

	cout << "Make several different graphs, and dump them to be sure dump works for all Graph types" << endl;
	// Graph with no nodes
	Graph G3(0);
	cout << "Test 6: Dump a graph with no verticies" << endl;
	G3.dump();

	// Graph with 1 nodes
	Graph G4(2);
	G4.addEdge(1, 0);

	cout << "Test 7: Dump graph that attempted to have bad vertex added, Should have 0: 1 edge, 1: 1 edge" << endl;
	G4.dump();

	//Iterator testing
	//Test nBIterator
	Graph::NbIterator nit;

	cout << "NBIterator tests" << endl << "Test 8: Test NB iterator for Graph 2" << endl;
	for (nit = Gptr2->nbBegin(4); nit != Gptr2->nbEnd(4); nit++) {
		cout << *nit << " ";
	}
	cout << endl;

	Graph G5(6);
	G5.addEdge(5, 4);

	cout << "Test 9: Test NB iterator for Graph 5, iterate over a null edge" << endl;
	for (nit = G5.nbBegin(0); nit != G5.nbEnd(0); nit++) {
		cout << *nit << " ";
	}
	cout << endl;
	

	//Test eBIterator
	Graph::EgIterator eit;
	pair<int, int> edge;

	cout << "Test 10: Test GB iterator for Graph 5, iterate over a graph with one edge at the end" << endl;
	for (eit = G5.egBegin(); eit != G5.egEnd(); eit++) {

		edge = *eit;   // get current edge

					   // the two data members of a pair are first and second
					   //
		cout << "(" << edge.first << ", " << edge.second << ") ";

	}
	cout << endl;

	cout << "Test 11: Test GB iterator for Graph 4, iterate over a graph with one edge at the begining" << endl;
	for (eit = G4.egBegin(); eit != G4.egEnd(); eit++) {

		edge = *eit;   // get current edge

					   // the two data members of a pair are first and second
					   //
		cout << "(" << edge.first << ", " << edge.second << ") ";

	}
	cout << endl;

	cout << "Test 12: Test GB iterator for Graph 2, iterate over a graph with many edges" << endl;
	for (eit = Gptr2->egBegin(); eit != Gptr2->egEnd(); eit++) {

		edge = *eit;   // get current edge

					   // the two data members of a pair are first and second
					   //
		cout << "(" << edge.first << ", " << edge.second << ") ";

	}
	cout << endl;

	delete Gptr2;

	int y = 0;
}
