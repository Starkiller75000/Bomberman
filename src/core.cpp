//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by Fedora28_VM_MAC,
//

#include "../include/core.hpp"

irrlicht *motor;

Core::Core(irr::u32 width, irr::u32 height) : _menu(), _width(width),
	_height(height), sizeX(int(13)), sizeY(int(11))
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
	while (_device->run())
		checkMainCases();
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
		checkSizeChoosen();
	}
}

void Core::Game(int nbPlayer, bool loaded)
{
	std::pair<int, int> mapSize(sizeX, sizeY);
	std::pair<int, int> screenSize(_width, _height);
	motor = new irrlicht(irr::video::EDT_OPENGL, sizeX, sizeY);
	game oui(mapSize, loaded, screenSize, nbPlayer);

	while (motor->isOk()) {
		if (motor->save() == irrlicht::Save::SAVE)
			oui.writeSave();
		winner = oui.checkWin();
		oui.checkAllBomb();
		motor->loop(&oui, winner);
		if (winner == -1) {
			motor->stopGame();
			break;
		}
		gameMode(&oui);
	}
}

void Core::ChooseDisplay()
{
	_menu->menuChooseInit();
	while (_device->run()) {
		switch (_menu->loop<Choose::choose>()) {
		case Choose::BACK:
			_menu->stop();
			_menu->mainInit();
			return;
		default:
			break;
		}
		checkGameChoosen();
	}
}

void Core::checkMainCases()
{
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
		_menu->close();
		nb = _menu->getNbPlayer();
		Game(nb, true);
		break;
	case Main::QUIT:
		return;
	default:
		break;
	}
}

void Core::checkSizeChoosen()
{
	switch (_menu->loop<Config::config>()) {
	case Config::SIZE1:
		sizeX = 13;
		sizeY = 11;
		break;
	case Config::SIZE2:
		sizeX = 23;
		sizeY = 21;
		break;
	case Config::SIZE3:
		sizeX = 33;
		sizeY = 31;
		break;
	case Config::SIZE4:
		sizeX = 43;
		sizeY = 41;
		break;
	default:
		break;
	}
}

void Core::checkGameChoosen()
{
	switch (_menu->loop<Choose::choose>()) {
	case Choose::SOLO:
		_menu->close();
		Game(1, false);
		return;
	case Choose::TWO:
		_menu->close();
		Game(2, false);
		break;
	case Choose::THREE:
		_menu->close();
		Game(3, false);
		break;
	case Choose::FOUR:
		_menu->close();
		Game(4, false);
		break;
	default:
		break;
	}
}

void Core::backToMenu()
{
	_device = irr::createDevice(irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(_width,
			_height), 32, false,
		true, false, nullptr);
	_menu = new Menu(_device, _width, _height);
}

void Core::player1(game *oui)
{
	KeyOne = motor->nextKeyOne();
	if (KeyOne != NOP) {
		auto p = oui->getBoard();
		for (auto &ob : p) {
			tmp = ob.second->getPosition();
			if (ob.second->getStatus() == PLAYER &&
				ob.second->getId() == 1)
				ob.second->movePlayer(KeyOne, oui);
		}
		KeyOne = NOP;
	}
}

void Core::player2(game *oui)
{
	KeyTwo = motor->nextKeyTwo();
	if (KeyTwo != NOP) {
		auto p = oui->getBoard();
		for (auto &ob : p) {
			tmp = ob.second->getPosition();
			if (ob.second->getStatus() == PLAYER &&
				ob.second->getId() == 2)
				ob.second->movePlayer(KeyTwo, oui);
		}
		KeyTwo = NOP;
	}
}

void Core::player3(game *oui)
{
	KeyThree = motor->nextKeyThree();
	if (KeyThree != NOP) {
		auto p = oui->getBoard();
		for (auto &ob : p) {
			tmp = ob.second->getPosition();
			if (ob.second->getStatus() == PLAYER &&
				ob.second->getId() == 3)
				ob.second->movePlayer(KeyThree, oui);
		}
		KeyThree = NOP;
	}
}

void Core::player4(game *oui)
{
	KeyFour = motor->nextKeyFour();
	if (KeyFour != NOP) {
		auto p = oui->getBoard();
		for (auto &ob : p) {
			tmp = ob.second->getPosition();
			if (ob.second->getStatus() == PLAYER &&
				ob.second->getId() == 4)
				ob.second->movePlayer(KeyFour, oui);
		}
		KeyFour = NOP;
	}
}

void Core::gameMode(game *oui)
{
	if (oui->getPlayersAlive(0))
		player1(oui);
	if (oui->getPlayersAlive(1))
		player2(oui);
	if (oui->getPlayersAlive(2))
		player3(oui);
	if (oui->getPlayersAlive(3))
		player4(oui);
}
