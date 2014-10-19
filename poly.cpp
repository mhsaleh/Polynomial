// @file poly.cpp
// @author Muhammed Saleh

#ifndef POLY_CPP
#define POLY_CPP

#include "poly.h"

//---------------------------------------------------------------------------
// Implements a Polynomial class storing a series of coefficients and 
//    non-negative exponents. Allows functionality for creation of new
//    poly objects using default and copy constructors, deletion of
//    poly objects, addition, subtraction, multiplication of poly objects
//    equality and inequality comparison of poly objects, assignment of one
//    poly object to another using =, +=, -=, and *=, as well as the input 
//    and output of poly objects.
//
// Implementation and assumptions:
//   -- polynomials are stored in an array
//   -- coefficients are stored in each array index
//   -- exponents are the array indices themselves
//   -- all exponents are >= 0
//   -- all user input must be valid integers
//   -- invalid exponents are set to 0 if passed into constructors
//   -- invalid exponents return 0 if passed in to methods that return ints
//   -- invalid exponents do nothing if passed into methods that return void

// ---------------------------------------------------------------------------
// Constructor
// Default constructor for Poly class
// takes in an int coeff and an int exponent
// sets the maximum exponent to the passed in value and the coefficient
// at that value to the passed in coefficient
// If the passed in exponent is negative, the exponent is set to 0
Poly::Poly(int coeff, int exponent) {
   if (exponent < 0) { // negative exponent, invalid
      maxExponent = 0;
   } else {
      maxExponent = exponent;
   }
   coeffPtr = new int[maxExponent + 1](); // initialize array
   coeffPtr[maxExponent] = coeff; // set coeff at exponent
}

// ---------------------------------------------------------------------------
// Copy
// Copy constructor for Poly class
// Takes in another Poly object and creates a copy of it
Poly::Poly(const Poly& other) {
   maxExponent = other.maxExponent; // copy maxExponent
   coeffPtr = new int[maxExponent + 1](); // initialize array
   for (int power = 0; power < maxExponent + 1; power++) {
      coeffPtr[power] = other.coeffPtr[power];  // copy contents of other
   }
}

// ---------------------------------------------------------------------------
// Destructor
// Destructor for Poly class
// Clears all memory in a Poly object
Poly::~Poly() {
   delete[] coeffPtr;
   coeffPtr = NULL;
}

// ---------------------------------------------------------------------------
// operator+
// Overloaded addition operator for Poly class
// Adds the left Poly object to the right Poly object
Poly Poly::operator+(const Poly& right) const {
   Poly sum(*this); // copy of left object, in case left is larger than right
   for (int power = 0; power < right.maxExponent + 1; power++) {
      // add values of right object
      sum.setCoeff(getCoeff(power) + right.getCoeff(power), power);
   }
   return sum;
}

// ---------------------------------------------------------------------------
// operator-
// Overloaded subtraction operator for Poly class
// Subtracts the right Poly object from the left Poly object
Poly Poly::operator-(const Poly& right) const {
   Poly difference(*this); // copy of left object
   for (int power = 0; power < right.maxExponent + 1; power++) {
      //subtract values of right object
      difference.setCoeff(getCoeff(power) - right.getCoeff(power), power);
   }
   return difference;
}

// ---------------------------------------------------------------------------
// operator*
// Overloaded multiplication operator for Poly class
// Multipliess two Poly objects
Poly Poly::operator*(const Poly& right) const {
   Poly product;
   
   // each value in left polynomial
   for (int leftPow = 0; leftPow < maxExponent + 1; leftPow++) {
      // each value in right polynomial
      for (int rightPow = 0; rightPow < right.maxExponent + 1; rightPow++) {
         // multiply coefficients and insert at sum of exponents
         product.setCoeff(getCoeff(leftPow) * right.getCoeff(rightPow)
						  + product.getCoeff(leftPow + rightPow),
						  leftPow + rightPow);
      }
   }
   return product;
}

// ---------------------------------------------------------------------------
// operator+=
// Overloaded addition assignment operator for Poly class
// Sets the Poly object on the left to the sum of the two objects
Poly& Poly::operator+=(const Poly& right) {
   for (int power = 0; power < right.maxExponent + 1; power++) {
      // add values of right object
      setCoeff(getCoeff(power) + right.getCoeff(power), power);
   }
   return *this;
}

// ---------------------------------------------------------------------------
// operator-=
// Overloaded subtraction assignment operator for Poly class
// Sets the Poly object on the left to the difference between the two objects
Poly& Poly::operator-=(const Poly& right) {
   for (int power = 0; power < right.maxExponent + 1; power++) {
      // subtract values of right object
      setCoeff(getCoeff(power) - right.getCoeff(power), power);
   }
   return *this;
}

// ---------------------------------------------------------------------------
// operator*=
// Overloaded multiplication assignment operator for Poly class
// Sets the Poly object on the left to the product of the two objects
Poly& Poly::operator*=(const Poly& right) {
   Poly product;
   // each coeff in left polynomial
   for (int leftPow = 0; leftPow < maxExponent + 1; leftPow++) {
      // each coeff in right polynomial
      for (int rightPow = 0; rightPow < right.maxExponent + 1; rightPow++) {
         // multiply coefficients and insert at sum of exponents
         product.setCoeff(getCoeff(leftPow) * right.getCoeff(rightPow)
						  + product.getCoeff(leftPow + rightPow),
						  leftPow + rightPow);
      }
   }
   return *this = product;
}

// ---------------------------------------------------------------------------
// operator=
// Overloaded assignment operator for Poly class
// Assigns the Poly object on the left to that on the right
Poly& Poly::operator=(const Poly& right) {
   if (&right != this) { // they aren't already the same
      delete[] coeffPtr; // clear left memory

      maxExponent = right.maxExponent;
      coeffPtr = new int[maxExponent + 1](); // new array for left object

      for (int power = 0; power < maxExponent + 1; power++) {
         setCoeff(right.getCoeff(power), power); // copy values from right
      }
   }
   return *this;
}

// ---------------------------------------------------------------------------
// operator==
// Overloaded equality operator for Poly class
// Checks to see if the Poly object on the left equals that on the right
bool Poly::operator==(const Poly& other) const {
   if (maxExponent == other.maxExponent) { // sizes are the same
      for (int power = 0; power < maxExponent + 1; power++) { // check each
         if (getCoeff(power) != other.getCoeff(power)) {
            return false; // coefficients aren't the same
         }
      }
      return true; // all coefficients have been checked and are equal
   }
   return false; // sizes aren't the same
}

// ---------------------------------------------------------------------------
// operator!=
// Overloaded inequality operator for Poly class
// Checks to see if the Poly object on the left does not equal the right
bool Poly::operator!=(const Poly& other) const {
   return !(*this == other);
}

// ---------------------------------------------------------------------------
// operator<<
// Overloaded output operator for Poly class
// If all coefficients in the polynomial are 0, outputs " 0"
// Otherwise ouputs each coefficient followed by "x^" and its exponent
// assuming that exponent is not 0 or 1
// If the exponent is 0, outputs the coefficient alone
ostream& operator<<(ostream& output, const Poly& poly) {
   bool printed = false; // assume all coefficients are zero
   // print powers from largest to smallest
   for (int power = poly.maxExponent; power >= 0; power--) {
      int coefficient = poly.getCoeff(power);
      
      if (coefficient != 0) {
         printed = true; // a nonzero coefficient is printed
         
         output << ' ';
         if (coefficient > 0) { // positive coefficient
            output << '+';
         }
         output << coefficient;
         
         if (power != 0) {
            output << 'x';
            if (power != 1) { // power is not 0 or 1
               output << "^" << power;
            }
         }
      }
   }
   if (!printed) { // nothing is printed, all coefficients are zero
      output << " 0";
   }
   return output;
}

// ---------------------------------------------------------------------------
// operator>>
// Overloaded input operator for Poly class
// Takes in coeff and exponent pairs until a both values are -1
istream& operator>>(istream& input, Poly& poly) {
   bool stop = false; // input while true
   int coeff = 0;
   int exponent = 0;
   
   while (!stop) { // both values are not -1
      input >> coeff;
      input >> exponent;
      
      if (coeff == -1 && exponent == -1) { // user inputs "-1 -1"
         stop = true; // end input
      }
      if (!stop) { // make sure stop hasn't just been changed
         poly.setCoeff(coeff, exponent); // set coeff at exponent
      }
   }
   return input;
}

// --------------------------------------------------------------------------
// getCoeff
// Takes in an int exponent and returns the coeff of that exponent
int Poly::getCoeff(int exponent) const {
   if (exponent < 0 || exponent > maxExponent) { // invalid exponent
      return 0;
   } else {
      return coeffPtr[exponent]; // coeff at passed in exponent
   }
}

// --------------------------------------------------------------------------
// setCoeff
// Takes in an int coeff and and int exponent and sets the coeff
// at the given exponent
void Poly::setCoeff(int coeff, int exponent) {
   if (exponent >= 0) { // valid exponent
      if (exponent > maxExponent) { // make room for larger exponent
         int* temp = new int[exponent + 1](); // room for larger exponent
         for (int power = 0; power < maxExponent + 1; power++) {
            temp[power] = coeffPtr[power]; // copy old array
         }
         
         delete[] coeffPtr; // clear memory of old array
         coeffPtr = temp;   // replace old array with larger array
         maxExponent = exponent;   // replace old max with new max
      } // dont need to make room
      coeffPtr[exponent] = coeff; // set coefficient
   }
}

#endif
