/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** Created by Fedora28_VM_MAC,
*/

#ifndef BOMBERMAN_MYEVENTRECEIVER_HPP
#define BOMBERMAN_MYEVENTRECEIVER_HPP

#include <irr/irrlicht.h>
#include <iostream>

struct SAppContext
{
	irr::IrrlichtDevice     *device;
	irr::gui::IGUIButton *play;
	irr::gui::IGUIEnvironment *GUI;
};

enum {
	GUI_ID_PLAY_BUTTON,
	GUI_ID_OPTIONS_BUTTON,
	GUI_ID_QUIT_BUTTON,
	GUI_ID_RETURN_BUTTON
};

class MyEventReceiver : public irr::IEventReceiver
{
	public:
	explicit MyEventReceiver(SAppContext &context) : Context(context) {};

	bool OnEvent(const irr::SEvent &event) override
	{
		if (event.EventType == irr::EET_GUI_EVENT) {
			irr::s32 id = event.GUIEvent.Caller->getID();
			irr::gui::IGUIEnvironment *env =
				Context.device->getGUIEnvironment();
			switch (event.GUIEvent.EventType)
			{
			case irr::gui::EGET_BUTTON_CLICKED:
				switch (id)
				{
				case GUI_ID_QUIT_BUTTON:
					Context.device->closeDevice();
					return true;
				case GUI_ID_OPTIONS_BUTTON:
					env->addButton(
						irr::core::rect<irr::s32>(650, 300, 750, 340), nullptr,
						GUI_ID_OPTIONS_BUTTON, L"OK");
					break;
				default:
					return false;
				}
			default:
				break;
			}
		}
		return false;
	}

	private:
	SAppContext &Context;
};

#endif //BOMBERMAN_MYEVENTRECEIVER_HPP
