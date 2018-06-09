#include "../inc/wall.hpp"
#include "../inc/irrlicht.hpp"

wall::wall(int x, int y)
        : element(x, y)
{
        setStatus(WALL);
        _node = motor->returnNewMesh("mesh/Block.obj");
        if (_node) {
                _node->setMaterialTexture(0, motor->returnNewTex("texture/DirtBlock.bmp"));
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

void wall::safeErase()
{
        delete this;
}
