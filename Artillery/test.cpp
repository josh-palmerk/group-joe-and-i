#include "testAngle.h"
#include "testAcceleration.h"
#include "testVelocity.h"

int main() {
    TestAngle test = TestAngle();
    TestAcceleration test2 = TestAcceleration();
    TestVelocity test3 = TestVelocity();
    test3.run();
    return 0;
}