#include "../inc/godWall.hpp"
#include "../inc/irrlicht.hpp"

godWall::godWall(int x, int y)
        : element(x, y)
{
        setStatus(GODWALL);
        _node = motor->returnNewMesh("mesh/Block.obj");
        if (_node) {
                _node->setMaterialTexture(0, motor->returnNewTex("texture/indestructible.bmp"));
                _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                _node->setPosition(irr::core::vector3df(x, y, 0));
                _node->setScale(irr::core::vector3df(0.11, 0.11,0.11));
        }
}

godWall::~godWall()
{
        _node->remove();
}
