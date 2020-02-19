// CMSC 341 - Spring 2020 - Project 1
//
// File: test2.cpp
//
// A simple driver excercising the copy constructor and assignment
// operator.

#include <iostream>

// need this for tuple template
//
#include <tuple>
using namespace std;

#include "Graph.h"

int main() {

   Graph* Gptr = new Graph(5) ;

   // add some edges
   Gptr->addEdge(3, 4, 1);
   Gptr->addEdge(1, 4, 1);
   Gptr->addEdge(0, 3, 1);
   Gptr->addEdge(0, 4, 1);
   Gptr->addEdge(0, 1, 1);
   Gptr->addEdge(1, 2, 1);
   Gptr->addEdge(2, 4, 1);

   // Dump the graph
   cout << "\nInitial graph (G1):\n";
   Gptr->dump() ;

   // Make a copy using copy constructor
   Graph* Gptr2 = new Graph(*Gptr) ;
   cout << "\nCopy G2 = Graph(G1):\n" ;
   Gptr2->dump() ;

   // Get rid off original graph; check if new (copy) graph is still
   // correct.
   delete Gptr ;
   cout << "\nCopy (G2) after deleting original (G1):\n" ;
   Gptr2->dump() ;

   // Make another graph and dump it
   Graph G3(3) ;
   G3.addEdge(0, 1, 1);
   G3.addEdge(0, 2, 1);
   G3.addEdge(1, 2, 1);
   cout << "\nNew graph (G3):\n";
   G3.dump() ;

   // Assign G2 to G3 and dump G3
   G3 = *Gptr2 ;
   cout << "\nAssign G3 = G2:\n";
   G3.dump() ;

   delete Gptr2 ;
}
