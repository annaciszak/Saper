#pragma once
#include<map>
#include<algorithm>
#include <vector>
#include <chrono>
#include "SFML/Graphics.hpp"
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Pole.hpp"
#include "Okno.hpp"
#include "Menu.hpp"
#include<fstream>

const float PoleWidth = 32;
const float PoleHeight = 32;
int czyFlagi = 0;

typedef std::vector<std::vector<Pole>> Plansza;

class Gra {
public:
	std::map<char, sf::Texture> mapaTekstur;

	static std::vector<std::vector<int>> wyniki;

	int liczbaFlag = 0;
	int stanGry;
	int ileNieBomb;
	int trudnosc;
	
	Plansza plansza;
	std::ostringstream flagi;
	sf::Text ileFlag;
	int iloscKolumn;
	int iloscWierszy;
	sf::Texture usmiech;
	sf::Texture smutek;
	sf::Texture wygrana;
	sf::Texture wstecz;
	std::ostringstream clock;
	sf::Text clockText;
	sf::Sprite u;
	sf::Sprite ws;
	sf::Sprite win;

	Gra(int iloscKolumn, int iloscWierszy, int trudnosc);
	void setup();
	int start(sf::RenderWindow& w);
	int handleMousePress(Plansza& plansza, sf::RenderWindow& w);
	void draw(sf::RenderWindow& w);
	void zaladujTekstury();
	void loadHighscore();
	void setHighscore(int time);
	void saveHighscore();
	void ifPuste(int w, int h);
	void ifLiczbazaPustym(int w, int h);
	bool czyOdkryte(int w, int h);
	int obslugaZdarzen(sf::RenderWindow& w);
	void obslugaBomb(Plansza& plansza, int i, int j);
	void obslugaFlag(Plansza& plansza, int i, int j);
	std::chrono::time_point<std::chrono::steady_clock> timer;
	std::chrono::seconds aktualneSekundy;
};

std::vector<std::vector<int>> Gra::wyniki = std::vector<std::vector<int>>(6, std::vector<int>(5));

Gra::Gra(int iloscKolumn, int iloscWierszy, int trudnosc) {
	plansza = std::vector<std::vector<Pole>>(iloscKolumn, std::vector<Pole>(iloscWierszy));
	this->stanGry = 0;
	this->iloscKolumn = iloscKolumn;
	this->iloscWierszy = iloscWierszy;
	this->trudnosc = trudnosc;
}

void Gra::zaladujTekstury() {
	//Generowanie planszy

	//³adowanie usmiechu i smutku
	usmiech.loadFromFile("usmiech.png");
	usmiech.setSmooth(true);
	smutek.loadFromFile("smutek.png");
	smutek.setSmooth(true);

	u.setTexture(this->usmiech);

	wygrana.loadFromFile("win.png");
	wygrana.setSmooth(true);
	win.setTexture(this->wygrana);


	//wstecz
	wstecz.loadFromFile("wstecz.png");
	wstecz.setSmooth(true);
	ws.setTexture(this->wstecz);

	sf::Texture t;
	t.loadFromFile("0.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('0', t));


	t.loadFromFile("bitmap.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('p', t));

	t.loadFromFile("bomba.png");
	t.setSmooth(true);
	mapaTekstur.insert(std::pair<char, sf::Texture>('b', t));

	t.loadFromFile("1.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('1', t));

	t.loadFromFile("2.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('2', t));

	t.loadFromFile("3.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('3', t));

	t.loadFromFile("4.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('4', t));

	t.loadFromFile("5.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('5', t));

	t.loadFromFile("6.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('6', t));

	t.loadFromFile("7.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('7', t));

	t.loadFromFile("8.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('8', t));

	t.loadFromFile("bombax.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('x', t));

	t.loadFromFile("flaga.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('f', t));

	t.loadFromFile("flagax.png");
	t.setSmooth(false);
	mapaTekstur.insert(std::pair<char, sf::Texture>('h', t));
}

void Gra::loadHighscore() {
	std::fstream w("wyniki.txt", std::ios::in);

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
		this->loadHighscore();
	}

	w.close();
}

void Gra::setHighscore(int time) {
	int index = this->trudnosc - 1;

	wyniki[index].push_back(time);
	std::sort(wyniki[index].begin(), wyniki[index].end());
	wyniki[index].pop_back();
}

void Gra::saveHighscore() {
	std::fstream w("wyniki.txt", std::ios::out);
	w.clear();
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			w << wyniki[i][j] << " ";
		}
		w << "\n";
	}

	w.close();
}

void Gra::setup() {
	if (mapaTekstur.size() == 0) zaladujTekstury();
	srand(time(NULL));
	for (int w = 0; w < iloscKolumn; w++) {
		for (int h = 0; h < iloscWierszy; h++) {

			if (rand() % 100 < 70) {
				plansza[w][h] = Pole('0', mapaTekstur);

				ileNieBomb++;
			}
			else {
				plansza[w][h] = Pole('b', mapaTekstur);
				liczbaFlag++;
			}

			if (trudnosc == 1) {
				plansza[w][h].sprite.setScale(0.25, 0.25);
			}
			if (trudnosc == 2) {
				plansza[w][h].sprite.setScale(0.2, 0.2);
			}
			if (trudnosc == 3) {
				plansza[w][h].sprite.setScale(0.16, 0.16);
			}
		}
	}

	int t;
	for (int w = 0; w < iloscWierszy; w++) {
		for (int h = 0; h < iloscKolumn; h++) {
			int ileBomb = 0;

			if (plansza[w][h].typ == '0') {

				if (w == 0 && h == 0) {
					if (plansza[w][h + 1].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h + 1].typ == 'b')
						ileBomb++;
				}
				if (w == 0 && h != 0 && h != (iloscKolumn - 1)) {
					if (plansza[w][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w][h + 1].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h + 1].typ == 'b')
						ileBomb++;
				}

				if ((w == 0) && (h == (iloscKolumn - 1))) {
					if (plansza[w][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h].typ == 'b')
						ileBomb++;
				}

				if (w != 0 && w != (iloscWierszy - 1) && h == 0) {
					if (plansza[w - 1][h].typ == 'b')
						ileBomb++;
					if (plansza[w - 1][h + 1].typ == 'b')
						ileBomb++;
					if (plansza[w][h + 1].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h + 1].typ == 'b')
						ileBomb++;
				}

				if (w == (iloscWierszy - 1) && h == 0) {
					if (plansza[w - 1][h].typ == 'b')
						ileBomb++;
					if (plansza[w - 1][h + 1].typ == 'b')
						ileBomb++;
					if (plansza[w][h + 1].typ == 'b')
						ileBomb++;
				}

				if (w == (iloscWierszy - 1) && h != 0 && h != (iloscKolumn - 1)) {
					if (plansza[w - 1][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w - 1][h].typ == 'b')
						ileBomb++;
					if (plansza[w - 1][h + 1].typ == 'b')
						ileBomb++;
					if (plansza[w][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w][h + 1].typ == 'b')
						ileBomb++;
				}

				if (w == (iloscWierszy - 1) && h == (iloscKolumn - 1)) {
					if (plansza[w - 1][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w - 1][h].typ == 'b')
						ileBomb++;
					if (plansza[w][h - 1].typ == 'b')
						ileBomb++;
				}

				if (w != 0 && w != (iloscWierszy - 1) && h == (iloscKolumn - 1)) {
					if (plansza[w - 1][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w - 1][h].typ == 'b')
						ileBomb++;
					if (plansza[w][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h].typ == 'b')
						ileBomb++;
				}

				if (w != 0 && w != (iloscWierszy - 1) && h != 0 && h != (iloscKolumn - 1)) {
					if (plansza[w - 1][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w - 1][h].typ == 'b')
						ileBomb++;
					if (plansza[w - 1][h + 1].typ == 'b')
						ileBomb++;
					if (plansza[w][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w][h + 1].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h - 1].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h].typ == 'b')
						ileBomb++;
					if (plansza[w + 1][h + 1].typ == 'b')
						ileBomb++;
				}
				plansza[w][h].typ = (char)((ileBomb)+48);
			}
		}
	}

	for (int w = 0; w < iloscKolumn; w++) {
		for (int h = 0; h < iloscWierszy; h++) {
			t = h;
			plansza[w][h].sprite.setTexture(mapaTekstur.at('p'));
			plansza[w][h].sprite.setOrigin(sf::Vector2f(plansza[w][h].sprite.getGlobalBounds().left + (plansza[w][h].sprite.getLocalBounds().width / 2),
				plansza[w][h].sprite.getGlobalBounds().top + (plansza[w][h].sprite.getLocalBounds().height / 2)));
			if (trudnosc == 1) {
				plansza[w][h].sprite.setPosition(sf::Vector2f(((w * PoleWidth)*0.95) + (8 * w) + 122, ((h* PoleHeight)*0.95) + (8 * h) + 136));
			}

			if (trudnosc == 2) {
				plansza[w][h].sprite.setPosition(sf::Vector2f(((w * PoleWidth)*0.8) + (5 * w) + 90, ((h* PoleHeight)*0.8) + (5 * h) + 112));
			}

			if (trudnosc == 3) {
				plansza[w][h].sprite.setPosition(sf::Vector2f(((w * PoleWidth)*0.8) + 68, ((h* PoleHeight)*0.8) + 80));
			}
		}
	}
	timer = std::chrono::high_resolution_clock::now();
	this->loadHighscore();

	win.setOrigin(sf::Vector2f((win.getGlobalBounds().left + win.getLocalBounds().width / 2), (win.getGlobalBounds().top + win.getLocalBounds().height / 2)));
	win.setPosition(sf::Vector2f(256, 95));
}

bool Gra::czyOdkryte(int w, int h) {
	if (plansza[w][h].odkryte == 1) {
		return true;
	}
	else
		return false;
}

void Gra::ifLiczbazaPustym(int w, int h) {
	plansza[w][h].sprite.setTexture(mapaTekstur.at(plansza[w][h].typ));
}


void Gra::ifPuste(int w, int h) {

	plansza[w][h].sprite.setTexture(mapaTekstur.at('0'));
	if ((w + 1) < iloscKolumn) {
		if (plansza[w + 1][h].flaga == 0) {
			if ((czyOdkryte(w + 1, h)) == false) {
				if (plansza[w + 1][h].typ == '0') {
					plansza[w + 1][h].odkryte = 1;
					ileNieBomb--;

					ifPuste(w + 1, h);
				}
				else if (plansza[w + 1][h].typ != 'b') {
					plansza[w + 1][h].sprite.setTexture(mapaTekstur.at(plansza[w + 1][h].typ));
					plansza[w + 1][h].odkryte = 1;
					ileNieBomb--;
				}
			}
		}
	}

	if (((w + 1) < iloscKolumn) && (h - 1 >= 0)) {
		if (plansza[w + 1][h - 1].flaga == 0) {
			if ((czyOdkryte(w + 1, h - 1)) == false) {
				if (plansza[w + 1][h - 1].typ == '0') {
					plansza[w + 1][h - 1].odkryte = 1;
					ileNieBomb--;

					ifPuste(w + 1, h - 1);
				}
				else if ((plansza[w + 1][h - 1].typ != 'b')) {
					plansza[w + 1][h - 1].sprite.setTexture(mapaTekstur.at(plansza[w + 1][h - 1].typ));
					plansza[w + 1][h - 1].odkryte = 1;
					ileNieBomb--;
				}
			}
		}
	}

	if ((w + 1) < iloscKolumn && (h + 1 < iloscWierszy)) {
		if (plansza[w + 1][h + 1].flaga == 0) {
			if ((czyOdkryte(w + 1, h + 1)) == false) {
				if (plansza[w + 1][h + 1].typ == '0') {
					plansza[w + 1][h + 1].odkryte = 1;
					ileNieBomb--;

					ifPuste(w + 1, h + 1);
				}
				else if (plansza[w + 1][h + 1].typ != 'b') {
					plansza[w + 1][h + 1].sprite.setTexture(mapaTekstur.at(plansza[w + 1][h + 1].typ));
					plansza[w + 1][h + 1].odkryte = 1;
					ileNieBomb--;
				}
			}
		}
	}

	if (((w - 1) >= 0) && (h - 1 >= 0)) {
		if (plansza[w - 1][h - 1].flaga == 0) {
			if ((czyOdkryte(w - 1, h - 1)) == false) {
				if (plansza[w - 1][h - 1].typ == '0') {
					plansza[w - 1][h - 1].odkryte = 1;
					ileNieBomb--;

					ifPuste(w - 1, h - 1);
				}
				else if (plansza[w - 1][h - 1].typ != 'b') {
					plansza[w - 1][h - 1].sprite.setTexture(mapaTekstur.at(plansza[w - 1][h - 1].typ));
					plansza[w - 1][h - 1].odkryte = 1;
					ileNieBomb--;
				}
			}
		}
	}


	if (((w - 1) >= 0) && (h + 1 < iloscWierszy)) {
		if (plansza[w - 1][h + 1].flaga == 0) {
			if ((czyOdkryte(w - 1, h + 1)) == false) {
				if (plansza[w - 1][h + 1].typ == '0') {
					plansza[w - 1][h + 1].odkryte = 1;
					ileNieBomb--;

					ifPuste(w - 1, h + 1);
				}
				else if (plansza[w - 1][h + 1].typ != 'b') {
					plansza[w - 1][h + 1].sprite.setTexture(mapaTekstur.at(plansza[w - 1][h + 1].typ));
					plansza[w - 1][h + 1].odkryte = 1;
					ileNieBomb--;
				}
			}
		}
	}

	if (((w - 1) >= 0)) {
		if (plansza[w - 1][h].flaga == 0) {
			if ((czyOdkryte(w - 1, h)) == false) {
				if (plansza[w - 1][h].typ == '0') {
					plansza[w - 1][h].odkryte = 1;
					ileNieBomb--;

					ifPuste(w - 1, h);
				}
				else if (plansza[w - 1][h].typ != 'b') {
					plansza[w - 1][h].sprite.setTexture(mapaTekstur.at(plansza[w - 1][h].typ));
					plansza[w - 1][h].odkryte = 1;
					ileNieBomb--;

				}
			}
		}
	}

	if ((h + 1) < iloscWierszy) {
		if (plansza[w][h + 1].flaga == 0) {
			if ((czyOdkryte(w, h + 1)) == false) {
				if (plansza[w][h + 1].typ == '0') {
					plansza[w][h + 1].odkryte = 1;
					ileNieBomb--;

					ifPuste(w, h + 1);
				}
				else if (plansza[w][h + 1].typ != 'b') {
					plansza[w][h + 1].sprite.setTexture(mapaTekstur.at(plansza[w][h + 1].typ));
					plansza[w][h + 1].odkryte = 1;
					ileNieBomb--;
				}
			}
		}
	}

	if ((h - 1) >= 0) {
		if (plansza[w][h - 1].flaga == 0) {
			if ((czyOdkryte(w, h - 1)) == false) {
				if (plansza[w][h - 1].typ == '0') {
					plansza[w][h - 1].odkryte = 1;
					ileNieBomb--;

					ifPuste(w, h - 1);
				}
				else if (plansza[w][h - 1].typ != 'b') {
					plansza[w][h - 1].sprite.setTexture(mapaTekstur.at(plansza[w][h - 1].typ));
					plansza[w][h - 1].odkryte = 1;
					ileNieBomb--;
				}
			}
		}
	}
}

void Gra::obslugaBomb(Plansza& plansza, int i, int j) {
	plansza[i][j].sprite.setTexture(mapaTekstur.at('x'));
	plansza[i][j].odkryte = 1;
	stanGry = 1;
	for (int m = 0; m < iloscKolumn; m++) {
		for (int n = 0; n < iloscWierszy; n++) {
			if (plansza[m][n].odkryte != 1) {
				if (plansza[m][n].flaga == 1) {
					if (plansza[m][n].typ != 'b') {

						plansza[m][n].sprite.setTexture(mapaTekstur.at('h'));
					}
				}
				else {
					plansza[m][n].sprite.setTexture(mapaTekstur.at(plansza[m][n].typ));
				}
			}
		}
	}
}

void Gra::obslugaFlag(Plansza& plansza, int i, int j) {
	if (plansza[i][j].odkryte == 0) {
		if (plansza[i][j].flaga == 1) {
			plansza[i][j].sprite.setTexture(mapaTekstur.at('p'));
			plansza[i][j].flaga = 0;
			liczbaFlag++;
			flagi.str("");
			flagi << "Flags: " << liczbaFlag;
			ileFlag.setString(flagi.str());
		}
		else {
			if (liczbaFlag > 0) {
				plansza[i][j].flaga = 1;
				plansza[i][j].sprite.setTexture(mapaTekstur.at('f'));
				liczbaFlag--;
			}
			flagi.str("");
			flagi << "Flags: " << liczbaFlag;
			ileFlag.setString(flagi.str());
		}
	}
}

int Gra::handleMousePress(Plansza& plansza, sf::RenderWindow& w) {
	auto mouse_pos = sf::Mouse::getPosition(w);
	auto translated_pos = w.mapPixelToCoords(mouse_pos);

	if (ws.getGlobalBounds().contains(translated_pos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			return 1;
		}
	}

	if (stanGry == 1) {
		if (u.getGlobalBounds().contains(translated_pos)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (trudnosc == 1) {
					Gra m(8, 8, 1);
					m.start(w);
					return 1;
				}
				if (trudnosc == 2) {
					Gra m(12, 12, 2);
					m.start(w);
					return 1;
				}
				if (trudnosc == 3) {
					Gra m(16, 16, 3);
					m.start(w);
					return 1;
				}
			}
		}
	}

	if (stanGry == 0) {
		for (int i = 0; i < iloscKolumn; i++) {
			for (int j = 0; j < iloscWierszy; j++) {
				if (plansza[i][j].sprite.getGlobalBounds().contains(translated_pos)) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						if (plansza[i][j].flaga != 1) {
							if (plansza[i][j].typ == '0') {
								ifPuste(i, j);
							}
							else if (plansza[i][j].typ == 'b') {
								obslugaBomb(plansza, i, j);
							}
							else {
								plansza[i][j].sprite.setTexture(mapaTekstur.at(plansza[i][j].typ));
								plansza[i][j].odkryte = 1;
								ileNieBomb--;
							}
						}
					}

					if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

						obslugaFlag(plansza, i, j);
					}
				}
			}
		}
	}
}

int Gra::obslugaZdarzen(sf::RenderWindow& w) {

	sf::Event event;

	while (w.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			w.close();

		if (event.type == sf::Event::MouseButtonPressed)
			return this->handleMousePress(plansza, w);
	}
}


void Gra::draw(sf::RenderWindow& w) {
	w.clear(sf::Color::White);

	sf::Font fontFlag;
	fontFlag.loadFromFile("mononoki.ttf");
	flagi.str("");
	flagi.clear();
	flagi << "Flags: " << liczbaFlag;

	//win.setPosition(sf::Vector2f(70, 50));


		
	ileFlag.setCharacterSize(18);
	ileFlag.setPosition(sf::Vector2f(30, 20));
	ileFlag.setFont(fontFlag);
	ileFlag.setFillColor(sf::Color::Black);
	ileFlag.setString(flagi.str());

	if (ileNieBomb == 0 && liczbaFlag == 0) {
		stanGry = 2;
		for (int i = 0; i < iloscKolumn; i++) {
			for (int j = 0; j < iloscWierszy; j++) {
				if ((plansza[i][j].typ == 'b')&&(plansza[i][j].odkryte==1)) {
					plansza[i][j].sprite.setTexture(mapaTekstur.at(plansza[i][j].typ));
				}
			}
		}
	}

	if (stanGry == 0) {
		aktualneSekundy = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - timer);
	}

	clock.str("");
	clock.clear();
	clock << aktualneSekundy.count();

	clockText.setCharacterSize(18);
	clockText.setPosition(sf::Vector2f(450, 20));
	clockText.setFont(fontFlag);
	clockText.setFillColor(sf::Color::Black);
	clockText.setString(clock.str());

	w.draw(ileFlag);
	w.draw(clockText);

	for (int x = 0; x < iloscKolumn; x++) {
		for (int y = 0; y < iloscWierszy; y++) {
			plansza[x][y].draw(w);
		}
	}

	if (trudnosc == 3) {
		u.setScale(sf::Vector2f(0.3, 0.3));
		u.setPosition(sf::Vector2f(240, 0));
		ws.setScale(sf::Vector2f(0.3, 0.3));
		ws.setPosition(sf::Vector2f(150, 10));
	}
	else {
		u.setScale(sf::Vector2f(0.5, 0.5));
		u.setPosition(sf::Vector2f(224, 0));
		ws.setScale(sf::Vector2f(0.3, 0.3));
		ws.setPosition(sf::Vector2f(150, 10));

	}

	if (stanGry == 1) {
		u.setTexture(this->smutek);
	}


	w.draw(u);
	w.draw(ws);
	if (stanGry == 2) {
		w.draw(win);
	}
	w.display();
}

int Gra::start(sf::RenderWindow& w) {
	this->setup();
	int czyPowrotDoMenuGlownego;
	bool scoreSaved = false;
	while (w.isOpen()) {
		czyPowrotDoMenuGlownego = this->obslugaZdarzen(w);
		this->draw(w);

		if (czyPowrotDoMenuGlownego == 1) {
			break;
		}

		if (stanGry == 2 && !scoreSaved) {
			this->setHighscore(this->aktualneSekundy.count());
			this->saveHighscore();
			scoreSaved = true;
		}
	}

	return 0;
}
