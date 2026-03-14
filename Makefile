CXX = g++
CXXFLAGS = -Iinclude -std=c++11 -I/opt/homebrew/opt/sfml@2/include -I/opt/homebrew/opt/openal-soft/include
LDFLAGS = -L/opt/homebrew/opt/sfml@2/lib -L/opt/homebrew/opt/openal-soft/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC = src/main.cpp src/Game.cpp src/Player.cpp src/Enemy.cpp src/Bullet.cpp src/Block.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = SpaceInvaders

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)