#pragma warning(disable : 4996) //Disables error (4996) bec it is just vs freaking on us  
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio> 
#include <vector>
#include <map>
#include <Windows.h>
#include <fstream>
#include <array>        
#include <random>       
#include <chrono> 
#include <conio.h>
#define directory "C:\\Users\\lenovo\\Documents\\GitHub\\Kojack-Player\\Kojack player\\Kojack player\\resources/"
#define max_numsongs 10000
using namespace std;
using namespace sf;

int main() {
	sf::RenderWindow window(sf::VideoMode(800 , 600), "My window" , sf::Style::Default);
	
	
	sf::RectangleShape seperator(sf::Vector2f(800.0f, 10.0f)); 
	seperator.setFillColor(sf::Color::Red);
	seperator.setPosition(0, 500); 
	
	sf::RectangleShape play_button(sf::Vector2f(50, 50)); 
	play_button.setOrigin(25, 25);
	play_button.setPosition(400, 550);


	sf::RectangleShape backward_button(sf::Vector2f(50, 50));
	backward_button.setOrigin(25, 25);
	backward_button.setPosition(300, 550);
	

	sf::RectangleShape forwad_button(sf::Vector2f(50, 50));
	forwad_button.setOrigin(25, 25);
	forwad_button.setPosition(500, 550);


	sf::RectangleShape songs_list(sf::Vector2f(200, 50));
	songs_list.setFillColor(sf::Color::Green);
	songs_list.setPosition(0, 50); 


	sf::RectangleShape artist_list(sf::Vector2f(200, 50));
	artist_list.setFillColor(sf::Color::Yellow);
	artist_list.setPosition(200, 50);


	sf::RectangleShape album_list(sf::Vector2f(200, 50));
	album_list.setFillColor(sf::Color::Blue);
	album_list.setPosition(400, 50); 



	sf::RectangleShape genre_list(sf::Vector2f(200, 50));
	genre_list.setFillColor(sf::Color::Cyan);
	genre_list.setPosition(600, 50); 

	sf::Font font; 
	

	sf::Text welcome; 
	welcome.setString("Welcome to Kojack player");
	welcome.setPosition(400, 0); 



	sf::RectangleShape back_pic(sf::Vector2f(800.0f,600.0f)); 
	sf::Texture background_texture;
	background_texture.loadFromFile("untitled1.png"); 
	if (!background_texture.loadFromFile("untitled1.png")) {
		cout << "error while loading the background"; 
	}
	back_pic.setTexture(&background_texture); 
	
	



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type) {
				case sf::Event::Closed :
					window.close(); 
					break; 
				case sf::Event::MouseMoved :
					cout << "X: " << event.mouseMove.x << "\t Y: " << event.mouseMove.y << endl;
			}
			
		}
		window.draw(back_pic); 
		window.draw(welcome); 
		window.draw(genre_list);
		window.draw(album_list); 
		window.draw(songs_list); 
		window.draw(artist_list); 
		window.draw(backward_button); 
		window.draw(forwad_button);
		window.draw(play_button); 
		window.draw(seperator); 
		window.display(); 
		window.clear();
	}


	//system("Pause"); 
	return 0;
}