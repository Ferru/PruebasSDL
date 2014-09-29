CC = g++
SDL_LIB = -lSDL2 -lSDL2_image
CFLAGS = -Wall -std=c++11 
LDFLAGS = ${SDL_LIB}
EXE = sdlTest

sdlTest:lTexture.o colorMod.cpp
	${CC} colorMod.cpp ${CFLAGS} ${LDFLAGS} -o ${EXE} lTexture.o
lTexture.o:LTexture.cpp LTexture.hpp
	${CC} LTexture.cpp ${CFLAGS} ${LDFLAGS} -c -o lTexture.o
clean:
	rm *.o
