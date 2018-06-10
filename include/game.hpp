/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#ifndef GAME_HPP_
# define GAME_HPP_

#include "element.hpp"

class game
{
public:
	game(std::pair<int, int>, bool, std::pair<int, int>, int);
	~game();
	void initBoard();
	std::map<int, element*> getBoard();
	void insertElement(element*);
	void eraseElement(std::pair<int, int>, status);
	int getwidth();
	int getheight();
	std::string findByPos(int x, int y);
	void checkAllBomb();
	void cleanBoard();
	void affGround();
	int getNbPlayer();
	void printScoreA(irr::video::ITexture *,
			 irr::video::ITexture *);
	void printScoreB(irr::video::ITexture *,
			 irr::video::ITexture *);
	void printScoreC(irr::video::ITexture *,
			 irr::video::ITexture *);
	void printScoreD(irr::video::ITexture *,
			 irr::video::ITexture *);
	int getxScreen();
	int getyScreen();
	void printAllScore();
	int checkWin();
	bool getPlayersAlive(int);
	void setPlayersAlive(int);
	void spawn(int);
	irr::core::stringw getScoreString(int id);
	void fixSizeMapWithLoad(int);
	irr::core::stringw getSpeedString(int id);
	irr::core::stringw getNbBombString(int id);
	irr::core::stringw getRadBombString(int id);
	void printScoreStringA(irr::core::stringw, irr::core::stringw,
			       irr::core::stringw, irr::core::stringw);
	void printScoreStringB(irr::core::stringw, irr::core::stringw,
			       irr::core::stringw, irr::core::stringw);
	void printScoreStringC(irr::core::stringw, irr::core::stringw,
			       irr::core::stringw, irr::core::stringw);
	void printScoreStringD(irr::core::stringw, irr::core::stringw,
			       irr::core::stringw, irr::core::stringw);
	void endMessage(int);
	void writeSave();
	void loadSave();
	std::string getCharByElem(element *);
	void loadSaveMap(std::string, int);
	std::string getSpeedId(int);
	std::string getRadBombId(int);
	std::string getNbBombId(int);
	std::string getScoreId(int);
	std::string colorForEndMessage(int);
	void createFence(int, int);
	void loadTextures();
	void saveOrLoad(bool, int);
	void initBoardIndes();
private:
	std::map<int, element*> _board;
	int _iBoard;
	int _width;
	int _timeEnd;
	int _lastPlayer;
	int _height;
	std::list<irr::scene::ISceneNode*> _node;
	bool *_playersAlive;
	int _nbPlayer;
	irr::video::ITexture *playerA;
	int _nbSetMaxPLayer;
	irr::video::ITexture *playerB;
	irr::core::stringw _mEnd;
	irr::video::ITexture *playerC;
	irr::video::ITexture *playerD;
	int _xScreen;
	bool _mEndSet;
	int _yScreen;
	irr::video::ITexture *playerAD;
	irr::video::ITexture *playerBD;
	irr::video::ITexture *playerCD;
	irr::video::ITexture *playerDD;
};

#endif /* GAME_HPP_ */
