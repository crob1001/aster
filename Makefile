#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:/mingwDevLibs/include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:/mingwDevLibs/lib

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Oz -s -x -w -Wl,-Bdynamic #-Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = out/main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)