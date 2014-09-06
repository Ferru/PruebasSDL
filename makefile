CC = g++
SDL_LIB = -lSDL2 -lSDL2_image
CFLAGS = -Wall -std=c++11 
LDFLAGS = ${SDL_LIB}
EXE = sdlTest

sdlTest:viewports.cpp
	${CC} viewports.cpp ${CFLAGS} ${LDFLAGS} -o ${EXE}
