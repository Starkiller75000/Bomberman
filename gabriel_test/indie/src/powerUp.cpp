#include "../inc/powerUp.hpp"
#include "../inc/irrlicht.hpp"

powerUp::powerUp(int x, int y, pUp stat)
        : element(x, y), _statusPUp(stat)
{
        setStatus(POWERUP);
        _node = motor->returnNewMesh("mesh/Block.obj");
        if (_node) {
                _node->setMaterialTexture(0, motor->returnNewTex("texture/BomberTexturePurple.bmp"));
                _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                _node->setPosition(irr::core::vector3df(x, y, 0));
                _node->setScale(irr::core::vector3df(0.08, 0.08,0.08));
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


