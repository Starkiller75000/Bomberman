#ifndef GAME_HPP_
# define GAME_HPP_

#include "element.hpp"

class game
{
        public:
                game(int, int, int, int);
                ~game();
                void initBoard();
                std::map<int, element*> getBoard();
                void insertElement(element*);
                void eraseElement(std::pair<int, int>, status);
                int getwidth();
                int getheight();
                bool findby_pos(std::pair<int, int>);
                void checkAllBomb();
                void cleanBoard();
                void affGround();
                int getNbPlayer();
                void printScoreA(irr::video::ITexture *, irr::video::ITexture *);
                void printScoreB(irr::video::ITexture *, irr::video::ITexture *);
                void printScoreC(irr::video::ITexture *, irr::video::ITexture *);
                void printScoreD(irr::video::ITexture *, irr::video::ITexture *);
                int getxScreen();
                int getyScreen();
                void printAllScore();
                int checkWin();
                bool getPlayersAlive(int);
                void setPlayersAlive(int);
                void spawn(int);
                irr::core::stringw getScoreString(int id);
                irr::core::stringw getSpeedString(int id);
                irr::core::stringw getNbBombString(int id);
                irr::core::stringw getRadBombString(int id);
                void printScoreStringA(irr::core::stringw, irr::core::stringw, irr::core::stringw, irr::core::stringw);
                void printScoreStringB(irr::core::stringw, irr::core::stringw, irr::core::stringw, irr::core::stringw);
                void printScoreStringC(irr::core::stringw, irr::core::stringw, irr::core::stringw, irr::core::stringw);
                void printScoreStringD(irr::core::stringw, irr::core::stringw, irr::core::stringw, irr::core::stringw);

        private:
                std::map<int, element*> _board;
                int _iBoard;
                int _width;
                int _height;
                std::list<irr::scene::ISceneNode*> _node;
                bool *_playersAlive;
                int _nbPlayer;
                // irr::video::ITexture *bomb;
                irr::video::ITexture *playerA;
                irr::video::ITexture *playerB;
                irr::video::ITexture *playerC;
                irr::video::ITexture *playerD;
                int _xScreen;
                int _yScreen;
                irr::video::ITexture *playerAD;
                irr::video::ITexture *playerBD;
                irr::video::ITexture *playerCD;
                irr::video::ITexture *playerDD;
};

#endif /* GAME_HPP_ */
