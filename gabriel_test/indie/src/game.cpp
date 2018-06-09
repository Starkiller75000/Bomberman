#include "../inc/game.hpp"
#include "../inc/element.hpp"
#include "../inc/playerIa.hpp"
#include "../inc/godWall.hpp"
#include "../inc/wall.hpp"
#include "../inc/player.hpp"
#include "../inc/irrlicht.hpp"

game::game(int width, int height)
        : _width(width), _height(height)
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
        bomb = motor->returnNewTex("texture/BOMB.png");
        playerA = motor->returnNewTex("texture/GREEN.png");
        playerB = motor->returnNewTex("texture/BLUE.png");
        playerC = motor->returnNewTex("texture/RED.png");
        playerD = motor->returnNewTex("texture/PURPLE.png");
}

game::~game()
{
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
        int nbWall = 30 + (rand() % 10);
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
}

std::map<int, element*> game::getBoard()
{
        return _board;
}

int game::getNbPlayer()
{
        return _nbPlayer;
}
void game::spawn(int nb)
{
        int spawn = nb;
	int id = 1;

        std::pair<int, int> pair;
        for (int i = 0; i < _width ; ++i) {
                for (int y = 0; y < _height ; ++y) {
                        if ((i == 0 && y == 0) || (i == 0 && y == _height-1)  ||
                                (i == _width-1 && y == 0 )  ||
                                (i == _width-1 && y == _height-1)) {
                                if (spawn > 0){
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
		case PLAYERIA:
			ob->second->walkOnFire(this);
			break;
                case FIRE:
                        ob->second->goDie(this);
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

void game::printScoreA(irr::video::ITexture *image)
{
        motor->print2D(image, irr::core::position2d<irr::s32>(20, 15),
                       irr::core::rect<irr::s32>(0, 0, 120, 120));
        motor->print2D(bomb, irr::core::position2d<irr::s32>(200, 30),
                       irr::core::rect<irr::s32>(0, 0, 100, 100));
}

void game::printScoreB(irr::video::ITexture *image)
{
        motor->print2D(image, irr::core::position2d<irr::s32>(1780, 20),
                       irr::core::rect<irr::s32>(0, 0, 116, 120));
        motor->print2D(bomb, irr::core::position2d<irr::s32>(1600, 35),
                       irr::core::rect<irr::s32>(0, 0, 100, 100));
}

void game::printScoreC(irr::video::ITexture *image)
{
        motor->print2D(image, irr::core::position2d<irr::s32>(20, 880),
                       irr::core::rect<irr::s32>(0, 0, 116, 120));
        motor->print2D(bomb, irr::core::position2d<irr::s32>(200, 900),
                       irr::core::rect<irr::s32>(0, 0, 100, 100));
}

void game::printScoreD(irr::video::ITexture *image)
{
        motor->print2D(image, irr::core::position2d<irr::s32>(1780, 880),
                       irr::core::rect<irr::s32>(0, 0, 116, 120));
        motor->print2D(bomb, irr::core::position2d<irr::s32>(1600, 900),
                       irr::core::rect<irr::s32>(0, 0, 100, 100));
}

void game::printAllScore()
{
        printScoreA(playerA);
        printScoreB(playerB);
        printScoreC(playerC);
        printScoreD(playerD);
}
