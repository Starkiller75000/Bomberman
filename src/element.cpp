/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
element
*/

#include "../include/element.hpp"

element::element(int x, int y)
	: _x(x), _y(y)
{
}

element::~element()
{
}

std::pair<int, int>	element::getPosition()
{
	return std::pair<int, int>(_x, _y);
}

void	element::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

status	element::getStatus()
{
	return _status;
}

void	element::setStatus(status statu)
{
	_status = statu;
}


void	element::run(game *t)
{
}

int	element::getMaxLimitBomb()
{
	return 0;
}

int	element::getRadius()
{
	return 0;
}

void	element::movePlayer(const moveDir, game *)
{
}

int	element::getScore()
{
	return 0;
}

int	element::getSpeed()
{
	return 0;
}

void	element::goDie(game *)
{
}

int	element::getId()
{
	return 0;
}

pUp	element::getStatusPUp()
{
	return MORERADIUS;
}
