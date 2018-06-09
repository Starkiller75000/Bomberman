##
## EPITECH PROJECT, 2018
## Projects
## File description:
## __DESCRIPTION__
##

NAME = indie

SRC =		src/bomb.cpp	\
		src/element.cpp \
		main.cpp	\
		src/godWall.cpp	\
		src/player.cpp	\
		src/wall.cpp	\
		src/event.cpp	\
		src/game.cpp	\
		src/playerIa.cpp	\
		src/irrlicht.cpp	\
		src/fire.cpp	\
		src/powerUp.cpp	\
		src/exception.cpp

OBJS =		$(SRC:.cpp=.o)

FLAGS +=	-Wall -Werror -Wextra -lIrrlicht -lGL -lX11 -lXxf86vm
FLAGS +=	-W -g3

CC =		g++

RM =		rm -rf

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(FLAGS)

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
