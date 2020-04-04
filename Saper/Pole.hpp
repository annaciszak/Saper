#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include <memory>
#include <map>

class Pole {
public:
	char typ;
	int odkryte;
	int flaga;
	int stanPola;
	sf::Texture texture;
	sf::Sprite sprite;


	Pole();
	Pole(char typ, std::map<char, sf::Texture>&mapaTekstur);

	void draw(sf::RenderWindow&);
};

Pole::Pole() {
	this->typ = 'p';
	this->odkryte = 0;
	this->flaga = 0;
	this->stanPola = 0;
	this->texture.loadFromFile("bitmap.png");
	this->sprite.setTexture(this->texture);
}

Pole::Pole(char typ, std::map<char, sf::Texture>&mapaTekstur) {
	this->typ = typ;
	this->odkryte = 0;
	this->flaga = 0;
	this->stanPola = 0;
	this->sprite.setTexture(mapaTekstur[typ]);
}

void Pole::draw(sf::RenderWindow& w) {
	w.draw(this->sprite);
}
