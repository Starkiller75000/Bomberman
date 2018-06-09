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
                void safeErase() {};
                int getId() {};
                void goDie(game *);
                void walkOnFire(game *) {};
        private:
                irr::scene::ISceneNode *_node;
                int _dead;
};

#endif /* FIRE_HPP_ */
