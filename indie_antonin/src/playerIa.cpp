#include "../inc/playerIa.hpp"
#include "../inc/bomb.hpp"
#include "../inc/irrlicht.hpp"
#include "../inc/element.hpp"

playerIa::playerIa(int x, int y, game *t, int id)
        : player(x, y, 0, id)
{
        setStatus(PLAYERIA);
        std::srand(std::time(nullptr));
        std::cout << "IA" << std::endl;
        _maxLimitBomb = 2;
        _limitBomb = 3;
        _timeResetBomb = 40;
        _onResetBomb = false;
        _radius = 1;
        _status = PLAYERIA;
        _alive = true;
        _time = 10;
        _node = motor->returnNewMesh("mesh/Bomberman.obj");
        if (_node) {
                texture(id);
                _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                _node->setPosition(irr::core::vector3df(x, y, 0));
                _node->setRotation(irr::core::vector3df(90, 180, 0));
                _node->setScale(irr::core::vector3df(0.2, 0.2,0.2));
        }
}

playerIa::~playerIa()
{
}

void playerIa::safeErase()
{
        delete this;
}

void playerIa::walkOnFire(game *t)
{
        auto s = t->getBoard();
        for (auto ob = s.begin(); ob != s.end(); ++ob) {
                if (getPosition() == ob->second->getPosition() && ob->second->getStatus() == FIRE) {
                        // t->setPlayersAlive(ob->second->getId() - 1);
                        t->eraseElement(getPosition(), PLAYERIA);
                }
        }
}

void playerIa::run(game *t)
{
        int rand;
        int i = 0;

        if (_node ) {
                std::cout << "run" << std::endl;
                std::pair<int, int> pos;
                _board = t->getBoard();

                pos = this->choose_mod();
                this->movePlayer(pos.first, pos.second, t);
                escape.clear();
        }
}

void playerIa::setlive()
{
        _alive = false;
}

void playerIa::putBomb(game *t)
{
        std::pair<int, int> pos(_x, _y);

        if (_limitBomb > 0) {
                t->insertElement(dynamic_cast<element*>(new bomb(_x, _y, getRadius())));
                _limitBomb--;
        }
}

std::pair<int, int> playerIa::get_cover(int find_x, int find_y)
{
        int lol;
        int x = 0;
        int y = 0;
        std::cout << "cover" << std::endl;

        std::pair<int, int> target;
        for (auto ob = _board.begin(); ob !=_board.end(); ++ob) {
                for (int i = -1; i <= 1; ++i) {
                        target = ob->second->getPosition();
                        if (ob->second->getPosition().first + i  == find_x + i
                            && ob->second->getPosition().second
                            == find_y && x < 2 && check_collision(target.first + i, target.second)) {
                                target.first = target.first + i;
                                escape.push_back(target);
                        }
                        if (ob->second->getPosition().second + i  == find_y + i
                            && ob->second->getPosition().first
                            == find_x && y < 2 && check_collision(target.first, target.second + i)) {
                                target.second = target.second + i;
                                escape.push_back(target);
                        }
                }
        }
        if (!escape.empty()) {
                lol = rand() % escape.size();
                return escape.at(lol);
        } else {
                return target;
        }
}

std::pair<int, int> playerIa::choose_mod()
{
        int n = rand() % 10;
        std::cout << "target" << std::endl;
        std::pair<int, int> pos(_x, _y);
        std::pair<int, int> target;

        if (n < 3) {
                target.first = rand() % 10;
                target.second = rand() % 10;
        } else {
                if (is_danger(pos)) { // prendre la bombe
                        target = find();
                } else {
                        target = get_cover(_x, _y);
                }
        }
        return target;
}

bool playerIa::is_danger(std::pair<int, int> pos)
{
        std::cout << "danger" << std::endl;
        for (auto ob = _board.begin(); ob !=_board.end(); ++ob) {
                if (pos == ob->second->getPosition()) {
                        if ( ob->second->getStatus() == BOMB)
                                return false;
                }
        }
        return true;
}

std::pair<int, int> playerIa::find()
{
        if(_node) {
                std::cout << "find" << std::endl;
                std::pair<int, int> pos;
                for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
                        if (ob->second->getStatus() == PLAYER) {
                                pos = ob->second->getPosition();
                                return pos;
                        }
                }
        }
}

bool playerIa::check_collision(int x, int y)
{
        if(_node) {
                std::cout << "collision" << std::endl;
                element *el;
                std::pair<int, int> pos(x, y);

                for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
                        if (pos == ob->second->getPosition()) {
                                el = ob->second;
                                break;
                        } else {
                                el = ob->second;
                        };
                }

                if (el->getStatus() != GODWALL && el->getStatus() != WALL &&
                    el->getStatus() != PLAYERIA &&
                    el->getStatus() != PLAYER && el->getStatus() != BOMB)
                        return true;
                else
                        return false;
        }
}

void playerIa::movePlayer(int find_x,int find_y, game *t)
{
        if (_time == 10) {
                oldx = _x;
                oldy = _y;
                bool move = true;

                if (_x > find_x && ntMove(_x - 1, _y, t) && move) {
                        _x--;
                        _node->setRotation(irr::core::vector3df(90, 180, 270));
                        move = false;
                }
                if (_x < find_x && ntMove(_x + 1, _y, t) && move) {
                        _x++;
                        _node->setRotation(irr::core::vector3df(90, 180, 90));
                        move = false;
                }
                if (_y > find_y && ntMove(_x, _y - 1, t) && move) {
                        _y--;
                        _node->setRotation(irr::core::vector3df(90, 180, 180));
                        move = false;
                }
                if (_y < find_y && ntMove(_x, _y + 1, t) && move) {
                        _node->setRotation(irr::core::vector3df(90, 180, 180));
                        _y++;
                        move = false;
                }
                if (oldx == _x && oldy == _y) {
                        putBomb(t);
                }
                _node->setPosition(irr::core::vector3df(_x, _y, 0));
                _time = 0;
        } else {
                _time++;
        }
}

bool playerIa::ntMove(int x, int y, game *t)
{
        std::pair<int, int> pos(x, y);

        for (auto ob = _board.begin(); ob !=_board.end(); ++ob) {
                if (pos == ob->second->getPosition() && ob->second->getStatus() == POWERUP)
                        return takePowerUp(t, pos, ob->second->getStatusPUp());
                if (pos == ob->second->getPosition() &&
                    (ob->second->getStatus() == GODWALL || ob->second->getStatus() == WALL ||
                     ob->second->getStatus() == WALL)) {            // changer
                        return false;
                }
        }
        return true;
}
