/*************************************************************
 * 1. Name:
 *      Joe Allen, David Wells
 * 2. Assignment Name:
 *      Practice 04, Method
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      Hardest part was trying to get 100% on test cases. Rounding issues
        were the root cause. Version Control also being a large issue on 
        my part (Joe).
 * 5. How long did it take for you to complete the assignment?
 *      2 hours. 1 hour each
 **************************************************************/

#pragma once

 // Mathematical constants used in angle conversions
#define TWO_PI              6.28318530718
#define PI                  3.14159265358
#define ONE_EIGHTY_OVER_PI 57.29577951326093
#define PI_OVER_180         0.01745329251989

#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

class TestAngle;

/************************************
 * ANGLE
 * Represents an angle using both radians and degrees.
 ************************************/
class Angle
{
   // grant test class access to private members
   friend class TestAngle;

public:
  /********************************************
   * DEFAULT CONSTRUCTOR
   * Initializes angle to 0 radians and 0 degrees.
   ********************************************/
   Angle()
   {
      radians = 0.0;
      degrees = 0.0;
   }

   /********************************************
    * NON-DEFAULT CONSTRUCTOR
    * Initializes the angle from a degree value.
    * Converts degrees to radians.
    ********************************************/
   Angle(double newDegrees)
   {
      degrees = newDegrees;
      radians = convertToRadians(newDegrees);
   }

   /********************************************
    * COPY CONSTRUCTOR
    * Initializes the angle by copying another.
    ********************************************/
   Angle(const Angle& other)
   {
      radians = other.radians;
      degrees = other.degrees;
   }

   /********************************************
    * GET DEGREES
    * Returns the angle in degrees (computed from radians).
    ********************************************/
   double getDegrees() const { return radians * ONE_EIGHTY_OVER_PI; }

   /********************************************
    * GET RADIANS
    * Returns the internal radian value.
    ********************************************/
   double getRadians() const { return radians; }

	/********************************************
	 * SET DEGREES
	 * Sets the angle in degrees and converts to radians.
	 ********************************************/
   void setDegrees(double degrees)
   {
      // Use 'this->degrees' to refer to the member variable (not the parameter)
      this->degrees = degrees;

      // Convert the new degree value to radians and store it
      radians = convertToRadians(degrees);
   }

	/********************************************
	 * SET RADIANS
	 * Sets the angle in radians and converts to degrees.
	 ********************************************/
   void setRadians(double radians)
   {
      // Use 'this->radians' to refer to the class member variable.
      this->radians = normalize(radians);

      // Convert the newly normalized radians to degrees and store it
      degrees = convertToDegrees(this->radians);
   }

   /********************************************
    * DISPLAY
    * Displays the angle in degrees to the given output stream
    * with fixed-point notation, 1 decimal place, no spacing.
    ********************************************/
   void display(ostream& out) const
   {
      out.setf(ios::fixed);
      out.setf(ios::showpoint);
      out.precision(1);
      out << convertToDegrees(radians) << "degrees";
   }

   /********************************************
    * NORMALIZE
    * Ensures the angle is in the range [0, 2π).
    ********************************************/
   double normalize(double radians) const
   {
      while (radians < 0)
         radians += TWO_PI;
      while (radians >= TWO_PI)
         radians -= TWO_PI;
      return radians;
   }

   /********************************************
   * CONVERT TO DEGREES
   * Converts a radian value to degrees after normalizing.
   ********************************************/
   double convertToDegrees(double radians) const
   {
      return normalize(radians) * ONE_EIGHTY_OVER_PI;
   }

   /********************************************
   * CONVERT TO RADIANS
   * Converts a degree value to radians after normalizing.
   ********************************************/
   double convertToRadians(double degrees) const
   {
      return normalize(degrees * PI_OVER_180);
   }

private:
   double radians;
   double degrees;
};
