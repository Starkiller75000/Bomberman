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
                void run(game *t) {};
                int getScore() {};
                int getSpeed() {};
                int getMaxLimitBomb() {};
                int getRadius() {};
        private:
                pUp _statusPUp;
                irr::scene::IAnimatedMeshSceneNode *_node;
                irr::scene::ISceneNodeAnimator* _anim;
};


#endif /* POWERUP_HPP_ */
