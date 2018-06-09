//
// EPITECH PROJECT, 2018
// Project
// File description:
// Created by bertag_l,
//

#ifndef PROJECT_SOUND_HPP
#define PROJECT_SOUND_HPP

#include <irrk/irrKlang.h>
#include <iostream>
#include <string>

class	Sound {
	public:
	enum type {
		MENU,
		GAME,
		EXPLO,
		DEATH,
		NONE
	};

	public:
	Sound();
	~Sound();
	irrklang::ISoundEngine* getEngine();
	irrklang::ISound*	getSound();
	Sound::type 			getType();
	void			player(Sound::type);
	void			stopMusic();

	private:
	irrklang::ISoundEngine* engine;
	irrklang::ISound*	sound;
	Sound::type		tipe;

};

#endif //PROJECT_SOUND_HPP
