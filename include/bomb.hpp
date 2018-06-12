/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#ifndef BOMB_HPP_
# define BOMB_HPP_

#include "game.hpp"
#include "sound.hpp"

class bomb : public element
{
public:
	bomb(int, int, int);
	~bomb();
	void timeExplode(game *);
	void takeRadius();
	void movePlayer(moveDir, game*) {};
	void setLimitBomb();
	void exploSpread(game *t);
	void killPlayer(game *, std::pair<int, int>, status);
	void downSpread(game *t, int x, int y);
	void upSpread(game *t, int x, int y);
	void rightSpread(game *t, int x, int y);
	void leftSpread(game *t, int x, int y);
	void depositPowerUp(game *, std::pair<int, int>);
	void noSpread(game *t, int x, int y);
	void safeErase();
	void goDie(game *);
	void walkOnFire(game *);
	bool checkNextSpread(game *t, std::pair<int, int> pos);
	bool checkNoSpread(game *, status, std::pair<int, int>);
private:
	int _power;
	bool _explode;
	int explosion;
	irr::scene::ISceneNode *_node;
	Sound sound;
};

#endif /* BOMB_HPP_ */
