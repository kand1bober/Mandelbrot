#include "draw_header.h"
#include <stdint.h>

int MakePicture()
{
    sf::RenderWindow window(sf::VideoMode( {1920, 1080} ), "MandelbrotWindow");  //854, 480

    sf::Texture texture;
    if( !texture.create(1920, 1080) ) return -1;    // crating texture 

    // Create a sprite that will display the texture
    sf::Sprite sprite(texture);

    while ( window.isOpen() )
    {
        //update texture
        sf::Uint8* pixels = ;
        texture.update( pixels )

        //clear previous frame
        window.clear( sf::Color::Black );
        
        //-------draw---------
        window.draw( sprite );
        
        window.display();
    }

    return 0;
}

