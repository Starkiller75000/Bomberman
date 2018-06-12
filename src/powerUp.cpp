/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#include "../include/powerUp.hpp"
#include "../include/irrlicht.hpp"

powerUp::powerUp(int x, int y, pUp stat)
	: element(x, y), _statusPUp(stat)
{
	setStatus(POWERUP);
	_node = motor->returnNewAMesh("assets/mesh/Powerup.md2");
	if (_node) {
		switch (stat) {
		case MOREBOMB:
			_node->setMaterialTexture(0,
						  motor->returnNewTex(
							  "assets/texture/BluePowerupTexture.bmp"));
			break;
		case MORERADIUS:
			_node->setMaterialTexture(0,
						  motor->returnNewTex("assets/texture/RedPowerup.bmp"));
			break;
		case MORESPEED:
			_node->setMaterialTexture(0,
						  motor->returnNewTex(
							  "assets/texture/GreenPowerup.bmp"));
		}
		checkAnim(x, y);
	}
}

powerUp::~powerUp()
{
	_node->remove();
}

void	powerUp::safeErase()
{
	delete this;
}

void	powerUp::goDie(game *)
{
}

int	powerUp::getId()
{
	return 0;
}

void	powerUp::setLimitBomb()
{
}

void	powerUp::timeExplode(game *)
{
}

void	powerUp::takeRadius()
{
}

void	powerUp::walkOnFire(game *)
{
}

void	powerUp::takeIt(element &target)
{
	target.takeRadius();
	delete this;
}

pUp	powerUp::getStatusPUp()
{
	return _statusPUp;
}

void	powerUp::checkAnim(int x, int y)
{
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->setPosition(irr::core::vector3df(x, y, 0));
	_node->setRotation(irr::core::vector3df(180, 0, 0));
	_node->setScale(irr::core::vector3df(0.0006, 0.0006,0.0006));
        _anim = motor->returnNewAnim();
        if (_anim) {
                _node->addAnimator(_anim);
                _anim->drop();
        }
	_node->setFrameLoop(1, 36);
	_node->setAnimationSpeed(15);
}
