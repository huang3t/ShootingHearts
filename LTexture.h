#ifndef LTexture_h
#define LTexture_h
#include <string>
#include <SDL2/SDL.h>


class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path );

    //Deallocates texture
    void free();
    //Set blending
    //void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    //void setAlpha( Uint8 alpha );


    //Renders texture at given point
    void render( int, int ,
        int expandw=-1,int expandh=-1,int XRatio=100);
    //expand: expand the size of target Rect

    void render2 (int i);//for stage 2 

    //Gets image dimensions
    int getWidth();
    int getHeight();
    double posX, posY;
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;

private:
    //The actual hardware texture


    //Image dimensions

};

#endif /* LTexture_h */
