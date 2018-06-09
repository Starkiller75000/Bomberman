//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by Fedora28_VM_MAC,
//

#ifndef BOMBERMAN_CORE_HPP
#define BOMBERMAN_CORE_HPP

#include "menu.hpp"
#include "../indie/inc/element.hpp"
#include "../indie/inc/irrlicht.hpp"
#include "../indie/inc/game.hpp"

class Core
{
	public:
	Core(irr::u32, irr::u32);
	~Core();
	void mainDisplay();
	void configDisplay();
	void Game(int);
	void ChooseDisplay();

	private:
	Menu *_menu;
	irr::IrrlichtDevice *_device;
	std::map<int, element*> map;
	irr::u32 _width;
	irr::u32 _height;
	irr::scene::ISceneManager *sceneManager;
};

#endif //BOMBERMAN_CORE_HPP
