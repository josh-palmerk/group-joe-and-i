/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   status = PLAYING;
   fuel = 5000.0;

   angle.setUp();

   velocity.setDX(random(-10.0, -4.0));
   velocity.setDY(random(-2.0, 2.0));

   pos.setX(posUpperRight.getX() - 1.0);
   pos.setY(random(posUpperRight.getY() * 0.75, posUpperRight.getY() * 0.95));
}

void Lander::land()
{
   angle.setUp();
   status = SAFE;
}

void Lander::crash()
{
   angle.setDown();
   status = DEAD;
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander::draw(const Thrust& thrust, ogstream& gout) const
{
   gout.drawLander(pos, angle.getRadians());
   gout.drawLanderFlames(pos, angle.getRadians(),
      thrust.isMain(),
      thrust.isClock(),
      thrust.isCounter());
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   Acceleration a;

   // Always apply gravity
   a.setDDY(gravity);

   //fuel = 5000.0; // to allow for lander movement. remove this for test cases
         
   // Always rotate if needed (even if no main engine)
   angle.add(thrust.rotation());

   // If fuel is gone, rotation is allowed but no thrust is applied
   if (fuel <= 0.0)
      return a;

   // If out of fuel, return early (rotation already applied)
   if ((thrust.isClock() || thrust.isCounter()))
   {
      fuel -= 1.0;
      if (fuel < 0.0)
         fuel = 0.0;
      
   }

   // Only apply thrust if main engine is on
   if (thrust.isMain())
   {
      fuel -= 10.0;
      if (fuel < 0.0)
         fuel = 0.0;

      double magnitude = thrust.mainEngineThrust();
      Acceleration thrustAccel;
      thrustAccel.set(angle, magnitude);

      // Invert the thrust vector to apply force opposite the nose direction
      thrustAccel.setDDX(-thrustAccel.getDDX());
      //thrustAccel.setDDY(thrustAccel.getDDY());

      a.add(thrustAccel);
   }

   return a;
}
/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   pos.add(acceleration, velocity, time); // use current velocity
   velocity.add(acceleration, time);      // update velocity for next frame
}
