// CMSC 341 - Spring 2020 - Project 0

// driver.cpp: a sample driver for the Stack class.
// This is NOT a test program; it just demonstrates basic usage of
// Stack.

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
  Stack<int> intStack;

  cout << "\nPush integers on stack and dump contents:\n";
  for (int i = 1; i <= 10; i++) {
    intStack.push(i);
  }

  intStack.dump();

  cout << "\nRead contents using top() and pop():\n";
  while ( not intStack.empty() ) {
    cout << intStack.top() << endl;
    intStack.pop();
  }

  cout << "\nAttempt pop() of empty stack:\n";
  try {
    intStack.pop();
  } catch (exception &e) {
    cout << "Caught exception:\n" << e.what() << endl;
  }

  return 0;
}
