#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>

class MyVector {
public:
  /* Constructor */
  MyVector();
  /* Copy Constructor */
  MyVector(const double& a, const double& b);
  MyVector& operator+=(const MyVector& MyV);
  MyVector& operator-=(const MyVector& MyV);
  MyVector& operator*=(const MyVector& MyV);
  MyVector& operator/=(const MyVector& MyV);
  /* Unary operator */
  MyVector operator-() const;

  /* Scalar operations. */
  MyVector& operator*=(const double& d);
  MyVector& operator/=(const double& d);

  double x;
  double y;
};
/* Just an overload of operators, changing the signature of the function.
The next four operations are between two MyVectors */
 MyVector operator+(const MyVector& a, const MyVector& b) ;
 MyVector operator-(const MyVector& a, const MyVector& b) ;
 MyVector operator*(const MyVector& a, const MyVector& b) ;
 MyVector operator/(const MyVector& a, const MyVector& b) ;

/* Operations between a MyVector and a double */
MyVector operator*(const MyVector& a, const double& d) ;
MyVector operator/(const MyVector& a, const double& d);

/* DotProdcut between two MyVectors */
double DotProduct(const MyVector& a, const MyVector& b);
/* Normalize the vector */
double EuclideanNorm(const MyVector& a);
/*Return the unit vector of the input */
MyVector Normalize(const MyVector& a);
/* How to print a MyVector */
std::ostream& operator<<(std::ostream& os, MyVector const& a);
/*If the magnitude of the vector is bigger than certain value,
then some swapping must be done. This is helpful for example
in the first part of the boid class, when a steering force is applied,
a maxforce and a maxvelocity must be checked in order for the fish
not to go crazy. */
MyVector MaxPossibleValue(const MyVector& a, const double& value);
double getAngle(const MyVector& a, const MyVector& b);
double CalculateDistance(const MyVector& a, const MyVector& b);
//double CalculateDistance2(const MyVector& a, const MyVector& b, int height, int width);
#endif
