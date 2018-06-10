//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by Fedora28_VM_MAC,
//

#ifndef BOMBERMAN_CORE_HPP
#define BOMBERMAN_CORE_HPP

#include "menu.hpp"
#include "element.hpp"
#include "irrlicht.hpp"
#include "game.hpp"

class Core
{
	public:
	Core(irr::u32, irr::u32);
	~Core();
	void mainDisplay();
	void configDisplay();
	void Game(int, bool);
	void ChooseDisplay();
	void checkMainCases();
	void checkSizeChoosen();
	void checkGameChoosen();
	void backToMenu();
	void player1(game *);
	void player2(game *);
	void player3(game *);
	void player4(game *);
	void gameMode(game *);

	private:
	Menu *_menu;
	irr::IrrlichtDevice *_device;
	std::map<int, element*> map;
	irr::u32 _width;
	irr::u32 _height;
	int nb;
	int sizeX;
	int sizeY;
	moveDir KeyOne;
	moveDir KeyTwo;
	moveDir KeyThree;
	moveDir KeyFour;
	std::pair<int, int> tmp;
	int winner;
};

#endif //BOMBERMAN_CORE_HPP
