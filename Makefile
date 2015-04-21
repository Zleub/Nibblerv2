NAME =	bin/Nibbler
INCS =	$(subst .cpp,.hpp,$(SRC))
OBJ =	$(subst .cpp,.o,$(SRC))
SRC =	src/Game.cpp\
		main.cpp

CC		=	clang++
FLAGS	=	-Wall -Werror -Wextra

INC		=	-Iinc
INC		+=	-Iext/SFML-2.2/include
# INC		+=	-Iext/lua-5.3.0/src/

LIBS	=	-Lext/SFML-2.2/lib
LIBS	+=	-lsfml-graphics
LIBS	+=	-lsfml-window
LIBS	+=	-lsfml-system
LIBS	+=	-lsfml-audio
# LIBS	+=	-lsfml-network

#LIBS	+=	-Llib/lua-5.3.0/src/
#LIBS	+=	-llua


.PHONY: all re clean fclean

all: _libgraphic $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS) -rpath ext/SFML-2.2/extlibs

_libgraphic:
	make -C lib

%.o: %.cpp
	$(CC) $(FLAGS) -o $@ -c $< $(INC)

re: fclean all

clean:
	make -C lib clean
	rm -rf $(OBJ)

fclean:
	make -C lib fclean
	rm -rf $(OBJ)
	rm -rf $(NAME)
