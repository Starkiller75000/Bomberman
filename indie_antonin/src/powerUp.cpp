#include "../inc/powerUp.hpp"
#include "../inc/irrlicht.hpp"

powerUp::powerUp(int x, int y, pUp stat)
        : element(x, y), _statusPUp(stat)
{
        setStatus(POWERUP);
        _node = motor->returnNewAMesh("mesh/Powerup.md2");
        if (_node) {
                switch (stat) {
                case MOREBOMB:
                        _node->setMaterialTexture(0, motor->returnNewTex("texture/BluePowerupTexture.bmp"));
                        break;
                case MORERADIUS:
                        _node->setMaterialTexture(0, motor->returnNewTex("texture/RedPowerup.bmp"));
                        break;
                }
                _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                _node->setPosition(irr::core::vector3df(x, y, 0));
                _node->setRotation(irr::core::vector3df(180, 0, 0));
                _node->setScale(irr::core::vector3df(0.0006, 0.0006,0.0006));
                // _node->setMD2Animation(irr::scene::EMAT_RUN);
                // _anim = motor->returnNewAnim();
                // if (_anim) {
                //         _node->addAnimator(_anim);
                //         _anim->drop();
                // }
                // _node->setFrameLoop(1, 36);
                // _node->setAnimationSpeed(15);
        }
}

powerUp::~powerUp()
{
        _node->remove();
}

void powerUp::takeIt(element &target)
{
        target.takeRadius();
        delete this;
}

pUp powerUp::getStatusPUp() {
        return _statusPUp;
}

void powerUp::safeErase()
{
        delete this;
}
