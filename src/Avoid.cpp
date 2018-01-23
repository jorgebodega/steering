#include "Avoid.h"
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

Avoid::Avoid(double x, double y){
  currentPosition = MyVector(x,y);
  shape.setRadius(10);
  shape.setPointCount(4);
}

MyVector Avoid::getPosition(){return currentPosition;}
void Avoid::update(const int& width,const int& height){
  if (currentPosition.x > width) { currentPosition.x =width -10;}
  if (currentPosition.x < 20) {currentPosition.x = 30;}
  if (currentPosition.y > height) {currentPosition.y = height-10;}
  if (currentPosition.y < 20) {currentPosition.y = 30;}
}
