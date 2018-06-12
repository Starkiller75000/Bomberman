/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#include "../include/fire.hpp"
#include "../include/irrlicht.hpp"

fire::fire(int x, int y)
	: element(x, y)
{
	setStatus(FIRE);
	_dead = 20;
	_node = motor->returnNewMesh("assets/mesh/Flameball.obj");
        if (_node) {
		_node->setMaterialTexture(0,
					  motor->returnNewTex(
						  "assets/texture/FlameballTexture.bmp"));
		_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_node->setPosition(irr::core::vector3df(x, y, 0));
		_node->setScale(irr::core::vector3df(0.6, 0.6,0.6));
		_node->setRotation(irr::core::vector3df(270, 0, 0));
	}
}

fire::~fire()
{
	_node->remove();
}

void	fire::goDie(game *t)
{
	_dead--;
	if (_dead <= 0)
		t->eraseElement(getPosition(), FIRE);
}

void	fire::safeErase()
{
	delete this;
}

pUp	fire::getStatusPUp()
{
	return MORERADIUS;
}

void	fire::setLimitBomb()
{
}

void	fire::movePlayer(moveDir, game *)
{
}

void	fire::walkOnFire(game *)
{
}

void	fire::takeRadius()
{
}

void	fire::timeExplode(game *)
{
}
