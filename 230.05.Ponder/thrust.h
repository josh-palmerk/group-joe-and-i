/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h"  // for Interface

class TestLander;
class TestThrust;

 /*****************************************************
  * THRUST
  * Represents activation of thrusters
  *****************************************************/
class Thrust
{
   friend TestLander;
   friend TestThrust;
   
public:
   // Thrust is initially turned off
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   // Get rotation in radians per second
   double rotation() const
   {
      // Check both so both are not on at once
      if (clockwise && !counterClockwise)
         return .1 * 30;
      else if (counterClockwise && !clockwise)
         return -.1 * 30;
      else
         return 0.0;
   }

   // get main engine thrust in  m / s ^ 2
   double mainEngineThrust() const
   {
      // a set number, so no need to re-calculate
      // return 45000.0 / 15103.0;
      return 2.9795404; 
   }

   // reflect what is firing
   bool isMain()    const { return true; }
   bool isClock()   const { return true; }
   bool isCounter() const { return true; }

   // set the thrusters
   void set(const Interface * pUI)
   {
      mainEngine = (pUI->isDown() != 0);
      // right arrow actually controls left thruster
      clockwise = (pUI->isRight() != 0);            
      counterClockwise = (pUI->isLeft() != 0); 
   }

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
