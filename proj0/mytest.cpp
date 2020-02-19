// CMSC 341 - Spring 2020 - Project 0

// mytest.cpp: a test to see that the program functions as needed.

// Assignment:
//   (1) Complete the copy constructor (in stack.h)
//   (2) Complete the assignment operator (in stack.h)
//   (3) Complete the destructor (in stack.h)
//   (4) Write a test program (mytest.cpp) to test copy and assignment
//   (5) Verify destructor by running the test program in Valgrind

#include <iostream>
#include "stack.h"

using namespace std;

int main() {  
  
  cout << "TEST #1:\n";
  
  //Initialize a starting stack.
  Stack<int> intStack;

  //Erase comment bars for large number
  //for (int i = 0; i < 1000; i++) {intStack.push(i);}

  for (int i = 0; i < 30; i++) {intStack.push(i);}

  //Copy stack
  cout << "Testing that a copy is made\n";
  Stack<int> copyStack(intStack);
  
  //Assign stack
  cout << "Testing that an assignment is done\n";
  Stack<int> assignStack = intStack;
      
  //output the stack.
  cout << "intStack output\n";
  intStack.dump();

  //deletion of instack to see if copy is deleted.
  cout << "Delete intStack and see if copyStack is unchanged using top and pop\n";
  while ( not intStack.empty() ) {
    cout << intStack.top() << endl;
    intStack.pop();
  }

  cout << "assign dump: \n";
  assignStack.dump();

  cout << "copy dump: \n";
  copyStack.dump();
  
  
  //test copy once more  
  cout << "copy top 4 on the stack\n";
  //try it 4 times.
  cout << copyStack.top() << endl;
  copyStack.pop();
  cout << copyStack.top() << endl;
  copyStack.pop();
  cout << copyStack.top() << endl;
  copyStack.pop();
  cout << copyStack.top() << endl;
  copyStack.pop();
  
  
  cout << "assign output top 4 on the stack\n";
  cout << assignStack.top() << endl;
  assignStack.pop();
  cout << assignStack.top() << endl;
  assignStack.pop();
  cout << assignStack.top() << endl;
  assignStack.pop();
  cout << assignStack.top() << endl;
  assignStack.pop();
  
  
  /**************************************************************/
    
  //Test 2
  cout << "TEST #2\n";
  cout << "\nMaking an empty stack\n";
  Stack<int> emptyStack;

  //make a copy of an empty set.
  cout << "Copy constructor using an empty set\n";
  Stack<int> testStack(emptyStack);

  //assign an empty set.
  cout << "Assignment operator using empty set\n";
  Stack<int> assignTest = emptyStack;

  //deletion of an empty set.
  cout << "Deleting an empty stack\n";
  emptyStack.~Stack();
  
  /**************************************************************/
    
  //Test 3
  Stack<int> guardTest;
  
  cout << "TEST #3\n";
  cout << "Checking that assigment operator is guarded against self-assignment.\n";
  guardTest = guardTest;
  
  return 0;
}
