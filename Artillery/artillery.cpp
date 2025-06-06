using namespace std;
#include <iostream>
#include <cmath>
#include <tuple>

const double OVERALL_SPEED = 827.0;
const int DEFAULT_ALTITUDE = 0;

double toRadians(double degrees);
double getVertSpeedComponent(double radians, double speed);
double getHorizSpeedComponent(double radians, double speed);
double getGravity(int altitude);
double getFlightTime(double verticalSpeed, double gravity);
double getDistance(double horizontalSpeed, double flightTime);
tuple<double, double> getDistanceAndHangTime(double angleDegrees);

int main() {
    double angleDegrees;
    cout << "What is the angle of the howitzer where 0 is up? ";
    cin >> angleDegrees;

    auto [distance, hangTime] = getDistanceAndHangTime(angleDegrees);

    cout << "Distance: " << distance << " m" << endl;
    cout << "Hang Time: " << hangTime << " s" << endl;

    return 0;
}

double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double getVertSpeedComponent(double radians, double speed) {
    return speed * cos(radians);
}

double getHorizSpeedComponent(double radians, double speed) {
    return speed * sin(radians);
}

double getGravity(int altitude) {
    return 9.81;
}

double getFlightTime(double verticalSpeed, double gravity) {
    return (2 * verticalSpeed) / gravity;
}

double getDistance(double horizontalSpeed, double flightTime) {
    return horizontalSpeed * flightTime;
}

tuple<double, double> getDistanceAndHangTime(double angleDegrees) {
    double radians = toRadians(angleDegrees);
    double verticalSpeed = getVertSpeedComponent(radians, OVERALL_SPEED);
    double horizontalSpeed = getHorizSpeedComponent(radians, OVERALL_SPEED);
    double gravity = getGravity(DEFAULT_ALTITUDE);
    double hangTime = getFlightTime(verticalSpeed, gravity);
    double distance = getDistance(horizontalSpeed, hangTime);
    return make_tuple(distance, hangTime);
}