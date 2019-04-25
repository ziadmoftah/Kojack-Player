/* To run smoothly without any errors :
	Please make sure the project folder contains a  usersInfo.txt and a data folder*/
#pragma warning(disable : 4996) //Disables error (4996) bec it is just vs freaking on us  
#include <SFML/Audio.hpp>
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
#define directory "C:\\Users\\Owner\\Documents\\GitHub\\Kojack-Player\\Kojack player\\Kojack player\\resources/"
#define users_directory "C:\\Users\\Owner\\Documents\\GitHub\\Kojack-Player\\Kojack player\\Kojack player\\Data/" 
#define max_numsongs 10000
#define Low_rating_activator 3
#define Highest_rating 10

using namespace std;

bool menu = false;
bool found;
string current_user;

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

struct user
{
	string name;
	string password;
}users_data[10];
int NumUsers = 0;

int shuffled[max_numsongs];

bool shufflle = false;

vector<string> underrated_songs;
vector<string> songs;

void get_all_files_names_within_folder(string folder);
void playMusic(const string& filename, int &play_num);
void list_display(vector<string> ToPlay, int what = 1);
void playback(vector <string>names, int play_num);
void shuffle(vector<string>ToShuffle);
void check_order(int &i, vector<string> playing);
void find(int choice);
int main_menu(bool first);
void decision(int x);
void View_all(int x);
void rate(int x, string name);
void Low_Rating(int x, string name);
void search_display(string searched, int choice, int year = 0);
void search();
void Read_MetaData();
void sorting();
void playSound();
void READ_RATING();
void read_users();
void begin();
void login();
void signup();



int main()
{
	// Welcome to main
	
	get_all_files_names_within_folder(directory);
	read_users();
	begin();
	bool first = true;
	Read_MetaData();
	READ_RATING();
	while (true)
	{
		system("cls");
		decision(main_menu(first));
		menu = false; 
	}
	return 0;
}


int main_menu(bool first)
{
	if (first) {
		cout << "Welcome in Kojack Player Thanks for using me " << endl;
		first = false;
	}
	cout << "Press \n1 to View all Songs" << endl;
	cout << "2 to View Artists \n3 to View Genres" << endl;
	cout << "4 to View Albums \n5 to Search" << endl;
	if (!shufflle)
		cout << "6 To Enable Shuffle" << endl;
	else
		cout << "6 To Disable Shuffle" << endl;
	cout << "7 to View Low Rated Songs" << endl;
	int x;
	cin >> x;
	system("cls");
	return x;
}

void decision(int choice)
{
	switch (choice) {
	case 1:
		list_display(songs, 0);
		break;
	case 2:
		View_all(1);
		break;
	case 3:
		View_all(2);
		break;
	case 4:
		View_all(3);
		break;
	case 5:
		search();
		break;
	case 6:
		if (shufflle)
			shufflle = false;
		else
		{
			shufflle = true;
		}
		break;
	case  7:
		list_display(underrated_songs);
	}
}


// Reading Data functions (called once at the begining of the program ) **************************************************************************************

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
				songs.push_back( song_data[i].name);
				i++;
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
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
	Rating_file.open(users_directory + current_user + ".txt");
	for (int i = 0; i < songs.size(); i++)
	{
		Rating_file >> song_data[i].rating;
		if (song_data[i].rating <= Low_rating_activator && song_data[i].rating > 0)
		{
			underrated_songs.push_back(song_data[i].name);
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


// User Verification

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

void begin()
{
	cout << "Press \n1 to Login \n2 to Sign up " << endl;
	char choice; 
	cin >> choice;
	switch (choice)
	{
	case '1':
		login();
		break;
	case '2':
		signup();
		break;
	default :
		system("cls");
		cout << "Invalid input" << endl;
		return begin();
	}

	system("cls");
}

void login()
{
	string password;
	bool Logedin = false;
	while (true)
	{
		cout << "Username : ";
		cin >> current_user;
		for (int i = 0; i < NumUsers; i++)
		{
			if (current_user == users_data[i].name)
			{
				cout << "\nPassword : ";
				cin >> password;
				if (password == users_data[i].password)
				{
					Logedin = true;
					break;
				}
			}
		}
		if (Logedin)
			break;
		else
			cout << "invalid username or password" << endl;
	}

	system("cls");
}

void signup()
{
	bool taken = false;
	cout << "Please enter your Username : ";
	string username;
	string password;
	cin >> username;
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
		cin >> password;
	}
	else
	{
		return signup();
		return;
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
	system("cls");
}

// Rating functions *******************************************************************************************************************************************

void rate(int x, string name)
{
	int rating;
	cout << "Enter Rating (1-"<<Highest_rating<<") :";
	while (true)
	{
		cin >> rating;
		if (rating > Highest_rating || rating < 0)
		{
			cout << "Invalid rating \nEnter Rating :";
		}
		else
		{
			if (rating <= Low_rating_activator)
			{
				Low_Rating(x, name); //playsound !display
			}
			break;
		}
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

void Low_Rating(int x, string name)
{
	playSound();
	for (int i = 0; i < songs.size(); i++)
	{
		if (name == song_data[i].name)
		{
			song_data[i].display = false;
		}
	}
}

// Searching functions ***************************************************************************************************************************************


void search_display(string searched, int choice, int year)
{
	vector<string> ToPlay;
	ToPlay.clear();
	switch (choice)
	{
	case 1:
		for (int i = 0; i < songs.size(); i++)
		{
			if (song_data[i].name.find(searched) < song_data[i].name.size())
			{
				ToPlay.push_back(song_data[i].name);
				found = true;
			}
		}
		break;
	case 2:
		for (int i = 0; i < songs.size(); i++)
		{
			if (song_data[i].album.find(searched) < song_data[i].album.size())
			{
				ToPlay.push_back(song_data[i].name);
				found = true;
			}
		}
		break;
	case 3:
		for (int i = 0; i < songs.size(); i++)
		{
			if (song_data[i].artist.find(searched) != -1)
			{
				ToPlay.push_back(song_data[i].name);
				found = true;
			}
		}
		break;
	case 4:
		for (int i = 0; i < songs.size(); i++)
		{
			if (song_data[i].year == year)
			{
				ToPlay.push_back(song_data[i].name);
				found = true;
			}
		}
		break;
	}
	if (found)
	{
		list_display(ToPlay);
	}
	else {
		cout << "Not Found" << endl;
	}
}

void search()
{
	cout << flush << "Press \n1 To Search by name\n2 To Search by by Album\n3 To search by artist name\n4 To Search by year\n5 To Return to The Kojack Menu " << endl;
	int n; cin >> n;
	switch (n)
	{
	case 1:
		find(n);
		break;
	case 2:
		find(n);
		break;
	case 3:
		find(n);
		break;
	case 4:
		find(n);
		break;
	case 5:
		return;
	default:
		cout << "not valid input" << endl;
		return search();
		break;

	}

}

void find(int choice)
{
	bool found = false;
	string s = "weg";
	switch (choice) {
	case 1:
		cout << "Enter Song Name : ";
		break;
	case 2:
		cout << "Enter Album : ";
		break;
	case 3:
		cout << "Enter Artist : ";
		break;
	case 4:
		cout << "Enter Release Year : ";
		break;
	}
	if (choice != 4)
	{
		cin.ignore();
		getline(cin, s);
		if (s[0] >= 97 && s[0] <= 122)
			s[0] -= 32;
		search_display(s, choice);
	}
	else
	{
		int year; cin >> year;
		search_display(s, choice, year);
	}
	
}

// Viewing functions *****************************************************************************************************************************************

void sorting()
{
	vector<string> names;
	names.clear();
	cout << "Enter\n1 to sort high to low\n2 to sort low to high :";
	int x, counter = 0; cin >> x;
	system("cls");
	if (x == 1)
	{
		for (int i = Highest_rating ; i >= 0; i--) {
			for (int j = 0; j < songs.size(); j++) {
				if (song_data[j].rating == i) {
					cout << counter + 1 << " ) " << song_data[j].name << endl;
					names.push_back(song_data[j].name);
					counter++;
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
					counter++;
				}
			}
		}
	}
	cout << endl << endl;
	cout << "Press 1 to play in this order \nPress 2 to Return to Kojack Menu" << endl;
	int k; cin >> k;
	switch (k) {
	case 1:
		playback(names, 0);
		break;
	case 2:
		break;
	}
}

void list_display(vector<string> ToPlay , int what)
{
	system("cls");
	int x;
	for (int i = 0; i < ToPlay.size(); i++)
	{
		cout << i + 1 << " : " << ToPlay[i] << endl;
	}
	cout << endl << endl;
	if (what == 0)
	{
		cout << "Press 1 to Play \nPress 2 to sort the list\nPress 3 to Play certain song (Not available while shuffling)\nPress 4 to Return to Kojack Menu" << endl;
		cin >> x;
		switch (x) {
		case 1:
			playback(ToPlay, 0);
			break;
		case 2:
			sorting();
			break;
		case 3:
			cout << "Enter song number :";
			cin >> x;
			playback(ToPlay, x - 1);
			break;
		case 4:
			break;
		}
	}
	else
	{
		cout << "Press 1 to Play \nPress 2 to Play certain song (Not available while shuffling)\nPress 3 to Return to Kojack Menu" << endl;
		cin >> x;
		switch (x) {
		case 1:
			playback(ToPlay, 0);
			break;
		case 2:
			cout << "Enter song number :";
			cin >> x;
			playback(ToPlay, x - 1);
			break;
		case 3:
			break;
		}
	}

}

void View_all(int choice)
{
	set<string> ones;
	vector<string>one;
	int counter = 0;
	one.clear();
	
	for (int i = 0; i < songs.size(); i++) {
		if (choice == 1)
			ones.insert(song_data[i].artist);
		else if (choice == 2 )
			ones.insert(song_data[i].genre);
		else if (choice == 3 )
			ones.insert(song_data[i].album);
	}
	for (auto i : ones) {
		cout << counter + 1 << " ) " << i << endl;
		one.push_back(i);
		counter++;
	}

	int x; cin >> x;

	vector<string>plays;
	plays.clear();
	for (int i = 0; i < songs.size(); i++)
	{
		if(choice == 1 )
		{
			if (song_data[i].artist == one[x - 1])
			{	
				plays.push_back(song_data[i].name);
			}
		}
		else if (choice == 2)
		{
			if (song_data[i].genre == one[x - 1])
			{
				plays.push_back(song_data[i].name);
			}
		}
		else if (choice == 3)
		{
			if (song_data[i].album == one[x - 1])
			{
				plays.push_back(song_data[i].name);
			}
		}
	}
	list_display(plays, 1);
}

// Playing functions *****************************************************************************************************************************************

void shuffle(vector<string>ToShuffle)
{
	array <int, max_numsongs> shuffled_order = {};


	// intializing the array with values from 1 to the number of songs in the folder
	for (int i = 0; i <= ToShuffle.size()-1; i++)
	{
		shuffled_order[i] = i;
	}
	for (int i = ToShuffle.size()-1; i >= 0; i--)
	{
		int j = rand()%(ToShuffle.size() - 1);
		int tmp = shuffled_order[j];
		shuffled_order[j] = shuffled_order[i];
		shuffled_order[i] = tmp;
	}
	for (int i = 0; i < ToShuffle.size(); i++)
	{
		shuffled[i] = shuffled_order[i];
	}
}

void playback(vector<string>names, int play_num)
{
	system("cls");
	if (!shufflle) {
		for (int i = play_num; i < names.size(); i++)
		{
			playMusic(names[i], i);
			check_order(i, names);
			system("cls");
			if (menu)
			{
				menu = false;
				return;
			}
		}
	}
	else {
		shuffle(names);
		for (int i = 0; i < names.size(); i++)
		{
			playMusic(names[shuffled[i]], i);
			check_order(i, names);
			system("cls");
			if (menu)
			{
				menu = false;
				return;
			}
		}
	}
}

void playMusic(const std::string& filename, int &play_num)
{
	// Load an ogg music file
	sf::Music music;
	if (!music.openFromFile(directory + filename + ".wav"))
		return;

	// Display music informations
	cout << filename << ":" << std::endl;
	cout << " " << music.getDuration().asSeconds() << " seconds" << std::endl;



	// Play it
	music.play();

	// Loop while the music is playing
	
	cout << "Press p to pause , Press it again to play  \ns to stop  \nb backwards  \nr to Rate  \nm to return to main menu" << endl;
	
	while (music.getStatus() == sf::Music::Playing || music.getPlayingOffset().asSeconds() < music.getDuration().asSeconds())
	{
		// Leave some CPU time for other processes
		sf::sleep(sf::milliseconds(100));
		if (music.getPlayingOffset().asSeconds() == music.getDuration().asSeconds())
			break;

		// Display the playing position
		std::cout << "\rPlaying... " << music.getPlayingOffset().asSeconds() << " sec        ";
		std::cout << std::flush;

		if (kbhit())
		{
			char x;
			if (cin >> x)
			{
				if (x == 'p' &&  music.getStatus() == sf::Music::Playing)
					music.pause();
				else if (x == 'p')
					music.play();
				else if (x == 'n')
				{
					//next
					return;
				}
				else if (x == 's' && music.getStatus() == sf::Music::Playing)
				{
					music.stop();
				}
				else if (x == 'b')
				{
					//b as in backwards 
					play_num -= 2;
					return;
				}
				else if (x == 'r')
				{
					rate(play_num, filename);
				}
				else if (x == 'm')
				{
					menu = true;
					break;
				}

			}
		}
	}
	std::cout << std::endl << std::endl;
}

void check_order(int &i, vector <string> playing)
{
	// the final i in both cases will be incrmented in the for loop in the calling function

	// to play the first song after the last song
	if (i == playing.size() - 1)
	{
		i = -1;
	}
	// if you play the previous song while playing the first song in the list the i would be -2 
	else if (i == -2)
	{
		i = playing.size() - 2;
	}
}

void playSound()
{
	// Load a sound buffer from a wav file
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Tda5ol.wav"))
		return;

	sf::Sound sound(buffer);
	sound.play();
	// Loop while the sound is playing
	while (sound.getStatus() == sf::Sound::Playing)
	{
		// Leave some CPU time for other processes
		sf::sleep(sf::milliseconds(100));
	}
	std::cout << std::endl << std::endl;
}
