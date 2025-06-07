using namespace std;
#include <iostream>
#include <cmath>
#include <tuple>
#include "gravity.h"

const double INITIAL_SPEED = 827.0;
const double PI = 3.1415926535897; 
const int DEFAULT_ALTITUDE = 0;
const int PROJECTILE_MASS = 46.7; // in kg
const int PROJECTILE_DIAMETER = 154.89; // in mm

Gravity g = Gravity();

double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

double getVertSpeedComponent(double radians, double speed) {
    return speed * cos(radians);
}

double getHorizSpeedComponent(double radians, double speed) {
    return speed * sin(radians);
}

// Gravity is a class that gives you the gravity at a given altitude

/* This can give distance for either horizontal or vertical, but not both (don't use velocity!)*/
double getDistance(double initialDistance, double axisVelocity, double time, double acceleration) {
    return initialDistance + (axisVelocity * time) + (0.5 * acceleration * time * time);
}

/* Returns the new axis velocity (NOT TOTAL VELOCITY, at least not yet) */
double getKinematics(double initialVelocity, double acceleration, double time) {
    return initialVelocity + (acceleration * time);
}

double getAngleFromComponents(double verticalSpeed, double horizontalSpeed) {
    return atan2(horizontalSpeed, verticalSpeed);
}

/* Referenced as Pythagorean Theorem in Lab07 Description*/
double getSpeedFromComponents(double verticalSpeed, double horizontalSpeed) {
    return sqrt(pow(verticalSpeed, 2) + pow(horizontalSpeed, 2));
}

// Linear Interpolation is found in the InterpolatableChart class
// and all of its derived classes, such as Gravity.

// THIS PASSED
void step1() {
    double angle = toRadians(75.0);
    double verticalSpeed = getVertSpeedComponent(angle, INITIAL_SPEED);
    double horizontalSpeed = getHorizSpeedComponent(angle, INITIAL_SPEED);
    double horizontalDistance = horizontalSpeed * 20;
    double verticalDistance = verticalSpeed * 20;
    cout << horizontalDistance << " m distance" << endl;
    cout << verticalDistance << " m altitude" << endl;
}
// THIS PASSED
void step2() {
    const double CONST_GRAVITY = -9.8; // m/s^2
    const double TIME_UNIT = 1;
    double angle = toRadians(75.0);
    double acceleration = CONST_GRAVITY;
    double horizontalDistance = 0;
    double verticalDistance   = DEFAULT_ALTITUDE;
    double velocity = INITIAL_SPEED;

    double verticalSpeed = getVertSpeedComponent(angle, velocity);
    double horizontalSpeed=getHorizSpeedComponent(angle,velocity);


    for (int i = 0; i < 20; i++) {
        cout << "iteration: " << i << endl;
        horizontalDistance += horizontalSpeed * TIME_UNIT;
        verticalDistance = getDistance(verticalDistance, verticalSpeed, TIME_UNIT, acceleration);
        
        // update for next iteration
        verticalSpeed = getKinematics(verticalSpeed, acceleration, TIME_UNIT);
        velocity = getSpeedFromComponents(verticalSpeed, horizontalSpeed);
        cout << "velocity: " << velocity << endl;
        cout << horizontalDistance << ", " << verticalDistance << endl;
    }

}

int main() {
    step2();
    return 0;   
}