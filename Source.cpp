#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

int main() 
{	
	sf::RenderWindow window(sf::VideoMode(640, 480), "My gyem",sf::Style::Titlebar | sf::Style::Close );//width,height,title
	sf::Event ev; //a window is a listener to the event!

	//GameLoop

	while (window.isOpen())
	{
		//event polling
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
					window.close();
					break;

			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}
		}

		//update

		//Render
		window.clear(sf::Color::Green); //clear the previous frame

		//draw the new stuff

		window.display(); //tell the app drawing is finished
	}


	


	//end of app!

	return 0;
}