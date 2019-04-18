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
#define Low_rating_activator 3
using namespace std;
using namespace sf; 
struct song
{
	string name;
	string genre;
	string album;
	string artist;
	int year;
	int rating = 0;
	bool display = true;
}song_data[max_numsongs];
bool quit = false;
bool menu = false;
bool found;

int shuffled[max_numsongs], counter = 0;

bool shufflle = false;
vector<string> songs;



bool focus(sf::FloatRect sprite, sf::Vector2f mouse_position);
void show_songs(sf::RenderWindow& window); 
void get_all_files_names_within_folder(string folder);
void Read_MetaData();
void READ_RATING();




int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Kojack Player", sf::Style::Default);
	get_all_files_names_within_folder(directory);
	Read_MetaData();
	READ_RATING();
	






	string mod = "songs";
	sf::Vector2f mouse_position;
	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			mouse_position.x = sf::Mouse::getPosition(window).x;
			mouse_position.y = sf::Mouse::getPosition(window).y;
			if (mod == "welcome menu") {
				// //////////////function to show the login window 
				//login_window(); 
			}
			if (mod == "sign up") {

			}
			if (mod == "log in") {

			}
			if (mod == "songs") {
				window.clear();
				show_songs(window); 
			}
			if (mod == "album") {

			}
			if (mod == "artist") {

			}
			if (mod == "genre") {

			}
			window.display();
		}
		

		//window.display();
	}


	

	
 
	return 0;
}




bool focus(sf::FloatRect sprite, sf::Vector2f mouse_position) {
	if (sprite.contains(mouse_position)) {
		return true;
	}
	return false;
}

void show_songs(sf::RenderWindow& window) {
	window.clear();

	sf::RectangleShape back_pic;
	sf::Texture background_texture;
	sf::RectangleShape play_button;
	sf::Texture play_pic;
	sf::RectangleShape backward_button;
	sf::Texture backward_pic;
	sf::Sprite backward_sprite;
	sf::Sprite play_sprite;
	sf::RectangleShape forward_button;
	sf::Texture forward_pic;
	sf::Sprite forward_sprite;
	sf::RectangleShape shuffle_button;
	sf::Texture shuffle_pic;
	sf::Sprite shuffle_sprite;
	sf::RectangleShape songs_list;
	sf::RectangleShape artist_list;
	sf::RectangleShape album_list;
	sf::RectangleShape genre_list;
	sf::Font welcome_font;
	sf::Text welcome;


	play_button.setSize(sf::Vector2f(75, 75));
	play_button.setOrigin(25, 25);
	play_button.setPosition(400, 540);
	play_pic.loadFromFile("pause-play.png");
	play_button.setTexture(&play_pic);
	play_sprite.setTexture(play_pic);
	play_sprite.setOrigin(25, 25);
	play_sprite.setPosition(400, 550);



	backward_button.setSize(sf::Vector2f(75, 75));
	backward_button.setOrigin(25, 25);
	backward_button.setPosition(300, 540);
	backward_pic.loadFromFile("previous.png");
	backward_button.setTexture(&backward_pic);
	backward_sprite.setTexture(backward_pic);
	backward_sprite.setOrigin(25, 25);
	backward_sprite.setPosition(300, 550);




	forward_button.setSize(sf::Vector2f(75, 75));
	forward_button.setOrigin(25, 25);
	forward_button.setPosition(500, 540);
	forward_pic.loadFromFile("next.png");
	forward_button.setTexture(&forward_pic);
	forward_sprite.setTexture(forward_pic);
	forward_sprite.setOrigin(25, 25);
	forward_sprite.setPosition(500, 550);



	shuffle_button.setSize(sf::Vector2f(75, 75));
	shuffle_button.setOrigin(37.5, 37.5);
	shuffle_button.setPosition(150, 550);
	shuffle_pic.loadFromFile("shuffle.png");
	shuffle_button.setTexture(&shuffle_pic);
	shuffle_sprite.setTexture(shuffle_pic);
	shuffle_sprite.setPosition(150, 550);
	shuffle_sprite.setOrigin(12.5, 12.5);






	songs_list.setSize(sf::Vector2f(200, 50));
	songs_list.setFillColor(sf::Color::Magenta);
	songs_list.setPosition(0, 80);


	artist_list.setSize(sf::Vector2f(200, 50));
	artist_list.setFillColor(sf::Color::Yellow);
	artist_list.setPosition(200, 80);


	album_list.setSize(sf::Vector2f(200, 50));
	album_list.setFillColor(sf::Color::Blue);
	album_list.setPosition(400, 80);



	genre_list.setSize(sf::Vector2f(200, 50));
	genre_list.setFillColor(sf::Color::Cyan);
	genre_list.setPosition(600, 80);



	welcome_font.loadFromFile("parkway lush.ttf");
	welcome.setString("Welcome to Kojack player");
	welcome.setFont(welcome_font);
	welcome.setFillColor(sf::Color::Black);
	welcome.setPosition(200, 10);
	welcome.setCharacterSize(50);





	back_pic.setSize(sf::Vector2f(800.0f, 600.0f));
	background_texture.loadFromFile("wallpaper dark final final.png");
	if (!background_texture.loadFromFile("wallpaper dark final final.png")) {
		cout << "error while loading the background";
	}
	back_pic.setTexture(&background_texture);

	window.draw(back_pic);
	window.draw(shuffle_button);
	window.draw(genre_list);
	window.draw(album_list);
	window.draw(songs_list);
	window.draw(artist_list);
	window.draw(backward_button);
	window.draw(forward_button);
	window.draw(play_button);
	window.draw(welcome);

}



void get_all_files_names_within_folder(string folder)
{
	// Reads all .wav files in specific folder
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		int i = 0;
		do
		{
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				song_data[i].name = fd.cFileName;

				songs.push_back(fd.cFileName);
				i++;
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	for (int i = 0; i < songs.size(); i++)
	{
		song_data[i].name = songs[i];
	}
}

void Read_MetaData()
{
	fstream fs;
	fs.open("data.txt");
	for (int i = 0; i < songs.size(); i++)
	{
		getline(fs, song_data[i].artist);
		getline(fs, song_data[i].genre);
		getline(fs, song_data[i].album);
		fs >> song_data[i].year;
	}

}


void READ_RATING()
{
	fstream Rating_file;
	Rating_file.open("Rating.txt");
	for (int i = 0; i < songs.size(); i++)
	{
		Rating_file >> song_data[i].rating;
		if (song_data[i].rating <= Low_rating_activator && song_data[i].rating > 0)
		{
			int counter = 0;
			song_data[i].display = false;
			while (true)
			{
				if (song_data[i].name == songs[counter])
				{
					songs.erase(songs.begin() + counter);
					break;
				}
				counter++;
			}
		}
	}
	Rating_file.close();

}