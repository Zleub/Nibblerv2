NAME =	libd1.so
INCS =	$(subst .cpp,.hpp,$(SRC))
OBJ =	$(subst .cpp,.o,$(SRC))
SRC =	src/SFML.cpp\
		src/IGlib_Event.cpp\
		src/IGlib_Exception.cpp
		# src/AGlib.cpp\

CC		=	clang++
FLAGS	=	-Wall -Werror -Wextra

INC		=	-Iinc -I../../inc
INC		+=	-I../../ext/SFML-2.2/include
#INC		+=	-I../../ext/lua-5.3.0/src/

LIBS	=	-L../../ext/SFML-2.2/lib
# LAISSER DANS CET ORDRE
LIBS	+= -lsfml-audio
LIBS	+=-lsfml-graphics
LIBS	+=-lsfml-network
LIBS	+=-lsfml-window
LIBS	+=-lsfml-system

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -shared -fPIC -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(FLAGS) -o $@ -c $< $(INC)

re: fclean all

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)
