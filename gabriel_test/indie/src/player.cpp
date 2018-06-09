#include "../inc/player.hpp"
#include "../inc/bomb.hpp"
#include "../inc/irrlicht.hpp"

player::player(int x, int y, int flags, int id)
        : element(x, y)
{

        _maxLimitBomb = 1;
        _limitBomb = 1;
        _timeResetBomb = 40;
        _onResetBomb = false;
        _radius = 1;
        setStatus(PLAYER);
        _node = motor->returnNewMesh("mesh/Bomberman.obj");
	std::cout << "player" << std::endl;
        if(_node) {
                texture(id);
                _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                _node->setPosition(irr::core::vector3df(x, y, 0));
                _node->setRotation(irr::core::vector3df(90, 180, 0));
                _node->setScale(irr::core::vector3df(0.2, 0.2, 0.2));
                if (flags == 0)
                        _node->remove();
        }
}

void player::texture(int n)
{                switch (n) {
	case 1:
		_node->setMaterialTexture(0, motor->returnNewTex("texture/BomberTextureRed.bmp"));
		break;
	case 2:
		_node->setMaterialTexture(0, motor->returnNewTex("texture/BomberTextureBlue.bmp"));
		break;
	case 3:
		_node->setMaterialTexture(0, motor->returnNewTex("texture/BomberTexturePurple.bmp"));
		break;
	case 4:
		_node->setMaterialTexture(0, motor->returnNewTex("texture/BomberTextureGreen.bmp"));
		break;
	}
}

player::~player()
{
        _node->remove();
}


int player::getId()
{
        return _id;
}

int player::getRadius()
{
        return _radius;
}

void player::takeRadius()
{
        _radius++;
}

int player::getLimitBomb()
{
        return _limitBomb;
}

void player::setLimitBomb()
{
        if (_limitBomb < _maxLimitBomb)
                _onResetBomb = true;
        if (_onResetBomb) {
                _timeResetBomb--;
                if (_timeResetBomb == 0) {
                        _onResetBomb = false;
                        _timeResetBomb = 40;
                        _limitBomb++;
                }
        }
}

int player::getMaxLimitBomb()
{
        return _maxLimitBomb;
}

void player::setMaxLimitBomb()
{
        _maxLimitBomb++;
}

void player::putBomb(game *t)
{
        std::pair<int, int> pos(_x, _y);

        auto s = t->getBoard();
        for (auto ob = s.begin(); ob != s.end(); ++ob) {
                if (pos == ob->second->getPosition() && ob->second->getStatus() != PLAYER)
                        return;
        }
        if (_limitBomb > 0) {
                t->insertElement(dynamic_cast<element*>(new bomb(_x, _y, getRadius())));
                _limitBomb--;
        }
}

bool player::takePowerUp(game *t, std::pair<int, int> pos, pUp power)
{
        t->eraseElement(pos, POWERUP);
        switch (power) {
        case MORERADIUS:
                takeRadius();
                break;
        case MOREBOMB:
                setMaxLimitBomb();
                break;
        }
        return true;
}

bool player::ntMove(int x, int y, game *t)
{
        std::pair<int, int> pos(x, y);

        auto s = t->getBoard();
        for (auto ob = s.begin(); ob != s.end(); ++ob) {
                if (pos == ob->second->getPosition() && ob->second->getStatus() == POWERUP)
                        return takePowerUp(t, pos, ob->second->getStatusPUp());
                if (pos == ob->second->getPosition() && ob->second->getStatus() != PLAYER && ob->second->getStatus() != PLAYERIA && ob->second->getStatus() != FIRE) { // changer
                        return false;
                }
        }
        return true;
}

int player::getScore()
{
        return _score;
}

void player::setScore(int score)
{
        _score += score;
}

void player::safeErase()
{
        delete this;
}

void player::walkOnFire(game *t)
{
        auto s = t->getBoard();
        for (auto ob = s.begin(); ob != s.end(); ++ob) {
                if (getPosition() == ob->second->getPosition() && ob->second->getStatus() == FIRE) {
                        t->eraseElement(getPosition(), PLAYER);
                }
        }
}

void player::movePlayer(moveDir dir, game *t)
{
        _x += (dir == RIGHT && _x + 1 < 13 && ntMove(_x + 1, _y, t)) ? 1 : 0;
        _x -= (dir == LEFT && _x - 1 >= 0 && ntMove(_x - 1, _y, t)) ? 1 : 0;
        _y += (dir == DOWN && _y + 1 < 11 && ntMove(_x, _y + 1, t)) ? 1 : 0;
        _y -= (dir == UP && _y - 1 >= 0 && ntMove(_x, _y - 1, t)) ? 1 : 0;
        if (dir == USEBOMB)
                putBomb(t);
        switch (dir) {
        case RIGHT:
                _node->setRotation(irr::core::vector3df(90, 180, 90));
                break;
        case LEFT:
                _node->setRotation(irr::core::vector3df(90, 180, 270));
                break;
        case DOWN:
                _node->setRotation(irr::core::vector3df(90, 180, 180));
                break;
        case UP:
                _node->setRotation(irr::core::vector3df(90, 180, 0));
                break;
        }
        _node->setPosition(irr::core::vector3df(_x, _y, 0));
}

void player::setlive()
{

}
