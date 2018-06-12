/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#ifndef WALL_HPP_
# define WALL_HPP_

#include "game.hpp"

class wall : public element
{
public:
	wall(int, int);
	~wall();
	void safeErase();
	int getId();
	void goDie(game *);
	void walkOnFire(game *);
	void takeRadius();
	void timeExplode(game *);
	void setLimitBomb();
private:
	irr::scene::ISceneNode *_node;
};

#endif /* WALL_HPP_ */
