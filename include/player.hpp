/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#include "game.hpp"
#include "sound.hpp"

class player : public element
{
public:
	player(int, int, int, int);
	~player();
	int getRadius();
	void takeRadius();
	int getLimitBomb();
	void setLimitBomb();
	int getMaxLimitBomb();
	void setMaxLimitBomb();
	void movePlayer(const moveDir, game *);
	bool ntMove(int, int, game *);
	virtual void putBomb(game *);
	void timeExplode(game *);
	bool takePowerUp(game *, std::pair<int, int>, pUp);
	pUp getStatusPUp();
	void safeErase();
	int getScore();
	virtual void setScore(int);
	int getId();
	void goDie(game *);
	void walkOnFire(game *);
	void texture(int n);
	int getSpeed();
	void takeSpeed();
	void switchDir(moveDir);
private:
	int _speed;
	int _radius;
	int _limitBomb;
	int _maxLimitBomb;
	int _timeResetBomb;
	bool _onResetBomb;
	irr::scene::ISceneNode *_node;
	float xa;
	float ya;
	int _score;
	int _id;
	int _time;
	Sound sound;
};

#endif /* PLAYER_HPP_ */
