NAME = libsfml.so

SRC = SFMLData.cpp\
	init.cpp \
	  ../core/GameObject.cpp \
	  ../core/Point.cpp \
	  ../core/Snake.cpp \
	  ../Data.cpp \

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -O3  -Wall -Wextra -Werror -std=c++11 -I .. -I SFML-2.2-osx-clang-universal/include

all: SFML $(NAME)

lib:
	make -C lib

.cpp.o:
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -dynamiclib -o $(NAME) $(OBJ)  -Wl,-rpath,$(shell pwd)/SFML-2.2-osx-clang-universal/Frameworks -Wl,-rpath,$(shell pwd)/SFML-2.2-osx-clang-universal/extlibs -F $(shell pwd)/SFML-2.2-osx-clang-universal/Frameworks -framework SFML -framework sfml-system -framework sfml-window -framework sfml-graphics

SFML:
	mkdir -p SFML/junk
	curl -L -o "SFML-2.2-osx-clang-universal.tar.gz" http://www.sfml-dev.org/files/SFML-2.2-osx-clang-universal.tar.gz
	tar -xf SFML-2.2-osx-clang-universal.tar.gz
	cp -r SFML-2.2-osx-clang-universal/extlibs/freetype.framework SFML-2.2-osx-clang-universal/Frameworks/freetype.framework
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
