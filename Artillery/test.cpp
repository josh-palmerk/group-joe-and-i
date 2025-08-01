/***********************************************************************
 * Source File:
 *    TEST
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testAngle.h"
#include "testPosition.h"
#include "testVelocity.h"
#include "testAcceleration.h"
#include "testHowitzer.h"
#include "testProjectile.h"

 // This code, and the similar IF_DEF in testRunner(), is to ensure that
 // you can see the text output (called the console window) and OpenGL's
 // graphics at the same time. It is not required on Apple's XCode, only
 // on Window's Visual Studio. If you have problems seeing the output window
 // and your team is exclusively on Visual Studio, you can safely remove
 // these two "#ifdef _WIN32" and the "#endif" below it.
#ifdef _WIN32
#include <windows.h>
#include <iostream>
using namespace std;
#endif


/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
// David: my computer doesn't compile with this, so I commented it out
// #ifdef _WIN32
//    AllocConsole();
//    FILE* stream;
//    errno_t err;
//    err = freopen_s(&stream, "CONOUT$", "a", stdout);
// #endif // _WIN32

   TestAngle().run();
   TestAcceleration().run();
   TestPosition().run();
   TestVelocity().run();
//   TestGround().run();  
   TestHowitzer().run();
   // TestProjectile().run();
   std::cout << "tests completed" << std::endl;
}
