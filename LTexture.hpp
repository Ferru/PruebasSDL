#include <string>
#include <SDL2/SDL.h>
#ifndef LTEXTURE_TEST
#define LTEXTURE_TEST
class LTexture
{
public:
    //Constructor
    LTexture();
    //Destructor
    ~LTexture();
    //Carga imagenes de la ruta especificada
    bool loadFromFile(std::string path2, SDL_Renderer* ren);
    //Libera recursos
    void free();
    //Renders texture at given point
    void render(SDL_Renderer* ren, int x, int y, SDL_Rect* clip = NULL);
    //Obtiene las dimensiones de la imagen
    int getWidth();
    int getHeight();
private:
    //La textura 
    SDL_Texture* mTexture;
    //Dimensiones de la imagen
    int mWidth;
    int mHeight;
};
#endif
