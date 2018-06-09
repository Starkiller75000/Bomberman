#ifndef EVENT_HPP_
# define EVENT_HPP_

#include <irr/irrlicht.h>

class MyEventReceiver : public irr::IEventReceiver
{
public:
        MyEventReceiver();
        virtual bool OnEvent(const irr::SEvent& event);
        virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
private:
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif /* EVENT_HPP_ */
