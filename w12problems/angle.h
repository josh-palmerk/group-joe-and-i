/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI

class TestAngle;

/************************************
 * ANGLE
 ************************************/
class Angle
{
public:
   friend TestAngle;


   // Constructors
   Angle() { radians = 0.0; }
   Angle(const Angle& rhs) { radians = rhs.radians; }
   Angle(double degrees) { radians = normalize(convertToRadians(degrees)); }

   // Getters
   double getDegrees() const { return convertToDegrees(radians); }
   double getRadians() const { return radians; }

   // Setters
   void setDegrees(double degrees) { radians = normalize(convertToRadians(degrees)); }
   void setRadians(double radians) { this->radians = normalize(radians); }

   void setUp() { radians = 0.0; }
   void setDown() { radians = M_PI; }
   void setRight() { radians = M_PI_2; }
   void setLeft() { radians = M_PI + M_PI_2; }

   void reverse() { radians = normalize(radians + M_PI); }

   Angle& add(double delta)
   {
      radians = normalize(radians + delta);
      return *this;
   }
   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
   /* Here are the problems we are meant to solve today: */
   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
   
   /*Assignment Operator*/
   Angle& operator=(Angle& rhs) {
      radians = rhs.radians;
      return *this;
   }
   /*Negative Operator*/
   Angle& operator-(Angle& rhs) {
      radians = -rhs.radians;
      return *this;
   }
   /*Equals and Not Equals*/
   bool operator==(const Angle& rhs) const {
      return getRadians() == rhs.getRadians();
   }
   bool operator!=(const Angle& rhs) const {
      return getRadians() != rhs.getRadians();
   }
   /*Insertion*/
   ostream& operator<<(const Angle& rhs);
   /*Extraction*/
   ostream& operator>>(const Angle& rhs);
   /*Increment and decrement*/
   Angle& operator++();
   Angle& operator--();


private:
   double normalize(double radians) const;

   double convertToDegrees(double radians) const
   {
      return radians * (180.0 / M_PI);
   }

   double convertToRadians(double degrees) const
   {
      return degrees * (M_PI / 180.0);
   }

   double radians;   // 360 degrees equals 2 PI radians
};
