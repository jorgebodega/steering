#include "MyVector.h"
#include <cmath>
#include <math.h>
#include <iostream>

#define PI 3.14159265

MyVector::MyVector() : x(0.0), y(0.0) {}
MyVector::MyVector(const double& a, const double& b): x(a), y(b) {}

MyVector& MyVector::operator+=(const MyVector& MyV){
   x = x + MyV.x;
   y = y + MyV.y;
   return *this;
 }

MyVector& MyVector::operator-=(const MyVector& MyV){
  x = x- MyV.x;
  y = y- MyV.y;
  return *this;
}

MyVector& MyVector::operator*=(const MyVector& MyV){
  x = x*MyV.x;
  y = y*MyV.y;
  return *this;
}

MyVector& MyVector::operator/=(const MyVector& MyV){
  x = x/MyV.x;
  y = y/MyV.y;
  return *this;
}

MyVector MyVector::operator-() const{
  return MyVector(-x,-y);
}

MyVector& MyVector::operator*=(const double& d){
  x = x*d;
  y = y*d;
  return *this;
}

MyVector& MyVector::operator/=(const double& d){
  x = x/d;
  y = y/d;
  return *this;
}

MyVector operator*(const MyVector& a, const double& d) {
  MyVector result = MyVector(a.x,a.y);
  return result *= d;
}

MyVector operator/(const MyVector& a, const double& d) {
  MyVector result = MyVector(a.x,a.y);
  return result /= d;
}

MyVector operator+(const MyVector& a, const MyVector& b) {
   MyVector result = MyVector(a.x,a.y);
   return result += b;
}

MyVector operator-(const MyVector& a, const MyVector& b) {
  MyVector result = MyVector(a.x,a.y);
  return result -= b;
}

MyVector operator*(const MyVector& a, const MyVector& b) {
  MyVector result = MyVector(a.x,a.y);
  return result *= b;
}

MyVector operator/(const MyVector& a, const MyVector& b) {
  MyVector result = MyVector(a.x,a.y);
  return result /= b;
}

double EuclideanNorm(const MyVector& a){
  return sqrt((a.x)*(a.x) + (a.y)*(a.y));
}

//Return the unit vector of the input
MyVector Normalize(const MyVector& a){
  return a/EuclideanNorm(a);
}

double DotProduct(const MyVector& a, const MyVector& b){
  return (a.x*b.x + a.y*b.y);
}

std::ostream& operator<<(std::ostream& os, MyVector const& a) {
    os << "The vector is (" << a.x << "," << a.y << ")." << std::endl;
    return os;
}

MyVector MaxPossibleValue(const MyVector& a, const double& value){
    MyVector b = a;
    if (EuclideanNorm(b) > value){
        b = Normalize(b);
        b = b * value;
    }
    return b;
}

double getAngle(const MyVector& a, const MyVector& b){
    double cosA = DotProduct(a,b)/(EuclideanNorm(a)*EuclideanNorm(b));
    return acos(cosA)*180/PI ;

}

double CalculateDistance(const MyVector& a, const MyVector& b){
    double diffY = a.y - b.y;
    double diffX = a.x - b.x;
    return sqrt((diffY * diffY) + (diffX * diffX));
}
/*double CalculateDistance2(const MyVector& a, const MyVector& b, int height, int width){
  double diffY1, diffY2, diffX1, diffX2;
    if (a.y > b.y){
       diffY1 = a.y - b.y;
       diffY2 = (height-10) - a.y + (b.y-10);
    }
    else{
       diffY1 = b.y - a.y;
       diffY2 = (height-10) - b.y + (a.y-10);
    }
    if (a.x > b.x){
       diffX1 = a.x - b.x;
       diffX2 = (width-10) - a.x + (b.x-10);
    }
    else{
       diffX1 = b.x - a.x;
       diffX2 = (width-10) - b.x + (a.x-10);
    }
    double minY = diffY1 < diffY2? diffY1 : diffY2;
    double minX = diffX1 < diffX2? diffX1 : diffX2;
    return sqrt((diffY * diffY) + (diffX * diffX));
} */
