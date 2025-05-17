/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "position.h"
#include "velocity.h"
#include "acceleration.h"

/******************************************
 * POINT : CONSTRUCTOR WITH X,Y
 * Initialize the point to the passed position
 *****************************************/
Position::Position(double x, double y) : x(x), y(y) {}

/******************************************
 * POINT : ADD
 * Update point based on the distance formula
 *   s = s_0 + vt + 1/2 a t^2
 *****************************************/
void Position::add(const Acceleration & a, const Velocity & v, double t)
{
   // increase the velocity according to the acceleration with time
   Velocity v2 = Velocity(v);
   v2.add(a, t);
   x += v.getDX();
   y += v.getDY();
}

