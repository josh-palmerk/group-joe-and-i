/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 using namespace std;


 void Projectile::advance(double simulationTime)
 {
     // setup
     const double gravity = -9.8;

     if (flightPath.empty())
         return;

     PositionVelocityTime prev = flightPath.back();

     // Calculate new velocity
     Velocity newVelocity = prev.v;
     newVelocity.addDy(gravity * simulationTime); // v = u + at

     // Calculate new position
     Position newPosition = prev.pos;
     newPosition.addMetersX(prev.v.getDx() * simulationTime);
     newPosition.addMetersY(prev.v.getDy() * simulationTime + 0.5 * gravity * simulationTime * simulationTime);

     // Advance time
     double newTime = prev.t + simulationTime;

     // New PVT for flight path
     PositionVelocityTime newPVT;
     newPVT.pos = newPosition;
     newPVT.v = newVelocity;
     newPVT.t = newTime;

     flightPath.push_back(newPVT);
 }


