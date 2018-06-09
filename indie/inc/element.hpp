#ifndef ELEMENT_HPP_
# define ELEMENT_HPP_

#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include <regex>
#include <vector>
#include <list>
#include <irr/irrlicht.h>

class irrlicht;

class game;

extern irrlicht *motor;

typedef enum status
{
        WALL,
        PLAYER,
        PLAYERIA,
        BOMB,
        POWERUP,
        GODWALL,
        FIRE,
}       status;

typedef enum move
{
        UP,
        DOWN,
        RIGHT,
        LEFT,
        USEBOMB,
        NOP
}       moveDir;

typedef enum pUp
{
        MOREBOMB,
        MORERADIUS
}       pUp;

class element
{
        public:
                element(int, int);
                ~element();
                std::pair<int, int> getPosition();
                void setPosition(int, int);
                status getStatus();
                void setStatus(status);
                virtual void takeRadius() = 0;
                virtual void movePlayer(moveDir, game*) = 0;
                virtual void timeExplode(game *) = 0;
                virtual void setLimitBomb() = 0;
                virtual pUp getStatusPUp() = 0;
                virtual void safeErase() = 0;
                virtual int getId() = 0;
                virtual void goDie(game *) = 0;
                virtual void walkOnFire(game *) = 0;
                virtual void run(game *t) = 0;
        protected:
                int _x;
                int _y;
                status _status;
};

#endif /* ELEMENT_HPP_ */
