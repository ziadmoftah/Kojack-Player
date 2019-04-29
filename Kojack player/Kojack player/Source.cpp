#pragma warning(disable : 4996) //Disables error (4996) bec it is just vs freaking on us  
#include "GUI Functions.h"
#include "Fuctions.h"



int main() {
	get_all_files_names_within_folder(directory);
	read_users();
	Read_MetaData();
	show_welcome_window(); 
	Show_main_program(); 
	return 0;
}




void searching_window() {
	//////////////////search_window///////////////////////////////////////



			//seacrh window
	sf::RenderWindow Searchwindow(sf::VideoMode(500, 500), "<Search_Window>");

	Searchwindow.clear();
	RectangleShape button_search[4];
	RectangleShape search_text_box;
	Text name_button_search[4];
	Texture texture;
	Texture ok_texture;
	Texture search_bar_texture;
	texture.loadFromFile(Imgs_directory"kojackplayer_background.png");
	ok_texture.loadFromFile(Imgs_directory"search bar button.png");
	search_bar_texture.loadFromFile(Imgs_directory"search bar.png");
	Sprite sprite;
	Vector2u size = texture.getSize();
	sprite.setTexture(texture);
	Font use_font;
	use_font.loadFromFile(Imgs_directory"Roboto-ThinItalic.ttf");
	Text search_text;
	RectangleShape searching_results_box[10];
	Text text_searching_results[10];


	search_text.setCharacterSize(16);
	search_text.setFont(use_font);
	search_text.setFillColor(sf::Color::Black);
	search_text.setPosition(200, 50);
	search_text.setStyle(Text::Bold);
	search_text.setCharacterSize(28);
	search_text_box.setSize(Vector2f(350, 40));
	search_text_box.setPosition(130, 50);
	search_text_box.setFillColor(Color::White);
	search_text_box.setTexture(&search_bar_texture);




	
	



	float x = 5;
	for (int i = 0; i < 4; ++i) {
		button_search[i].setSize(Vector2f(90, 40));
		button_search[i].setPosition(x, 10);
		button_search[i].setFillColor(Color::Transparent);
		name_button_search[i].setFont(use_font);
		name_button_search[i].setStyle(Text::Bold);
		if (searchicator == i) {
			name_button_search[i].setFillColor(sf::Color::Black);
		}
		else {
			name_button_search[i].setFillColor(sf::Color::Blue);
		}
		name_button_search[i].setPosition(x, 10);
		name_button_search[i].setCharacterSize(32);
		x += 130;



	}

	name_button_search[0].setString("Name");
	name_button_search[1].setString("Album");
	name_button_search[2].setString("artist");
	name_button_search[3].setString("year");


	while (Searchwindow.isOpen())
	{

		sf::Event starting_search;
		while (Searchwindow.pollEvent(starting_search)) {
			mouse_position.x = sf::Mouse::getPosition(Searchwindow).x;
			mouse_position.y = sf::Mouse::getPosition(Searchwindow).y;
			cout << mouse_position.x
				<< "\t\t" << mouse_position.y << endl;
			if (starting_search.type == sf::Event::Closed) {
				Searchwindow.close();
				searching_results.clear();
			}
			//text Entred
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
			//ok function

			if (focus(search_text_box.getGlobalBounds(), mouse_position) && mouse_position.x < 195) {
				if (starting_search.type == sf::Event::MouseButtonPressed  && starting_search.mouseButton.button == sf::Mouse::Left) {
					{

						searching_results = search_display(userinput_search, searchicator);


					}


				}
			}


			float y = 120;
			for (int i = 0; i < searching_results.size(); ++i) {
				searching_results_box[i].setSize(Vector2f(110, 40));
				searching_results_box[i].setPosition(6, y);
				searching_results_box[i].setFillColor(Color::Transparent);
				text_searching_results[i].setFont(use_font);
				text_searching_results[i].setStyle(Text::Bold);
				text_searching_results[i].setColor(Color::Black);
				text_searching_results[i].setPosition(6, y);
				text_searching_results[i].setCharacterSize(22);
				text_searching_results[i].setString(searching_results[i]);
				y += 45;
			}
			//button function 
			for (int i = 0; i < 4; i++) {
				if (focus(button_search[i].getGlobalBounds(), mouse_position)) {
					if (starting_search.type == sf::Event::MouseButtonPressed  && starting_search.mouseButton.button == sf::Mouse::Left) {
						{
							searchicator = i;




						}


					}

				}
			}
			//playing button function
			for (int i = 0; i < searching_results.size(); ++i) {
				if (focus(text_searching_results[i].getGlobalBounds(), mouse_position)) {
					if (starting_search.type == sf::Event::MouseButtonPressed  && starting_search.mouseButton.button == sf::Mouse::Left) {
						playMusic(searching_results[i]);

					}
				}
			}

		}



		Searchwindow.draw(sprite);

		for (int i = 0; i < 4; i++) {
			Searchwindow.draw(button_search[i]);
			Searchwindow.draw(name_button_search[i]);

		}
		for (int i = 0; i < searching_results.size(); i++) {
			Searchwindow.draw(searching_results_box[i]);
			Searchwindow.draw(text_searching_results[i]);
		}
		for (int i = 0; i < 4; ++i) {
			if (searchicator == i) {
				Searchwindow.draw(search_text_box);

			}
		}
		Searchwindow.draw(search_text);
		

		Searchwindow.display();

	}



}





