//
// EPITECH PROJECT, 2018
// Project
//File description:
// Created by bertag_l,
//

#include "../inc/sound.hpp"

Sound::Sound() :
	engine(irrklang::createIrrKlangDevice()),
	tipe(NONE)
{
}

Sound::~Sound()
{
}

irrklang::ISoundEngine * Sound::getEngine()
{
	return engine;
}

irrklang::ISound * Sound::getSound()
{
	return sound;
}

Sound::type Sound::getType()
{
	return tipe;
}

void Sound::player(Sound::type tipe)
{
	switch (tipe){
	case MENU:
		sound = engine->play2D("assets/music/menu_music.ogg");
		break;
	case GAME:
		sound = engine->play2D("assets/music/game_music.ogg");
		break;
	case EXPLO:
		sound = engine->play2D("assets/music/explosion.ogg");
		break;
	case NONE:
		break;
	default:
		break;
	}
}

void Sound::stopMusic()
{
	engine->stopAllSounds();
}
