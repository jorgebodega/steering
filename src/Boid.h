#ifndef BOID_H
#define BOID_H
#include "MyVector.h"
#include "Avoid.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iterator>
#define PI 3.14159265
class Boid
{
	typedef std::vector<Boid> Values;
public:
	typedef Values::iterator iterator;
	Boid(double x, double y);
	//void update();
	void update(const int& width,const int& height);
	void applyForceFrom(const MyVector& force);
	MyVector seekTo(const MyVector& goal);
	MyVector arriveTo(const MyVector& goal);
	//MyVector arriveTo(const MyVector& goal,int width, int height);
	void wanderTo(const std::vector<Avoid>& avoids, bool flag);
	void borders(const int& width,const int& height);
	void boundaries(const int& width,const int& height);
	void applyBehaviors(const std::vector<Boid>& boids, const std::vector<Avoid>& avoids, const MyVector& goal, bool flag);
    void applyBehaviorsForTarget( const std::vector<Avoid>& avoids, const MyVector& goal, bool flag);
	//void applyBehaviors(const std::vector<Boid>& boids, const MyVector& goal,int width, int height);
	void run(const int& width,const int& height);
	MyVector separationBetweenBoids(const std::vector<Boid>& boids);
    MyVector separationWithAvoids(const std::vector<Avoid>& avoids);
	MyVector getPosition();
	MyVector getDirection();
	MyVector getVelocity();
	double translateValue(double x, double a, double b, double c, double d);
	sf::CircleShape shape;
	Boid& operator[](int i);
	iterator begin();
	iterator end();
private:
      	MyVector currentPosition;
      	MyVector currentVelocity;
      	MyVector currentAcceleration;
      	MyVector directionDesired;
      	MyVector desired;
      	MyVector seekingSteer;
      	MyVector boundariesForce;
      	double maxVelocity;
      	double maxForce;
      	double radiusWander;
      	double angleWander;
		std::vector<Boid> myBoids;

};

#endif // BOID_H
