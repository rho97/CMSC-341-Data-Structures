// CMSC 341 - Spring 2020 - Project 1
//
// File: driver1.cpp
//
// A simple driver for the Graph class

#include <iostream>
#include <tuple>
#include "Graph.h"

using namespace std;

int main() {

   // G has 5 vertices numbered 0 thru 4
   Graph G(5) ;

   // add some edges
   G.addEdge(3,4,11);
   G.addEdge(1,4,12);
   G.addEdge(0,3,13);
   G.addEdge(0,4,14);
   G.addEdge(0,1,15);
   G.addEdge(1,2,16);
   G.addEdge(2,4,17);

   // dump the graph
   G.dump();

   // Use the neighbor iterator.  Loop over all the vertices; print
   // each vertex's neighbors.
    
   Graph::NbIterator nit ;
   
   for (int i = 0; i < G.numVert(); i++) {
     cout << "\nThe neighbors of vertex " << i << " are:\n"; 
     for (nit = G.nbBegin(i); nit != G.nbEnd(i) ; nit++) {
       cout << "(" << (*nit).first << ", " << (*nit).second << ")" << " " ;
     }
     cout << endl ;
   }
   
   // Use the edge iterator.  Iterate over all edges and print them.
   
   Graph::EgIterator eit ;
   std::tuple<int,int,int> edge ;

   cout << "\nnumVert = " << G.numVert() << ", numEdge = " << G.numEdge() << endl;
   cout << "The edges in the graph are:\n" ;
   
   eit = G.egEnd();
      
   for (eit = G.egBegin() ; eit != G.egEnd() ; eit++) {

     edge = *eit ;   // get current edge
     // the two data members of a pair are first and second
     //
     cout << "(" << get<0>(edge) << ", "
   	  << get<1>(edge) << ", "
   	  << get<2>(edge) << ") " ;

   }
   cout << endl ;
   

   // Remove some edges and then print all the edges again

   cout << "\nRemove edges (3,4), (0,4), and (1,2)...\n";
   G.removeEdge(3,4);
   G.removeEdge(0,4);
   G.removeEdge(1,2);

   cout << "\nnumVert = " << G.numVert() << ", numEdge = " << G.numEdge() << endl;
   cout << "The edges in the graph are:\n" ;
   for (eit = G.egBegin() ; eit != G.egEnd() ; eit++) {
     edge = *eit ;   // get current edge

     // the two data members of a pair are first and second
     //
     cout << "(" << get<0>(edge) << ", "
   	  << get<1>(edge) << ", "
   	  << get<2>(edge) << ") " ;

   }
   cout << endl ;

   
   return 0;
}
