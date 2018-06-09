#include <irr/irrlicht.h>
using namespace irr;

int main()
{
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
					      core::dimension2d<u32>(640,480));
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* scenemgr = device->getSceneManager();
	device->setWindowCaption(L"Hello World!");
	scene::ISceneNode* node = scenemgr->addAnimatedMeshSceneNode(
		scenemgr->getMesh("Bomberman.md2"));
	if (node)
	{
		node->setMaterialTexture(0, driver->getTexture("ocean.bmp"));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
	}
	scenemgr->addCameraSceneNodeFPS();
	while(device->run() && driver)
	{
		driver->beginScene(true, true, video::SColor(255,0,0,255));
		scenemgr->drawAll();
		driver->endScene();
	}
	device->drop();
	return 0;
}
