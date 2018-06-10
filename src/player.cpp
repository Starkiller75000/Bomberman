//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by adrichat,
//

#include "../include/player.hpp"
#include "../include/bomb.hpp"
#include "../include/irrlicht.hpp"

player::player(int x, int y,int flags, int id)
	: element(x, y), sound(Sound())
{
	_maxLimitBomb = 1;
	_limitBomb = 1;
	_timeResetBomb = 60;
	_onResetBomb = false;
	_radius = 1;
	_time = 4;
	_id = id;
	_speed = 1;
	_score = 0;
	setStatus(PLAYER);
	_node = motor->returnNewMesh("assets/mesh/Bomberman.obj");
	texture(_id);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setPosition(irr::core::vector3df(x, y, 0));
	_node->setRotation(irr::core::vector3df(90, 180, 0));
	_node->setScale(irr::core::vector3df(0.2, 0.2,0.2));
	if (flags == 0)
		_node->remove();
}

player::~player()
{
	_node->remove();
}

int	player::getSpeed()
{
	return _speed;
}

void	player::texture(int n)
{
	switch (n) {
	case 1:
		_node->setMaterialTexture(
			0, motor->returnNewTex(
				"assets/texture/BomberTextureRed.bmp"));
		break;
	case 4:
		_node->setMaterialTexture(
			0, motor->returnNewTex(
				"assets/texture/BomberTextureBlue.bmp"));
		break;
	case 3:
		_node->setMaterialTexture(
			0, motor->returnNewTex(
				"assets/texture/BomberTexturePurple.bmp"));
		break;
	case 2:
		_node->setMaterialTexture(
			0, motor->returnNewTex(
				"assets/texture/BomberTextureGreen.bmp"));
		break;
	}
}
void	player::goDie(game *t)
{
}


int	player::getId()
{
	return _id;
}

int	player::getRadius()
{
	return _radius;
}

void	player::takeRadius()
{
	_radius++;
}

int	player::getLimitBomb()
{
	return _limitBomb;
}

void	player::setLimitBomb()
{
	if (_limitBomb < _maxLimitBomb)
		_onResetBomb = true;
	if (_onResetBomb) {
		_timeResetBomb--;
		if (_timeResetBomb == 0) {
			_onResetBomb = false;
			_timeResetBomb = 60;
			_limitBomb++;
		}
	}
}

int	player::getMaxLimitBomb()
{
	return _maxLimitBomb;
}

void	player::setMaxLimitBomb()
{
	_maxLimitBomb++;
}

void	player::putBomb(game *t)
{
	std::pair<int, int>	pos(_x, _y);
	auto			s = t->getBoard();

	for (auto ob = s.begin(); ob != s.end(); ++ob) {
		if (pos == ob->second->getPosition() &&
		    ob->second->getStatus() != PLAYER)
			return;
	}
	if (_limitBomb > 0) {
		printf("kekkk\n");
		t->insertElement(new bomb(_x, _y, getRadius()));
		_limitBomb--;
	}
}

void	player::takeSpeed()
{
	_speed += (_speed < 3 ) ? 1 : 0;
}

bool	player::takePowerUp(game *t, std::pair<int, int> pos, pUp power)
{
	t->eraseElement(pos, POWERUP);
	setScore(10);
	switch (power) {
	case MORERADIUS:
		takeRadius();
		break;
	case MOREBOMB:
		setMaxLimitBomb();
		break;
	case MORESPEED:
		takeSpeed();
		break;
	}
	return true;
}

bool	player::ntMove(int x, int y, game *t)
{
	std::pair<int, int>	pos(x, y);
	auto			s = t->getBoard();

	for (auto ob = s.begin(); ob != s.end(); ++ob) {
		if (pos == ob->second->getPosition() &&
		    ob->second->getStatus() == POWERUP)
			return takePowerUp(t, pos, ob->second->getStatusPUp());
		if (pos == ob->second->getPosition() &&
		    ob->second->getStatus() != PLAYER && ob->second->getStatus() !=
		    PLAYERIA && ob->second->getStatus() != FIRE) {
			return false;
		}
	}
	return true;
}

int	player::getScore()
{
	return _score;
}

void	player::setScore(int score)
{
	_score += score;
}

void	player::safeErase()
{
	delete this;
}

void	player::walkOnFire(game *t)
{
	auto s = t->getBoard();
	for (auto ob = s.begin(); ob != s.end(); ++ob) {
		if (getPosition() == ob->second->getPosition()
		    && ob->second->getStatus() == FIRE) {
			t->setPlayersAlive(getId() - 1);
			sound.player(Sound::DEATH);
			t->eraseElement(getPosition(), PLAYER);
		}
	}
}

void	player::switchDir(moveDir dir)
{
	switch (dir) {
	case RIGHT:
		_node->setRotation(irr::core::vector3df(90, 180, 90));
		break;
	case LEFT:
		_node->setRotation(irr::core::vector3df(90, 180, 270));
		break;
	case DOWN:
		_node->setRotation(irr::core::vector3df(90, 180, 180));
		break;
	case UP:
		_node->setRotation(irr::core::vector3df(90, 180, 0));
		break;
	}
}

void	player::movePlayer(moveDir dir, game *t)
{
	if (dir == USEBOMB)
		putBomb(t);
	if (_time == (4 - (_speed - 1))) {
		_x += (dir == RIGHT && _x + 1 < t->getwidth() &&
		       ntMove(_x + 1, _y, t)) ? 1 : 0;
		_x -= (dir == LEFT && _x - 1 >= 0 &&
		       ntMove(_x - 1, _y, t)) ? 1 : 0;
		_y += (dir == DOWN && _y + 1 < t->getheight() &&
		       ntMove(_x, _y + 1, t)) ? 1 : 0;
		_y -= (dir == UP && _y - 1 >= 0 &&
		       ntMove(_x, _y - 1, t)) ? 1 : 0;
		switchDir(dir);
		_node->setPosition(irr::core::vector3df(_x, _y, 0));
		_time = 0;
	} else
		_time++;
}

void	player::timeExplode(game *)
{
}

pUp	player::getStatusPUp()
{
	return MORERADIUS;
}
