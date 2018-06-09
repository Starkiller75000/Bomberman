#include "../inc/game.hpp"
#include "../inc/element.hpp"
#include "../inc/godWall.hpp"
#include "../inc/wall.hpp"
#include "../inc/player.hpp"
#include "../inc/irrlicht.hpp"
#include "../inc/powerUp.hpp"
#include "../inc/playerIa.hpp"

game::game(int width, int height, int xScreen, int yScreen)
        : _width(width), _height(height), _xScreen(xScreen), _yScreen(yScreen)
{
        _iBoard = -1;
        srand(time(NULL));
        initBoard();
        cleanBoard();
        for (int y = -1; y <= height; y++) {
                for (int x = -1; x <= width; x++) {
                        if (y == -1 || y == height || x == -1 || x == width) {
                                _node.push_front(motor->returnNewMesh("mesh/Block.obj"));
                                if (_node.front()) {
                                        _node.front()->setMaterialTexture(0, motor->returnNewTex("texture/fence.bmp"));
                                        _node.front()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                                        _node.front()->setPosition(irr::core::vector3df(x, y, 0));
                                        _node.front()->setScale(irr::core::vector3df(0.13, 0.13,0.13));
                                }
                        }
                }
        }
        affGround();
        // bomb = motor->returnNewTex("texture/BOMB.png");
        playerA = motor->returnNewTex("texture/REDmenu.png");
        playerB = motor->returnNewTex("texture/GREENmenu.png");
        playerC = motor->returnNewTex("texture/BLUEmenu.png");
        playerD = motor->returnNewTex("texture/PURPLEmenu.png");
        playerAD = motor->returnNewTex("texture/REDDmenu.png");
        playerBD = motor->returnNewTex("texture/GREENDmenu.png");
        playerCD = motor->returnNewTex("texture/BLUEDmenu.png");
        playerDD = motor->returnNewTex("texture/PURPLEDmenu.png");
        _playersAlive = new bool[4];
        std::fill(_playersAlive, _playersAlive + 4, true);
}

game::~game()
{
}

int game::checkWin()
{
        _nbPlayer = 0;
        for (int i = 0; i < 4; ++i) {
                if (_playersAlive[i])
                        _nbPlayer++;
        }
        if (_nbPlayer == 1) {
                for (int i = 0; i < 4; ++i) {
                        if (_playersAlive[i])
                                return i + 1;
                }
        }
        return 0;
}

void game::spawn(int nb)
{
        int spawn = nb;
        int id = 1;

        std::pair<int, int> pair;
        for (int i = 0; i < _width; ++i) {
                for (int y = 0; y < _height; ++y) {
                        if ((i == 0 && y == 0) || (i == 0 && y == _height-1)  ||
                            (i == _width-1 && y == 0 )  ||
                            (i == _width-1 && y == _height-1)) {
                                if (spawn > 0) {
                                        this->insertElement(new player(i, y, 1, id));
                                        spawn--;
                                }
                                else  {
                                        this->insertElement(new playerIa(i, y, this, id));
                                }
                                id++;
                        }
                }
        }
}

bool game::getPlayersAlive(int index)
{
        return _playersAlive[index];
}

void game::setPlayersAlive(int index)
{
        _playersAlive[index] = false;
}

int game::getwidth()
{
        return _width;
}

int game::getheight()
{
        return _height;
}

void game::initBoard()
{
        int nbWall = ((_width * _height) / 2) + (rand() % 10);
        std::pair<int, int> rdPos;
        bool tmp;

        for (int y = 0; y < _height; y++) {
                for (int x = 0; x < _width; x++) {
                        if (x % 2 == 1 && y % 2 == 1)
                                _board.insert(std::make_pair<int, element*>((int)++_iBoard, new godWall(x, y)));
                }
        }
        while (nbWall > 0) {
                tmp = false;
                rdPos = std::make_pair<int, int>(rand() % _width, rand() % _height);
                for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
                        if (rdPos == ob->second->getPosition()) {
                                tmp = true;
                                break;
                        }
                }
                if (!tmp) {
                        _board.insert(std::make_pair<int, element*>((int)++_iBoard, new wall(rdPos.first, rdPos.second)));
                        nbWall--;
                }
        }
        _nbPlayer = 2;
}

std::map<int, element*> game::getBoard()
{
        return _board;
}

int game::getNbPlayer()
{
        return _nbPlayer;
}

void game::affGround()
{
        for (int x = 0; x < getwidth(); x++) {
                for (int y = 0; y < getheight(); y++) {
                        _node.push_front(motor->returnNewMesh("mesh/Block.obj"));
                        if (_node.front()) {
                                _node.front()->setMaterialTexture(0, motor->returnNewTex("texture/ground.bmp"));
                                _node.front()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                                _node.front()->setPosition(irr::core::vector3df(x, y, 1));
                                _node.front()->setScale(irr::core::vector3df(0.125, 0.125,0.125));
                        }
                }
        }
}

void game::eraseElement(std::pair<int, int> pos, status statu)
{
        for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
                if (ob->second->getPosition() == pos && ob->second->getStatus() == statu) {
                        ob->second->safeErase();
                        _board.erase(ob);
                        break;
                }
        }
}

void game::insertElement(element *elem)
{
        _board.insert(std::make_pair((int)++_iBoard, elem));
}

void game::checkAllBomb(void)
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
                        ob->second->run(this);
                        ob->second->walkOnFire(this);
                        break;
                }
        }
}

void game::cleanBoard(void)
{
        int x = _width - 1;
        int y = _height - 1;

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

void game::printScoreA(irr::video::ITexture *image, irr::video::ITexture *imageD)
{
        irr::core::stringw score = getScoreString(0);
        irr::core::stringw speed = getSpeedString(0);
        irr::core::stringw nbBomb = getNbBombString(0);
        irr::core::stringw radBomb = getRadBombString(0);

        if (getPlayersAlive(0))
                motor->print2D(image, irr::core::position2d<irr::s32>(20, getxScreen() - 300),
                               irr::core::rect<irr::s32>(0, 0, 100, 225));
        else {
                motor->print2D(imageD, irr::core::position2d<irr::s32>(20, getxScreen() - 300),
                               irr::core::rect<irr::s32>(0, 0, 100, 225));
        }
        printScoreStringA(score, speed, nbBomb, radBomb);

}

irr::core::stringw game::getScoreString(int id)
{
        irr::core::stringw score = "";

        for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
                if ((ob->second->getStatus() == PLAYER || ob->second->getStatus() == PLAYERIA) && ob->second->getId() == id)
                        score += ob->second->getScore();
        }
        return score;
}

irr::core::stringw game::getSpeedString(int id)
{
        irr::core::stringw speed = "";

        for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
                if ((ob->second->getStatus() == PLAYER || ob->second->getStatus() == PLAYERIA) && ob->second->getId() == id)
                        speed += ob->second->getSpeed();
        }
        return speed;
}

irr::core::stringw game::getNbBombString(int id)
{
        irr::core::stringw nbBomb = "";

        for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
                if ((ob->second->getStatus() == PLAYER || ob->second->getStatus() == PLAYERIA) && ob->second->getId() == id)
                        nbBomb += ob->second->getMaxLimitBomb();
        }
        return nbBomb;
}

irr::core::stringw game::getRadBombString(int id)
{
        irr::core::stringw radBomb = "";

        for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
                if ((ob->second->getStatus() == PLAYER || ob->second->getStatus() == PLAYERIA) && ob->second->getId() == id)
                        radBomb += ob->second->getRadius();
        }
        return radBomb;
}

void game::printScoreB(irr::video::ITexture *image, irr::video::ITexture *imageD)
{
        irr::core::stringw score = getScoreString(1);
        irr::core::stringw speed = getSpeedString(1);
        irr::core::stringw nbBomb = getNbBombString(1);
        irr::core::stringw radBomb = getRadBombString(1);

        if (getPlayersAlive(1)) {
                motor->print2D(image, irr::core::position2d<irr::s32>(20, 15),
                               irr::core::rect<irr::s32>(0, 0, 100, 225));
        }
        else {
                motor->print2D(imageD, irr::core::position2d<irr::s32>(20, 15),
                               irr::core::rect<irr::s32>(0, 0, 100, 225));
        }
        printScoreStringB(score, speed, nbBomb, radBomb);
}

void game::printScoreC(irr::video::ITexture *image, irr::video::ITexture *imageD)
{
        irr::core::stringw score = getScoreString(3);
        irr::core::stringw speed = getSpeedString(3);
        irr::core::stringw nbBomb = getNbBombString(3);
        irr::core::stringw radBomb = getRadBombString(3);

        if (getPlayersAlive(3))
                motor->print2D(image, irr::core::position2d<irr::s32>(getyScreen() - 120, 20),
                               irr::core::rect<irr::s32>(0, 0, 100, 225));
        else {
                motor->print2D(imageD, irr::core::position2d<irr::s32>(getyScreen() - 120, 20),
                               irr::core::rect<irr::s32>(0, 0, 100, 225));
        }
        printScoreStringC(score, speed, nbBomb, radBomb);
}

void game::printScoreD(irr::video::ITexture *image, irr::video::ITexture *imageD)
{
        irr::core::stringw score = getScoreString(2);
        irr::core::stringw speed = getSpeedString(2);
        irr::core::stringw nbBomb = getNbBombString(2);
        irr::core::stringw radBomb = getRadBombString(2);

        if (getPlayersAlive(2))
                motor->print2D(image, irr::core::position2d<irr::s32>(getyScreen() - 120, getxScreen() - 300),
                               irr::core::rect<irr::s32>(0, 0, 100, 225));
        else {
                motor->print2D(imageD, irr::core::position2d<irr::s32>(getyScreen() - 120, getxScreen() - 300),
                               irr::core::rect<irr::s32>(0, 0, 100, 225));
        }
        printScoreStringD(score, speed, nbBomb, radBomb);
}

void game::printScoreStringA(irr::core::stringw score, irr::core::stringw speed, irr::core::stringw nbBomb, irr::core::stringw radBomb)
{
    motor->writeFont(140, 60, score);
    motor->writeFont(70, 130, speed);
    motor->writeFont(70, 165, nbBomb);
    motor->writeFont(70, 205, radBomb);
}

void game::printScoreStringB(irr::core::stringw score, irr::core::stringw speed, irr::core::stringw nbBomb, irr::core::stringw radBomb)
{
    motor->writeFont(getyScreen() - 190, 60, score);
    motor->writeFont(getyScreen() - 100, 130, speed);
    motor->writeFont(getyScreen() - 100, 170, nbBomb);
    motor->writeFont(getyScreen() - 100, 210, radBomb);
}

void game::printScoreStringC(irr::core::stringw score, irr::core::stringw speed, irr::core::stringw nbBomb, irr::core::stringw radBomb)
{
    motor->writeFont(140, getxScreen() - 130, score);
    motor->writeFont(70, getxScreen() - 215, speed);
    motor->writeFont(70, getxScreen() - 255, nbBomb);
    motor->writeFont(70, getxScreen() - 295, radBomb);
}

void game::printScoreStringD(irr::core::stringw score, irr::core::stringw speed, irr::core::stringw nbBomb, irr::core::stringw radBomb)
{
    motor->writeFont(getyScreen() - 190, getxScreen() - 130, score);
    motor->writeFont(getyScreen() - 100, getxScreen() - 215, speed);
    motor->writeFont(getyScreen() - 100, getxScreen() - 255, nbBomb);
    motor->writeFont(getyScreen() - 100, getxScreen() - 295, radBomb);
}

void game::printAllScore()
{
        printScoreA(playerA, playerAD);
        printScoreB(playerB, playerBD);
        printScoreC(playerC, playerCD);
        printScoreD(playerD, playerDD);
}

int game::getxScreen()
{
        return _xScreen;
}

int game::getyScreen()
{
        return _yScreen;
}