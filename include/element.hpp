#ifndef ELEMENT_HPP_
# define ELEMENT_HPP_

#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include <vector>
#include <list>
#include <../librairies/irrlicht/include/irrlicht.h>
#pragma comment(lib, "Irrlicht.lib")

class irrlicht;

class game;

extern irrlicht *motor;

typedef enum status
{
	WALL,
	PLAYER,
	PLAYERIA,
	BOMB,
	POWERUP,
	GODWALL,
	FIRE
}	status;

typedef enum move
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	USEBOMB,
	NOP
}	moveDir;

typedef enum pUp
{
	MOREBOMB,
	MORERADIUS,
	MORESPEED
}	pUp;

class	element
{
	public:
		element(int, int);
		~element();
		std::pair<int, int>	getPosition();
		void			setPosition(int, int);
		status			getStatus();
		void			setStatus(status);
		virtual void		takeRadius() = 0;
		virtual void		movePlayer(const moveDir, game*);
		virtual void		timeExplode(game *) = 0;
		virtual void		setLimitBomb() = 0;
		virtual pUp		getStatusPUp();
		virtual void		safeErase() = 0;
		virtual int		getId();
		virtual void		goDie(game *);
		virtual void		walkOnFire(game *) = 0;
		virtual void		run(game *t);
		virtual int		getScore();
		virtual int		getSpeed();
		virtual int		getMaxLimitBomb();
		virtual int		getRadius();
	protected:
		int			_x;
		int			_y;
		status			_status;
};

#endif /* ELEMENT_HPP_ */
