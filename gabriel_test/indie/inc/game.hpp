#ifndef GAME_HPP_
# define GAME_HPP_

#include "element.hpp"

class game
{
        public:
                game(int, int);
                ~game();
                void initBoard();
                std::map<int, element*> getBoard();
                void insertElement(element*);
                void eraseElement(std::pair<int, int>, status);
                int getwidth();
                int getheight();
                bool findby_pos(std::pair<int, int>);
		void spawn(int);
                void checkAllBomb();
                void cleanBoard();
                void affGround();
                int getNbPlayer();
                void printScoreA(irr::video::ITexture *);
                void printScoreB(irr::video::ITexture *);
                void printScoreC(irr::video::ITexture *);
                void printScoreD(irr::video::ITexture *);
                void printAllScore();
        private:
                std::map<int, element*> _board;
                int _iBoard;
                int _width;
                int _height;
                std::list<irr::scene::ISceneNode*> _node;
                int _nbPlayer;
                irr::video::ITexture *bomb;
                irr::video::ITexture *playerA;
                irr::video::ITexture *playerB;
                irr::video::ITexture *playerC;
                irr::video::ITexture *playerD;
};

#endif /* GAME_HPP_ */
