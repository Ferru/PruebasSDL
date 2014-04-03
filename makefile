CC = g++
SDL_LIB = -lSDL2
CFLAGS = -Wall -std=c++11 
LDFLAGS = ${SDL_LIB}
EXE = sdlTest

sdlTest:main.cpp
	${CC} main.cpp ${CFLAGS} ${LDFLAGS} -o ${EXE}
