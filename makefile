CC = g++
SDL_LIB = ${shell sdl2-config --libs} -lSDL2_image
SDL_FLAGS = ${shell sdl2-config --cflags}
CFLAGS = -Wall -std=c++11 ${SDL_FLAGS}
LDFLAGS = ${SDL_LIB}
EXE = sdlTest

sdlTest:lTexture.o alpha.cpp
	${CC} alpha.cpp ${CFLAGS} ${LDFLAGS} -o ${EXE} lTexture.o
lTexture.o:LTexture.cpp LTexture.hpp
	${CC} LTexture.cpp ${CFLAGS} ${LDFLAGS} -c -o lTexture.o
clean:
	rm *.o
