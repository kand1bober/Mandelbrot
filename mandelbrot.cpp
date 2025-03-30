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
    sf::Clock clock;
    sf::Event event;
    while ( window.isOpen() )
    {   
        float cur_time = clock.restart().asSeconds();
        float fps = 1.0f / cur_time;
        printf("%f\n", fps);
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code) 
                {
                    case sf::Keyboard::Up:
                        key_code = kUp;
                        break;
                    case sf::Keyboard::Down:
                        key_code = kDown;
                        break;
                    case sf::Keyboard::Left:
                        key_code = kLeft;
                        break;
                    case sf::Keyboard::Right:
                        key_code = kRight;
                        break;
                    case sf::Keyboard::Add:
                        key_code = kPlus;
                        break;
                    case sf::Keyboard::Subtract:
                        key_code = kMinus;
                        break;
                    default:
                        key_code = kNoKey;
                        break;
                }
            }
        }

        // calculate new picture 
        CalculateFrame(pixel_frame, key_code);
        key_code = kNoKey;
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
