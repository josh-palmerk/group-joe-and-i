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
 *      1 hour
 *****************************************************************/

#include <iostream>
using namespace std;

// Take functions from apollo-sim.cpp and put them here
#include "apollo-sim.cpp"

int main() {
    // Initial prompts for user input
    // Requirements specify for vertical velocity first
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    // double x = prompt("What is your position (m)? ");
    double x = 0.0; // Requirements set x to 0.0
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
    int t = 5; // time in whole seconds
    double aRadians;            // Angle in radians
    double accelerationThrust;  // Acceleration due to thrust 
    double ddxThrust;           // Horizontal acceleration due to thrust
    double ddyThrust;           // Vertical acceleration due to thrust
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double v;                   // Total velocity

    // Constants
    const double mass = WEIGHT;

    
    // We're required to run the simulation twice
    for (int sim = 0; sim < 2; sim++) {
        // Loop once per second
        if (sim != 0) {
            aDegrees = prompt("\nWhat is the new angle of the LM where 0 is up (degrees)? ");
        }
        aRadians = radiansFromDegrees(aDegrees);
    
        // Compute total acceleration from thrust
        accelerationThrust = computeAcceleration(THRUST, mass);
    
        // Split acceleration into components
        ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
        ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);
    
        // Add gravity to vertical component
        ddx = ddxThrust;
        ddy = ddyThrust + GRAVITY;
        cout << "\nFor the next " << t << " seconds with the main engine on, the position of the lander is:\n\n";
        for (int i = 0; i < t; i++)
        {

            // Compute new position
            x = computeDistance(x, dx, ddx, 1);
            y = computeDistance(y, dy, ddy, 1);

            // Compute new velocity
            dx = computeVelocity(dx, ddx, 1);
            dy = computeVelocity(dy, ddy, 1);

            // Compute total velocity
            double v = computeTotalComponent(dx, dy);

            // Output results
            cout.setf(ios::fixed | ios::showpoint);
            cout.precision(2);
            int second = i + 1 + (sim * 5);
            if (second  < 10) {
                cout << " ";
            }
            cout << second << "s - x,y:(" << x << ", " << y << ")m ";
            cout << " dx,dy:(" << dx << ", " << dy << ")m/s ";
            cout << " speed:" << v << "m/s ";
            cout << " angle:" << aDegrees << "deg\n";
        }
    }

    return 0;
}