
   /*************************************************************
   * 1. Name:
   *      Joe Allen
   * 2. Assignment Name:
   *      Practice 02: Physics simulator
   * 3. Assignment Description:
   *      Compute how the Apollo lander will move across the screen
   * 4. What was the hardest part? Be as specific as possible.
   *      Trying to figure out how to do the actual project. I made some
   *        assumptions and wasnt sure where to start. Finally settled on 
   *        making the functions as simple as possible and just performing
   *        math and returning results. Then calling said functions within main.
   * 5. How long did it take for you to complete the assignment?
	*      2.5 hours
   **************************************************************/

   #include <iostream>  // for CIN and COUT
   #include <cmath>   // for M_PI and sqrt
   using namespace std;
   #ifndef M_PI
   #define M_PI 3.14159265358979323846
   #endif

   #define WEIGHT   15103.000   // Weight in KG
   #define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
   #define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

   /***************************************************
   * COMPUTE DISTANCE
   * Apply inertia to compute a new position using the distance equation.
   * The equation is:
   *     s = s + v t + 1/2 a t^2
   * INPUT
   *     s : original position, in meters
   *     v : velocity, in meters/second
   *     a : acceleration, in meters/second^2
   *     t : time, in seconds
   * OUTPUT
   *     s : new position, in meters
   **************************************************/
   double computeDistance(double s, double v, double a, double t)
   {
		// Distance equation:
      // s = s + vt + 1/2 at^2
      return s + (v * t) + (0.5 * a * t * t);
   }

   /**************************************************
   * COMPUTE ACCELERATION
   * Find the acceleration given a thrust and mass.
   * This will be done using Newton's second law of motion:
   *     f = m * a
   * INPUT
   *     f : force, in Newtons (kg * m / s^2)
   *     m : mass, in kilograms
   * OUTPUT
   *     a : acceleration, in meters/second^2
   ***************************************************/
   double computeAcceleration(double force, double mass)
   {
		// Acceleration equation:
      return force / mass;
   }

  /***********************************************
   * COMPUTE VELOCITY
   * Starting with a given velocity, find the new
   * velocity once acceleration is applied. This is
   * called the Kinematics equation. The
   * equation is:
   *     v = v + a t
   * INPUT
   *     v : velocity, in meters/second
   *     a : acceleration, in meters/second^2
   *     t : time, in seconds
   * OUTPUT
   *     v : new velocity, in meters/second
   ***********************************************/
   
   double computeVelocity(double velocity, double acceleration, double time)
   {

      return velocity + (acceleration * time);
   }

   /***********************************************
   * COMPUTE VERTICAL COMPONENT
   * Find the vertical component of a velocity or acceleration.
   * The equation is:
   *     cos(a) = y / total
   * This can be expressed graphically:
   *      x
   *    +-----
   *    |   /
   *  y |  / total
   *    |a/
   *    |/
   * INPUT
   *     a : angle, in radians
   *     total : total velocity or acceleration
   * OUTPUT
   *     y : the vertical component of the total
   ***********************************************/
   
   double computeVerticalComponent(double a, double total)
   {
		// Vertical component equation:
      return total * cos(a);
   }

   /***********************************************
   * COMPUTE HORIZONTAL COMPONENT
   * Find the horizontal component of a velocity or acceleration.
   * The equation is:
   *     sin(a) = x / total
   * This can be expressed graphically:
   *      x
   *    +-----
   *    |   /
   *  y |  / total
   *    |a/
   *    |/
   * INPUT
   *     a : angle, in radians
   *     total : total velocity or acceleration
   * OUTPUT
   *     x : the vertical component of the total
   ***********************************************/
   
   double computeHorizontalComponent(double a, double total)
   {
		// Horizontal component equation:
      return total * sin(a);
   }

   /************************************************
   * COMPUTE TOTAL COMPONENT
   * Given the horizontal and vertical components of
   * something (velocity or acceleration), determine
   * the total component. To do this, use the Pythagorean Theorem:
   *    x^2 + y^2 = t^2
   * where:
   *      x
   *    +-----
   *    |   /
   *  y |  / total
   *    | /
   *    |/
   * INPUT
   *    x : horizontal component
   *    y : vertical component
   * OUTPUT
   *    total : total component
   ***********************************************/
   
   double computeTotalComponent(double x, double y)
   {
		// Total component equation:
      return sqrt((x * x) + (y * y));
   }


   /*************************************************
   * RADIANS FROM DEGEES
   * Convert degrees to radians:
   *     radians / 2pi = degrees / 360
   * INPUT
   *     d : degrees from 0 to 360
   * OUTPUT
   *     r : radians from 0 to 2pi
   **************************************************/
   
   double radiansFromDegrees(double d)
   {
		// Radians equation:
      return d * (M_PI / 180.0);
   }

   /**************************************************
   * PROMPT
   * A generic function to prompt the user for a double
   * INPUT
   *      message : the message to display to the user
   * OUTPUT
   *      response : the user's response
   ***************************************************/
   
   double prompt(const char* message)
   {
      // Declare a variable to store the user's input.
      double response;

      // Display the provided message to the user on the console.
      cout << message;

      // Read the user's input from the console.
      cin >> response;

      // Return the input
      return response;
   }

   /****************************************************************
   * MAIN
   * Prompt for input, compute new position, and display output
   ****************************************************************/
   int main()
   {

      // Prompt for input and variables to be computed
      double dx = prompt("What is your horizontal velocity (m/s)? ");
      double dy = prompt("What is your vertical velocity (m/s)? ");
      double y = prompt("What is your altitude (m)? ");
      double x = prompt("What is your position (m)? ");
      double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
      double t = prompt("What is the time interval (s)? ");
      double aRadians;            // Angle in radians
      double accelerationThrust;  // Acceleration due to thrust 
      double ddxThrust;           // Horizontal acceleration due to thrust
      double ddyThrust;           // Vertical acceleration due to thrust
      double ddx;                 // Total horizontal acceleration
      double ddy;                 // Total vertical acceleration
      double v;                   // Total velocity

      // Constants
      const double mass = WEIGHT;

      aRadians = radiansFromDegrees(aDegrees);

      // Compute total acceleration from thrust
      accelerationThrust = computeAcceleration(THRUST, mass);

      // Split acceleration into components
      ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
      ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);

      // Add gravity to vertical component
      ddx = ddxThrust;
      ddy = ddyThrust + GRAVITY;

      // Loop 5 times
      for (int i = 0; i < 5; i++)
      {


         // Compute new position
         x = computeDistance(x, dx, ddx, t);
         y = computeDistance(y, dy, ddy, t);

         // Compute new velocity
         dx = computeVelocity(dx, ddx, t);
         dy = computeVelocity(dy, ddy, t);

         // Compute total velocity
         double v = computeTotalComponent(dx, dy);

         // Output results
         cout.setf(ios::fixed | ios::showpoint);
         cout.precision(2);
         cout << "\tNew position:   (" << x << ", " << y << ")m\n";
         cout << "\tNew velocity:   (" << dx << ", " << dy << ")m/s\n";
         cout << "\tTotal velocity:  " << v << "m/s\n\n";
      }

      return 0;
   }

