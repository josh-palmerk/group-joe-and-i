/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#pragma once

 // Forward declarations
class Velocity;        // for Position::add()
class Acceleration;    // for Position::add()
class TestPosition;    // for the unit tests
class TestLander;      // for the unit tests

/*********************************************
 * POSITION
 * A single position on the screen
 *********************************************/
class Position
{
   friend TestPosition;    // for the unit tests
   friend TestLander;      // for the unit tests

public:
   /*************************************
   * Default constructor
   * Initializes position to (0.0, 0.0)
   *************************************/
   Position() : x(0.0), y(0.0) {}

   /****************************************
   * Copy constructor
   * Initializes from another Position
   ****************************************/
   Position(const Position& pos) : x(pos.getX()), y(pos.getY()) {}

   /****************************************
   * Non-default constructor
   * Initializes position to given x and y
   * @param x Horizontal coordinate
   * @param y Vertical coordinate
   ****************************************/
   Position(double x, double y);


   /****************************************
   * GET X
   * Returns the horizontal component
   * @return x position
   ****************************************/
   double getX() const { return x; }

   /****************************************
   * GET Y
   * Returns the vertical component
   * @return y position
   ****************************************/
   double getY() const { return y; }

   /****************************************
   * EQUALITY OPERATOR ==
   * Compares two positions for equality
   * @param rhs The other position
   * @return true if equal
   ****************************************/
   bool operator == (const Position& rhs) const
   {
      return rhs.getX() == x && rhs.getY() == y;
   }

   /****************************************
   * INEQUALITY OPERATOR !=
   * Compares two positions for inequality
   * @param rhs The other position
   * @return true if not equal
   ****************************************/
   bool operator != (const Position& rhs) const
   {
      return rhs.getX() != x || rhs.getY() != y;
   }

   /****************************************
   * SET X
   * Assign a new x value
   * @param x New horizontal coordinate
   ****************************************/
   void setX(double x) { this->x = x; }

   /****************************************
   * SET Y
   * Assign a new y value
   * @param y New vertical coordinate
   ****************************************/
   void setY(double y) { this->y = y; }


   /****************************************
   * ADD X
   * Increment x by a value
   * @param x Delta-x
   ****************************************/
   void addX(double x) { this->x += x; }

   /****************************************
   * ADD Y
   * Increment y by a value
   * @param y Delta-y
   ****************************************/
   void addY(double y) { this->y += y; }

   /****************************************
   * ADD
   * Move the position forward using the formula:
   * s = s + vt + ½at²
   * @param a Acceleration to apply
   * @param v Initial velocity
   * @param t Time interval in seconds
   ****************************************/
   void add(const Acceleration& a, const Velocity& v, double t);

   /****************************************
   * ASSIGNMENT OPERATOR =
   * Assigns one position to another
   * @param rhs The position to copy
   * @return Reference to this
   ****************************************/
   Position& operator = (const Position& rhs)
   {
      x = rhs.getX();
      y = rhs.getY();
      return *this;
   }

private:
   double x;           // horizontal position
   double y;           // vertical position
};

