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
    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);    //Renders texture at given point
    //Set blending
    void setBlendMode( SDL_BlendMode blending);
    //Set alpha modulation
    void setAlpha(Uint8 alpha);
    //Dibuja en pantalla
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    //para modificar renderer
    void setRenderer(SDL_Renderer* render);
    //Obtiene las dimensiones de la imagen
    int getWidth();
    int getHeight();
private:
    //La textura 
    SDL_Texture* mTexture;
    SDL_Renderer* ren;
    //Dimensiones de la imagen
    int mWidth;
    int mHeight;
};
#endif
