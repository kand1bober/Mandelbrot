#include "mandelbrot_header.h"

int main( int argc, char* argv[] )
{
    uint8_t* pixel_frame = (uint8_t* )malloc( kWindowHeight * kWindowWidth * 4 );


    sf::RenderWindow window(sf::VideoMode( {1920, 1080} ), "MandelbrotWindow");  //854, 480

    sf::Texture texture;
    if( !texture.create(1920, 1080) ) return -1;    // crating texture 

    // Create a sprite that will display the texture
    sf::Sprite sprite(texture);

    while ( window.isOpen() )
    {
        // // calculate new picture 
        CalculateFrame( pixel_frame );
        
        //update texture
        sf::Uint8* pixels = pixel_frame;
        texture.update( pixels );
        
        //-------draw---------
        window.draw( sprite );
        
        window.display();
    }

    free( pixel_frame );

    return 0;
}
