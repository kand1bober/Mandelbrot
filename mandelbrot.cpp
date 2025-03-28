#include "mandelbrot_header.h"

int main( int argc, char* argv[] )
{
    uint8_t* pixel_frame = (uint8_t* )malloc( 1920 * 1080 * 4 );


    sf::RenderWindow window(sf::VideoMode( {1920, 1080} ), "MandelbrotWindow");  //854, 480

    sf::Texture texture;
    if( !texture.create(1920, 1080) ) return -1;    // crating texture 

    // Create a sprite that will display the texture
    sf::Sprite sprite(texture);

    while ( window.isOpen() )
    {
        // // calculate new picture 
        CalculateFrame( pixel_frame );

        // for( int i = 0; i < 100; i++ )
        // {
        //     pixel_frame[ int( ( 1920 * i + 500 ) * 4 ) ] = (uint8_t)(kPink >> 24) ;
        //     pixel_frame[ int( ( 1920 * i + 500 ) * 4 + 1) ] = (uint8_t)((kPink << 8) >> 24);
        //     pixel_frame[ int( ( 1920 * i + 500 ) * 4 + 2) ] = (uint8_t)((kPink << 16) >> 24);
        //     pixel_frame[ int( ( 1920 * i + 500 ) * 4 + 3) ] = (uint8_t)((kPink << 24) >> 24);
        // }
        
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
