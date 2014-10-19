// @file poly.h
// @author Muhammed Saleh

#ifndef POLY_H
#define POLY_H

#include <iostream>
using namespace std;

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

class Poly {
   friend ostream& operator<<(ostream& output, const Poly& poly); // output
   friend istream& operator>>(istream& input, Poly& poly);        // input

public:
   // default constructor: coefficient and exponent params
   Poly(int coeff = 0, int exp = 0); 
   Poly(const Poly& other);          // copy constructor
   ~Poly();                          // destructor

   // arithmetic operators
   Poly operator+(const Poly& right) const;   // add two polynomials
   Poly operator-(const Poly& right) const;   // subtract two polynomials
   Poly operator*(const Poly& right) const;   // multiply two polynomials

   // boolean comparison operators
   bool operator==(const Poly& other) const;  // equality
   bool operator!=(const Poly& other) const;  // inequality
   
   // assignment operators
   Poly& operator=(const Poly& right);   // assign left to right
   Poly& operator+=(const Poly& right);  // assign left to left + right
   Poly& operator-=(const Poly& right);  // assign left to left - right
   Poly& operator*=(const Poly& right);  // assign left to left * right

   int getCoeff(int exponent) const;  // return coefficient at given exponent
   void setCoeff(int coeff, int exp); // set coefficient at given exponent

private:
	int* coeffPtr;   // array storing polynomial
	int maxExponent; // maximum polynomial for current array
};

#endif
