
/*************************************************************
 * 1. Name:
 *      David Wells
 *      Joe Allen
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      Figuring out what changes had to be made per 5-second interval
 * 5. How long did it take for you to complete the assignment?
 *      2 hours
 *****************************************************************/

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

   /**************************************************
   * CONFIRM
   * Prompt user with a yes/no question.
   * INPUT
   *     message : A question string to display to the user.
   * OUTPUT
   *     true if the user responds with 'y' or 'Y', false otherwise.
   **************************************************/
   bool confirm(const char* message)
   {
      char response;
      cout << message << " (y/n): ";
      cin >> response;
      return response == 'y' || response == 'Y';
   }


   /**************************************************
   * RUN TEST CASES
   * Run the predefined Apollo 11 simulations. Each test
   * runs twice: once with the initial angle and once with
   * the new angle. Results are printed to the console.
   **************************************************/
   void runTestCases()
   {
      const double mass = WEIGHT;
      const int t = 5; // duration per phase

      // Define a list of test cases with fixed input values
      struct TestCase
      {
         const char* name;
         double dy;
         double dx;
         double y;
         double x;
         double initialAngle;
         double newAngle;
      };

      TestCase tests[] = {
         {"Hard landing", -13.959, 10.53, 106.08, 0.0, -45, 0},
         {"Crash",        -15.000, -35.00, 207.77, 0.0, 90, 45},
         {"Armstrong is awesome!", -10.000, 10.00, 62.70, 0.0, -42.185, 0}
      };

      // Loop through each test case
      for (const TestCase& test : tests)
      {
         cout << "\n=== Test Case: " << test.name << " ===\n";

         // Initialize position and velocity from test input
         double dy = test.dy;
         double dx = test.dx;
         double y = test.y;
         double x = test.x;
         double aDegrees = test.initialAngle;

         // Run the simulation twice: once for each angle
         for (int sim = 0; sim < 2; sim++)
         {
            if (sim == 1)
               aDegrees = test.newAngle;

            // Convert angle to radians
            double aRadians = radiansFromDegrees(aDegrees);

            // Compute total acceleration from thrust
            double accelerationThrust = computeAcceleration(THRUST, mass);

            // Split acceleration into components
            double ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
            double ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);
            double ddx = ddxThrust;
            double ddy = ddyThrust + GRAVITY;

            cout << "\nFor the next " << t << " seconds with the main engine on, the position of the lander is:\n\n";

            // Loop through each second of simulation
            for (int i = 0; i < t; i++)
            {
               // Update position based on current velocity and acceleration
               x = computeDistance(x, dx, ddx, 1);
               y = computeDistance(y, dy, ddy, 1);

               // Update velocity based on current acceleration
               dx = computeVelocity(dx, ddx, 1);
               dy = computeVelocity(dy, ddy, 1);

               // Compute total speed
               double v = computeTotalComponent(dx, dy);

               // Format and output the results
               cout.setf(ios::fixed | ios::showpoint);
               cout.precision(2);
               int second = i + 1 + (sim * 5);
               if (second < 10)
                  cout << " ";
               cout << second << "s - x,y:(" << x << ", " << y << ")m ";
               cout << " dx,dy:(" << dx << ", " << dy << ")m/s ";
               cout << " speed:" << v << "m/s ";
               cout << " angle:" << aDegrees << "deg\n";
            }
         }
      }
   }

   /**************************************************
   * RUN USER INPUT
   * Prompt the user to manually enter all simulation values.
   * The simulation is then run twice: first with initial angle,
   * then with a new user-supplied angle.
   **************************************************/
   void runUserInput()
   {
      const double mass = WEIGHT;
      const int t = 5; // duration per phase

      // Prompt user for initial values
      double dy = prompt("What is your vertical velocity (m/s)? ");
      double dx = prompt("What is your horizontal velocity (m/s)? ");
      double y = prompt("What is your altitude (m)? ");
      double x = 0.0; // x starts at zero by requirement
      double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");

      // Run the simulation twice: once for each angle
      for (int sim = 0; sim < 2; sim++)
      {
         // Prompt for new angle on second pass
         if (sim != 0)
            aDegrees = prompt("\nWhat is the new angle of the LM where 0 is up (degrees)? ");

         // Convert angle to radians
         double aRadians = radiansFromDegrees(aDegrees);

         // Compute thrust-based acceleration
         double accelerationThrust = computeAcceleration(THRUST, mass);

         // Compute horizontal and vertical components
         double ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
         double ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);
         double ddx = ddxThrust;
         double ddy = ddyThrust + GRAVITY;

         cout << "\nFor the next " << t << " seconds with the main engine on, the position of the lander is:\n\n";

         // Loop through each second of simulation
         for (int i = 0; i < t; i++)
         {
            x = computeDistance(x, dx, ddx, 1);
            y = computeDistance(y, dy, ddy, 1);
            dx = computeVelocity(dx, ddx, 1);
            dy = computeVelocity(dy, ddy, 1);
            double v = computeTotalComponent(dx, dy);

            cout.setf(ios::fixed | ios::showpoint);
            cout.precision(2);
            int second = i + 1 + (sim * 5);
            if (second < 10)
               cout << " ";
            cout << second << "s - x,y:(" << x << ", " << y << ")m ";
            cout << " dx,dy:(" << dx << ", " << dy << ")m/s ";
            cout << " speed:" << v << "m/s ";
            cout << " angle:" << aDegrees << "deg\n";
         }
      }
   }

   /****************************************************************
   * MAIN
   * Prompt user to choose between running test cases or
   * manually entering simulation data, and run the appropriate path.
   ****************************************************************/
   int main()
   {
      if (confirm("Would you like to run the predefined test cases?"))
         runTestCases();
      else
         runUserInput();

      return 0;
	}
	/****************************************************************
	* END OF FILE
	****************************************************************/
