/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#include "../include/bomb.hpp"
#include "../include/powerUp.hpp"
#include "../include/fire.hpp"
#include "../include/irrlicht.hpp"

bomb::bomb(int x, int y, int power)
	: element(x, y), _power(power), sound(Sound())
{
	explosion = 60;
	_explode = false;
	setStatus(BOMB);
	_node = motor->returnNewMesh("assets/mesh/bomb.obj");
	if (_node) {
		_node->setMaterialTexture(0,
					  motor->returnNewTex(
						  "assets/texture/BlackBomb.bmp"));
		_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_node->setPosition(irr::core::vector3df(x, y, 0));
		_node->setRotation(irr::core::vector3df(270, 0, 0));
		_node->setScale(irr::core::vector3df(0.35, 0.35, 0.35));
	}
}

bomb::~bomb()
{
	_node->remove();
}

void	bomb::timeExplode(game *target)
{
	explosion--;
	if (explosion == 6)
		_explode = true;
	else if (explosion == 0) {
		exploSpread(target);
		target->eraseElement(getPosition(), BOMB);
		delete this;
	}
}

void	bomb::killPlayer(game *t, std::pair<int, int> pos, status p)
{
	auto s = t->getBoard();

	for (auto ob = s.begin(); ob != s.end(); ++ob) {
		if (pos == ob->second->getPosition() &&
		    ob->second->getStatus() == p)
			t->setPlayersAlive(ob->second->getId() - 1);
	}
	t->eraseElement(pos, PLAYER);
}

void	bomb::downSpread(game *t, int x, int y)
{
	std::pair<int, int>	pos;
	auto	s = t->getBoard();
	int	a = 0;

	for (int a = 0; a < _power; ++a) {
		pos = {x, ++y};
		if (y >= t->getheight())
			break;
		if (!checkNextSpread(t, pos))
			return;
		t->insertElement(new fire(pos.first, pos.second));
	}
}

bool	bomb::checkNextSpread(game *t, std::pair<int, int> p)
{
	auto	s = t->getBoard();

	for (auto ob = s.begin(); ob != s.end(); ++ob) {
		if (p == ob->second->getPosition())
			switch (ob->second->getStatus()) {
			case WALL:
				depositPowerUp(t, p);
				t->insertElement(new fire(p.first, p.second));
				return false;
			case GODWALL:
				return false;
			case PLAYER:
				killPlayer(t, p, PLAYER);
				break;
			case PLAYERIA:
				killPlayer(t, p, PLAYERIA);
				break;
			}
	}
	return true;
}

void	bomb::upSpread(game *t, int x, int y)
{
	std::pair<int, int>	pos;
	auto	s = t->getBoard();
	int	a = 0;

	for (int a = 0; a < _power; ++a) {
		pos = {x, --y};
		if (y < 0)
			break;
		if (!checkNextSpread(t, pos))
			return;
		t->insertElement(new fire(pos.first, pos.second));
	}
}

void	bomb::rightSpread(game *t, int x, int y)
{
	std::pair<int, int>	pos;
	auto	s = t->getBoard();
	int	a = 0;

	for (int a = 0; a < _power; ++a) {
		pos = {++x, y};
		if (x >= t->getwidth())
			break;
		if (!checkNextSpread(t, pos))
			return;
		t->insertElement(new fire(pos.first, pos.second));
	}
}

void	bomb::depositPowerUp(game *t, std::pair<int, int> pos)
{
	t->eraseElement(pos, WALL);
	if (rand() % 4 == 1)
		t->insertElement(dynamic_cast<element*>(new powerUp(pos.first,
								    pos.second, (pUp)(rand() % 3))));
}

void	bomb::leftSpread(game *t, int x, int y)
{
	std::pair<int, int>	pos;
	auto	s = t->getBoard();
	int	a = 0;

	for (int a = 0; a < _power; ++a) {
		pos = {--x, y};
		if (x < 0)
			break;
		if (!checkNextSpread(t, pos))
			return;
		t->insertElement(new fire(pos.first, pos.second));
	}
}

bool	bomb::checkNoSpread(game *t, status statu, std::pair<int, int> pos)
{
	switch (statu) {
	case WALL:
		depositPowerUp(t, pos);
		t->insertElement(new fire(pos.first, pos.second));
		return false;
	case PLAYER:
		killPlayer(t, pos, PLAYER);
		break;
	case PLAYERIA:
		killPlayer(t, pos, PLAYERIA);
		break;
	}
	return true;
}

void	bomb::noSpread(game *t, int x, int y)
{
	std::pair<int, int>	pos(x, y);
	auto	s = t->getBoard();
	int	a = 0;

	for (auto ob = s.begin(); ob != s.end(); ++ob) {
		if (pos == ob->second->getPosition()) {
			if (!checkNoSpread(t, ob->second->getStatus(), pos))
				return;
			t->insertElement(new fire(pos.first, pos.second));
		}
	}
}

void	bomb::exploSpread(game *t)
{
	noSpread(t, getPosition().first, getPosition().second);
	downSpread(t, getPosition().first, getPosition().second);
	upSpread(t, getPosition().first, getPosition().second);
	rightSpread(t, getPosition().first, getPosition().second);
	leftSpread(t, getPosition().first, getPosition().second);
}

void	bomb::walkOnFire(game *)
{
}

void	bomb::safeErase()
{
}

void	bomb::goDie(game *t)
{
	element::goDie(t);
}

void	bomb::takeRadius()
{
}

void	bomb::setLimitBomb()
{
}
