/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#ifndef POWERUP_HPP_
# define POWERUP_HPP_

#include "game.hpp"

class powerUp : public element
{
public:
	powerUp(int, int, pUp);
	~powerUp();
	void safeErase();
	int getId();
	void goDie(game *);
	void walkOnFire(game *);
	void takeRadius();
	void timeExplode(game *);
	void setLimitBomb();
	void takeIt(element &);
	pUp getStatusPUp();
	void checkAnim(int, int);
private:
	pUp _statusPUp;
	irr::scene::IAnimatedMeshSceneNode *_node;
	irr::scene::ISceneNodeAnimator* _anim;
};

#endif /* POWERUP_HPP_ */
