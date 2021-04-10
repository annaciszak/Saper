#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>

class Menu {
public:
	Menu(sf::RenderWindow&);
	void setupBackground(sf::RenderWindow&);
	int MainMenu(sf::RenderWindow&);
	int Trudnosc(sf::RenderWindow&);
	int TrudnoscCzasowa(sf::RenderWindow& w);
	int Statistics(sf::RenderWindow& w);
private:
	sf::Sprite background;
	sf::Font font;
};

void Menu::setupBackground(sf::RenderWindow& w) {
	sf::Texture texture;
	sf::Vector2u TextureSize;
	sf::Vector2u WindowSize;
	texture.loadFromFile("bitmap.png");
	TextureSize = texture.getSize();
	WindowSize = w.getSize();

	float ScaleX = (float)WindowSize.x / TextureSize.x;
	float ScaleY = (float)WindowSize.y / TextureSize.y;

	this->background.setTexture(texture);
	this->background.setScale(ScaleX, ScaleY);
}

Menu::Menu(sf::RenderWindow& w) {
	this->font.loadFromFile("mononoki.ttf");
	this->setupBackground(w);
}

int Menu::MainMenu(sf::RenderWindow& w) {

	const int ileNapisow = 4;

	sf::Text tekst[ileNapisow];

	std::string napisy[] = { "Standard", "Time attack", "Statistics", "Quit" };

	for (int i = 0; i < ileNapisow; i++) {
		tekst[i].setFont(this->font);
		tekst[i].setString(napisy[i]);
		tekst[i].setOrigin(sf::Vector2f(tekst[i].getGlobalBounds().left + (tekst[i].getLocalBounds().width / 2),
			tekst[i].getGlobalBounds().top + (tekst[i].getLocalBounds().height / 2)));
		tekst[i].setPosition(sf::Vector2f((w.getSize().x / 2), (w.getSize().y / ileNapisow) * (i + 1) - 90));
	}

	int wybrany = 0;

	while (true) {
		sf::Event event;

		while (w.pollEvent(event)) {

			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased &&
				event.key.code == sf::Keyboard::Escape)) {
				return -1;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
			{
				if (wybrany != 0) wybrany--;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
			{
				if (wybrany != ileNapisow - 1) wybrany++;

			}
			if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
				switch (wybrany) {
				case 0:
					return this->Trudnosc(w);
				case 1:
					return this->TrudnoscCzasowa(w);
					break;
				case 2:
					return this->Statistics(w);
					break;
				case 3:
					return -1;
					break;
				default:
					std::cout << napisy[wybrany] << std::endl;
				}
			}
		}

		for (int i = 0; i < ileNapisow; i++) {
			if (i == wybrany)
				tekst[i].setFillColor(sf::Color::Red);
			else
				tekst[i].setFillColor(sf::Color::White);
		}

		w.clear();

		for (int i = 0; i < ileNapisow; i++)
			w.draw(tekst[i]);

		w.display();
	}
}

int Menu::Trudnosc(sf::RenderWindow& w) {

	const int ileNapisow = 4;

	sf::Text tekst[ileNapisow];

	std::string napisy[] = { "Easy", "Medium", "Hard", "Return" };

	for (int i = 0; i < ileNapisow; i++) {
		tekst[i].setFont(this->font);
		tekst[i].setString(napisy[i]);
		tekst[i].setOrigin(sf::Vector2f(tekst[i].getGlobalBounds().left + (tekst[i].getLocalBounds().width / 2),
			tekst[i].getGlobalBounds().top + (tekst[i].getLocalBounds().height / 2)));
		tekst[i].setPosition(sf::Vector2f((w.getSize().x / 2), (w.getSize().y / ileNapisow) * (i + 1) - 90));
	}

	int wybrany = 0;

	while (true) {
		sf::Event event;

		while (w.pollEvent(event)) {

			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased &&
				event.key.code == sf::Keyboard::Escape)) {
				return -1;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
			{
				if (wybrany != 0) wybrany--;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
			{
				if (wybrany != ileNapisow - 1) wybrany++;

			}

			if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
				switch (wybrany) {
				case 0:
					return 1;
					break;
				case 1:
					return 2;
					break;
				case 2:
					return 3;
					break;
				case 3:
					return 0;
					break;
				default:
					std::cout << napisy[wybrany] << std::endl;
				}
			}
		}

		for (int i = 0; i < ileNapisow; i++) {
			if (i == wybrany)
				tekst[i].setFillColor(sf::Color::Red);
			else
				tekst[i].setFillColor(sf::Color::White);
		}

		w.clear();

		for (int i = 0; i < ileNapisow; i++)
			w.draw(tekst[i]);

		w.display();
	}
}

std::vector<std::vector<std::string>> loadHighscore() {

	std::fstream w("wyniki.txt", std::ios::in);

	std::vector<std::vector<std::string>> wyniki = std::vector<std::vector<std::string>>(6, std::vector<std::string>(5));

	if (w.peek() != std::ifstream::traits_type::eof()) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 5; j++) {
				w >> wyniki[i][j];
			}
		}
	}
	else {
		w.close();
		w.open("wyniki.txt", std::ios::out);
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 5; j++) {
				if (i < 3)
					w << INT_MAX << " ";
				else
					w << -1 << " ";
			}
			w << '\n';
		}
		w.close();
		return loadHighscore();
	}

	w.close();
	return wyniki;
}

int Menu::Statistics(sf::RenderWindow& w) {

	const int ileNapisow = 1;

	sf::Text tekst;

	std::string napis = "Return";

	tekst.setFont(this->font);
	tekst.setString(napis);
	tekst.setOrigin(sf::Vector2f(tekst.getGlobalBounds().left + (tekst.getLocalBounds().width / 2),
		tekst.getGlobalBounds().top + (tekst.getLocalBounds().height / 2)));
	tekst.setPosition(sf::Vector2f(w.getSize().x / 2, w.getSize().y - 44));
	tekst.setFillColor(sf::Color::Red);

	std::vector<std::vector<std::string>> wyniki = loadHighscore();

	std::vector<std::string> naglowek{"", "1", "2", "3", "4", "5"};

	wyniki.insert(wyniki.begin(), naglowek);

	wyniki[1].insert(wyniki[1].begin(), "East");
	wyniki[2].insert(wyniki[2].begin(), "Medium");
	wyniki[3].insert(wyniki[3].begin(), "Hard");
	wyniki[4].insert(wyniki[4].begin(), "Time attack\n  Easy");
	wyniki[5].insert(wyniki[5].begin(), "Time attack\n  Medium");
	wyniki[6].insert(wyniki[6].begin(), "Time attack\n  Hard");

	std::vector<std::vector<sf::Text>> test(7, std::vector<sf::Text>(6));

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			if (i != 0 || j != 0) {
				if (std::atoi(wyniki[i][j].c_str()) == INT_MAX) wyniki[i][j] = "-";
				if (std::atoi(wyniki[i][j].c_str()) == -1) wyniki[i][j] = "-";
			}
			test[i][j].setFont(this->font);
			test[i][j].setScale(sf::Vector2f(0.4, 0.4));
			test[i][j].setString(wyniki[i][j]);
			test[i][j].setPosition(sf::Vector2f(((w.getSize().x / 8)*(j+1)) + 15, (w.getSize().y / 8) * (i + 1) - 44));
			test[i][j].setFillColor(sf::Color::White);
		}
	}

	while (true) {
		sf::Event event;

		while (w.pollEvent(event)) {

			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased &&
				event.key.code == sf::Keyboard::Escape)) {
				return -1;
			}

			if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
				return 0;
			}
		}

		w.clear();

		w.draw(tekst);

		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				w.draw(test[i][j]);
			}
		}

		w.display();
	}
}

int Menu::TrudnoscCzasowa(sf::RenderWindow& w) {

	const int ileNapisow = 4;

	sf::Text tekst[ileNapisow];

	std::string napisy[] = { "Easy", "Medium", "Hard", "Return" };

	for (int i = 0; i < ileNapisow; i++) {
		tekst[i].setFont(this->font);
		tekst[i].setString(napisy[i]);
		tekst[i].setOrigin(sf::Vector2f(tekst[i].getGlobalBounds().left + (tekst[i].getLocalBounds().width / 2),
			tekst[i].getGlobalBounds().top + (tekst[i].getLocalBounds().height / 2)));
		tekst[i].setPosition(sf::Vector2f((w.getSize().x / 2), (w.getSize().y / ileNapisow) * (i + 1) - 90));
	}

	int wybrany = 0;

	while (true) {
		sf::Event event;

		while (w.pollEvent(event)) {

			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased &&
				event.key.code == sf::Keyboard::Escape)) {
				return -1;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
			{
				if (wybrany != 0) wybrany--;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
			{
				if (wybrany != ileNapisow - 1) wybrany++;

			}

			if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
				switch (wybrany) {
				case 0:
					return 4;
					break;
				case 1:
					return 5;
					break;
				case 2:
					return 6;
					break;
				case 3:
					return 0;
					break;
				default:
					std::cout << napisy[wybrany] << std::endl;
				}
			}
		}

		for (int i = 0; i < ileNapisow; i++) {
			if (i == wybrany)
				tekst[i].setFillColor(sf::Color::Red);
			else
				tekst[i].setFillColor(sf::Color::White);
		}

		w.clear();

		for (int i = 0; i < ileNapisow; i++)
			w.draw(tekst[i]);

		w.display();
	}
}