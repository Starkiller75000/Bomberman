#ifndef POWERUP_HPP_
# define POWERUP_HPP_

#include "game.hpp"



class powerUp : public element
{
        public:
                powerUp(int, int, pUp);
                ~powerUp();
                void takeIt(element &);
                void takeRadius() {};
                void movePlayer(moveDir, game*) {};
                void timeExplode(game *) {};
                void setLimitBomb() {};
                pUp getStatusPUp();
                void safeErase();
                int getId() {};
                void goDie(game *) {};
                void walkOnFire(game *) {};

        private:
                pUp _statusPUp;
                irr::scene::ISceneNode *_node;
};


#endif /* POWERUP_HPP_ */
