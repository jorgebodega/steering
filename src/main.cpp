#include <iostream>
#include "Boid.cpp"
#include "Avoid.cpp"
#include "MyVector.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <math.h>
#include <vector>

#define PI 3.14159265
#define width 820
#define height 826
#define rt 1.4762f
// The frequency at which our update step will execute
#define UPDATE_RATE 1.0f / 60.0f
// The limit of how many times we can update if lagging
#define UPDATE_LIMIT 10

using namespace std;

int main(){
    // Create the main window
	sf::RenderWindow TestWindow(sf::VideoMode(1188, 840), "Cursor test!");

	// -------------------- BACKGROUND ----------
	sf::Texture texture;
	if (!texture.loadFromFile("Gallery/background.jpg")){
	    system("echo No se pudo cargar la textura&pause");
		return EXIT_FAILURE;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);

    sf::RectangleShape avoid_box(sf::Vector2f(int(55),int(55)));
    avoid_box.setPosition(int(1521), int(555));
    avoid_box.setFillColor(sf::Color(0,0,0,0));
    sf::RectangleShape alignment_box(sf::Vector2f(int(55),int(55)));
    alignment_box.setPosition(int(1521), int(625));
    alignment_box.setFillColor(sf::Color(0,0,0,0));
    sf::RectangleShape cohesion_box(sf::Vector2f(int(55),int(55)));
    cohesion_box.setPosition(int(1521), int(705));
    cohesion_box.setFillColor(sf::Color(0,0,0,0));
    sf::RectangleShape crowding_box(sf::Vector2f(int(55),int(55)));
    crowding_box.setPosition(int(1521), int(778));
    crowding_box.setFillColor(sf::Color(0,0,0,0));

	// ---------------- MUSIC -------------------
	sf::SoundBuffer buffer;
	if(!buffer.loadFromFile("music/Pokemon.ogg")){
		system("echo No se pudo cargar la textura&pause");
		return EXIT_FAILURE;
	}
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

	// ---------------- TIMESTEP -------------------
	// The sf::Clock class will allow us to keep track of time
    sf::Clock clock;
    // This variable accumulates the time spent during render steps
    float total_time = 0.0f;
    // This variable holds the amount of time the last render step took
    float frame_time = 0.0f;
    // This variable keeps track of how many times the update step ran
    int update_count = 0;

    bool avoid_flag = true;

	srand(time(NULL));

	//---------------- Configuration of the target------------------------
	Boid boidTarget = Boid((rand() % width), (rand() % height));
	boidTarget.shape.setFillColor(sf::Color::Yellow);
	boidTarget.shape.setOrigin(10.f,10.f);
	boidTarget.shape.setPosition(TestWindow.getSize().x,TestWindow.getSize().y);

	//---------------- Configuration of the group------------------------
	std::vector<Boid> boids;
    std::vector<Avoid> avoids;

	while (TestWindow.isOpen()){
		// Get how long it took to draw the last frame
        frame_time = clock.restart().asSeconds();
        // Add that time to the total time
        total_time += frame_time;
        // Reset our counter
        update_count = 0;

        // While the total amount of time spend on the render step is
        // greater or equal to the update rate (1/60) and we have
        // not executed the update step 10 times then do the loop
        // If the counter hits 10 we break because it means that the
        // render step is lagging behind the update step
        while(total_time >= UPDATE_RATE && update_count < UPDATE_LIMIT){
			sf::Event TestEvent;
			while(TestWindow.pollEvent(TestEvent)){
				if (TestEvent.type == sf::Event::Closed) TestWindow.close();
				if (TestEvent.type == sf::Event::KeyPressed && (TestEvent.key.code== sf::Keyboard::Escape)) TestWindow.close();
				if (TestEvent.type == sf::Event::KeyPressed && (TestEvent.key.code== sf::Keyboard::M)) sound.pause();
				if (TestEvent.type == sf::Event::KeyPressed && (TestEvent.key.code== sf::Keyboard::U)) sound.play();
                if (TestEvent.type == sf::Event::KeyPressed && (TestEvent.key.code== sf::Keyboard::X)) avoids.clear();
                if (TestEvent.type == sf::Event::KeyPressed && (TestEvent.key.code== sf::Keyboard::D)) if(!avoids.empty()) avoids.pop_back();
                if (TestEvent.type == sf::Event::KeyPressed && (TestEvent.key.code== sf::Keyboard::F)) if(!boids.empty()) boids.pop_back();
                if (TestEvent.type == sf::Event::KeyPressed && (TestEvent.key.code== sf::Keyboard::C)) boids.clear();
                if (TestEvent.type == sf::Event::KeyPressed && (TestEvent.key.code== sf::Keyboard::Q)){
                    avoid_flag = !avoid_flag;
                }
				if (TestEvent.type == sf::Event::MouseButtonPressed && TestEvent.mouseButton.button==sf::Mouse::Left) {
                    //mouse button avoid

    					Boid newBoidMouse = Boid(sf::Mouse::getPosition(TestWindow).x,sf::Mouse::getPosition(TestWindow).y);
    					newBoidMouse.shape.setFillColor(sf::Color::Black);
    					newBoidMouse.shape.setOrigin(10.f,10.f);
    					newBoidMouse.shape.setPosition(TestWindow.getSize().x/2.f,TestWindow.getSize().y/2.f);
    					boids.push_back(newBoidMouse);
				}
                if (TestEvent.type == sf::Event::MouseButtonPressed && TestEvent.mouseButton.button==sf::Mouse::Right) {
                    Avoid newAvoidMouse = Avoid(sf::Mouse::getPosition(TestWindow).x,sf::Mouse::getPosition(TestWindow).y);
                    newAvoidMouse.shape.setFillColor(sf::Color::Red);
                    newAvoidMouse.shape.setOrigin(10.f,10.f);
                    newAvoidMouse.shape.setPosition(TestWindow.getSize().x/2.f,TestWindow.getSize().y/2.f);
                    avoids.push_back(newAvoidMouse);
				}
			}
			// Subtract the udpate frequency from the total time
			total_time -= UPDATE_RATE;
			// Increase the counter
			update_count++;
		}

		TestWindow.clear();
		TestWindow.draw(sprite);
		boidTarget.wanderTo(avoids, avoid_flag);
		boidTarget.shape.setPosition(boidTarget.getPosition().x,boidTarget.getPosition().y );
		boidTarget.shape.setRotation(atan2(boidTarget.getVelocity().y,boidTarget.getVelocity().x)*180/PI+90);
		boidTarget.update((width),(height));
		TestWindow.draw(boidTarget.shape);

		for (uint i=0; i<boids.size();i++){
			//boids[i].applyBehaviors(boids,boidTarget.getPosition(),width, height);
			boids[i].applyBehaviors(boids,avoids,boidTarget.getPosition(), avoid_flag);
			boids[i].shape.setPosition(boids[i].getPosition().x,boids[i].getPosition().y );
			boids[i].shape.setRotation(atan2(boids[i].getVelocity().y,boids[i].getVelocity().x)*180/PI+90);
			boids[i].update((width),(height));
			TestWindow.draw(boids[i].shape);
		}

        for (uint i=0; i<avoids.size();i++){
            avoids[i].shape.setPosition(avoids[i].getPosition().x,avoids[i].getPosition().y );
            avoids[i].update((width),(height));
            TestWindow.draw(avoids[i].shape);
        }

		TestWindow.display();
	}
	return 0;
}
