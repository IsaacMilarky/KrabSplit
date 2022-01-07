#include <SFML/Graphics.hpp>
#include <boost/thread.hpp>
#include "include/SplitTimerCounter.h"
#include <sstream>

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
    //Load potential fonts.
    sf::Font freeFont;

    if(!freeFont.loadFromFile("/usr/share/fonts/gnu-free/FreeSans.otf"))
    {
        std::cout << "Error! Could not load free fonts from file" << std::endl;
        return -1;
    }


    //Define the sfml objects.
    //Top Timer Text
    sf::Text timerText;
    timerText.setFont(freeFont);
    timerText.setString("0:00:00.000");
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Green);

    window.setKeyRepeatEnabled(false);

    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    //Start timer thread
    boost::thread thread1(timerThread);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:

                    if(event.key.code == sf::Keyboard::F1)
                    {
                        timer.toggle();
                    }

                    break;
                default:
                    break;
            }
        }

        //Make a string stream to store data like a print.
        std::stringstream timerConcat;
        timerConcat << timer.readHours() << ":" << timer.readMinutes() << ":" << timer.readSeconds() << "." << timer.readMilliseconds();
        timerText.setString(timerConcat.str());

        //Then print.
        std::cout << "Hours: " << timer.readHours() << " Minutes: " << timer.readMinutes() << " Seconds: " << timer.readSeconds() << " Milliseconds: " << timer.readMilliseconds() << std::endl;

        window.clear();
        usleep(1000);
        //window.draw(shape);
        window.draw(timerText);
        window.display();
    }

    thread1.join();
    return 0;
}