#ifndef AVOID_H
#define AVOID_H
#include "MyVector.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iterator>
#define PI 3.14159265
class Avoid{
public:
	Avoid(double x, double y);
	MyVector getPosition();
    void update(const int& width,const int& height);
	sf::CircleShape shape;
private:
    MyVector currentPosition;

};

#endif // BOID_H
