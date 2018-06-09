#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#include "game.hpp"


class player : public element
{
        public:
                player(int, int, int, int);
                ~player();
                int getRadius();
                void takeRadius();
                int getLimitBomb();
                void setLimitBomb();
                int getMaxLimitBomb();
                void setMaxLimitBomb();
                void movePlayer(moveDir, game *);
                bool ntMove(int, int, game *);
                void putBomb(game *);
                void timeExplode(game *) {};
                bool takePowerUp(game *, std::pair<int, int>, pUp);
                pUp getStatusPUp() {};
                void safeErase();
                int getScore();
                void setScore(int);
                int getId();
                void goDie(game *) {};
                void walkOnFire(game *);
                void texture(int n);
                int getSpeed();
                void run(game *t) {};
        private:
                int _speed;
                int _radius;
                int _limitBomb;
                int _maxLimitBomb;
                int _timeResetBomb;
                bool _onResetBomb;
                irr::scene::ISceneNode *_node;
                float xa;
                float ya;
                int _score;
                int _id;
                int _time;
};


#endif /* PLAYER_HPP_ */
