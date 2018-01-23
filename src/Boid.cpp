#include "Boid.h"
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

/**
Constructor: The idea here is to set the given currentPosition
to the vector, a certain velocity and null acceleration.
Also setting the max Parameters of Steering.
*/
Boid::Boid(double x, double y){
  currentPosition = MyVector(x,y);
  currentVelocity = MyVector(0,-0.5);
  currentAcceleration = MyVector(0,0);
  maxVelocity  = 0.35;
  maxForce = 0.05;
  directionDesired = MyVector(0,0);
  // radiusWander=100;
  angleWander = 0;
  shape.setRadius(10);
  shape.setPointCount(3);
}

/**
Update the velocity by just adding the acceleration,
checking if its bigger than the maxVelocity
and setting the acceleration back to zero.
*/
void Boid::update(const int& width,const int& height){
  currentVelocity += currentAcceleration;
  currentVelocity = MaxPossibleValue(currentVelocity,maxVelocity);
  currentPosition += currentVelocity ;
  currentAcceleration *= 0;
  if (currentPosition.x > width) { currentPosition.x =width -10;}
  if (currentPosition.x < 20) {currentPosition.x = 30;}
  if (currentPosition.y > height) {currentPosition.y = height-10;}
  if (currentPosition.y < 20) {currentPosition.y = 30;}
}

/**
Changes the acceleration by adding a force. Taking
here that the mass is one.
*/
void Boid::applyForceFrom(const MyVector& force){currentAcceleration+=force;}

/**We need the substraction between goal and current currentPosition
 to get a direction. This direction will be scaled to max parameters*/

MyVector Boid::arriveTo(const MyVector& goal){
    /*double diffY1, diffY2, diffX1, diffX2;
    if (goal.y > currentPosition.y){
       diffY1 = goal.y - currentPosition.y;
       diffY2 = (height-10) - goal.y + (currentPosition.y-10);
    }
    else{
       diffY1 = currentPosition.y - goal.y;
       diffY2 = (height-10) - currentPosition.y + (goal.y-10);
    }
    if (goal.x > currentPosition.x){
       diffX1 = goal.x - currentPosition.x;
       diffX2 = (width-10) - goal.x + (currentPosition.x-10);
    }
    else{
       diffX1 = currentPosition.x - goal.x;
       diffX2 = (width-10) - currentPosition.x + (goal.x-10);
    }
      double minY = diffY1 < diffY2? diffY1 : diffY2;
      double minX = diffX1 < diffX2? diffX1 : diffX2;
      directionDesired = MyVector(minX,minY); */
      directionDesired = goal -currentPosition;
      double mag= EuclideanNorm(directionDesired);
      directionDesired = Normalize(directionDesired);
      if (mag <150){
            double mapp = translateValue(mag,0,100,0,maxVelocity);
            directionDesired*= mapp;
      } else{
            directionDesired*= maxVelocity;
      }
      //MyVector seekingSteer;
      seekingSteer = directionDesired - currentVelocity;
      seekingSteer = MaxPossibleValue(seekingSteer,maxForce);
      //applyForceFrom(seekingSteer);
      return seekingSteer;
}

void Boid::wanderTo(const std::vector<Avoid>& avoids, bool flag){
    srand(time(NULL));
    double wanderRadius = 1;
    double wanderDistance = 80;
    double deltaAngle = 50;
    int randNum = rand() % static_cast<int> (deltaAngle - (-deltaAngle) + 1) + (-deltaAngle);
    angleWander+=randNum;

    MyVector circlePosition = getVelocity();
    circlePosition = Normalize(circlePosition);
    circlePosition *= wanderDistance;
    circlePosition += getPosition();
    double heading = atan2(this->getVelocity().y, this->getVelocity().x)*180/PI;
    MyVector circleOff = MyVector(wanderRadius*cos(angleWander+heading),wanderRadius*sin(angleWander+heading));

    MyVector target = circlePosition;
    target+=circleOff;
    applyBehaviorsForTarget(avoids,target,flag);
}

MyVector Boid::seekTo(const MyVector& goal){

  directionDesired = goal -currentPosition;
  directionDesired = Normalize(directionDesired);
  directionDesired*= maxVelocity;
  //MyVector seekingSteer;
  seekingSteer = directionDesired - currentVelocity;
  seekingSteer = MaxPossibleValue(seekingSteer,maxForce);
  return seekingSteer;
  // applyForceFrom(seekingSteer);
}

void Boid::applyBehaviorsForTarget(const std::vector<Avoid>& avoids, const MyVector& goal, bool flag){
    if(flag){
        MyVector separateAvoidForce = separationWithAvoids(avoids);
        separateAvoidForce*=3.5;
        applyForceFrom(separateAvoidForce);
    }
    MyVector seekForce = seekTo(goal);
    seekForce*=1;
    applyForceFrom(seekForce);
}

void Boid::applyBehaviors(const std::vector<Boid>& boids, const std::vector<Avoid>& avoids, const MyVector& goal, bool flag) {
    if(flag){
        MyVector separateAvoidForce = separationWithAvoids(avoids);
        separateAvoidForce*=3;
        applyForceFrom(separateAvoidForce);
    }
     MyVector separateForce = separationBetweenBoids(boids);
     MyVector seekForce = arriveTo(goal);
     separateForce*=1.2;
     seekForce*=1;
     applyForceFrom(separateForce);
     applyForceFrom(seekForce);
}

MyVector Boid::separationBetweenBoids(const std::vector<Boid>& boids){
    double separationWanted = 12*3;
    MyVector sum = MyVector(0,0);
    int count = 0;
    // For every boid in the system, check if it's too close
    for (Boid other: boids) {
      double dist = CalculateDistance(getPosition(), other.getPosition());
      // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
      if ((dist > 0) && (dist < separationWanted)) {
        // Calculate vector pointing away from neighbor
        MyVector diff = getPosition()- other.getPosition();
        diff = Normalize(diff);
        diff /=dist;        // Weight by distance
        sum+=diff;
        count++;            // Keep track of how many
      }
    }
    // Average -- divide by how many
    if (count > 0) {
      sum/=count;
      // Our desired vector is the average scaled to maximum speed
      sum= Normalize(sum);
      sum*=maxVelocity;
      // Implement Reynolds: Steering = Desired - Velocity
      sum-=currentVelocity;
      sum=MaxPossibleValue(sum,maxForce);
    }
    return sum;
  }
  MyVector Boid::separationWithAvoids(const std::vector<Avoid>& avoids){
      double separationWanted = 12*3;
      MyVector sum = MyVector(0,0);
      int count = 0;
      // For every boid in the system, check if it's too close
      for (Avoid other: avoids) {
        double dist = CalculateDistance(getPosition(), other.getPosition());
        // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
        if ((dist > 0) && (dist < separationWanted)) {
          // Calculate vector pointing away from neighbor
          MyVector diff = getPosition()- other.getPosition();
          diff = Normalize(diff);
          diff /=dist;        // Weight by distance
          sum+=diff;
          count++;            // Keep track of how many
        }
      }
      // Average -- divide by how many
      if (count > 0) {
        sum/=count;
        // Our desired vector is the average scaled to maximum speed
        sum= Normalize(sum);
        sum*=maxVelocity;
        // Implement Reynolds: Steering = Desired - Velocity
        sum-=currentVelocity;
        sum=MaxPossibleValue(sum,maxForce);
      }
      return sum;
    }

MyVector Boid::getPosition(){return currentPosition;}
MyVector Boid::getDirection(){return directionDesired;}
MyVector Boid::getVelocity(){return currentVelocity;}

// a,b old values.
double Boid::translateValue(double x, double a, double b, double c, double d){
    double y;
    if (std::abs(a-b) == 0){y=0;}
    else{
        y = (x-a)/(b-a) * (d-c) + c;
    }return y;
}

Boid& Boid::operator[](int i){return myBoids[i];}
Boid::iterator Boid::begin(){return myBoids.begin();}
Boid::iterator Boid::end(){return myBoids.end();}
