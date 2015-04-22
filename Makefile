NAME =	bin/Nibbler
INCS =	$(subst .cpp,.hpp,$(SRC))
OBJ =	$(subst .cpp,.o,$(SRC))
SRC =	src/Game.cpp\
		main.cpp

CC		=	clang++
FLAGS	=	-Wall -Werror -Wextra

INC		=	-Iinc

.PHONY: all re clean fclean

all: _libgraphic $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) -rpath ext/SFML-2.2/extlibs

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
