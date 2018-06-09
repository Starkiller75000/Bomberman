#ifndef IRRLICHT_HPP_
# define IRRLICHT_HPP_

#include "game.hpp"
#include "event.hpp"

class irrlicht
{
public:
        irrlicht(irr::video::E_DRIVER_TYPE, int, int);
        ~irrlicht();
        void loop(game *);
        bool isOk();
        irr::scene::ISceneNode *returnNewMesh(const irr::io::path &filename);
        irr::video::ITexture *returnNewTex(const irr::io::path &path);
        moveDir nextKeyOne();
        moveDir nextKeyTwo();
        moveDir nextKeyThree();
        moveDir nextKeyFour();
        void print2D(irr::video::ITexture *img, irr::core::position2d<irr::s32> pos, irr::core::rect<irr::s32> size);
        void writeFont(int x, int y, const irr::core::stringw& msg);
        irr::scene::ISceneNodeAnimator *returnNewAnim();
        irr::scene::IAnimatedMeshSceneNode *returnNewAMesh(const irr::io::path &path);

private:
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver* driver;
        irr::scene::ISceneManager* scenemgr;
        MyEventReceiver receiver;
        irr::gui::IGUIFont* _font;
        irr::video::ITexture *image;
};

#endif /* IRRLICHT_HPP_ */
