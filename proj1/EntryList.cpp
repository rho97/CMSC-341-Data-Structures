//Paul Roh
//groh1@umbc.edu

#include "EntryList.h"

using std::cout;
using std::endl;
using std::range_error;

//factors by which arrays dynamically double (> 1/2) or halve (< 1/4).
int DOUBLE_SCALE = 2;
int HALVE_SCALE = 4;

// Constructor - DO NOT MODIFY
EntryList::EntryList() {
  _array = new Entry[DEFAULT_SIZE];
  _capacity = DEFAULT_SIZE;
  _size = 0;
}

//copy constructor
EntryList::EntryList(const EntryList& rhs) {
  //initialize base values  
  _array = nullptr;
  _capacity = DEFAULT_SIZE;
  _size = 0;

  //copy the values of capacity and size if not empty.
  if (rhs.size() > 0 && rhs._array != nullptr) {
    _array = new Entry[capacity()];

    //implement iterator to insert each value.
    for (int i = 0; i < rhs.size(); i++) {
      int vert = rhs._array[i].getVertex();
      int weight = rhs._array[i].getWeight();
      Entry item = Entry(vert,weight);
      
      insert(item);
    }
  }
}


//assignment operator
const EntryList& EntryList::operator=(const EntryList& rhs) {
  cout << "assign called \n";
  //protect against self assignment
  if (_array != rhs._array) {

    //check to see that this is not filled.
    if (_array != nullptr) { delete[] _array; }

    //initialize base values.
    _array = nullptr;
    _capacity = DEFAULT_SIZE;
    _size = 0;

    //protects against empty assignemnt
    if (rhs.size() > 0 && rhs._array != nullptr) {
      _array = new Entry[capacity()];

      //implement iterator to insert each value.
      for (int i = 0; i < rhs.size(); i++) {
	int vert = rhs._array[i].getVertex();
	int weight = rhs._array[i].getWeight();
	Entry item = Entry(vert, weight);

	insert(item);
      }
    }
  }
  
  return *this;
}

//destructor
EntryList::~EntryList() {
  if (_array != nullptr) { delete[] _array; }
}

bool EntryList::insert(const Entry& e) {

  //index for the location of equivalent or greater vertex value.
  int index = 0;

  //tells whether size was incremented or a vertex was updated.
  bool increment = false;
  bool updated = false;

  //guard against comparing null values.
  if (e.getWeight() != 0) {

    //case where the e is the first value of the list.
    if (size() == 0) {
      _array[size()] = e;
      _size++;
      increment = true;
    }
    
    else if (size() > 0) {
      
      //iterate through and determine the location of the vertex to change.
      for (int i = 0; i < size(); i++) {
	//save the index of where to place vertex.
	if (_array[i].getWeight() != 0 && _array[i].getVertex() <= e.getVertex()) { index = i; }
      }
	
      //if there is an equivalent vertex, update the weight
      if (_array[index].getVertex() == e.getVertex()) {
	update(e);
	updated = true;
      }
      
      //else if the vertex value is greater than any other, put at the end.
      else if (_array[size() - 1].getVertex() < e.getVertex()) {
	_array[size()] = e;
	
	_size++;
	increment = true;
      }
      
      //otherwise push the higher value vertices to the right and insert at index.
      else {
	Entry nextEntry = _array[index];
	Entry tmpEntry = e;

	//iterate through and move values to become in order.
	for (int i = index; i < _size; i++) {
	  nextEntry = _array[i];
	  _array[i] = tmpEntry;
	  tmpEntry = nextEntry;  
	}

	_array[size()] = nextEntry;
	_size++;
	increment = true;
      }
      
      //if size fills more than half the space, double the array.
      if (capacity() < (size() * DOUBLE_SCALE)) {
	if (increment || updated) {
	  
	  //double the capacity and make a bigger array.
	  _capacity *= DOUBLE_SCALE;
	  Entry *tempList = new Entry[capacity()];
	  
	  //make entries for each vertex in _array.
	  for (int i = 0; i < size(); i++) {
	    tempList[i] = Entry(_array[i].getVertex(), _array[i].getWeight());
	  }
	  
	  //delete the current array and set it to a null value.
	  if (_array != nullptr) {
	    delete[] _array;
	    _array = nullptr;
	  }
	  
	  //set the array equal to new list.
	  _array = tempList;
	}

	_array[size()] = Entry();
      }
    }
  }
  
  
  //if the size was increased or a vertex was updated, return true.
  if (increment)
    return true;  
  return false;
}

bool EntryList::update(const Entry& e) {

  //iterate through and change the equivalent vertex.
  for (int i = 0; i < size(); i++) {
    if (_array[i].getVertex() == e.getVertex()) {
      _array[i].setWeight(e.getWeight());

      //say that the vertex was changed.
      return true;
    }
  }

  //no matching vertex.
  return false;
}

bool EntryList::getEntry(int vertex, Entry &ret) {

  //find the entry by iterating through and matching vertex value.
  for (int i = 0; i < size(); i++) {
    if (_array[i].getVertex() == vertex) {
      ret = _array[i];
      return true;
    }
  }

  //could not find entry
  return false;
}

bool EntryList::remove(int vertex, Entry &ret) {
  //index for the location of equivalent or greater vertex value.
  int index = -1;
  //tells whether size was decremented.
  bool decrement = false;

  //iterate through and determine the location of the vertex to change.
  for (int i = 0; i < size(); i++) {  
    //save the index of where to place vertex.
    if (_array[i].getVertex() == vertex) { index = i; }
  }
  
  //if there is an equivalent vertex, move the values and decrement the size.
  if (index != -1 && _array[index].getVertex() == vertex) {
    _array[index] = Entry();
    _size--;
    decrement = true;

    //move the array elements down fill the empty space.
    for (int i = index; i < size(); i++) { _array[i] = _array[i + 1]; }
  }

  //if size fills less than fourth the space, halve the array.
  if (capacity() > DEFAULT_SIZE && capacity() > (size() * HALVE_SCALE )) {

    //halve the capacity and make a smaller array.
    _capacity = _capacity / DOUBLE_SCALE;
    Entry *tempList = new Entry[capacity()];

    //make entries for each vertex in _array.
    for (int i = 0; i < size(); i++) {
      tempList[i] = Entry(_array[i].getVertex(), _array[i].getWeight());
    }

    //delete the current array and set it to a null value.
    if (_array != nullptr) {
      delete[] _array;
      _array = nullptr;
    }

    //set the array equal to new list.
    _array = tempList;
  }

  //if the size was decreased, return true.
  if (decrement)
    return true;
  return false;
}

EntryList::Entry& EntryList::at(int indx) const {
  //throw if indx is out of bounds.
  if (indx >= size() || indx < 0) { throw range_error("EntryList::at(): index is out of bounds"); }

  //catch block for the throw when index is out of bounds.
  //catch(range_error) { cout << "exception occurred: " << range_error << "\n"; }

  //return the reference to the entry if index is in bounds.
  else { return _array[indx]; }
}

// dump data structure - DO NOT MODIFY
void EntryList::dump() {
  for (int i = 0; i < size(); i++) {
    cout << "  " << _array[i] << endl;
  }
}

//Iterator
/********************************************************/

EntryList::Iterator::Iterator(EntryList *EList, int indx) {
  _ELptr = EList;
  _indx = indx;
  
}

bool EntryList::Iterator::operator!=(const EntryList::Iterator& rhs) {
  //values of vertex and weight
  int vrtx = _ELptr->_array[_indx].getVertex();
  weight_t wght = _ELptr->_array[_indx].getWeight();

  //if the weight and vertex of the two do not match return true.
  if (_ELptr->_array != rhs._ELptr->_array
      ||vrtx != rhs._ELptr->_array[rhs._indx].getVertex()
      || wght != rhs._ELptr->_array[rhs._indx].getWeight()) {
     return true;
  }

  return false;
}

bool EntryList::Iterator::operator==(const EntryList::Iterator& rhs) {
  //values of vertex and weight
  int vrtx = _ELptr->_array[_indx].getVertex();
  weight_t wght = _ELptr->_array[_indx].getWeight(); 

  //if the weight and vertex of the two do match return true.
  if (vrtx == rhs._ELptr->_array[rhs._indx].getVertex()
      && wght == rhs._ELptr->_array[rhs._indx].getWeight()) {
    return true;
  }

  return false;
}

void EntryList::Iterator::operator++(int dummy) {
  _indx++;
}

//return an entry
EntryList::Entry EntryList::Iterator::operator*() {
  return _ELptr->_array[_indx];
}

//make an iterator set to the first value.
EntryList::Iterator EntryList::begin() {
  return Iterator(this, 0);
}

//make an iterator set to the last value and return.
EntryList::Iterator EntryList::end() {
  int indexSize = size();
  return Iterator(this, indexSize);
}

// Insertion operator for Entry objects - DO NOT MODIFY
ostream& operator<<(ostream& sout, const EntryList::Entry& e) {
  sout << e._vertex << ": " << e._weight;
  return sout;
}

// A convenient way to write test code for a single class is to write
// a main() function at the bottom of the .cpp file.  Just be sure to
// comment-out main() once you are done testing!

// Following is example test code.  There is no guarantee that it is
// complete -- you are responsbile for thoroughly testing your code.
// In particular, passing these tests does not mean your
// implementation will pass all grading tests.

/*
 int main() {
   EntryList el;
   EntryList::Entry e;

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;
   
   for (int i = 1; i < 13; i++) {
     el.insert( EntryList::Entry((i*5)%13, i) );
   }

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;

   
   for (int i = 1; i < 13; i+=2) {
     el.remove(i, e);
   }

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;


   for (int i = 2; i < 13; i+=2) {
     el.update( EntryList::Entry(i, 2*i) );
   }

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;

   for (int i = 3; i < 13; i*=2) {
     el.remove(i, e);
   }

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;

   cout << "\nPrint using iterator:\n";
   for (auto itr = el.begin(); itr != el.end(); itr++) {
     cout << *itr << endl;
   }
   
   return 0;
 }
*/
