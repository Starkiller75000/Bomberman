//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by adrichat,
//

#include "../include/godWall.hpp"
#include "../include/irrlicht.hpp"

godWall::godWall(int x, int y)
	: element(x, y)
{
	setStatus(GODWALL);
	_node = motor->returnNewMesh("assets/mesh/Block.obj");
	if (_node) {
		_node->setMaterialTexture(0,
					  motor->returnNewTex(
						  "assets/texture/indestructible.bmp"));
		_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_node->setPosition(irr::core::vector3df(x, y, 0));
		_node->setScale(irr::core::vector3df(0.11, 0.11,0.11));
	}
}

godWall::~godWall()
{
	_node->remove();
}

void	godWall::goDie(game *)
{
}

int	godWall::getId()
{
	return 0;
}

void	godWall::safeErase()
{
}

void	godWall::setLimitBomb()
{
}

void	godWall::timeExplode(game *)
{
}

void	godWall::takeRadius()
{
}

void	godWall::walkOnFire(game *)
{
}
