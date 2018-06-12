//
// EPITECH PROJECT, 2017
// bomberman
// File description:
// Created by adrichat,
//

#include "../include/wall.hpp"
#include "../include/irrlicht.hpp"

wall::wall(int x, int y)
	: element(x, y)
{
	setStatus(WALL);
	_node = motor->returnNewMesh("assets/mesh/Block.obj");
	if (_node) {
		_node->setMaterialTexture(0,
					  motor->returnNewTex(
						  "assets/texture/DirtBlock.bmp"));
		_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_node->setPosition(irr::core::vector3df(x, y, 0));
		_node->setScale(irr::core::vector3df(0.11, 0.11,0.11));
		_node->setRotation(irr::core::vector3df(270, 0,0));
	}
}

wall::~wall()
{
	_node->remove();
}

void	wall::safeErase()
{
	delete this;
}

void	wall::goDie(game *)
{
}

int	wall::getId()
{
	return 0;
}

void	wall::setLimitBomb()
{
}

void	wall::timeExplode(game *)
{
}

void	wall::takeRadius()
{
}

void	wall::walkOnFire(game *)
{
}
