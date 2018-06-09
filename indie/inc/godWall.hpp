#ifndef GODWALL_HPP_
# define GODWALL_HPP_

#include "game.hpp"

class godWall : public element
{
        public:
                godWall(int, int);
                ~godWall();
                void timeExplode(game *) {};
                void takeRadius() {};
                void movePlayer(moveDir, game*) {};
                void setLimitBomb() {};
                pUp getStatusPUp() {};
                void safeErase() {};
                int getId() {};
                void goDie(game *) {};
                void walkOnFire(game *) {};
                void run(game *t) {};
        private:
                irr::scene::ISceneNode *_node;
};

#endif /* GODWALL_HPP_ */
