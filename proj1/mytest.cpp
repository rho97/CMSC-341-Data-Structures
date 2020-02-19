//Paul Roh
//groh1@umbc.edu

// CMSC 341 - Spring 2020 - Project 1
// mytest.cpp: a test to see that the program functions as needed.

// Assignment:
// Basic tests of insert(), update(), remove(), and getEntry:
// Tests of the copy constructor and assignment operator:
// All functions that return a bool status return the correct value.
// at(int indx) throws range_error if indx is not a valid index.
// Expansion functions correctly. For example, insert 10 entries; check capacity;
//    insert another entry; capacity should double.
// Contraction functions correctly. For example, insert 11 entries;
//    check capacity; remove seven entries (so size falls to four); check capacity.
// Iterator-based for loop lists entries in array order and terminates correctly.
// Iterator-based for loop functions correctly for an empty EntryList.
// *begin() returns first element of non-empty EntryList; begin() != end()
//    unless the EntryList is empty.
// Test for memory leaks and errors using Valgrind.
// Graph::Basic tests of constructor, addEdge(), and removeEdge():
// Graph::Tests of the copy constructor and assignment operator:
// Graph::Tests of the edge iterator:
// Graph::Tests of the neighbor iterator:

#include <iostream>
#include <tuple>

using namespace std;
using std::range_error;
using std::invalid_argument;

#include "Graph.cpp"
#include "EntryList.cpp"

int main() {

  // Test for memory leaks and errors using Valgrind.
  // All functions that return a bool status return the correct value.
  cout << "Basic tests of insert(), update(), remove(), and getEntry: \n"
       << "******************************************************************\n\n";
  
  EntryList el;
  EntryList::Entry e;
  bool funcRet;
  
  //insert()
  cout << "insert (1,1) \n";
  funcRet = el.insert(EntryList::Entry(1, 1));
  cout << "insert (2,2) \n";
  el.insert(EntryList::Entry(2, 2));
  cout << "insert (3,3) \n";
  el.insert(EntryList::Entry(3, 3));

  //insert true test
  if (funcRet) { cout << "Insert = true\n"; }
  
  cout << "insert test\n";
  el.dump();

  //update()
  funcRet = el.update(EntryList::Entry(1, 4));

  //update true test
  if (funcRet) { cout << "Update = true\n"; }

  cout << "update test (1,4)\n";
  el.dump();

  //getEntry()
  funcRet = el.getEntry(1, e);
  if (funcRet) { cout << "getEntry = true\n"; }
  
  cout << "getEntry test (1, entry)\n";
  cout << e << endl;
  
  //remove()
  funcRet = el.remove(1, e);
  if (funcRet) { cout << "Remove = true\n"; }
  cout << "remove test (1, entry)\n";
  el.dump();

  cout << "removed entry: ";
  cout << e << endl;

  //order/duplicate
  cout << "order/duplicate test\n";
  cout << "pre: \n";

  el.dump();

  cout << "\ninserting/removing:\n";

  cout << "insert (3,3) \n";
  el.insert(EntryList::Entry(3, 3));
  cout << "insert (0,4) \n";
  el.insert(EntryList::Entry(0, 4));
  cout << "insert (5,2) \n";
  el.insert(EntryList::Entry(5, 2));

  cout << "\npost: \n";

  cout << "remove (3) \n";
  el.remove(3, e);
  cout << "remove (5) \n";
  el.remove(5, e);

  el.dump();
  
  cout << "Tests of the copy constructor and assignment operator: \n"
       << "******************************************************************\n\n";

  EntryList copyList;
  EntryList assignList;
  EntryList emptyList;

  //empty value
  cout << "guard against empty copy/assigment (should show nothing): \n";
  copyList = EntryList(emptyList);
  assignList = emptyList;

  //Will function when source is empty
  copyList.dump();
  assignList.dump();
  
  //protects against self assign
  cout << "\nguard against self assigment (should not error out): \n";
  assignList = assignList;

  //copy/assign
  cout << "\nuse copy and assignment\n";
  assignList = el;
  copyList = EntryList(el);

  cout << "copy dump of first entrylist: \n";
  copyList.dump();

  cout << "assign dump: \n";
  assignList.dump();

  //deep copy check.
  cout << "\ndeep copy check. remove(0, e) and insert(1, 2) into original:\n";
  cout << "copy dump: \n";
  copyList.dump();

  cout << "assign dump: \n";
  assignList.dump();

  //Capacity check
  cout << "Capacity check: \n"
       << "******************************************************************\n\n";
  
  EntryList capList;

  cout << "initial capacity: \n";
  cout << "size: " << capList.size() << ", capacity: " << capList.capacity() << endl;
  capList.dump();
  cout << endl;
  
  cout << "insert a bunch of stuff.\n";
  
  //marron's code
  for (int i = 1; i < 13; i++) {
    capList.insert( EntryList::Entry((i*5)%13, i) );
  }

  //check capacity
  cout << "size: " << capList.size() << ", capacity: " << capList.capacity() << endl;
  capList.dump();
  cout << endl;

  cout << "remove a bunch of stuff. \n";
  
  for (int i = 1; i < 13; i+=2) {
    capList.remove(i, e);
  }

  cout << "size: " << capList.size() << ", capacity: " << capList.capacity() << endl;
  capList.dump();
  cout << endl;

  cout << "\nCheck that the iterator works fine. \n";
  for (auto itr = capList.begin(); itr != capList.end(); itr++) {
    cout << *itr << endl;
  }

  //iterating empty list.
  cout << "\nCheck that the iterator works fine for empty lists (should not output anything). \n";
  for (auto itr = emptyList.begin(); itr != emptyList.end(); itr++) {
    cout << *itr << endl;
  }

  cout << "\nCheck that begin works fine.\n";
  auto itr = capList.begin();
  cout << "begin output: " << *itr << endl;
  
  //trying expceptions
  cout << "To test exceptions, UNCOMMENT TO TEST THAT IT WORKS. \n";
  //emptyList.at(-1);
  //emptyList.at(10000);
  
  cout << "\nGraph: Basic test of constructor, addEdge(), removeEdge(): \n"
       << "******************************************************************\n\n";

  //Constructor
  cout << "Making an empty graph.\n";
  
  Graph* Gptr = new Graph(5) ;

  //addEdge()
  cout << "Adding edges and checking that edges can be to itself (2,2) \n";
  
  Gptr->addEdge(3, 1, 1);
  Gptr->addEdge(1, 3, 1);
  Gptr->addEdge(0, 2, 1);
  Gptr->addEdge(2, 3, 1);
  Gptr->addEdge(0, 1, 1);
  Gptr->addEdge(0, 2, 1);
  Gptr->addEdge(2, 4, 1);
  Gptr->addEdge(0, 4, 1);
  Gptr->addEdge(2, 2, 1);
  
  // Dump the graph
  cout << "\nInitial graph (G1):\n";
  Gptr->dump();

  //test removal
  cout << "Removing edge (0,3) \n";
  Gptr->removeEdge(0,3);
  Gptr->dump();

  //Try exception
  cout << "To test exceptions, UNCOMMENT TO TEST THAT IT WORKS. \n";
  //Gptr->addEdge(-1, -1, -1);
  //Gptr->removeEdge(-1, -1);

  cout << "\nGraph: copy/assignment (partial marron code)\n"
       << "******************************************************************\n\n";

  Graph* emptyGraph = new Graph(5);
  Graph* Gptr2 = new Graph(5);
  
  Gptr2->addEdge(3, 4, 1);
  Gptr2->addEdge(1, 4, 1);
  Gptr2->addEdge(0, 3, 1);
  Gptr2->addEdge(0, 4, 1);
  Gptr2->addEdge(0, 1, 1);
  Gptr2->addEdge(1, 2, 1);
  Gptr2->addEdge(2, 4, 1);

  
  cout << "Try the empty copy/assign. \n";
  Graph* copyGptr = new Graph(*emptyGraph);
  Graph assign = *emptyGraph;

  //self assignment
  cout << "Try self assignment (nothing should happen)\n";
  assign = assign;

  cout << "Try to output/ test functions (should do nothing). \n";
  copyGptr->dump();
  assign.dump();

  //check that the other ones are deep copies.
  cout << "remove on original and cout copy/assign \n";
  Gptr->removeEdge(1,2);
  copyGptr->dump();
  assign.dump(); 

  //clear memory
  delete copyGptr;
  copyGptr = nullptr;
  delete emptyGraph;
  emptyGraph = nullptr;
  
  //Copy constructor
  cout << "\nTest copy constructor. \n";
  copyGptr = new Graph(*Gptr2);
  copyGptr->dump();
    
  //Testing Assignment operator
  cout << "\nTesting assingment \n";
  Graph assign2 = *Gptr2;
  assign2.dump();

  //Checking deep copy of copy and assign.
  cout << "check deep copy. of assignment and copy \n";
  cout << "addEdge(2,2,3) to gptr2. \n";
  Gptr2->addEdge(2, 2, 3);
  Gptr2->dump();

  cout << "copy \n";
  copyGptr->dump();

  cout << "assignGptr \n";
  assign2.dump();

  cout << "\nGraph: Iterator tests: (partial marron's test shows functionality.)\n"
       << "******************************************************************\n\n";
  
  // Graph::Tests of the edge iterator:
  Graph G(5);

  // add some edges
  G.addEdge(1,3,6);
  G.addEdge(0,2,6);
  G.addEdge(1,4,10);
  G.addEdge(0,1,5);
  G.addEdge(2,4,4);
  G.addEdge(0,1,20);
  G.addEdge(1,0,10);
  G.addEdge(2,3,12);

  cout << "what is in the list: \n";
  G.dump();

  cout << "\nedge iterator: \n";
  
  Graph::EgIterator eit;
  std::tuple<int,int,int> edge;

  //test for egbegin
  cout << "Testing the egbegin to work well." << endl;
  eit = G.egBegin();
  edge = *eit;

  
  cout << "Output: "
       << "(" << get<0>(edge) << ", "
       << get<1>(edge) << ", "
       << get<2>(edge) << ") " ;

  cout << endl;
  
  //output the edges.
  cout << "egBegin must return the first value and egEnd must return the last\n";
  
  for (eit = G.egBegin() ; eit != G.egEnd() ; eit++) {
    edge = *eit;

    cout << "(" << get<0>(edge) << ", "
	 << get<1>(edge) << ", "
	 << get<2>(edge) << ") " ;
  }
  
  cout << endl;
  
  // Graph::Tests of the neighbor iterator:
  cout << "\nneighbor iterator: \n";
  
  Graph::NbIterator nit ;

  cout << "Deferencing and incrementing exceptions.\n"
       << "UNCOMMENT TO ALLOW OCCUR\n";

  //This one
  //*nit;
  //Or this one. Only one at a time.
  //Graph::NbIterator excepNit = Graph::NbIterator(copyGptr, -1, false);
  //excepNit++;

  cout << endl;
  
  //output the neighbors,
  cout << "nbBegin must return the first value and nbEnd must return the last\n";

  for (int i = 0; i < G.numVert(); i++) {
    cout << "\nThe neighbors of vertex " << i << " are:\n" ;
    for (nit = G.nbBegin(i); nit != G.nbEnd(i) ; nit++) {
      cout << "(" << (*nit).first << ", " << (*nit).second << ")" << " " ;
    }
    cout << endl ;
  }

  
  
  //clear memory.
  delete Gptr;
  Gptr = nullptr;
  delete Gptr2;
  Gptr2 = nullptr;
  delete copyGptr;
  copyGptr = nullptr;
  //delete assignGptr;
  //assignGptr = nullptr;

  assign.~Graph();
  assign2.~Graph();
  
  return 0;
}



