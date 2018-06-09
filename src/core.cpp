//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by Fedora28_VM_MAC,
//

#include "../include/core.hpp"

irrlicht *motor;

Core::Core(irr::u32 width, irr::u32 height) : _menu(), _width(width),
	_height(height)
{
	_device = irr::createDevice(irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(width, height), 32, false,
		        true, false, nullptr);
	_menu = new Menu(_device, width, height);
}

Core::~Core()
{
	delete _menu;
}

void Core::mainDisplay()
{
	_menu->mainInit();
	while (_device->run()) {
		switch (_menu->loop<Main::main>()) {
		case Main::PLAY:
			_menu->stop();
			ChooseDisplay();
			break;
		case Main::CONFIG:
			_menu->stop();
			configDisplay();
			break;
		case Main::LOAD:
			_menu->stop();
			_menu->load();
			break;
		case Main::QUIT:
			return;
		default:
			break;
		}
	}
}

void Core::configDisplay()
{
	_menu->configInit();
	while (_device->run()) {
		switch (_menu->loop<Config::config>()) {
		case Config::BACK:
			_menu->stop();
			_menu->mainInit();
			return;
		case Config::MUTE:
			_menu->Mute();
			break;
		default:
			break;
		}
	}
}

void Core::Game(int nbPlayer)
{
	motor = new irrlicht(irr::video::EDT_OPENGL); // linux ? windows
	game oui(13, 11, _width, _height);
	std::pair<int, int> tmp;
	moveDir KeyOne = NOP;
	moveDir KeyTwo = NOP;
	moveDir KeyThree = NOP;
	moveDir KeyFour = NOP;

	oui.spawn(nbPlayer); // prendre du menu
	while (motor->isOk()) {
		oui.checkAllBomb();
		motor->loop(&oui);
		motor->save();
		// touche joueur 1
		if (oui.getPlayersAlive(0)) {
			KeyOne = motor->nextKeyOne();
			if (KeyOne != NOP) {
				auto p = oui.getBoard();
				for (auto ob = p.begin(); ob != p.end(); ++ob) {
					tmp = ob->second->getPosition();
					if (ob->second->getStatus() == PLAYER && ob->second->getId() == 1)
						ob->second->movePlayer(KeyOne, &oui);
				}
				KeyOne = NOP;
			}
		}
		// touche joueur 2
		if (oui.getPlayersAlive(1)) {
			KeyTwo = motor->nextKeyTwo();
			if (KeyTwo != NOP) {
				auto p = oui.getBoard();
				for (auto ob = p.begin(); ob != p.end(); ++ob) {
					tmp = ob->second->getPosition();
					if (ob->second->getStatus() == PLAYER && ob->second->getId() == 2)
						ob->second->movePlayer(KeyTwo, &oui);
				}
				KeyTwo = NOP;
			}
		}
		// touche joueur 3
		if (oui.getPlayersAlive(2)) {
			KeyThree = motor->nextKeyThree();
			if (KeyThree != NOP) {
				auto p = oui.getBoard();
				for (auto ob = p.begin(); ob != p.end(); ++ob) {
					tmp = ob->second->getPosition();
					if (ob->second->getStatus() == PLAYER && ob->second->getId() == 3)
						ob->second->movePlayer(KeyThree, &oui);
				}
				KeyThree = NOP;
			}
		}
		// touche joueur 4
		if (oui.getPlayersAlive(3)) {
			KeyFour = motor->nextKeyFour();
			if (KeyFour != NOP) {
				auto p = oui.getBoard();
				for (auto ob = p.begin(); ob != p.end(); ++ob) {
					tmp = ob->second->getPosition();
					if (ob->second->getStatus() == PLAYER && ob->second->getId() == 4)
						ob->second->movePlayer(KeyFour, &oui);
				}
				KeyFour = NOP;
			}
		}

	}
}

void Core::ChooseDisplay()
{
	_menu->menuChooseInit();
	while (_device->run()) {
		switch (_menu->loop<Choose::choose>()) {
		case Choose::SOLO:
			_menu->close();
			Game(1);
			return;
		case Choose::TWO:
			_menu->close();
			Game(2);
			break;
		case Choose::THREE:
			_menu->close();
			Game(3);
			break;
		case Choose::FOUR:
			_menu->close();
			Game(4);
			break;
		case Choose::BACK:
			_menu->stop();
			_menu->mainInit();
			return;
		default:
			break;
		}
	}
}
