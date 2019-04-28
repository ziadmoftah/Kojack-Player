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
#include <set>
#include <random>       
#include <chrono> 
#include <conio.h>
#define directory "C:\\Users\\lenovo\\Documents\\GitHub\\Kojack-Player\\Kojack player\\Kojack player\\resources/"
#define users_directory "C:\\Users\\lenovo\\Documents\\GitHub\\Kojack-Player\\Kojack player\\Kojack player\\Data/" 
#define Imgs_directory "C:\\Users\\lenovo\\Documents\\GitHub\\Kojack-Player\\Kojack player\\Kojack player\\Imgs/"
#define max_numsongs 10000
#define Low_rating_activator 2
#define Highest_rating 5


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
struct second_window {
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
	sf::Texture album_pic;
	sf::Sprite album_sprite;
	sf::Texture genre_pic;
	sf::Sprite genre_sprite;
	sf::Texture song_pic;
	sf::Sprite song_sprite;
	sf::Texture artist_pic;
	sf::Sprite artist_sprite;
	sf::CircleShape search_box;
	sf::Text seacr_text;
	sf::RectangleShape rating_bar;
	RectangleShape music_box[20];
	Text name_music[20];
	Font use_font;
	sf::RectangleShape sorting_button[2];
	sf::Texture sorting_pic[2];
	sf::Texture rating_pic;
}while_playing;
struct user
{
	string name;
	string password;
}users_data[16];



//////// FUCTIONS RELATED TO GUI ///*****

void wpage(sf::RenderWindow& window, sf::Event& event, string& mod, sf::Vector2f& mouse_position);
bool focus(sf::FloatRect sprite, sf::Vector2f mouse_position);
void song_tab(sf::RenderWindow& window, sf::Vector2f& mouse_position, sf::Event& event, string& mod, sf::Music& music, bool& playing);
void album_tab(sf::RenderWindow& window, sf::Vector2f& mouse_position, sf::Event& event, string& mod, sf::Music& music, bool& playing);
void artist_tab(sf::RenderWindow& window, sf::Vector2f& mouse_position, sf::Event& event, string& mod, sf::Music& music, bool& playing);
void genre_tab(sf::RenderWindow& window, sf::Vector2f& mouse_position, sf::Event& event, string& mod, sf::Music& music, bool& playing);
void searching_window();

////// LOGICAL FUCNTIONS /////***
void get_all_files_names_within_folder(string folder);
void playMusic(const std::string& filename, int &play_num, bool& playing, sf::Music& music);
vector<string> View_song(int choice, string name);
void read_users();
bool signup(string username, string password);
bool login(string current_user, string password);
void READ_RATING();
void Read_MetaData();
vector<string> View_all(int choice);
void playback(vector<string>names, int play_num);
void shuffle(vector<string>ToShuffle);
void check_order(int& index_of_playing_song);
vector<string> sorting(int x);
void rate(string name, int& rating);




int NumUsers = 0;
int index_of_playing_song;
bool quit = false;
bool menu = false;
bool found;
int shuffled[max_numsongs], counter = 0;
bool shufflle = false;
string current_user;
vector<string> songs;
vector<string> sorted_songs;
int is_songs_sorted = 0;
bool playing = false;
vector <string> songs_by_a_default_thing;
int showanythingiwant;
sf::Music music;
int number_of_current_songs = 0;
int rating = 0;
string playing_song_name = "";
string userinput_search = ""; 



///// welcome window 
sf::Vector2f mouse_position;
sf::RectangleShape back_pic;
sf::Texture background_texture;
sf::RectangleShape done_button;
sf::Texture done_texture;
sf::Sprite donesprite;
std::string userinput;
sf::Text username;
sf::RectangleShape usertextbox;
sf::RectangleShape pwtextbox;
sf::Text password;
std::string pwinput;
string shown_password = "";
sf::Text error_message[2];
sf::Font error_message_font;
///////*

int main() {
	get_all_files_names_within_folder(directory);
	read_users();

	string mod = "welcome";

	sf::RenderWindow starting_window(sf::VideoMode(600, 300), "Kojack Player", sf::Style::Default);

	error_message_font.loadFromFile(Imgs_directory"Roboto-ThinItalic.ttf");
	error_message[0].setFont(error_message_font);
	error_message[0].setCharacterSize(25);
	error_message[0].setFillColor(sf::Color::Red);
	error_message[0].setStyle(sf::Text::Bold);
	error_message[0].setPosition(50, 135);
	error_message[0].setString("Username already taken");



	error_message[1].setFont(error_message_font);
	error_message[1].setCharacterSize(25);
	error_message[1].setFillColor(sf::Color::Red);
	error_message[1].setStyle(sf::Text::Bold);
	error_message[1].setPosition(50, 205);
	error_message[1].setString("Invalid username or password");


	usertextbox.setSize(sf::Vector2f(175, 21));
	usertextbox.setOrigin(85, 143);
	usertextbox.setPosition(265, 242);


	pwtextbox.setSize(sf::Vector2f(175, 21));
	pwtextbox.setOrigin(85, 143);
	pwtextbox.setPosition(265, 319);


	done_button.setSize(sf::Vector2f(165, 96));
	done_button.setOrigin(85, 143);
	done_button.setPosition(300, 375);
	done_texture.loadFromFile(Imgs_directory"done button.png");
	done_button.setTexture(&done_texture);
	donesprite.setTexture(done_texture);
	donesprite.setOrigin(85, 143);
	donesprite.setPosition(300, 375);


	sf::Font myfont;
	myfont.loadFromFile(Imgs_directory"parkway lush.ttf");
	username.setFont(myfont);
	username.setFillColor(sf::Color::Blue);
	username.setPosition(265, 235);
	username.setOrigin(85, 143);


	password.setFont(myfont);
	password.setFillColor(sf::Color::Blue);
	password.setPosition(265, 311);
	password.setOrigin(85, 143);



	back_pic.setSize(sf::Vector2f(600.0f, 300.0f));
	background_texture.loadFromFile(Imgs_directory"datawindow.png");
	if (!background_texture.loadFromFile(Imgs_directory"datawindow.png")) {
		cout << "error while loading the background";
	}
	back_pic.setTexture(&background_texture);
	int windicator = 0;
	while (starting_window.isOpen())
	{
		sf::Event starting;
		while (starting_window.pollEvent(starting))
		{

			if (starting.type == sf::Event::Closed) {
				starting_window.close();
			}
			mouse_position.x = sf::Mouse::getPosition(starting_window).x;
			mouse_position.y = sf::Mouse::getPosition(starting_window).y;
			cout << mouse_position.x << "\t\t" << mouse_position.y << endl;
			if (mod == "welcome")
			{
				starting_window.clear();
				wpage(starting_window, starting, mod, mouse_position);

			}
			if (mod == "login")
			{
				starting_window.clear();
				starting_window.draw(back_pic);
				starting_window.draw(done_button);
				starting_window.draw(usertextbox);
				starting_window.draw(pwtextbox);
				if (focus(usertextbox.getGlobalBounds(), mouse_position))
				{
					if (starting.type == sf::Event::MouseButtonPressed &&starting.mouseButton.button == sf::Mouse::Left)
					{
						windicator = 1;
					}
				}
				if (focus(pwtextbox.getGlobalBounds(), mouse_position))
				{
					if (starting.type == sf::Event::MouseButtonPressed &&starting.mouseButton.button == sf::Mouse::Left)
					{
						windicator = 2;
					}
				}
				if (starting.type == sf::Event::TextEntered)
				{
					if (starting.text.unicode < 128 && starting.text.unicode != 8 && windicator == 1)
					{
						userinput += starting.text.unicode;
						username.setString(userinput);
					}
					if (starting.text.unicode == 8 && userinput.size() > 0 && windicator == 1)
					{
						userinput.erase(userinput.begin() + userinput.size() - 1);
						username.setString(userinput);
					}

				}
				starting_window.draw(username);
				if (starting.type == sf::Event::TextEntered)
				{
					if (starting.text.unicode < 128 && starting.text.unicode != 8 && windicator == 2)
					{
						pwinput += starting.text.unicode;
						shown_password += "*";
						password.setString(shown_password);
					}
					else if (starting.text.unicode == 8 && pwinput.size() > 0 && windicator == 2 && shown_password.size() > 0)
					{
						pwinput.erase(pwinput.begin() + pwinput.size() - 1);
						shown_password.erase(shown_password.size() - 1);
						password.setString(shown_password);
					}


				}
				starting_window.draw(password);
				if (focus(done_button.getGlobalBounds(), mouse_position))
				{
					if (starting.type == sf::Event::MouseButtonPressed &&starting.mouseButton.button == sf::Mouse::Left)
					{
						if (login(userinput, pwinput) == true) {
							starting_window.close();
						}
						else {
							starting_window.draw(error_message[1]);
						}
					}
				}
			}
			if (mod == "sign up")
			{

				starting_window.clear();
				starting_window.draw(back_pic);
				starting_window.draw(done_button);
				starting_window.draw(usertextbox);
				starting_window.draw(pwtextbox);
				if (focus(usertextbox.getGlobalBounds(), mouse_position))
				{
					if (starting.type == sf::Event::MouseButtonPressed &&starting.mouseButton.button == sf::Mouse::Left)
					{
						windicator = 1;
					}
				}
				if (focus(pwtextbox.getGlobalBounds(), mouse_position))
				{
					if (starting.type == sf::Event::MouseButtonPressed &&starting.mouseButton.button == sf::Mouse::Left)
					{
						windicator = 2;
					}
				}
				if (starting.type == sf::Event::TextEntered)
				{
					if (starting.text.unicode < 128 && starting.text.unicode != 8 && windicator == 1)
					{
						userinput += starting.text.unicode;
						username.setString(userinput);
					}
					if (starting.text.unicode == 8 && userinput.size() > 0 && windicator == 1)
					{
						userinput.erase(userinput.begin() + userinput.size() - 1);
						username.setString(userinput);
					}

				}
				starting_window.draw(username);
				if (starting.type == sf::Event::TextEntered)
				{
					if (starting.text.unicode < 128 && starting.text.unicode != 8 && windicator == 2)
					{
						pwinput += starting.text.unicode;
						shown_password += "*";
						password.setString(shown_password);
					}
					else if (starting.text.unicode == 8 && pwinput.size() > 0 && windicator == 2 && shown_password.size() > 0)
					{
						pwinput.erase(pwinput.begin() + pwinput.size() - 1);
						shown_password.erase(shown_password.size() - 1);
						password.setString(shown_password);
					}


				}
				starting_window.draw(password);
				if (focus(done_button.getGlobalBounds(), mouse_position))
				{
					if (starting.type == sf::Event::MouseButtonPressed &&starting.mouseButton.button == sf::Mouse::Left)
					{
						if (signup(userinput, pwinput) == true)
							starting_window.close();
						else {
							starting_window.draw(error_message[0]);
						}
					}
				}
			}
			starting_window.display();
			starting_window.clear();

		}

	}






	sf::RenderWindow window(sf::VideoMode(800, 600), "Kojack Player", sf::Style::Default);
	window.setKeyRepeatEnabled(false); 
	mod = "song";
	Read_MetaData();
	READ_RATING();
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
			//cout << mouse_position.x << "\t" << mouse_position.y << endl;
		}
		if (mod == "song") {
			window.clear();
			song_tab(window, mouse_position, event, mod, music, playing);
		}
		if (mod == "album") {
			window.clear();
			album_tab(window, mouse_position, event, mod, music, playing);
		}
		if (mod == "artist") {
			window.clear();
			artist_tab(window, mouse_position, event, mod, music, playing);

		}
		if (mod == "genre") {
			window.clear();
			genre_tab(window, mouse_position, event, mod, music, playing);
		}
		window.display();
		window.clear();


	}






	return 0;
}




bool focus(sf::FloatRect sprite, sf::Vector2f mouse_position) {
	if (sprite.contains(mouse_position)) {

		return true;
	}
	return false;
}

void song_tab(sf::RenderWindow& window, sf::Vector2f& mouse_position, sf::Event& event, string& mod, sf::Music& music, bool& playing) {
	window.clear();


	while_playing.use_font.loadFromFile(Imgs_directory"Roboto-ThinItalic.ttf");


	while_playing.sorting_button[0].setSize(sf::Vector2f(50, 75));
	while_playing.sorting_pic[0].loadFromFile(Imgs_directory"arrow dn.png");
	while_playing.sorting_button[0].setPosition(550, 100);
	while_playing.sorting_button[0].setTexture(&while_playing.sorting_pic[0]);
	while_playing.sorting_button[0].setFillColor(sf::Color::Yellow);

	while_playing.sorting_button[1].setSize(sf::Vector2f(50, 75));
	while_playing.sorting_pic[1].loadFromFile(Imgs_directory"arrow up.png");
	while_playing.sorting_button[1].setPosition(500, 100);
	while_playing.sorting_button[1].setTexture(&while_playing.sorting_pic[1]);
	while_playing.sorting_button[1].setFillColor(sf::Color::Magenta);

	float x = 55;
	for (int i = 0; i < songs.size(); ++i){
		while_playing.music_box[i].setSize(Vector2f(400, 30));
		while_playing.music_box[i].setPosition(3, x);
		while_playing.music_box[i].setFillColor(Color::Transparent);
		while_playing.name_music[i].setFont(while_playing.use_font);
		while_playing.name_music[i].setStyle(Text::Bold);
		if (is_songs_sorted) {
			while_playing.name_music[i].setString(sorted_songs[i]);

		}
		else {
			while_playing.name_music[i].setString(songs[i]);
		}
		if ( i == index_of_playing_song && !shufflle ) {
			while_playing.name_music[i].setColor(Color::Magenta);
		}
		else {
			while_playing.name_music[i].setColor(Color::Blue);
		}
		while_playing.name_music[i].setPosition(5, x);
		while_playing.name_music[i].setCharacterSize(24);
		x += 33;


	}

	while_playing.search_box.setRadius(30);
	while_playing.search_box.setPosition(10, 530);
	while_playing.search_box.setFillColor(sf::Color::Green);
	if (focus(while_playing.search_box.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			searching_window(); 

		}
	}




	while_playing.rating_bar.setSize(sf::Vector2f(200, 40));
	while_playing.rating_bar.setPosition(600, 535);
	while_playing.rating_pic.loadFromFile(Imgs_directory"rating 0.png");
	while_playing.rating_bar.setTexture(&while_playing.rating_pic);

	if (rating == 1)
	{
		while_playing.rating_pic.loadFromFile(Imgs_directory"rating1.png");
	}
	if (rating == 2)
	{
		while_playing.rating_pic.loadFromFile(Imgs_directory"rating2.png");
	}
	if (rating == 3)
	{
		while_playing.rating_pic.loadFromFile(Imgs_directory"rating3.png");
	}
	if (rating == 4)
	{
		while_playing.rating_pic.loadFromFile(Imgs_directory"rating4.png");
	}
	if (rating == 5)
	{
		while_playing.rating_pic.loadFromFile(Imgs_directory"rating5.png");
	}
	if (focus(while_playing.rating_bar.getGlobalBounds(), mouse_position) && mouse_position.x > 600 && mouse_position.x < 635)
	{
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			rating = 1;
			rate(playing_song_name, rating);

		}
	}
	if (focus(while_playing.rating_bar.getGlobalBounds(), mouse_position) && mouse_position.x > 640 && mouse_position.x < 675)
	{
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			rating = 2;
			rate(playing_song_name, rating);
		}
	}
	if (focus(while_playing.rating_bar.getGlobalBounds(), mouse_position) && mouse_position.x > 680 && mouse_position.x < 715)
	{
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			rating = 3;
			rate(playing_song_name, rating);
		}
	}
	if (focus(while_playing.rating_bar.getGlobalBounds(), mouse_position) && mouse_position.x > 720 && mouse_position.x < 755)
	{
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			rating = 4;
			rate(playing_song_name, rating);
		}
	}
	if (focus(while_playing.rating_bar.getGlobalBounds(), mouse_position) && mouse_position.x > 760 && mouse_position.x < 795)
	{
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			rating = 5;
			rate(playing_song_name, rating);
		}
	}









	while_playing.play_button.setSize(sf::Vector2f(75, 75));
	while_playing.play_button.setOrigin(25, 25);
	while_playing.play_button.setPosition(400, 540);
	while_playing.play_pic.loadFromFile(Imgs_directory"pause-play.png");
	while_playing.play_button.setTexture(&while_playing.play_pic);
	while_playing.play_sprite.setTexture(while_playing.play_pic);
	while_playing.play_sprite.setOrigin(25, 25);
	while_playing.play_sprite.setPosition(400, 550);


	while_playing.backward_button.setSize(sf::Vector2f(75, 75));
	while_playing.backward_button.setOrigin(25, 25);
	while_playing.backward_button.setPosition(300, 540);
	while_playing.backward_pic.loadFromFile(Imgs_directory"previous.png");
	while_playing.backward_button.setTexture(&while_playing.backward_pic);
	while_playing.backward_sprite.setTexture(while_playing.backward_pic);
	while_playing.backward_sprite.setOrigin(25, 25);
	while_playing.backward_sprite.setPosition(300, 550);




	while_playing.forward_button.setSize(sf::Vector2f(75, 75));
	while_playing.forward_button.setOrigin(25, 25);
	while_playing.forward_button.setPosition(500, 540);
	while_playing.forward_pic.loadFromFile(Imgs_directory"next.png");
	while_playing.forward_button.setTexture(&while_playing.forward_pic);
	while_playing.forward_sprite.setTexture(while_playing.forward_pic);
	while_playing.forward_sprite.setOrigin(25, 25);
	while_playing.forward_sprite.setPosition(500, 550);



	while_playing.shuffle_button.setSize(sf::Vector2f(60, 60));
	while_playing.shuffle_button.setOrigin(37.5, 37.5);
	while_playing.shuffle_button.setPosition(145, 565);
	if (!shufflle) {
		while_playing.shuffle_pic.loadFromFile(Imgs_directory"not shuffled.png");
	}
	else {
		while_playing.shuffle_pic.loadFromFile(Imgs_directory"shuffled.png");
	}
	while_playing.shuffle_button.setTexture(&while_playing.shuffle_pic);
	while_playing.shuffle_sprite.setTexture(while_playing.shuffle_pic);
	while_playing.shuffle_sprite.setPosition(145, 570);
	while_playing.shuffle_sprite.setOrigin(12.5, 12.5);






	while_playing.songs_list.setSize(sf::Vector2f(200, 50));
	while_playing.songs_list.setPosition(0, 0);
	while_playing.song_pic.loadFromFile(Imgs_directory"songs  pressed.png");
	while_playing.songs_list.setTexture(&while_playing.song_pic);
	while_playing.song_sprite.setTexture(while_playing.song_pic);
	while_playing.song_sprite.setPosition(0, 0);



	while_playing.artist_list.setSize(sf::Vector2f(200, 50));
	while_playing.artist_list.setPosition(200, 0);
	while_playing.artist_pic.loadFromFile(Imgs_directory"artists unpressed.png");
	while_playing.artist_list.setTexture(&while_playing.artist_pic);
	while_playing.artist_sprite.setTexture(while_playing.artist_pic);
	while_playing.artist_sprite.setPosition(200, 0);





	while_playing.album_list.setSize(sf::Vector2f(200, 50));
	while_playing.album_list.setPosition(400, 0);
	while_playing.album_pic.loadFromFile(Imgs_directory"albums unpressed.png");
	while_playing.album_list.setTexture(&while_playing.album_pic);
	while_playing.album_sprite.setTexture(while_playing.album_pic);
	while_playing.album_sprite.setPosition(400, 0);



	while_playing.genre_list.setSize(sf::Vector2f(200, 50));
	while_playing.genre_list.setPosition(600, 0);
	while_playing.genre_pic.loadFromFile(Imgs_directory"genres unpressed.png");
	while_playing.genre_list.setTexture(&while_playing.genre_pic);
	while_playing.genre_sprite.setTexture(while_playing.genre_pic);
	while_playing.genre_sprite.setPosition(600, 0);





	while_playing.back_pic.setSize(sf::Vector2f(800.0f, 600.0f));
	while_playing.background_texture.loadFromFile(Imgs_directory"wallpaper dark final final.png");
	if (!while_playing.background_texture.loadFromFile(Imgs_directory"wallpaper dark final final.png")) {
		cout << "error while loading the background";
	}
	while_playing.back_pic.setTexture(&while_playing.background_texture);

	window.draw(while_playing.back_pic);
	window.draw(while_playing.shuffle_button);
	window.draw(while_playing.genre_list);
	window.draw(while_playing.album_list);
	window.draw(while_playing.songs_list);
	window.draw(while_playing.sorting_button[0]);
	window.draw(while_playing.sorting_button[1]);
	window.draw(while_playing.artist_list);
	window.draw(while_playing.rating_bar);
	window.draw(while_playing.backward_button);
	window.draw(while_playing.forward_button);
	window.draw(while_playing.play_button);
	window.draw(while_playing.search_box);

	for (int i = 0; i < songs.size(); i++) {
		window.draw(while_playing.music_box[i]);
		window.draw(while_playing.name_music[i]);
	}





	if (focus(while_playing.album_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "album";
			songs_by_a_default_thing.clear();
		}
	}
	if (focus(while_playing.genre_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "genre";
			songs_by_a_default_thing.clear();
		}
	}
	if (focus(while_playing.artist_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "artist";
			songs_by_a_default_thing.clear();
		}
	}



	shuffle(songs);


	////////play button pressing
	if (focus(while_playing.play_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			if (playing == true) {
				music.pause();
				playing = false;
			}
			else {
				music.play();
				playing = true;

			}
		}
	}


	/////// enabling shuffle 
	if (focus(while_playing.shuffle_button.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			if (shufflle) {
				shufflle = false;
			}
			else {
				shufflle = true;
			}

		}
	}





	cout << is_songs_sorted << endl; 
	for (int i = 0; i < songs.size(); i++) {

		if (focus(while_playing.music_box[i].getGlobalBounds(), mouse_position))
		{
			if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left)
			{
				rating = song_data[i].rating;
				if (shufflle == false) {
					if (!is_songs_sorted) {
						index_of_playing_song = i;
						playMusic(songs[index_of_playing_song], index_of_playing_song, playing, music);
						playing_song_name = songs[index_of_playing_song];
					}
					else {
						index_of_playing_song = i;
						playMusic(sorted_songs[index_of_playing_song], index_of_playing_song, playing, music);
						playing_song_name = sorted_songs[index_of_playing_song];
					}
				}
				
				if (shufflle){
					index_of_playing_song = shuffled[index_of_playing_song];
					playMusic(songs[shuffled[index_of_playing_song]], index_of_playing_song, playing, music);
					playing_song_name = songs[shuffled[index_of_playing_song]];
				}
			}
		}


	}


	if (focus(while_playing.backward_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			index_of_playing_song--;
			if (shufflle == false) {
				check_order(index_of_playing_song);
				playMusic(songs[index_of_playing_song], index_of_playing_song, playing, music);
				rating = song_data[index_of_playing_song].rating;
			}
			else {
				index_of_playing_song = shuffled[index_of_playing_song];
				playMusic(songs[shuffled[index_of_playing_song]], index_of_playing_song, playing, music);
				rating = song_data[shuffled[index_of_playing_song]].rating;
			}
		}
	}


	if (focus(while_playing.forward_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {

			index_of_playing_song++;
			if (shufflle == false) {

				check_order(index_of_playing_song);
				playMusic(songs[index_of_playing_song], index_of_playing_song, playing, music);
				rating = song_data[index_of_playing_song].rating; 
			}
			else {
				check_order(index_of_playing_song);
				playMusic(songs[shuffled[index_of_playing_song]], index_of_playing_song, playing, music);
				rating = song_data[shuffled[index_of_playing_song]].rating;
			}
		}
	}
	if (music.getStatus() == sf::SoundSource::Stopped && playing) {
		index_of_playing_song++;
		if (shufflle == false) {

			check_order(index_of_playing_song);
			playMusic(songs[index_of_playing_song], index_of_playing_song, playing, music);
		}
		else {
			check_order(index_of_playing_song);
			playMusic(songs[shuffled[index_of_playing_song]], index_of_playing_song, playing, music);
		}
	}


	// from high to low 
	if (focus(while_playing.sorting_button[0].getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			if (is_songs_sorted == 0 || is_songs_sorted == -1) {
				is_songs_sorted = 1;
				sorted_songs = sorting(1);
			}
			else if (is_songs_sorted == 1) {
				is_songs_sorted = 0;
			}
		}
	}
	if (focus(while_playing.sorting_button[1].getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			if (is_songs_sorted == 0 || is_songs_sorted == 1) {
				is_songs_sorted = -1;
				sorted_songs = sorting(2);
			}
			else if (is_songs_sorted == -1) {
				is_songs_sorted = 0;
			}
		}
	}
}




void playMusic(const std::string& filename, int &play_num, bool& playing, sf::Music& music)
{
	// Load an ogg music file

	if (!music.openFromFile(directory + filename + ".wav"))
		return;

	// Display music informations
	cout << filename << ":" << std::endl;
	cout << " " << music.getDuration().asSeconds() << " seconds" << std::endl;



	// Play it


	music.openFromFile(directory + filename + ".wav");
	music.play();
	playing = true;


}


void get_all_files_names_within_folder(string folder)
{
	// Reads all .wav files in specific folder
	int i = 0;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				song_data[i].name = fd.cFileName;
				// erases .wav from songs title 
				song_data[i].name.erase(song_data[i].name.end() - 4, song_data[i].name.end());
				songs.push_back(song_data[i].name);
				i++;
				number_of_current_songs++;
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}




void album_tab(sf::RenderWindow& window, sf::Vector2f& mouse_position, sf::Event& event, string& mod, sf::Music& music, bool& playing) {
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
	sf::Texture album_pic;
	sf::Sprite album_sprite;
	sf::Texture genre_pic;
	sf::Sprite genre_sprite;
	sf::Texture song_pic;
	sf::Sprite song_sprite;
	sf::Texture artist_pic;
	sf::Sprite artist_sprite;
	RectangleShape album[20];
	RectangleShape album_result[20];
	Text album_result_text[20];
	Text name_album[20];

	Font use_font;
	use_font.loadFromFile(Imgs_directory"Roboto-ThinItalic.ttf");

	vector<string> to_be_shown = View_all(3);

	float y = 55;
	for (int i = 0; i < to_be_shown.size(); ++i) {
		album[i].setSize(Vector2f(200, 30));
		album[i].setPosition(0, y);
		album[i].setFillColor(Color::Transparent);
		name_album[i].setFont(use_font);
		name_album[i].setStyle(Text::Bold);
		name_album[i].setString(to_be_shown[i]);
		name_album[i].setColor(Color::Blue);
		name_album[i].setPosition(0, y);
		name_album[i].setCharacterSize(24);




		y += 33;

	}















	play_button.setSize(sf::Vector2f(75, 75));
	play_button.setOrigin(25, 25);
	play_button.setPosition(400, 540);
	play_pic.loadFromFile(Imgs_directory"pause-play.png");
	play_button.setTexture(&play_pic);
	play_sprite.setTexture(play_pic);
	play_sprite.setOrigin(25, 25);
	play_sprite.setPosition(400, 550);



	backward_button.setSize(sf::Vector2f(75, 75));
	backward_button.setOrigin(25, 25);
	backward_button.setPosition(300, 540);
	backward_pic.loadFromFile(Imgs_directory"previous.png");
	backward_button.setTexture(&backward_pic);
	backward_sprite.setTexture(backward_pic);
	backward_sprite.setOrigin(25, 25);
	backward_sprite.setPosition(300, 550);




	forward_button.setSize(sf::Vector2f(75, 75));
	forward_button.setOrigin(25, 25);
	forward_button.setPosition(500, 540);
	forward_pic.loadFromFile(Imgs_directory"next.png");
	forward_button.setTexture(&forward_pic);
	forward_sprite.setTexture(forward_pic);
	forward_sprite.setOrigin(25, 25);
	forward_sprite.setPosition(500, 550);



	shuffle_button.setSize(sf::Vector2f(75, 75));
	shuffle_button.setOrigin(37.5, 37.5);
	shuffle_button.setPosition(150, 550);
	shuffle_pic.loadFromFile(Imgs_directory"shuffle.png");
	shuffle_button.setTexture(&shuffle_pic);
	shuffle_sprite.setTexture(shuffle_pic);
	shuffle_sprite.setPosition(150, 550);
	shuffle_sprite.setOrigin(12.5, 12.5);






	songs_list.setSize(sf::Vector2f(200, 50));

	songs_list.setPosition(0, 0);
	song_pic.loadFromFile(Imgs_directory"songs 200  unpressed.png");
	songs_list.setTexture(&song_pic);
	song_sprite.setTexture(song_pic);
	song_sprite.setPosition(0, 0);



	artist_list.setSize(sf::Vector2f(200, 50));

	artist_list.setPosition(200, 0);
	artist_pic.loadFromFile(Imgs_directory"artists unpressed.png");
	artist_list.setTexture(&artist_pic);
	artist_sprite.setTexture(artist_pic);
	artist_sprite.setPosition(200, 0);





	album_list.setSize(sf::Vector2f(200, 50));
	album_list.setPosition(400, 0);
	album_pic.loadFromFile(Imgs_directory"albums pressed.png");
	album_list.setTexture(&album_pic);
	album_sprite.setTexture(album_pic);
	album_sprite.setPosition(400, 0);



	genre_list.setSize(sf::Vector2f(200, 50));

	genre_list.setPosition(600, 0);
	genre_pic.loadFromFile(Imgs_directory"genres unpressed.png");
	genre_list.setTexture(&genre_pic);
	genre_sprite.setTexture(genre_pic);
	genre_sprite.setPosition(600, 0);





	back_pic.setSize(sf::Vector2f(800.0f, 600.0f));
	background_texture.loadFromFile(Imgs_directory"wallpaper dark final final.png");
	if (!background_texture.loadFromFile(Imgs_directory"wallpaper dark final final.png")) {
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
	for (int i = 0; i < to_be_shown.size(); i++) {
		window.draw(album[i]);
		window.draw(name_album[i]);
	}

	for (int i = 0; i < to_be_shown.size(); ++i) {
		if (focus(album[i].getGlobalBounds(), mouse_position)) {
			if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
				songs_by_a_default_thing = View_song(1, to_be_shown[i]);

			}
		}

	}

	y = 55;
	for (int i = 0; i < songs_by_a_default_thing.size(); i++) {
		album_result[i].setSize(Vector2f(200, 30));
		album_result[i].setPosition(300, y);
		album_result[i].setFillColor(Color::Transparent);
		album_result_text[i].setFont(use_font);
		album_result_text[i].setStyle(Text::Bold);
		album_result_text[i].setColor(Color::Magenta);
		album_result_text[i].setPosition(300, y);
		album_result_text[i].setString(songs_by_a_default_thing[i]);
		album_result_text[i].setCharacterSize(24);
		y += 33;
		window.draw(album_result[i]);
		window.draw(album_result_text[i]);
	}
	for (int i = 0; i < songs_by_a_default_thing.size(); ++i) {
		if (focus(album_result[i].getGlobalBounds(), mouse_position)) {
			if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
				playMusic(songs_by_a_default_thing[i], i, playing, music);
				songs_by_a_default_thing.clear();
			}
		}
	}







	if (focus(song_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "song";

		}
	}
	if (focus(genre_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "genre";
			songs_by_a_default_thing.clear();
		}
	}
	if (focus(artist_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "artist";
			songs_by_a_default_thing.clear();
		}
	}






	////////play button pressing
	if (focus(play_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			if (playing == true) {
				music.pause();
				playing = false;
			}
			else {
				music.play();
				playing = true;

			}
		}
	}


	/////// enabling shuffle 
	if (focus(shuffle_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {


		}
	}

	///////// backward button pressing
	if (focus(backward_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {


		}
	}

	///////// forward button pressing 
	if (focus(forward_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {


		}
	}

}


void artist_tab(sf::RenderWindow& window, sf::Vector2f& mouse_position, sf::Event& event, string& mod, sf::Music& music, bool& playing) {
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
	sf::Texture album_pic;
	sf::Sprite album_sprite;
	sf::Texture genre_pic;
	sf::Sprite genre_sprite;
	sf::Texture song_pic;
	sf::Sprite song_sprite;
	sf::Texture artist_pic;
	sf::Sprite artist_sprite;
	RectangleShape artist[20];
	Text name_artist[20];
	Font use_font;
	RectangleShape artist_result[20];
	Text artist_result_text[20];
	use_font.loadFromFile(Imgs_directory"Roboto-ThinItalic.ttf");


	vector<string> to_be_shown = View_all(1);


	float y = 55;
	for (int i = 0; i < to_be_shown.size(); ++i) {
		artist[i].setSize(Vector2f(200, 30));
		artist[i].setPosition(0, y);
		artist[i].setFillColor(Color::Transparent);
		name_artist[i].setFont(use_font);
		name_artist[i].setStyle(Text::Bold);
		name_artist[i].setString(to_be_shown[i]);
		name_artist[i].setColor(Color::Blue);
		name_artist[i].setPosition(0, y);
		name_artist[i].setCharacterSize(24);
		y += 33;

	}







	play_button.setSize(sf::Vector2f(75, 75));
	play_button.setOrigin(25, 25);
	play_button.setPosition(400, 540);
	play_pic.loadFromFile(Imgs_directory"pause-play.png");
	play_button.setTexture(&play_pic);
	play_sprite.setTexture(play_pic);
	play_sprite.setOrigin(25, 25);
	play_sprite.setPosition(400, 550);



	backward_button.setSize(sf::Vector2f(75, 75));
	backward_button.setOrigin(25, 25);
	backward_button.setPosition(300, 540);
	backward_pic.loadFromFile(Imgs_directory"previous.png");
	backward_button.setTexture(&backward_pic);
	backward_sprite.setTexture(backward_pic);
	backward_sprite.setOrigin(25, 25);
	backward_sprite.setPosition(300, 550);




	forward_button.setSize(sf::Vector2f(75, 75));
	forward_button.setOrigin(25, 25);
	forward_button.setPosition(500, 540);
	forward_pic.loadFromFile(Imgs_directory"next.png");
	forward_button.setTexture(&forward_pic);
	forward_sprite.setTexture(forward_pic);
	forward_sprite.setOrigin(25, 25);
	forward_sprite.setPosition(500, 550);



	shuffle_button.setSize(sf::Vector2f(75, 75));
	shuffle_button.setOrigin(37.5, 37.5);
	shuffle_button.setPosition(150, 550);
	shuffle_pic.loadFromFile(Imgs_directory"shuffle.png");
	shuffle_button.setTexture(&shuffle_pic);
	shuffle_sprite.setTexture(shuffle_pic);
	shuffle_sprite.setPosition(150, 550);
	shuffle_sprite.setOrigin(12.5, 12.5);






	songs_list.setSize(sf::Vector2f(200, 50));

	songs_list.setPosition(0, 0);
	song_pic.loadFromFile(Imgs_directory"songs 200  unpressed.png");
	songs_list.setTexture(&song_pic);
	song_sprite.setTexture(song_pic);
	song_sprite.setPosition(0, 0);



	artist_list.setSize(sf::Vector2f(200, 50));

	artist_list.setPosition(200, 0);
	artist_pic.loadFromFile(Imgs_directory"artists pressed.png");
	artist_list.setTexture(&artist_pic);
	artist_sprite.setTexture(artist_pic);
	artist_sprite.setPosition(200, 0);





	album_list.setSize(sf::Vector2f(200, 50));
	album_list.setPosition(400, 0);
	album_pic.loadFromFile(Imgs_directory"albums unpressed.png");
	album_list.setTexture(&album_pic);
	album_sprite.setTexture(album_pic);
	album_sprite.setPosition(400, 0);



	genre_list.setSize(sf::Vector2f(200, 50));

	genre_list.setPosition(600, 0);
	genre_pic.loadFromFile(Imgs_directory"genres unpressed.png");
	genre_list.setTexture(&genre_pic);
	genre_sprite.setTexture(genre_pic);
	genre_sprite.setPosition(600, 0);





	back_pic.setSize(sf::Vector2f(800.0f, 600.0f));
	background_texture.loadFromFile(Imgs_directory"wallpaper dark final final.png");
	if (!background_texture.loadFromFile(Imgs_directory"wallpaper dark final final.png")) {
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
	for (int i = 0; i < to_be_shown.size(); i++) {
		window.draw(artist[i]);
		window.draw(name_artist[i]);
	}
	for (int i = 0; i < to_be_shown.size(); ++i) {
		if (focus(artist[i].getGlobalBounds(), mouse_position)) {
			if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
				songs_by_a_default_thing = View_song(2, to_be_shown[i]);
			}
		}

	}

	y = 55;
	for (int i = 0; i < songs_by_a_default_thing.size(); i++) {
		artist_result[i].setSize(Vector2f(200, 30));
		artist_result[i].setPosition(200, y);
		artist_result[i].setFillColor(Color::Transparent);
		artist_result_text[i].setFont(use_font);
		artist_result_text[i].setStyle(Text::Bold);
		artist_result_text[i].setColor(Color::Magenta);
		artist_result_text[i].setPosition(200, y);
		artist_result_text[i].setString(songs_by_a_default_thing[i]);
		artist_result_text[i].setCharacterSize(24);
		y += 33;
		window.draw(artist_result[i]);
		window.draw(artist_result_text[i]);
	}
	for (int i = 0; i < songs_by_a_default_thing.size(); ++i) {
		if (focus(artist_result[i].getGlobalBounds(), mouse_position)) {
			if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
				playMusic(songs_by_a_default_thing[i], i, playing, music);
				songs_by_a_default_thing.clear();
			}
		}
	}





	if (focus(album_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "album";
			songs_by_a_default_thing.clear();
		}
	}
	if (focus(genre_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "genre";
			songs_by_a_default_thing.clear();

		}
	}
	if (focus(song_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "song";

		}
	}









	////////play button pressing
	if (focus(play_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			if (playing == true) {
				music.pause();
				playing = false;
			}
			else {
				music.play();
				playing = true;

			}
		}
	}


	/////// enabling shuffle 
	if (focus(shuffle_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {


		}
	}

	///////// backward button pressing
	if (focus(backward_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {


		}
	}

	///////// forward button pressing 
	if (focus(forward_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {


		}
	}
}



void genre_tab(sf::RenderWindow& window, sf::Vector2f& mouse_position, sf::Event& event, string& mod, sf::Music& music, bool& playing) {
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
	sf::Texture album_pic;
	sf::Sprite album_sprite;
	sf::Texture genre_pic;
	sf::Sprite genre_sprite;
	sf::Texture song_pic;
	sf::Sprite song_sprite;
	sf::Texture artist_pic;
	sf::Sprite artist_sprite;
	RectangleShape genre[20];
	Text name_genre[20];
	Font use_font;
	RectangleShape genre_result[20];
	Text genre_result_text[20];
	use_font.loadFromFile(Imgs_directory"Roboto-ThinItalic.ttf");

	vector<string> to_be_shown = View_all(2);

	float y = 55;
	for (int i = 0; i < to_be_shown.size(); ++i) {
		genre[i].setSize(Vector2f(200, 30));
		genre[i].setPosition(0, y);
		genre[i].setFillColor(Color::Transparent);
		name_genre[i].setFont(use_font);
		name_genre[i].setStyle(Text::Bold);
		name_genre[i].setString(to_be_shown[i]);
		name_genre[i].setColor(Color::Blue);
		name_genre[i].setPosition(0, y);
		name_genre[i].setCharacterSize(24);

		y += 33;

	}




	play_button.setSize(sf::Vector2f(75, 75));
	play_button.setOrigin(25, 25);
	play_button.setPosition(400, 540);
	play_pic.loadFromFile(Imgs_directory"pause-play.png");
	play_button.setTexture(&play_pic);
	play_sprite.setTexture(play_pic);
	play_sprite.setOrigin(25, 25);
	play_sprite.setPosition(400, 550);



	backward_button.setSize(sf::Vector2f(75, 75));
	backward_button.setOrigin(25, 25);
	backward_button.setPosition(300, 540);
	backward_pic.loadFromFile(Imgs_directory"previous.png");
	backward_button.setTexture(&backward_pic);
	backward_sprite.setTexture(backward_pic);
	backward_sprite.setOrigin(25, 25);
	backward_sprite.setPosition(300, 550);




	forward_button.setSize(sf::Vector2f(75, 75));
	forward_button.setOrigin(25, 25);
	forward_button.setPosition(500, 540);
	forward_pic.loadFromFile(Imgs_directory"next.png");
	forward_button.setTexture(&forward_pic);
	forward_sprite.setTexture(forward_pic);
	forward_sprite.setOrigin(25, 25);
	forward_sprite.setPosition(500, 550);



	shuffle_button.setSize(sf::Vector2f(75, 75));
	shuffle_button.setOrigin(37.5, 37.5);
	shuffle_button.setPosition(150, 550);
	shuffle_pic.loadFromFile(Imgs_directory"shuffle.png");
	shuffle_button.setTexture(&shuffle_pic);
	shuffle_sprite.setTexture(shuffle_pic);
	shuffle_sprite.setPosition(150, 550);
	shuffle_sprite.setOrigin(12.5, 12.5);






	songs_list.setSize(sf::Vector2f(200, 50));

	songs_list.setPosition(0, 0);
	song_pic.loadFromFile(Imgs_directory"songs 200  unpressed.png");
	songs_list.setTexture(&song_pic);
	song_sprite.setTexture(song_pic);
	song_sprite.setPosition(0, 0);



	artist_list.setSize(sf::Vector2f(200, 50));

	artist_list.setPosition(200, 0);
	artist_pic.loadFromFile(Imgs_directory"artists unpressed.png");
	artist_list.setTexture(&artist_pic);
	artist_sprite.setTexture(artist_pic);
	artist_sprite.setPosition(200, 0);





	album_list.setSize(sf::Vector2f(200, 50));
	album_list.setPosition(400, 0);
	album_pic.loadFromFile(Imgs_directory"albums unpressed.png");
	album_list.setTexture(&album_pic);
	album_sprite.setTexture(album_pic);
	album_sprite.setPosition(400, 0);



	genre_list.setSize(sf::Vector2f(200, 50));

	genre_list.setPosition(600, 0);
	genre_pic.loadFromFile(Imgs_directory"genres  pressed.png");
	genre_list.setTexture(&genre_pic);
	genre_sprite.setTexture(genre_pic);
	genre_sprite.setPosition(600, 0);





	back_pic.setSize(sf::Vector2f(800.0f, 600.0f));
	background_texture.loadFromFile(Imgs_directory"wallpaper dark final final.png");
	if (!background_texture.loadFromFile(Imgs_directory"wallpaper dark final final.png")) {
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
	for (int i = 0; i < to_be_shown.size(); i++) {
		window.draw(genre[i]);
		window.draw(name_genre[i]);
	}
	for (int i = 0; i < to_be_shown.size(); ++i) {
		if (focus(genre[i].getGlobalBounds(), mouse_position)) {
			if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
				songs_by_a_default_thing = View_song(3, to_be_shown[i]);
			}
		}

	}

	y = 55;
	for (int i = 0; i < songs_by_a_default_thing.size(); i++) {
		genre_result[i].setSize(Vector2f(200, 30));
		genre_result[i].setPosition(300, y);
		genre_result[i].setFillColor(Color::Transparent);
		genre_result_text[i].setFont(use_font);
		genre_result_text[i].setStyle(Text::Bold);
		genre_result_text[i].setColor(Color::Magenta);
		genre_result_text[i].setPosition(300, y);
		genre_result_text[i].setString(songs_by_a_default_thing[i]);
		genre_result_text[i].setCharacterSize(24);
		y += 33;
		window.draw(genre_result[i]);
		window.draw(genre_result_text[i]);
	}
	for (int i = 0; i < songs_by_a_default_thing.size(); ++i) {
		if (focus(genre_result[i].getGlobalBounds(), mouse_position)) {
			if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
				playMusic(songs_by_a_default_thing[i], i, playing, music);
				songs_by_a_default_thing.clear();
			}
		}
	}



	if (focus(album_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "album";
			songs_by_a_default_thing.clear();
		}
	}
	if (focus(song_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "song";

		}
	}
	if (focus(artist_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			mod = "artist";
			songs_by_a_default_thing.clear();
		}
	}













	////////play button pressing
	if (focus(play_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {
			if (playing == true) {
				music.pause();
				playing = false;
			}
			else {
				music.play();
				playing = true;

			}
		}
	}


	/////// enabling shuffle 
	if (focus(shuffle_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {


		}
	}

	///////// backward button pressing
	if (focus(backward_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {


		}
	}

	///////// forward button pressing 
	if (focus(forward_sprite.getGlobalBounds(), mouse_position)) {
		if (event.type == sf::Event::MouseButtonPressed  && event.mouseButton.button == sf::Mouse::Left) {


		}
	}


}





void wpage(sf::RenderWindow& window, sf::Event& event, string& mod, sf::Vector2f& mouse_position)
{
	window.clear();
	sf::RectangleShape back_pic;
	sf::Texture background_texture;
	sf::RectangleShape login_button;
	sf::Texture login_texture;
	sf::RectangleShape sign_button;
	sf::Texture sign_texture;
	sf::Sprite loginsprite;
	sf::Sprite signsprite;

	login_button.setSize(sf::Vector2f(165, 96));
	login_button.setOrigin(85, 143);
	login_button.setPosition(263, 244);
	login_texture.loadFromFile(Imgs_directory"login button.png");
	login_button.setTexture(&login_texture);
	loginsprite.setTexture(login_texture);
	loginsprite.setOrigin(85, 143);
	loginsprite.setPosition(263, 244);


	sign_button.setSize(sf::Vector2f(165, 96));
	sign_button.setOrigin(83, 143);
	sign_button.setPosition(100, 244);
	sign_texture.loadFromFile(Imgs_directory"sign up.png");
	sign_button.setTexture(&sign_texture);
	signsprite.setTexture(sign_texture);
	signsprite.setOrigin(83, 143);
	signsprite.setPosition(100, 244);


	back_pic.setSize(sf::Vector2f(600.0f, 300.0f));
	background_texture.loadFromFile(Imgs_directory"welcoming page clean.png");
	if (!background_texture.loadFromFile(Imgs_directory"welcoming page clean.png")) {
		cout << "error while loading the background";
	}
	back_pic.setTexture(&background_texture);

	window.draw(back_pic);
	window.draw(login_button);
	window.draw(sign_button);

	if (focus(login_button.getGlobalBounds(), mouse_position))
	{
		if (event.type == sf::Event::MouseButtonPressed &&event.mouseButton.button == sf::Mouse::Left)
		{
			mod = "login";
		}
	}

	if (focus(sign_button.getGlobalBounds(), mouse_position))
	{
		if (event.type == sf::Event::MouseButtonPressed &&event.mouseButton.button == sf::Mouse::Left)
		{
			mod = "sign up";
		}
	}









}



void read_users()
{
	fstream users;
	users.open("usersInfo.txt");
	users >> NumUsers;
	users.ignore();
	for (int i = 0; i < NumUsers; i++)
	{
		getline(users, users_data[i].name);
		getline(users, users_data[i].password);
	}

}




bool signup(string username, string password)
{
	bool taken = false;

	for (int i = 0; i < NumUsers; i++)
	{
		if (username == users_data[i].name)
		{
			cout << "Username already taken" << endl;
			taken = true;
		}
	}
	if (!taken)
	{

		cout << "\nPlease enter your Password : ";
	}
	else {
		return false;
	}


	NumUsers++;

	// updates user info file
	fstream users;
	users.open("usersInfo.txt", ios::out | ios::trunc);
	users << NumUsers << endl;
	users << username << endl;
	users << password << endl;
	if (NumUsers > 1)
	{
		for (int i = 0; i < NumUsers; i++)
		{
			users << users_data[i].name << endl;
			users << users_data[i].password << endl;
		}
	}
	current_user = username;
	// create rating file 
	ofstream new_file;
	new_file.open(users_directory + username + ".txt");
	for (int i = 0; i < songs.size(); i++)
		cout << 0 << endl;
	return true;

}



bool login(string current_user, string password)
{
	bool Logedin = false;
	while (true)
	{
		cout << "Username : ";
		for (int i = 0; i < NumUsers; i++)
		{
			if (current_user == users_data[i].name)
			{
				cout << "\nPassword : ";
				//cin >> password;
				if (password == users_data[i].password)
				{
					Logedin = true;

				}
			}
		}
		if (Logedin)
			return true;
		else {
			return false;
			cout << "invalid username or password" << endl;
		}

	}

	system("cls");
}



void READ_RATING()
{
	fstream Rating_file;
	Rating_file.open(users_directory + current_user + ".txt");
	int counter = 0;
	for (int i = 0; i < songs.size() + counter; i++)
	{
		Rating_file >> song_data[i].rating;
		if (song_data[i].rating <= Low_rating_activator && song_data[i].rating > 0)
		{
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



vector<string> View_all(int choice)
{
	set<string> ones;
	vector<string>to_be_shown;
	int counter = 0;
	to_be_shown.clear();
	ones.clear();
	for (int i = 0; i < songs.size(); i++) {
		if (choice == 1) {
			ones.insert(song_data[i].artist);
		}
		else if (choice == 2)
			ones.insert(song_data[i].genre);
		else if (choice == 3)
			ones.insert(song_data[i].album);
	}
	for (auto i : ones) {
		to_be_shown.push_back(i);
	}
	//cout << ones.size() << endl << to_be_shown.size() << endl;
	//system("pause");

	return to_be_shown;
}


vector<string> View_song(int choice, string name)
{
	set<string> ones;
	vector<string>to_beshown;
	to_beshown.clear();
	ones.clear();
	for (int i = 0; i < songs.size(); i++) {
		if (choice == 1 && name == song_data[i].album) {
			ones.insert(song_data[i].name);
		}
		else if (choice == 2 && name == song_data[i].artist)
			ones.insert(song_data[i].name);
		else if (choice == 3 && name == song_data[i].genre)
			ones.insert(song_data[i].name);
	}
	for (auto i : ones) {
		to_beshown.push_back(i);
	}

	return to_beshown;
}


void shuffle(vector<string>ToShuffle)
{
	array <int, max_numsongs> shuffled_order = {};


	// intializing the array with values from 1 to the number of songs in the folder
	for (int i = 0; i <= ToShuffle.size() - 1; i++)
	{
		shuffled_order[i] = i;
	}
	for (int i = ToShuffle.size() - 1; i >= 0; i--)
	{
		int j = rand() % (ToShuffle.size() - 1);
		int tmp = shuffled_order[j];
		shuffled_order[j] = shuffled_order[i];
		shuffled_order[i] = tmp;
	}
	for (int i = 0; i < ToShuffle.size(); i++)
	{
		shuffled[i] = shuffled_order[i];
	}
}



void check_order(int& index_of_playing_song) {
	if (index_of_playing_song < 0) {
		index_of_playing_song = songs.size() - 1;
	}
	if (index_of_playing_song > songs.size() - 1) {
		index_of_playing_song = 0;
	}
}




vector<string> sorting(int x)
{



	vector<string> names;
	names.clear();

	
	if (x == 1)
	{
		for (int i = Highest_rating; i >= 0; i--) {
			for (int j = 0; j < songs.size(); j++) {
				if (song_data[j].rating == i) {

					names.push_back(song_data[j].name);

				}
			}
		}
	}
	else if (x == 2)
	{
		for (int i = 0; i <= Highest_rating; i++) {
			for (int j = 0; j < songs.size(); j++) {
				if (song_data[j].rating == i) {
					cout << counter + 1 << " ) " << song_data[j].name << endl;
					names.push_back(song_data[j].name);

				}
			}
		}
	}



	return names;

}


void rate(string name, int& rating)
{
	if (rating < 2) {
		music.openFromFile("Tda5ol.wav");
		music.play();
	}
	fstream Rating_file;
	Rating_file.open(users_directory + current_user + ".txt");
	for (int i = 0; i < songs.size(); i++)
	{
		if (name == song_data[i].name)
		{
			song_data[i].rating = rating;
			Rating_file << song_data[i].rating << endl;
		}
		else
		{
			Rating_file << song_data[i].rating << endl;
		}

	}
	Rating_file.close();
}




void searching_window() {
	//////////////////search_window///////////////////////////////////////
	
	

			//seacrh window
			sf::RenderWindow Searchwindow(sf::VideoMode(500, 500), "<Search_Window>");

			Searchwindow.clear();
			RectangleShape button_search[4];
			RectangleShape search_text_box;
			RectangleShape button_search_name[4];
			Text name_button_search[4];
			Texture texture;
			texture.loadFromFile(Imgs_directory"kojackplayer_background.png");
			Sprite sprite;
			Vector2u size = texture.getSize();
			sprite.setTexture(texture);
			Font use_font;
			use_font.loadFromFile(Imgs_directory"Roboto-ThinItalic.ttf");
			Text search_text;

			search_text.setCharacterSize(16);
			search_text.setFont(use_font);
			search_text.setFillColor(sf::Color::Blue);
			search_text.setPosition(130, 200);
			search_text.setStyle(Text::Bold);
			search_text.setCharacterSize(28);
			search_text_box.setSize(Vector2f(250, 40));
			search_text_box.setPosition(130, 200);
			search_text_box.setFillColor(Color::White);


			float x = 5;
			for (int i = 0; i < 4; ++i) {
				button_search[i].setSize(Vector2f(90, 40));
				button_search[i].setPosition(x, 10);
				button_search[i].setFillColor(Color::Transparent);
				name_button_search[i].setFont(use_font);
				name_button_search[i].setStyle(Text::Bold);
				name_button_search[i].setColor(Color::Blue);
				name_button_search[i].setPosition(x, 10);
				name_button_search[i].setCharacterSize(32);
				x += 130;



			}

			name_button_search[0].setString("  Name");
			name_button_search[1].setString("Album");
			name_button_search[2].setString("artist");
			name_button_search[3].setString("year");
			int windicator = 0;
			int showanything = 0;
			
			while (Searchwindow.isOpen())
			{
				sf::Event starting_search;
				while (Searchwindow.pollEvent(starting_search)) {
					mouse_position.x = sf::Mouse::getPosition(Searchwindow).x;
					mouse_position.y = sf::Mouse::getPosition(Searchwindow).y;
					
					if (starting_search.type == sf::Event::Closed)
						Searchwindow.close();
					
					//button function 
					for (int i = 0; i < 4; ++i) {
						if (focus(button_search[i].getGlobalBounds(), mouse_position)) {
							if (starting_search.type == sf::Event::MouseButtonPressed  && starting_search.mouseButton.button == sf::Mouse::Left) {
								{
									cout << "5555555";




								}

							}

						}
					}

					//text entred
					if (starting_search.type == sf::Event::TextEntered)
					{
						if (starting_search.text.unicode < 128 && starting_search.text.unicode != 8)
						{
							userinput_search += starting_search.text.unicode;
							search_text.setString(userinput_search);
							cout << userinput_search;
						}
						if (starting_search.text.unicode == 8 && userinput_search.size() > 0)
						{
							userinput_search.erase(userinput_search.begin() + userinput_search.size() - 1);
							search_text.setString(userinput_search);
						}
					}

				}


				Searchwindow.draw(sprite);
				for (int i = 0; i < 4; i++) {
					Searchwindow.draw(button_search[i]);
					Searchwindow.draw(name_button_search[i]);
				}
				Searchwindow.draw(search_text_box);
				Searchwindow.draw(search_text);

				Searchwindow.display();

			}

		

}