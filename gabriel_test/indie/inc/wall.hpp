#ifndef WALL_HPP_
# define WALL_HPP_

#include "game.hpp"

class wall : public element
{
        public:
                wall(int, int);
                ~wall();
                void takeRadius() {};
                void movePlayer(moveDir, game*) {};
                void timeExplode(game *) {};
                void setLimitBomb() {};
                pUp getStatusPUp() {};
                void safeErase();
                int getId() {};
                void goDie(game *) {};
                void walkOnFire(game *) {};


        private:
                irr::scene::ISceneNode *_node;
};

#endif /* WALL_HPP_ */
