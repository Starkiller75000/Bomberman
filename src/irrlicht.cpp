/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#include "../include/irrlicht.hpp"

irrlicht::irrlicht(irr::video::E_DRIVER_TYPE os, int x, int y)
{
	device = irr::createDevice(irr::video::EDT_OPENGL,
				   irr::core::dimension2d<irr::u32>(1920, 1080),
				   16, false, false, false, &receiver);
	driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();
	device->setWindowCaption(L"Bomberman");
	scenemgr->addCameraSceneNode(0, irr::core::vector3df((x + 1) / 2,
							     (y + 1) / 2, ((x + y) / 2) * -1),
				     irr::core::vector3df((x + 1) / 2, (y + 1) / 2, 180), -1, true);
	image = driver->getTexture ("assets/texture/space.jpg");
	driver->setTextureCreationFlag (irr::video::ETCF_ALWAYS_16_BIT, true);
	_font = device->getGUIEnvironment()->getFont("assets/font/font.png");
	_fontBig =
		device->getGUIEnvironment()->getFont("assets/font/font30.png");
}

irrlicht::~irrlicht()
{
	device->drop();
}

bool	irrlicht::isOk()
{
	return device->run() && driver;
}

void	irrlicht::writeFont(int x, int y, const irr::core::stringw& msg)
{
	if (_font)
		_font->draw(msg, irr::core::rect<irr::s32>(x, y, 3000, 3000),
			    irr::video::SColor(255,255,255,255));
}


void	irrlicht::writeFontBig(int x, int y, const irr::core::stringw& msg)
{
	if (_font)
		_fontBig->draw(msg, irr::core::rect<irr::s32>(x, y, 3000, 3000),
			       irr::video::SColor(255,255,255,255));
}



moveDir	irrlicht::nextKeyOne()
{
	if(receiver.IsKeyDown(irr::KEY_KEY_S))
		return UP;
	else if(receiver.IsKeyDown(irr::KEY_KEY_Z))
		return DOWN;
	if(receiver.IsKeyDown(irr::KEY_KEY_Q))
		return LEFT;
	else if(receiver.IsKeyDown(irr::KEY_KEY_D))
		return RIGHT;
	else if(receiver.IsKeyDown(irr::KEY_KEY_E))
		return USEBOMB;
	return NOP;
}

moveDir	irrlicht::nextKeyTwo()
{
	if(receiver.IsKeyDown(irr::KEY_KEY_G))
		return UP;
	else if(receiver.IsKeyDown(irr::KEY_KEY_T))
		return DOWN;
	if(receiver.IsKeyDown(irr::KEY_KEY_F))
		return LEFT;
	else if(receiver.IsKeyDown(irr::KEY_KEY_H))
		return RIGHT;
	else if(receiver.IsKeyDown(irr::KEY_KEY_Y))
		return USEBOMB;
	return NOP;
}

moveDir	irrlicht::nextKeyThree()
{
	if(receiver.IsKeyDown(irr::KEY_KEY_K))
		return UP;
	else if(receiver.IsKeyDown(irr::KEY_KEY_I))
		return DOWN;
	if(receiver.IsKeyDown(irr::KEY_KEY_J))
		return LEFT;
	else if(receiver.IsKeyDown(irr::KEY_KEY_L))
		return RIGHT;
	else if(receiver.IsKeyDown(irr::KEY_KEY_O))
		return USEBOMB;
	return NOP;
}

moveDir	irrlicht::nextKeyFour()
{
	if(receiver.IsKeyDown(irr::KEY_DOWN))
		return UP;
	else if(receiver.IsKeyDown(irr::KEY_UP))
		return DOWN;
	if(receiver.IsKeyDown(irr::KEY_LEFT))
		return LEFT;
	else if(receiver.IsKeyDown(irr::KEY_RIGHT))
		return RIGHT;
	else if(receiver.IsKeyDown(irr::KEY_RSHIFT))
		return USEBOMB;
	return NOP;
}

void	irrlicht::loop(game *t, int winner)
{
	driver->beginScene(true, true, irr::video::SColor(255,0,0,255));
	driver->draw2DImage(image, irr::core::position2d<irr::s32>(0,0),
			    irr::core::rect<irr::s32>(0,0,1920, 1080), 0,
			    irr::video::SColor(255, 255, 255, 255), true);
	t->printAllScore();
	scenemgr->drawAll();
	if (winner > 0)
		t->endMessage(winner);
	driver->endScene();
}

irr::scene::ISceneNode	*irrlicht::returnNewMesh(const irr::io::path &path)
{
	return scenemgr->addAnimatedMeshSceneNode(scenemgr->getMesh(path));
}

irr::scene::IAnimatedMeshSceneNode	*irrlicht::returnNewAMesh(
	const irr::io::path &path)
{
	return scenemgr->addAnimatedMeshSceneNode(scenemgr->getMesh(path));
}


irr::scene::ISceneNodeAnimator	*irrlicht::returnNewAnim()
{
	return scenemgr->createRotationAnimator(irr::core::vector3df(0,0,1));
}

irr::video::ITexture	*irrlicht::returnNewTex(const irr::io::path &path)
{
	return driver->getTexture(path);
}

void	irrlicht::print2D(irr::video::ITexture *img,
			  irr::core::position2d<irr::s32> pos, irr::core::rect<irr::s32> size)
{
	driver->draw2DImage(img, pos, size, 0,
			    irr::video::SColor(255, 255, 255, 255), true);
}

irrlicht::Save	irrlicht::save()
{
	if (receiver.IsKeyDown(irr::EKEY_CODE::KEY_ESCAPE))
		return SAVE;
	return NONE;
}

void	irrlicht::stopGame()
{
	device->closeDevice();
	device->drop();
}
