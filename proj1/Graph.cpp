//Paul Roh
//groh1@umbc.edu

#include <iostream>
#include "Graph.h"

using std::cout;
using std::endl;
using std::exception;
using std::invalid_argument;

// Constructor - DO NOT MODIFY
Graph::Graph(int n) {
  if (n <= 0)
    throw invalid_argument("Graph::Graph(): number of vertices must be positive");

  _rows = new EntryList*[n];
  for (int i = 0; i < n; i++) {
    _rows[i] = new EntryList();
  }
  _numVert = n;
  _numEdge = 0;
}

Graph::Graph(const Graph& G) {
  //assign basic values.  
  _rows = nullptr;

  //copy the vertices and edges.
  _numVert = G.numVert();
  _numEdge = G.numEdge();
  
  //check to see whether it is an empty graph or not.
  if (G._rows != nullptr) {
    
    //copy the rows with the same number of vertices n.
    _rows = new EntryList*[numVert()];
    for (int i = 0; i < numVert(); i++) {
      _rows[i] = new EntryList(*(G._rows[i]));
    }
  }
}


const Graph& Graph::operator=(const Graph& rhs) {

  cout << "GRAPH ASSIGN\n";
  //If this is not self assignment
  if (this->_rows != rhs._rows) {

    //copy the vertices and edges.
    _numVert = rhs.numVert();
    _numEdge = rhs.numEdge();
    
    //check to see whether it is an empty graph or not.
    if (rhs._rows != nullptr) {
      //copy the rows with the same number of vertices n.
      _rows = new EntryList*[numVert()];
      for (int i = 0; i < numVert(); i++) {	
	_rows[i] = new EntryList(*(rhs._rows[i]));
      }
    }
    
    //else make it empty
    else {
      _rows = nullptr;
      _numVert = 0;
      _numEdge = 0;
    }
  }
  
  return *this;
}

Graph::~Graph() {
  _numEdge = 0;
  
  //guard against empty deletion.
  if (_rows != nullptr) {
    //delete each row.
    for (int i = 0; i < _numVert; i++) {  
      delete _rows[i];
      _rows[i] = nullptr;
    }
    
    //delete the whole thing.
    _numVert = 0;
    delete[] _rows;
    _rows = nullptr;
  }
}

// Number of vertices - DO NOT MODIFY
int Graph::numVert() const {
  return _numVert;
}

// Number of edges - DO NOT MODIFY
int Graph::numEdge() const {
  return _numEdge;
}

void Graph::addEdge(int u, int v, weight_t x) {
  //find out if the values of n and v are valid.
  if (u < 0 || v < 0 || u >= numVert() || v >= numVert())
    throw invalid_argument("Graph::addEdge(): number of vertices must be between 0 and number of vertices");
  
  //make a new weight for vertex u to vertex v.
  EntryList::Entry tmpEntry = EntryList::Entry(v,x);
  
  //insert and increment numedge if added successfully.
  bool added = _rows[u]->insert(tmpEntry);
  if (added) { _numEdge++; }
}

bool Graph::removeEdge(int u, int v) {
  //find out if the values of n and v are valid.
  if (u < 0 || v < 0 || u >= _numVert || v >= _numVert)
    throw invalid_argument("Graph::removeEdge(): number of vertices must be between 0 and number of vertices");
  
  EntryList::Entry ret;
  //remove the edge between u and v. returns if it was successful or not.
  bool removed = _rows[u]->remove(v, ret);
  
  if (removed) { _numEdge--; }
  return removed;
}


// Dump the graph - DO NOT MODIFY
void Graph::dump() const {
  
  cout << "Dump of graph (numVert = " << _numVert
       << ", numEdge = " << _numEdge << ")" << endl;
  
  for (int i = 0; i < _numVert; i++) {
    cout << "Row " << i << ": \n";
    _rows[i]->dump();
  }
}

/**********************Edge iterator*****************************/

//Edge iterator
Graph::EgIterator::EgIterator(Graph *Gptr, bool enditr) {
  _Gptr = Gptr;
  _row = 0;
  
  if (Gptr == nullptr || Gptr->_rows == nullptr) {
    //uninitialized iterator
    _itr = EntryList::Iterator();
  }
  
  else if (enditr) {
    //vertex at the end of graph and index of that vertex.
    int endVert = _Gptr->numVert() - 1;
    int listIndex = _Gptr->_rows[endVert]->size();

    //set the index to the last real value.
    while (listIndex == 0 && endVert > 0) {
      endVert--;
      listIndex = _Gptr->_rows[endVert]->size();
    }
    
    //set itr to the vert last value of the entry lists.
    _itr = EntryList::Iterator(_Gptr->_rows[endVert], listIndex);
  }

  //determine the start of the iterator.
  else {
    int listIndex = _Gptr->_rows[_row]->size();

    //reset the start iterator to the first valid value.
    while (_row < _Gptr->numVert() && listIndex == 0) {
      _row++;
      listIndex = _Gptr->_rows[_row]->size();
    } 

    //set begin iterator.
    _itr = EntryList::Iterator(_Gptr->_rows[_row], 0); }
}

tuple<int,int,weight_t> Graph::EgIterator::operator*() {
  if (_Gptr == nullptr) {
    throw invalid_argument("Graph::EgIterator::operator*: expected a graph, got a nullptr.");
  }
  
  //find the entry associated with itr and get the vertex and weight.
  EntryList::Entry tmpEntry = *_itr;
  return std::make_tuple(_row, tmpEntry.getVertex(), tmpEntry.getWeight());
}

bool Graph::EgIterator::operator!=(const EgIterator& rhs) {
  if (_itr != rhs._itr)
    return true;
  return false;
}

void Graph::EgIterator::operator++(int dummy) { 
  //increment if there are more entries in the row.
  if (_itr != _Gptr->_rows[_row]->end()) {
    //increment the iterator.
    _itr++;

    //check for any placeholder values and skip them.
    EntryList::Entry tmpEntry = *_itr;

    //Compares the end of the iterator to _itr.
    EgIterator endItr(_Gptr, true);
  
    //Set the first value after a placeholder.
    if (_itr != endItr._itr && tmpEntry.getWeight() == 0) {
      _row++;
      _itr = EntryList::Iterator(_Gptr->_rows[_row], 0);
    } 
  }
  
  //rest the index and set the pointer to the next _Gptr.
  else {
    _row++;
    int listIndex = _Gptr->_rows[_row]->size();
    
    //reset the start iterator to the first valid value.
    while (_row < _Gptr->numVert() && listIndex == 0) {
      _row++;
      listIndex = _Gptr->_rows[_row]->size();
    }
    
    _itr = EntryList::Iterator(_Gptr->_rows[_row], 0);
  }
}

Graph::EgIterator Graph::egBegin() {
  //make the iterator and set the enditr to false to tell program to start.
  EgIterator egItr = Graph::EgIterator(this, false);
  return egItr;
}

Graph::EgIterator Graph::egEnd() {
  //make the iterator and set the enditr to true to tell program where the end is.
  EgIterator egItr = Graph::EgIterator(this, true);
  return egItr;
}

/**************************Neighbor iterator*********************************/

Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool enditr) {
  //initialize values and set an index for the last entry.
  _row = v;
  _Gptr = Gptr;
  
  //set uninitialized iterator.
  if (_Gptr == nullptr || _Gptr->_rows[v] == nullptr) { _itr = EntryList::Iterator(); }
  
  //throw an argument if not a valid vertex.
  else if (v < 0 || v >= Gptr->numVert()) {
    throw invalid_argument("Graph::NbIterator::NbIterator(): invalid vertex number. must be an existing vertex");
  }
  
  //if end is true, make it the last entry.
  else if (enditr) {
    int listIndex = _Gptr->_rows[v]->size();
    _itr = EntryList::Iterator(Gptr->_rows[v], listIndex);
  }
  
  //otherwise, begin.
  else { _itr = EntryList::Iterator(Gptr->_rows[v], 0); }
}


bool Graph::NbIterator::operator!=(const NbIterator& rhs) {
  //compares the values of Gptr, row, and itr to see if any of them differ.
  if (_itr != rhs._itr)
    return true;
  return false;
}

void Graph::NbIterator::operator++(int dummy) {
  _itr++;
}

pair<int,weight_t> Graph::NbIterator::operator*() {
  if (_Gptr == nullptr) {
    throw invalid_argument("Graph::NbIterator::operator*: iterator is NULL or invalid.");
  }
  
  //find the entry associated with itr and get the vertex and weight.
  EntryList::Entry tmpEntry = *_itr;
  return std::make_pair(tmpEntry.getVertex(), tmpEntry.getWeight());
}

Graph::NbIterator Graph::nbBegin(int v) {
  //determine the size and check if v is a valid value. If not throw exception.
  if (v < 0 || v >= numVert())
    throw invalid_argument("Graph::nbBegin(int v): invalid argument. vertex is not within the existing list.");
  
  //make the iterator and set enditr to false as this is the beginning.
  NbIterator nbItr = Graph::NbIterator(this, v, false);
  
  return nbItr;
}

Graph::NbIterator Graph::nbEnd(int v) {
  //determine the size and check if v is a valid value. If not throw exception.
  if (v < 0 || v >= numVert())
    throw invalid_argument("Graph::nbBegin(int v): invalid argument. vertex is not within the existing list.");
  
  //make the iterator and set the enditr to true to tell program where the end is.
  NbIterator nbItr = Graph::NbIterator(this, v, true);
  
  return nbItr;
}
