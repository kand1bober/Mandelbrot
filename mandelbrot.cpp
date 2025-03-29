#include "mandelbrot_header.h"

int main( int argc, char* argv[] )
{
    uint8_t* pixel_frame = (uint8_t* )malloc( kWindowHeight * kWindowWidth * 4 );


    sf::RenderWindow window(sf::VideoMode( {1920, 1080} ), "MandelbrotWindow");  //854, 480

    sf::Texture texture;
    if( !texture.create(1920, 1080) ) return -1;    // crating texture 

    // Create a sprite that will display the texture
    sf::Sprite sprite(texture);

    Keys key_code = kNoKey;
    while ( window.isOpen() )
    {
        sf::Event event;
        if(event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::Up)
            {
                key_code = kUp;
            }
            if(event.key.code == sf::Keyboard::Down)
            {
                key_code = kDown;
            }   
            if(event.key.code == sf::Keyboard::Left)
            {   
                key_code = kLeft;
            }
            if(event.key.code == sf::Keyboard::Right)
            {       
                key_code = kRight;
            }
            if(event.key.code == sf::Keyboard::Add)
            {   
                key_code = kPlus;
            }
            if(event.key.code == sf::Keyboard::Subtract)
            {   
                key_code = kMinus;
            }
        }

        // calculate new picture 
        CalculateFrame(pixel_frame, key_code);
        
        //update texture
        sf::Uint8* pixels = pixel_frame;
        texture.update( pixels );
        
        //-------draw---------
        window.clear(sf::Color::Black); 
        window.draw(sprite);
        
        window.display();
    }

    free( pixel_frame );

    return 0;
}
