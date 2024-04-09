
OBJS = Game.cpp WorldGenerator.cpp WindowManager.cpp

CC = g++

INCLUDE_PATHS = -IC:/mingw_dev_lib/SDL2/include/SDL2

LIBRARY_PATHS = -LC:/mingw_dev_lib/SDL2/lib

COMPILER_FLAGS = -w

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

OBJ_NAME = app

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)