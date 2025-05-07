/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 03: Angle Class
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

#pragma once

#define TWO_PI              6.28318530718
#define PI                  3.14159265358
#define ONE_EIGHTY_OVER_PI 57.29577951326093
#define PI_OVER_180         0.01745329251989

#include <cmath>    // for floor()
// I heard this is better than math.h
#include <iostream>  // for cout
#include <cassert>   // for assert()
using namespace std;

class TestAngle;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   private:
      // store both for quicker calculations
      // made private for more control
      double angleRadians;
      double angleDegrees;
   public:
      double getDegrees() {
         return angleDegrees;
      }
      double getRadians() {
         return angleRadians;
      }
      /*
      * Preferable to call this over setRadians (it's faster)
      */
      void setDegrees(double degrees) {
         angleRadians = convertToRadians(degrees);
         angleDegrees = convertToDegrees(degrees);
      }
      void setRadians(double radians) {
         // this also normalizes
         angleRadians = normalize(radians);
         // this normalizes twice, but I didn't want to
         // create another normalize function
         angleDegrees = convertToDegrees(angleRadians);
      }
      void display(ostream& out) {
         // Set up the print style:
         // fixed-point, with 1 decimal point and a decimal point
         // displaying DEGREES as requested by the professor
         out.setf(std::ios::fixed);
         out.setf(std::ios::showpoint);
         out.precision(1);
         cout << angleDegrees << " deg." << endl;
      }

   private:
      /*
       * Takes radians and normalizes it to be between 0 and 2*PI
       */
      double normalize(double radians) {
         while (radians < 0) {
            radians += TWO_PI;
         }
         while (radians >= TWO_PI) {
            radians -= TWO_PI;
         }
         return radians;
      }
      double convertToDegrees(double radians) {
         return normalize(radians) * ONE_EIGHTY_OVER_PI;
      }
      double convertToRadians(double degrees) {
         return normalize(degrees * PI_OVER_180);
      }

};


