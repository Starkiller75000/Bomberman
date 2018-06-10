/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#include "../include/playerIa.hpp"
#include "../include/bomb.hpp"
#include "../include/irrlicht.hpp"
#include "../include/element.hpp"

playerIa::playerIa(int x, int y, int id)
        : player(x, y, 0, id), sound(Sound())
{
        setStatus(PLAYERIA);
        std::srand(std::time(nullptr));
        _maxLimitBomb = 1;
        _limitBomb = 1;
        _timeResetBomb = 60;
        _onResetBomb = false;
        _radius = 1;
        _status = PLAYERIA;
        _alive = true;
        _time = 4;
	cx = 0;
	cy = 0;
        _node = motor->returnNewMesh("assets/mesh/Bomberman.obj");
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
                if (getPosition() == ob->second->getPosition()
			&& ob->second->getStatus() == FIRE) {
			sound.player(Sound::DEATH);
                        t->eraseElement(getPosition(), PLAYERIA);
                }
        }
}

void playerIa::run(game *t)
{
	std::pair<int, int> pos;

        if (_node ) {
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
                t->insertElement(dynamic_cast<element*>
		(new bomb(_x, _y, getRadius())));
                _limitBomb--;
        }
}

void playerIa::setLimitBomb()
{
        if (_limitBomb < _maxLimitBomb)
                _onResetBomb = true;
        if (_onResetBomb) {
                _timeResetBomb--;
                if (_timeResetBomb == 0) {
                        _onResetBomb = false;
                        _timeResetBomb = 60;
                        _limitBomb++;
                }
        }
}

std::pair<int, int> playerIa::get_cover(int find_x, int find_y)
{
        int alt;
	std::pair<int, int> target;

        for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
                for (int i = -1; i <= 1; ++i) {
			find_escape(i, find_x ,find_y, ob->second);
			i++;
		}
	}
	cx = 0;
	cy = 0;
        if (!escape.empty()) {
                alt = rand() % escape.size();
                return escape.at(alt);
        } else {
                return target;
        }
}

void playerIa::find_escape(int i, int x, int y, element *el)
{
	std::pair<int, int> target;

	if (el->getPosition().first + i ==
		x + i && el->getPosition().second == y &&
		cx < 2 && check_collision(el->
		getPosition().first + i, el->getPosition().second )) {
		target = el->getPosition();
		target.first = target.first + i;
		escape.push_back(target);
		cx++;
	}
	if (el->getPosition().second + i ==
		y + i && el->getPosition().first == x &&
		cy < 2 && check_collision(el->
		getPosition().first, el->getPosition().second + i )) {
		target = el->getPosition();
		target.second = target.second + i;
		escape.push_back(target);
		cy++;
	}
}

std::pair<int, int> playerIa::choose_mod()
{
        int n = rand() % 10;
        std::pair<int, int> pos(_x, _y);
        std::pair<int, int> target;

        if (n < 3) {
                target.first = rand() % 10;
                target.second = rand() % 10;
        } else {
                if (is_danger(pos)) {
                        target = find();
                } else {
                        target = get_cover(_x, _y);
                }
        }
        return target;
}

bool playerIa::is_danger(std::pair<int, int> pos)
{
        for (auto ob = _board.begin(); ob !=_board.end(); ++ob) {
                if ((pos == ob->second->getPosition())
			&& (ob->second->getStatus() == BOMB
			|| ob->second->getStatus() == FIRE)) {
                        return false;
                }
        }
        return true;
}

std::pair<int, int> playerIa::find()
{
	std::pair<int, int> pos;

	for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
		if (ob->second->getStatus() == PLAYER
			|| ob->second->getStatus() == PLAYERIA) {
			pos = ob->second->getPosition();
			return pos;
		}
	}
	return pos;
}

bool playerIa::check_collision(int x, int y)
{
	element *el;
	std::pair<int, int> pos(x, y);

        if(_node) {
                for (auto ob = _board.begin(); ob != _board.end(); ++ob) {
                        if (pos == ob->second->getPosition()) {
                                el = ob->second;
                                break;
                        } else {
                                el = ob->second;
                        };
                }
                if (el->getStatus() == BOMB || el->getStatus() == WALL
			|| el->getStatus() == GODWALL) {
                        return true;
                }
                else {
                        return false;
                }
        }
	return false;
}

void playerIa::movePlayer(int find_x,int find_y, game *t)
{
	oldx = _x;
	oldy = _y;
	bool move = true;

        if (_time == 4) {
                if (_x > find_x && _x - 1 < t->getwidth() &&
                    ntMove(_x - 1, _y, t) && move) {
                        _x--;
                        _node->setRotation(
                                irr::core::vector3df(90, 180, 270));
                        move = false;
                }
                if (_x < find_x && _x + 1 < t->getwidth() &&
                    ntMove(_x + 1, _y, t) && move) {
                        _x++;
                        _node->setRotation(
                                irr::core::vector3df(90, 180, 90));
                        move = false;
                }
                if (_y > find_y && _y - 1 < t->getheight() &&
                    ntMove(_x, _y - 1, t) && move) {
                        _y--;
                        _node->setRotation(
                                irr::core::vector3df(90, 180, 180));
                        move = false;
                }
                if (_y < find_y && _y + 1 < t->getheight() &&
                    ntMove(_x, _y + 1, t) && move) {
                        _node->setRotation(
				irr::core::vector3df(90, 180, 180));
                        _y++;
                        move = false;
                }
                if (oldx == _x && oldy == _y) {
                        putBomb(t);
                }
                _node->setPosition(
			irr::core::vector3df(_x, _y, 0));
                _time = 0;
        } else {
                _time++;
        }
}

bool playerIa::ntMove(int x, int y, game *t)
{
        std::pair<int, int> pos(x, y);

        for (auto ob = _board.begin(); ob !=_board.end(); ++ob) {
                if (pos == ob->second->getPosition()
			&& ob->second->getStatus() == POWERUP)
                        return takePowerUp(t, pos, ob->second->getStatusPUp());
                if (pos == ob->second->getPosition() &&
                    (ob->second->getStatus() == GODWALL
			    || ob->second->getStatus() == WALL ||
                     ob->second->getStatus() == BOMB
			     ||ob->second->getStatus() == FIRE )) {
                        return false;
                }
        }
        return true;
}


void playerIa::timeExplode(game *)
{

}

void playerIa::takeRadius()
{

}
