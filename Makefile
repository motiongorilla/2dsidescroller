# Compiler
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wno-unused-parameter

# SDL paths
INCLUDES = -I ../libraries/SDL3-3.2.26/x86_64-w64-mingw32/include -I ../libraries/SDL3_image-3.2.4/x86_64-w64-mingw32/include
LIBS     = -L ../libraries/SDL3-3.2.26/x86_64-w64-mingw32/lib -lSDL3 -L ../libraries/SDL3_image-3.2.4/x86_64-w64-mingw32/lib -lSDL3_image

# Source files
SRC = Main.cpp Game.cpp Actor.cpp Component.cpp SpriteComponent.cpp AnimSpriteComponent.cpp BackgroundSpriteComponent.cpp
OBJ = $(SRC:.cpp=.o)

# Output
OUT = game.exe

all: $(OUT)

$(OUT) : $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -o $(OUT)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	del *.o $(OUT)
