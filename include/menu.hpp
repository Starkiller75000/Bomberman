//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by Fedora28_VM_MAC,
//

#ifndef BOMBERMAN_MENU_HPP
#define BOMBERMAN_MENU_HPP

#include <../librairies/irrlicht/include/irrlicht.h>
#include <../librairies/irrKlang/include/irrKlang.h>
#include <vector>
#include "sound.hpp"
#include <fstream>
#pragma comment(lib, "irrKlang.lib")
#pragma comment(lib, "Irrlicht.lib")

namespace Main
{
	enum	main : int
	{
		NONE = -1 ,
		PLAY = 0 ,
		LOAD = 1 ,
		CONFIG = 2 ,
		QUIT = 3
	};
}

namespace Game
{
	enum game : int
	{
		SINGLE,
		BACK
	};
}

namespace Config
{
	enum	config : int
	{
		SIZE1,
		SIZE2,
		SIZE3,
		SIZE4,
		MUTE,
		BACK
	};
}

namespace Choose
{
	enum choose : int
	{
		SOLO,
		TWO,
		THREE,
		FOUR,
		BACK
	};
}

class Menu
{
	public:
	explicit Menu(irr::IrrlichtDevice*, irr::u32, irr::u32);
	Menu();
	~Menu();
	void displayTitle() const;
	void createButton(irr::core::rect<irr::s32>, const wchar_t *);
	void mainInit();
	void configInit();
	void SetSound(irrklang::ik_f32);
	void Mute();
	void menuLoop() const;
	void menuChooseInit();
	void stop();
	void close();
	int getNbPlayer();

	public:
	template<typename T>
	const T	loop() const
	{
		unsigned int button;

		menuLoop();
		for (button = 0; button <_buttons.size(); ++button)
			if (_buttons[button]->isPressed())
				return (static_cast<T>(button));
		return (static_cast<T>(-1));
	}

	private:
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_driver;
	irr::video::ITexture *_background;
	irr::u32 _width;
	irr::u32 _height;
	irr::gui::IGUIEnvironment *_GUI;
	wchar_t _titre[100];
	irr::gui::IGUIFont *_font;
	std::vector<irr::gui::IGUIButton*> _buttons;
	irrklang::ik_f32 sound;
	Sound mixer;
	int nb;
};

#endif //BOMBERMAN_MENU_HPP
