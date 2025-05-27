/*************************************************************
 * 1. Name:
 *      David Wells, Joe Allen
 * 2. Assignment Name:
 *      Practice 06: Templates
 * 3. Assignment Description:
 *      Find the biggest element in an array, and a stack data structure.
 * 4. What was the hardest part? Be as specific as possible.
 *      Getting started and staying on task as always.
 * 5. How long did it take for you to complete the assignment?
 *      1.5 hours. Not a strong reader, I prefer pop-up books.
 **************************************************************/

#pragma once

#include <iostream>

 /***************************************
  * FIND BIGGEST
  **************************************/
template <typename T>
T findBiggest(T array[], int numElements)
{
   // Assume the first element is the biggest
	T biggest = array[0];

	// Loop through the array to find the biggest element
   for (int i = 1; i < numElements; i++)
   {
      // Update biggest if a larger value is found
      if (array[i] > biggest)
         biggest = array[i];
	}

	// return the largest value found
	return biggest;
}

class TestStack;

/***************************************
 * STACK
 **************************************/
template <typename T>
class Stack
{
   friend TestStack;

public:
   Stack() : numElements(0) {}

	// Add an element to the stack
   void push(const T & value)
   {
      if (numElements < 10)
         data[numElements++] = value;
      else
			std::cout << "Stack is full, cannot push " << value << std::endl;
   }

	// Remove the top element from the stack
   void pop()
   {
      if (numElements > 0)
         numElements--;
      else
			std::cout << "Stack is empty, cannot pop" << std::endl;
   }

	// Access the top element of the stack
   T top()
   {
      if (numElements)
			return data[numElements - 1];

      // Default return based on type
      if constexpr (std::is_same<T, char>::value)
         return '\0'; // Return null character for char type
      return T{}; // Default-constructed value for all other types
      
   }

private:
   T data[10]; // Fixed-size array to hold stack elements
   int numElements; // Current number of elements
};