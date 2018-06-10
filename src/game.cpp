/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#include "../include/game.hpp"
#include "../include/element.hpp"
#include "../include/godWall.hpp"
#include "../include/wall.hpp"
#include "../include/player.hpp"
#include "../include/irrlicht.hpp"
#include "../include/exception.hpp"
#include "../include/powerUp.hpp"
#include "../include/playerIa.hpp"

game::game(std::pair<int, int> ms, bool loaded, std::pair<int, int> ss, int pl)
{
	_iBoard = -1;
	srand(time(NULL));
	_width = ms.first;
	_height = ms.second;
	_xScreen = ss.second;
	_yScreen = ss.first;
	_nbSetMaxPLayer = (loaded) ? 0 : pl;
	saveOrLoad(loaded, pl);
	_timeEnd = 100;
	_mEndSet = false;
	_lastPlayer = 0;
	_playersAlive = new bool[4];
	std::fill(_playersAlive, _playersAlive + 4, true);
	for (int y = -1; y <= _height; y++) {
		for (int x = -1; x <= _width; x++)
			createFence(x, y);
	}
	affGround();
	loadTextures();
}

void	game::createFence(int x, int y)
{
	if (y == -1 || y == _height || x == -1 || x == _width) {
		_node.push_front(motor->returnNewMesh("assets/mesh/Block.obj"));
		if (_node.front()) {
			_node.front()->setMaterialTexture(0,
							  motor->returnNewTex("assets/texture/fence.bmp"));
			_node.front()->setMaterialFlag(
				irr::video::EMF_LIGHTING, false);
			_node.front()->setPosition(irr::core::vector3df(x,
									y, 0));
			_node.front()->setScale(irr::core::vector3df(0.13,
								     0.13,0.13));
		}
	}
}

void	game::loadTextures()
{
	playerA = motor->returnNewTex("assets/texture/REDmenu.png");
	playerB = motor->returnNewTex("assets/texture/GREENmenu.png");
	playerC = motor->returnNewTex("assets/texture/BLUEmenu.png");
	playerD = motor->returnNewTex("assets/texture/PURPLEmenu.png");
	playerAD = motor->returnNewTex("assets/texture/REDDmenu.png");
	playerBD = motor->returnNewTex("assets/texture/GREENDmenu.png");
	playerCD = motor->returnNewTex("assets/texture/BLUEDmenu.png");
	playerDD = motor->returnNewTex(
		"assets/texture/PURPLEDmenu.png");
}

game::~game()
{
}

void	game::saveOrLoad(bool loaded, int pl)
{
	if (loaded)
		loadSave();
	else {
		initBoard();
		cleanBoard();
		spawn(pl);
	}
}

int	game::checkWin()
{
	if (_lastPlayer != 0)
		return (--_timeEnd == 0) ? -1 : _lastPlayer;
	_nbPlayer = 0;
	for (int i = 0; i < 4; ++i) {
		if (_playersAlive[i])
			_nbPlayer++;
	}
	if (_nbPlayer == 1) {
		for (int i = 0; i < 4; ++i) {
			if (_playersAlive[i]) {
				_lastPlayer = i + 1;
				return (--_timeEnd == 0) ? -1 : _lastPlayer;
			}
		}
	}
	return 0;
}

std::string	game::findByPos(int x, int y)
{
	std::pair<int, int>	r(x, y);

	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if (r == ob->second->getPosition())
			return getCharByElem(ob->second);
	}
	return " ";
}

std::string	game::getCharByElem(element *m)
{
	switch (m->getStatus()) {
	case WALL:
		return "#";
	case PLAYER:
		return std::to_string(m->getId());
	case PLAYERIA:
		return std::to_string(m->getId());
	case GODWALL:
		return "Q";
	}
	return "";
}

std::string	game::getSpeedId(int id)
{
	int	nb = 0;

	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if ((ob->second->getStatus() == PLAYER ||
		     ob->second->getStatus() == PLAYERIA) &&
		    ob->second->getId() == id)
			nb = ob->second->getSpeed();
	}
	return std::to_string(nb);
}

std::string	game::getScoreId(int id)
{
        int	nb = 0;

	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if ((ob->second->getStatus() == PLAYER ||
		     ob->second->getStatus() == PLAYERIA) &&
		    ob->second->getId() == id)
			nb = ob->second->getScore();
	}
	return std::to_string(nb);
}

std::string	game::getRadBombId(int id)
{
        int	nb = 0;

	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if ((ob->second->getStatus() == PLAYER ||
		     ob->second->getStatus() == PLAYERIA) &&
		    ob->second->getId() == id)
			nb = ob->second->getRadius();
	}
	return std::to_string(nb);
}

std::string	game::getNbBombId(int id)
{
	int nb = 0;

	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if ((ob->second->getStatus() == PLAYER ||
		     ob->second->getStatus() == PLAYERIA) &&
		    ob->second->getId() == id)
			nb = ob->second->getMaxLimitBomb();
	}
	return std::to_string(nb);
}

void	game::writeSave()
{
	std::string map;
	std::ofstream file("saves/file1.bmb");

	map +=  std::to_string(_nbSetMaxPLayer) + ".";
	for (int y = 0; y < getheight(); ++y) {
		if (y > 0)
			map += "\n";
		for (int x = 0; x < getwidth(); ++x) {
			map += findByPos(x, y);
		}
	}
	if (file.is_open()) {
		file << map << std::endl;
		file.close();
	}
}

void	game::loadSave()
{
	std::string map;
	std::string line;
	std::string info;
	std::ifstream file("saves/file1.bmb");

	if (file.is_open()) {
		while (getline(file, line))
			map += line + "\n";
		file.close();
	}
	info = map.substr(0, map.find("."));
	map.erase(0, map.find("."));
	loadSaveMap(map, (int)info[0] - '0');
}

void	game::fixSizeMapWithLoad(int x)
{
	switch (x) {
	case 12:
		_width = 13;
		_height = 11;
		break;
	case 22:
		_width = 23;
		_height = 21;
		break;
	case 32:
		_width = 33;
		_height = 31;
		break;
	case 42:
		_width = 43;
		_height = 41;
		break;
	}
}


void	game::loadSaveMap(std::string str, int players)
{
	int	x = 0;
	int	y = 0;

	for (auto o = str.begin(); o != str.end(); ++o) {
		if (*o == '#')
			this->insertElement(new wall(x, y));
		else if (*o == 'Q')
			this->insertElement(new godWall(x, y));
		else if (isdigit(*o) && (int)*o - '0' <= players)
			this->insertElement(new player(x, y, 1, (int)*o - '0'));
		else if (isdigit(*o) && (int)*o - '0' > players)
			this->insertElement(new playerIa(x, y,
							 (int)*o - '0'));
		if (*o == '\n') {
			y++;
			x = 0;
			fixSizeMapWithLoad(x);
		} else
			x++;
	}
}

std::string	game::colorForEndMessage(int i)
{
	switch (i) {
	case 4:
		return "Blue Bomberman has win\nwith ";
	case 1:
		return "Red Bomberman has win\nwith ";
	case 2:
		return "Green Bomberman has win\nwith ";
	case 3:
		return "Purple Bomberman has win\nwith ";
	}
	return "";
}

void	game::endMessage(int i)
{
	if (_mEndSet) {
		motor->writeFontBig(500, 500, _mEnd);
		return;
	}
	_mEnd = "The ";
	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if ((ob->second->getStatus() == PLAYER ||
		     ob->second->getStatus() == PLAYERIA) &&
		    ob->second->getId() == i) {
			_mEnd += colorForEndMessage(i).c_str();
			_mEnd += ob->second->getScore();
			_mEnd += " points !";
			break;
		}
	}
	_mEndSet = true;
	motor->writeFontBig(getwidth() % 5, getheight() % 2, _mEnd);
	return;
}

void	game::spawn(int nb)
{
	int	spawn = nb;
	int	id = 1;

	for (int i = 0; i < _width; ++i) {
		for (int y = 0; y < _height; ++y) {
			if ((i == 0 && y == 0) || (i == 0 && y == _height-1) ||
			    (i == _width-1 && y == 0 )  ||
			    (i == _width-1 && y == _height-1)) {
				if (spawn > 0) {
					this->insertElement(new player(i,
								       y, 1, id));
					spawn--;
				}
				else
					this->insertElement(new playerIa(i,
									 y, id));
				id++;
			}
		}
	}
}

bool	game::getPlayersAlive(int index)
{
	return _playersAlive[index];
}

void	game::setPlayersAlive(int index)
{
	_playersAlive[index] = false;
}

int	game::getwidth()
{
	return _width;
}

int	game::getheight()
{
	return _height;
}

void	game::initBoardIndes()
{
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			if (x % 2 == 1 && y % 2 == 1)
				_board.insert(std::make_pair<int, element*>
					      ((int)_iBoard++, new godWall(x, y)));
		}
	}
}

void	game::initBoard()
{
	int	nbWall = ((_width * _height) / 2) + (rand() % 10);
        std::pair<int, int>	rdPos;
        bool	tmp;

	initBoardIndes();
	while (nbWall > 0) {
		tmp = false;
		rdPos = {rand() % _width, rand() % _height};
		for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
			if (rdPos == ob->second->getPosition()) {
				tmp = true;
				break;
			}
		}
		if (!tmp) {
			this->insertElement(new wall(rdPos.first,
						     rdPos.second));
			nbWall--;
		}
	}
}

std::map<int, element*>	game::getBoard()
{
	return _board;
}

int	game::getNbPlayer()
{
	return _nbPlayer;
}

void	game::affGround()
{
	for (int x = 0; x < getwidth(); x++) {
		for (int y = 0; y < getheight(); y++) {
			_node.push_front(motor->returnNewMesh(
						 "assets/mesh/Block.obj"));
			if (_node.front()) {
				_node.front()->setMaterialTexture(0,
								  motor->returnNewTex(
									  "assets/texture/ground.bmp"));
				_node.front()->setMaterialFlag(
					irr::video::EMF_LIGHTING, false);
				_node.front()->setPosition(
					irr::core::vector3df(x, y, 1));
				_node.front()->setScale(
					irr::core::vector3df(0.125,
							     0.125,0.125));
			}
		}
	}
}

void	game::eraseElement(std::pair<int, int> pos, status statu)
{
	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if (ob->second->getPosition() == pos &&
		    ob->second->getStatus() == statu) {
			ob->second->safeErase();
			_board.erase(ob);
			break;
		}
	}
}

void	game::insertElement(element *elem)
{
	_board.insert(std::make_pair((int)++_iBoard, elem));
}

void	game::checkAllBomb(void)
{
	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		switch (ob->second->getStatus()) {
		case BOMB:
			ob->second->timeExplode(this);
			break;
		case PLAYER:
			ob->second->setLimitBomb();
			ob->second->walkOnFire(this);
			break;
		case FIRE:
			ob->second->goDie(this);
			break;
		case PLAYERIA:
			ob->second->setLimitBomb();
			ob->second->run(this);
			ob->second->walkOnFire(this);
			break;
		}
	}
}

void	game::cleanBoard(void)
{
        int	x = _width - 1;
        int	y = _height - 1;

	eraseElement(std::pair<int, int>(0, 0), WALL);
	eraseElement(std::pair<int, int>(0, 1), WALL);
	eraseElement(std::pair<int, int>(1, 0), WALL);
	eraseElement(std::pair<int, int>(x, 0), WALL);
	eraseElement(std::pair<int, int>(x, 1), WALL);
	eraseElement(std::pair<int, int>(x-1, 0), WALL);
	eraseElement(std::pair<int, int>(1, y), WALL);
	eraseElement(std::pair<int, int>(0, y), WALL);
	eraseElement(std::pair<int, int>(0, y-1), WALL);
	eraseElement(std::pair<int, int>(x, y), WALL);
	eraseElement(std::pair<int, int>(x-1, y), WALL);
	eraseElement(std::pair<int, int>(x, y-1), WALL);
}

irr::core::stringw	game::getScoreString(int id)
{
	irr::core::stringw	score = "";

	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if ((ob->second->getStatus() == PLAYER ||
		     ob->second->getStatus() == PLAYERIA) &&
		    ob->second->getId() == id)
			score += ob->second->getScore();
	}
	return score;
}

irr::core::stringw	game::getSpeedString(int id)
{
	irr::core::stringw	speed = "";

	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if ((ob->second->getStatus() == PLAYER ||
		     ob->second->getStatus() == PLAYERIA) &&
		    ob->second->getId() == id)
			speed += ob->second->getSpeed();
	}
	return speed;
}

irr::core::stringw	game::getNbBombString(int id)
{
	irr::core::stringw	nbBomb = "";

	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if ((ob->second->getStatus() == PLAYER ||
		     ob->second->getStatus() == PLAYERIA) &&
		    ob->second->getId() == id)
			nbBomb += ob->second->getMaxLimitBomb();
	}
	return nbBomb;
}

irr::core::stringw	game::getRadBombString(int id)
{
	irr::core::stringw	radBomb = "";

	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if ((ob->second->getStatus() == PLAYER ||
		     ob->second->getStatus() == PLAYERIA) &&
		    ob->second->getId() == id)
			radBomb += ob->second->getRadius();
	}
	return radBomb;
}

void	game::printScoreA(irr::video::ITexture *im, irr::video::ITexture *imD)
{
	irr::core::stringw	score = getScoreString(1);
	irr::core::stringw	speed = getSpeedString(1);
	irr::core::stringw	nbBomb = getNbBombString(1);
	irr::core::stringw	radBomb = getRadBombString(1);

	if (getPlayersAlive(0))
		motor->print2D(im, irr::core::position2d<irr::s32>
			       (20, getxScreen() - 300),
			       irr::core::rect<irr::s32>(0, 0, 100, 225));
	else {
		motor->print2D(imD, irr::core::position2d<irr::s32>
			       (20, getxScreen() - 300),
			       irr::core::rect<irr::s32>(0, 0, 100, 225));
	}
	printScoreStringA(score, speed, nbBomb, radBomb);
}

void	game::printScoreB(irr::video::ITexture *im, irr::video::ITexture *imD)
{
	irr::core::stringw	score = getScoreString(2);
	irr::core::stringw	speed = getSpeedString(2);
	irr::core::stringw	nbBomb = getNbBombString(2);
	irr::core::stringw	radBomb = getRadBombString(2);

	if (getPlayersAlive(1)) {
		motor->print2D(im, irr::core::position2d<irr::s32>
			       (20, 15),
			       irr::core::rect<irr::s32>(0, 0, 100, 225));
	}
	else {
		motor->print2D(imD, irr::core::position2d<irr::s32>
			       (20, 15),
			       irr::core::rect<irr::s32>(0, 0, 100, 225));
	}
	printScoreStringB(score, speed, nbBomb, radBomb);
}

void	game::printScoreC(irr::video::ITexture *im, irr::video::ITexture *imD)
{
	irr::core::stringw	score = getScoreString(3);
	irr::core::stringw	speed = getSpeedString(3);
	irr::core::stringw	nbBomb = getNbBombString(3);
	irr::core::stringw	radBomb = getRadBombString(3);

	if (getPlayersAlive(3))
		motor->print2D(im, irr::core::position2d<irr::s32>
			       (getyScreen() - 120, 20),
			       irr::core::rect<irr::s32>(0, 0, 100, 225));
	else {
		motor->print2D(imD, irr::core::position2d<irr::s32>
			       (getyScreen() - 120, 20),
			       irr::core::rect<irr::s32>(0, 0, 100, 225));
	}
	printScoreStringC(score, speed, nbBomb, radBomb);
}

void	game::printScoreD(irr::video::ITexture *im, irr::video::ITexture *imD)
{
	irr::core::stringw	score = getScoreString(4);
	irr::core::stringw	speed = getSpeedString(4);
	irr::core::stringw	nbBomb = getNbBombString(4);
	irr::core::stringw	radBomb = getRadBombString(4);

	if (getPlayersAlive(2))
		motor->print2D(im, irr::core::position2d<irr::s32>
			       (getyScreen() - 120, getxScreen() - 300),
			       irr::core::rect<irr::s32>(0, 0, 100, 225));
	else {
		motor->print2D(imD, irr::core::position2d<irr::s32>
			       (getyScreen() - 120, getxScreen() - 300),
			       irr::core::rect<irr::s32>(0, 0, 100, 225));
	}
	printScoreStringD(score, speed, nbBomb, radBomb);
}

void	game::printScoreStringB(irr::core::stringw score,
				irr::core::stringw speed, irr::core::stringw nbBomb,
				irr::core::stringw radBomb)
{
	motor->writeFont(140, 60, score);
	motor->writeFont(70, 130, speed);
	motor->writeFont(70, 165, nbBomb);
	motor->writeFont(70, 205, radBomb);
}

void	game::printScoreStringD(irr::core::stringw score,
				irr::core::stringw speed, irr::core::stringw nbBomb,
				irr::core::stringw radBomb)
{
	motor->writeFont(getyScreen() - 190, 60, score);
	motor->writeFont(getyScreen() - 100, 130, speed);
	motor->writeFont(getyScreen() - 100, 170, nbBomb);
	motor->writeFont(getyScreen() - 100, 210, radBomb);
}

void	game::printScoreStringA(irr::core::stringw score,
				irr::core::stringw speed, irr::core::stringw nbBomb,
				irr::core::stringw radBomb)
{
	motor->writeFont(140, getxScreen() - 130, score);
	motor->writeFont(70, getxScreen() - 215, radBomb);
	motor->writeFont(70, getxScreen() - 255, nbBomb);
	motor->writeFont(70, getxScreen() - 295, speed);
}

void	game::printScoreStringC(irr::core::stringw score,
				irr::core::stringw speed, irr::core::stringw nbBomb,
				irr::core::stringw radBomb)
{
	motor->writeFont(getyScreen() - 190, getxScreen() - 130, score);
	motor->writeFont(getyScreen() - 100, getxScreen() - 215, radBomb);
	motor->writeFont(getyScreen() - 100, getxScreen() - 255, nbBomb);
	motor->writeFont(getyScreen() - 100, getxScreen() - 295, speed);
}

void	game::printAllScore()
{
	printScoreA(playerA, playerAD);
	printScoreB(playerB, playerBD);
	printScoreC(playerC, playerCD);
	printScoreD(playerD, playerDD);
}

int	game::getxScreen()
{
	return _xScreen;
}

int	game::getyScreen()
{
	return _yScreen;
}
