#ifndef BOMB_HPP_
# define BOMB_HPP_

#include "game.hpp"

class bomb : public element
{
        public:
                bomb(int, int, int);
                ~bomb();
                void timeExplode(game *);
                void takeRadius() {};
                void movePlayer(moveDir, game*) {};
                void setLimitBomb() {};
                void exploSpread(game *t);
                void killPlayer(game *, std::pair<int, int>, status);
                void downSpread(game *t, int x, int y);
                void upSpread(game *t, int x, int y);
                void rightSpread(game *t, int x, int y);
                void leftSpread(game *t, int x, int y);
                void depositPowerUp(game *, std::pair<int, int>);
                void noSpread(game *t, int x, int y);
                pUp getStatusPUp() {};
                void safeErase() {};
                int getId() {};
                void goDie(game *) {};
                void walkOnFire(game *) {};
                void run(game *t) {};
        private:
                int _power;
                bool _explode;
                int explosion;
                irr::scene::ISceneNode *_node;
};

#endif /* BOMB_HPP_ */
