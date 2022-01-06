#include <SFML/Graphics.hpp>
#include <boost/thread.hpp>
#include "include/SplitTimerCounter.h"


SplitTimerCounter timer;
sf::RenderWindow window(sf::VideoMode(200, 200), "Splits");

//Set up timer thread
void timerThread()
{
    while(window.isOpen())
    {
        timer.tick();
    }
}


int main(int argc, char ** argv)
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    //Start timer thread
    boost::thread thread1(timerThread);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::cout << " Minutes: " << timer.readMinutes() << " Seconds: " << timer.readSeconds() << std::endl;

        window.clear();
        window.draw(shape);
        window.display();
    }

    thread1.join();
    return 0;
}