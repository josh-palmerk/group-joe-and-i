/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
using namespace std;


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight)
      : ground(posUpperRight), lander(posUpperRight)
   {
      for (int i = 0; i < 50; i++)
         stars[i].reset(posUpperRight.getX(), posUpperRight.getY());
   }

   Ground ground;
   Lander lander;
   Thrust thrust;
   Star stars[50];
};



/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator * pSimulator = (Simulator *)p;
   ogstream gout;

   // Step A: draw the stars
   for (int i = 0; i < 50; i++)
      pSimulator->stars[i].draw(gout);

   // Step B: handle thrust
   pSimulator->thrust.set(pUI);

   // Step C: compute acceleration from input
   double gravity = -1.0;
   Acceleration a = pSimulator->lander.input(pSimulator->thrust, gravity);

   // Step D: move the lander
   double time = 0.1;
   pSimulator->lander.coast(a, time);

   // Step E: draw terrain and lander
   pSimulator->ground.draw(gout);
   pSimulator->lander.draw(pSimulator->thrust, gout);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char** argv)
{
   // Run the unit tests
   testRunner();

   
   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void *)&simulator);

   return 0;
}
