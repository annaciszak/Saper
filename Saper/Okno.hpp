#pragma once
#include "SFML/Graphics.hpp"

#include <memory>
#include <iostream>

#include "Gra.hpp"
#include"GraNaCzas.hpp"
#include "Menu.hpp"

enum STANY_OKNO { EXIT = -1, MENU = 0, GRA = 1, GRASREDNI = 2, GRATRUDNY = 3, GRAS = 4, GRASSREDNI = 5, GRASTRUDNY = 6};

class Okno {
public:
	sf::RenderWindow window;
	int stan;

	Okno();
	void start();
	void rysujGre();
	void rysujGreSredni();
	void rysujGreTrudny();
	void rysujGreS();
	void rysujGreSSredni();
	void rysujGreSTrudny();
	void rysujMenu();
	void exit();
};

Okno::Okno() {
	this->window.create(sf::VideoMode(512, 512), "Minesweeper");
	this->stan = STANY_OKNO::MENU;
}

void Okno::start() {
	while (this->window.isOpen()) {
		switch (stan) {
		case STANY_OKNO::GRA:
			this->rysujGre();
			break;
		case STANY_OKNO::GRASREDNI:
			this->rysujGreSredni();
			break;
		case STANY_OKNO::GRATRUDNY:
			this->rysujGreTrudny();
			break;
		case STANY_OKNO::GRAS:
			this->rysujGreS();
			break;
		case STANY_OKNO::GRASSREDNI:
			this->rysujGreSSredni();
			break;
		case STANY_OKNO::GRASTRUDNY:
			this->rysujGreSTrudny();
			break;
		case STANY_OKNO::MENU:
			this->rysujMenu();
			break;
		case STANY_OKNO::EXIT:
			this->exit();
			break;
		}
	}
}

void Okno::rysujGre() {
	Gra g(8, 8, 1);
	this->stan = g.start(this->window);
}

void Okno::rysujGreSredni() {
	Gra g(12, 12, 2);
	this->stan = g.start(this->window);
}

void Okno::rysujGreTrudny() {
	Gra g(16, 16, 3);
	this->stan = g.start(this->window);
}

void Okno::rysujGreS() {
	GraCzasowa g(8, 8, 1, 60);
	this->stan = g.start(this->window);
}

void Okno::rysujGreSSredni() {
	GraCzasowa g(12, 12, 2, 45);
	this->stan = g.start(this->window);
}

void Okno::rysujGreSTrudny() {
	GraCzasowa g(16, 16, 3, 30);
	this->stan = g.start(this->window);
}
void Okno::rysujMenu() {
	Menu m(this->window);
	this->stan = m.MainMenu(this->window);
}

void Okno::exit() {
	this->window.close();
}