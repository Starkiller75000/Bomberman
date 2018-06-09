//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by Fedora28_VM_MAC,
//

#include "../include/menu.hpp"
#include <iostream>

Menu::Menu() = default;

Menu::Menu(irr::IrrlichtDevice *device, irr::u32 width, irr::u32 height) :
	_device(device), _driver(_device->getVideoDriver()), _background(
			_driver->getTexture("assets/image/BG.png")),
	_width(width), _height(height), _GUI(_device->getGUIEnvironment()),
	_font(_GUI->getFont("assets/font/fontlucida.png")),
	_buttons(std::vector<irr::gui::IGUIButton*>()),
	sound(int(1)), mixer(Sound())
{
	irr::gui::IGUISkin *skin;

	skin = _GUI->getSkin();
	skin->setFont(_font);
	skin->setColor(irr::gui::EGDC_3D_FACE, irr::video::SColor(255, 102, 255,
		51));
	skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 0, 0,
		0));
}



Menu::~Menu() = default;

void Menu::displayTitle() const
{
	_device->setWindowCaption(_titre);
}

void Menu::createButton(irr::core::rect<irr::s32> rec, const wchar_t *name)
{
	irr::gui::IGUIButton *button;
	_buttons.push_back(button = _GUI->addButton(rec, nullptr, -1, name));
	button->setOverrideFont(_font);
}

void Menu::mainInit()
{
	mixer.stopMusic();
	mixer.player(Sound::MENU);
	SetSound(mixer.getEngine()->getSoundVolume());
	createButton(irr::core::rect<irr::s32>(600, 350, 850, 420),
	        L"NEW GAME");
	createButton(irr::core::rect<irr::s32>(600, 450, 850, 520), L"LOAD");
	createButton(irr::core::rect<irr::s32>(600, 550, 850, 620), L"CONFIG");
	createButton(irr::core::rect<irr::s32>(600, 650, 850, 720), L"QUIT");
}

void Menu::menuLoop() const
{
	displayTitle();
	_driver->beginScene(true, true);
	_driver->draw2DImage(_background, irr::core::position2d<irr::s32>(0, 0),
		irr::core::rect<irr::s32>(0, 0, 1550, 800), nullptr,
		irr::video::SColor(255, 255, 255, 255), true);
	_device->getSceneManager()->drawAll();
	_GUI->drawAll();
	_driver->endScene();
}

void Menu::SetSound(irrklang::ik_f32 _sound)
{
	sound = _sound;
}

void Menu::Mute()
{
	if (sound == 1)
		mixer.getEngine()->setSoundVolume(0);
	else if (sound == 0)
		mixer.getEngine()->setSoundVolume(1);
}

void Menu::configInit()
{
	mixer.stopMusic();
	mixer.player(Sound::MENU);
	createButton(irr::core::rect<irr::s32>(500, 550, 950, 620), L"MUTE");
	createButton(irr::core::rect<irr::s32>(500, 650, 950, 720), L"BACK");
}

void Menu::stop()
{
	if (!_buttons.empty()) {
		for (auto &element : _buttons)
			element->remove();
		_buttons.clear();
	}
}

void Menu::menuChooseInit()
{
	mixer.stopMusic();
	mixer.player(Sound::GAME);
	createButton(irr::core::rect<irr::s32>(600, 250, 850, 320),
		L"1 PLAYER/3 AI");
	createButton(irr::core::rect<irr::s32>(600, 350, 850, 420),
	        L"2 PLAYERS/2 AI");
	createButton(irr::core::rect<irr::s32>(600, 450, 850, 520),
	        L"3 PLAYERS/1 AI");
	createButton(irr::core::rect<irr::s32>(600, 550, 850, 620),
	        L"4 PLAYERS");
	createButton(irr::core::rect<irr::s32>(600, 650, 850, 720), L"RETURN");
}

Load::load Menu::load()
{
	std::ifstream ifile("saves/bomberman.irr");

	if (!ifile) {
		_GUI->addMessageBox(L"Error", L"The file bomberman.irr doesn't "
					      "exist try to save first before "
	   "trying to load the game", true,
			irr::gui::EMBF_OK);
		return (Load::load::BACK);
	}
	return (Load::load::NONE);
}

void Menu::close()
{
	_device->closeDevice();
	_device->drop();
}
