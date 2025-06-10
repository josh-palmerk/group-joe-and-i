/*************************************************************
 * 1. Name:
 *      David Wells, Josh Palmer, Joe Allen
 * 2. Assignment Name:
 *      Practice 08: Allocation
 * 3. Assignment Description:
 *      Allocate an array and then use it
 * 4. What was the hardest part? Be as specific as possible.
 *      Working as a group to complete the assignment.
 * 5. How long did it take for you to complete the assignment?
 *      -1 hours
 **************************************************************/

 /****************************
  * ALLOCATE ONE FLOAT
  * Dynamically allocates a float on the heap and initializes it
  * with the given value. Returns a pointer to the allocated float.
  ****************************/
inline float* allocateOneFloat(float value)
{
   float* p = new float(value); // Allocate and initialize a float
   return p;
}

/****************************
 * DELETE ONE FLOAT
 * Deletes a dynamically allocated float and sets the pointer to nullptr
 * to avoid dangling pointer issues.
 ****************************/
inline void deleteOneFloat(float*& p)
{ 
   if (p != nullptr) // Only delete if pointer is valid
   {
      delete p;  // Free the allocated memory
      p = nullptr;  // Nullify the pointer to prevent reuse
   }
}

/****************************
 * ALLOCATE ARRAY of DOUBLEs
 * Allocates a dynamic array of doubles of the specified size.
 * Returns nullptr if the size is zero or negative.
 ****************************/
inline double* allocateArrayDouble(int size)
{
   if (size <= 0) // Invalid size, return null pointer
      return nullptr;
   return new double[size]; // Allocate array on heap
}

/****************************
 * DELETE ARRAY of DOUBLEs
 * Deletes a dynamically allocated array of doubles and nullifies the pointer.
 ****************************/
inline void deleteArrayDouble(double*& arr)
{
   if (arr != nullptr) // Only delete if pointer is valid
   {
      delete[] arr; // Free the array memory
      arr = nullptr; // Prevent dangling pointer
   }
}
