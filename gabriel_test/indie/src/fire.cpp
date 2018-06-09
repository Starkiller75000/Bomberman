#include "../inc/fire.hpp"
#include "../inc/irrlicht.hpp"

fire::fire(int x, int y)
        : element(x, y)
{
        setStatus(FIRE);
        _dead = 20;
        _node = motor->returnNewMesh("mesh/Block.obj");
        if (_node) {
                _node->setMaterialTexture(0, motor->returnNewTex("texture/RedBomb.bmp"));
                _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                _node->setPosition(irr::core::vector3df(x, y, 0));
                _node->setScale(irr::core::vector3df(0.09, 0.09,0.09));
        }
}

fire::~fire()
{
        _node->remove();
}

void fire::goDie(game *t)
{
        _dead--;
        if (_dead == 0) {
                t->eraseElement(getPosition(), FIRE);
                delete this;
        }
}

