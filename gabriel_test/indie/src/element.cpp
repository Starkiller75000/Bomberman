#include "../inc/element.hpp"

element::element(int x, int y)
        : _x(x), _y(y)
{
}

element::~element()
{
}

std::pair<int, int> element::getPosition()
{
        return std::pair<int, int>(_x, _y);
}

void element::setPosition(int x, int y)
{
        _x = x;
        _y = y;
}

status element::getStatus()
{
        return _status;
}

void element::setStatus(status statu)
{
        _status = statu;
}

void element::run(game *t)
{

}

void element::setlife()
{

}
