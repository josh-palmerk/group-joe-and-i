/***********************************************************************
 * Source File:
 *    GROUND
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Where the ground is located and where the landing pad is located
 ************************************************************************/

#include "ground.h"   // for the Ground class definition
#include "uiDraw.h"   // for random() and drawLine()
#include <cassert>

const long   LZ_SIZE   = 30;    // size of the landing zone
const double MAX_SLOPE = 2.7;   // steapness of the features. Smaller number is flatter
const double LUMPINESS = 1.0;   // size of the hills. Smaller number is bigger features
const double TEXTURE   = 3.0;   // size of the small features such as rocks

 /************************************************************************
  * GROUND constructor
  * Create a new grond object
  ************************************************************************/
Ground::Ground(const Position& posUpperRight) : posUpperRight(posUpperRight)
{
   assert(posUpperRight.getX() > 0.0);
   assert(posUpperRight.getY() > 0.0);

   ground = new double[(int)posUpperRight.getX()];

   // Move iLZ randomization HERE so it only happens at launch
   iLZ = (int)random(posUpperRight.getX() * 0.1,
      posUpperRight.getX() * 0.9 - (double)LZ_SIZE);


   reset(); // Still generates the terrain, but won't change iLZ anymore
}

/************************************************************************
 * RESET
 * Create a new ground
 ************************************************************************/
void Ground::reset()
{
   // determine the landing location
   iLZ = (int)random(posUpperRight.getX() * 0.1,
      posUpperRight.getX() * 0.9 - (double)LZ_SIZE);

   // Set pad elevation visibly on screen
   ground[iLZ] = posUpperRight.getY() * 0.3 + random(0.0, 20.0);
   ground[0] = ground[iLZ];  // ensure terrain starts at pad height

   double dy = random(-2.0, 2.0);
   for (int i = 1; i < int(posUpperRight.getX()); i++)
   {
      if (i >= iLZ && i < iLZ + LZ_SIZE)
      {
         ground[i] = ground[i - 1];  // keep pad flat
      }
      else
      {
         double percent = ground[i - 1] / (posUpperRight.getY() / 2.0) * 0.5;
         dy += random(-MAX_SLOPE, MAX_SLOPE);

         if (dy > MAX_SLOPE) dy = MAX_SLOPE;
         if (dy < -MAX_SLOPE) dy = -MAX_SLOPE;

         ground[i] = ground[i - 1] + dy + random(-TEXTURE, TEXTURE);

         // Clamp ground to visible screen range
         if (ground[i] < 40.0)
            ground[i] = 40.0;
         if (ground[i] > posUpperRight.getY() - 20.0)
            ground[i] = posUpperRight.getY() - 20.0;
      }
   }
}

/***********************************************************
 * HTI GROUND
 * Did the lander hit the ground?
 **********************************************************/
bool Ground::hitGround(const Position& pos, int landerWidth) const
{
   // find the extent of the lander
   int xMin = (int)(pos.getX() - (double)landerWidth / 2.0);
   int xMax = (int)(pos.getX() + (double)landerWidth / 2.0);

   // determine the extent
   xMin = (xMin < 0 ? 0 : xMin);
   xMax = (xMax > (int)posUpperRight.getX() - 1 ? (int)posUpperRight.getX() - 1 :  xMax);

   // find the max elevation for the width of the lander
   double maxElevation = ground[xMin];
   for (int i = xMin + 1; i <= xMax; i++)
      if (ground[i] > maxElevation)
         maxElevation = ground[i];

   // return whether we hit the ground
   return pos.getY() < maxElevation;
}

/************************************************************************
 * ON PLATFORM
 * Have we landed on the platform?
 ************************************************************************/
bool Ground::onPlatform(const Position& pos, int landerWidth) const
{
   double altitude = getElevation(pos);

   // Relaxed vertical range for better success
   if (altitude < -1.0 || altitude > 3.0)
      return false;

   double x = pos.getX();
   double leftEdge = x - landerWidth / 2.0;
   double rightEdge = x + landerWidth / 2.0;

   double padLeft = static_cast<double>(iLZ);
   double padRight = padLeft + 30.0;

   return leftEdge >= padLeft && rightEdge <= padRight;
}

/*****************************************************************
 * DRAW
 * Draw the ground on the screen
 ****************************************************************/
void Ground::draw(ogstream & gout) const
{
   // iterate through the entire ground and draw it all
   for (long i = 0; i < (int)posUpperRight.getX(); i++)
      gout.drawRectangle(Position((double)i, 0.0), 
                         Position((double)(i + 1), ground[i]), 
                         0.3 /*red*/, 0.2 /*green*/, 0.1 /*blue*/);

   // draw the landing pad
   gout.drawRectangle(Position((double)iLZ, ground[iLZ]),
                      Position((double)(iLZ + LZ_SIZE), ground[iLZ] - 2.0),
                      0.0 /*red*/, 0.0 /*green*/, 1.0 /*blue*/);

}
