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
#include <iostream>


using namespace std;


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight)
      : posUpperRight(posUpperRight), ground(posUpperRight), lander(posUpperRight)
   {
      lander.reset(posUpperRight);
      for (int i = 0; i < 50; i++)
         stars[i].reset(posUpperRight.getX(), posUpperRight.getY());
   }

   Ground ground;
   Lander lander;
   Thrust thrust;
   Star stars[50];
   int delayFramesRemaining = 0;
   bool showLandingMessage = false;
   bool showCrashMessage = false;
   Position posUpperRight;
};



/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   Simulator* pSimulator = (Simulator*)p;
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
// Step D: move the lander
   if (pSimulator->delayFramesRemaining == 0)
   {
      double time = 0.1;
      pSimulator->lander.coast(a, time);
   }

   const Position& pos = pSimulator->lander.getPosition();
   const Ground& ground = pSimulator->ground;

   double altitude = ground.getElevation(pos);
   double speed = pSimulator->lander.getSpeed();

   // Only attempt platform check if we’re close enough to ground
   if (pSimulator->delayFramesRemaining == 0)
   {
      if (altitude <= 1.5)
      {
         double x = pos.getX();
         double landerWidth = pSimulator->lander.getWidth();
         double leftEdge = x - landerWidth / 2.0;
         double rightEdge = x + landerWidth / 2.0;

         // Declare pad range before using it
         double padLeft = 0.1 * pSimulator->posUpperRight.getX();
         double padRight = padLeft + 30.0;

         // consoile outputs for debugging
         std::cout << "Pad: " << padLeft << " - " << padRight
            << " | Lander: " << leftEdge << " - " << rightEdge << std::endl;
         std::cout << "Speed: " << speed << " | MaxAllowed: "
            << pSimulator->lander.getMaxSpeed() << std::endl;

         // Display Hud
         gout << "DEBUG - X: " << x
            << " | LeftEdge: " << leftEdge
            << " | RightEdge: " << rightEdge
            << " | Speed: " << speed
            << "\n";

         bool onPlatform = ground.onPlatform(pos, pSimulator->lander.getWidth());
         bool safeSpeed = speed <= pSimulator->lander.getMaxSpeed();

         if (onPlatform && safeSpeed)
         {
            pSimulator->lander.land();
            pSimulator->showLandingMessage = true;
         }
         else
         {
            pSimulator->lander.crash();
            pSimulator->showCrashMessage = true;
         }

         pSimulator->delayFramesRemaining = 90; // 3 seconds
      }
   }

   // Step E: draw terrain and lander
   pSimulator->ground.draw(gout);
   pSimulator->lander.draw(pSimulator->thrust, gout);
   
   // Step G: show landing or crash message
   if (pSimulator->showLandingMessage)
   {
      Position msgPos(100.0, 200.0);
      gout.setPosition(msgPos);
      gout << "The Eagle has landed!";
   }
   else if (pSimulator->showCrashMessage)
   {
      Position msgPos(100.0, 200.0);
      gout.setPosition(msgPos);
      gout << "You have crashed!";
   }

   // Step F: draw HUD
   Position hudPos;
   hudPos.setX(10.0);
   hudPos.setY(390.0);
   gout.setPosition(hudPos);

   int fuel = pSimulator->lander.getFuel();

   //double speed = pSimulator->lander.getSpeed();
   //double altitude = pSimulator->ground.getElevation(pSimulator->lander.getPosition());

   gout << "Fuel:    " << fuel << " lbs\n"
      << "Altitude: " << altitude << " meters\n"
      << "Speed:   " << speed << " m/s\n";

   /*
   // Step G: show landing or crash message
   if (pSimulator->showLandingMessage)
   {
      Position msgPos(100.0, 200.0);
      gout.setPosition(msgPos);
      gout << "The Eagle has landed!";
   }
   else if (pSimulator->showCrashMessage)
   {
      Position msgPos(100.0, 200.0);
      gout.setPosition(msgPos);
      gout << "You have crashed!";
   }
   */
   // Step H: handle pause and reset after land/crash
   if (pSimulator->delayFramesRemaining > 0)
   {
      pSimulator->delayFramesRemaining--;

      if (pSimulator->delayFramesRemaining == 0)
      {
         pSimulator->lander.reset(pSimulator->posUpperRight);
         pSimulator->showLandingMessage = false;
         pSimulator->showCrashMessage = false;
      }

      return; // Prevent lander from moving during the pause
   }
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
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
