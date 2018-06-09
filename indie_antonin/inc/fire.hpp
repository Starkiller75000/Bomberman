#ifndef FIRE_HPP_
# define FIRE_HPP_

#include "game.hpp"

class fire : public element
{
        public:
                fire(int, int);
                ~fire();
                void timeExplode(game *) {};
                void takeRadius() {};
                void movePlayer(moveDir, game*) {};
                void setLimitBomb() {};
                pUp getStatusPUp() {};
                void safeErase();
                int getId() {};
                void goDie(game *);
                void walkOnFire(game *) {};
                void run(game *t) {};
                int getScore() {};
                int getSpeed() {};
                int getMaxLimitBomb() {};
                int getRadius() {};
        private:
                irr::scene::ISceneNode *_node;
                int _dead;
};

#endif /* FIRE_HPP_ */
