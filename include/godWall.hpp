/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#ifndef GODWALL_HPP_
# define GODWALL_HPP_

#include "game.hpp"

class godWall : public element
{
public:
	godWall(int, int);
	~godWall();
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

#endif /* GODWALL_HPP_ */
