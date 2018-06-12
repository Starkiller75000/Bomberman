/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#ifndef FIRE_HPP_
# define FIRE_HPP_

#include "game.hpp"

class fire : public element
{
public:
	fire(int, int);
	~fire();
	void timeExplode(game *);
	void takeRadius();
	void movePlayer(moveDir, game*);
	void setLimitBomb();
	pUp getStatusPUp();
	void safeErase();
	void walkOnFire(game *);
	void goDie(game *);
private:
	irr::scene::ISceneNode *_node;
	int _dead;
};

#endif /* FIRE_HPP_ */
