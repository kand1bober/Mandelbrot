#include "mandelbrot_header.h"

int main(int argc, char* argv[])
{
    ProgConfig config = {};
    config.graphics = kYes;
    GetArgs(argc, argv, &config );

    uint8_t* pixel_frame = (uint8_t* )malloc( kWindowHeight * kWindowWidth * 4 );

    sf::RenderWindow window(sf::VideoMode( {1920, 1080} ), "MandelbrotWindow");  

    sf::Texture texture;
    if( !texture.create(1920, 1080) ) return -1;
    sf::Sprite sprite(texture);
    Keys key_code = kNoKey;
    sf::Event event;

    //-------------
    float cur_time = 0;
    float fps = 0;
    uint64_t iter_number = 0;
    //-------------

    uint64_t ticks_start = 0, ticks_end = 0, ticks_res = 0;


    //many times start cycle
    TESTS
    (
        for(int runs_counter = 0; runs_counter < config.runs; runs_counter++)
        {
            ticks_start = __rdtsc();
            for(int i = 0; i < config.frames; i++) 
    )
    NO_TESTS
    ( 
        while ( window.isOpen() ) 
    ) 
    {   
        iter_number++;

        NO_TESTS
        (
            while (window.pollEvent(event)) 
            {
                if (event.type == sf::Event::Closed) 
                {
                    window.close();
                }
                else    
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        key_code = kUp;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        key_code = kDown;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        key_code = kLeft;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        key_code = kRight;
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                    {
                        key_code = kPlus;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
                    {
                        key_code = kMinus;
                    }
                    else
                    {
                        key_code = kNoKey;
                    }
                }
            }
        )

        // calculate new picture 
        CalculateFrame(pixel_frame, key_code);
        key_code = kNoKey;

        // switch((int)config.graphics)
        // {
        //     case kYes:
        //     {
        //         // update texture
        //         sf::Uint8* pixels = pixel_frame;
        //         texture.update( pixels );
                
        //         //-------draw---------
        //         window.clear(sf::Color::Black); 
        //         window.draw(sprite);
        //         window.display();
        //         break;
        //     }

        //     case kNo:
        //         break;
            
        //     default:
        //     {
        //         printf("variable 'graphics' shouldn't be touched\n");
        //         exit(1);
        //         break;
        //     }
        // }
    }
    ticks_end = __rdtsc();
    ticks_res = ticks_end - ticks_start;

    TESTS
    (
        printf("%d run: %lu ticks\n", runs_counter, ticks_res );
        }
    )

    free( pixel_frame );

    return 0;
}

int GetArgs(int argc, char* argv[], ProgConfig* config)
{
    for(int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-graphics"))
        {
            config->graphics = kYes;
        }
        else if (!strcmp(argv[i], "-no-graphics"))
        {
            config->graphics = kNo;
        }
        else if (!strcmp(argv[i], "-frames"))
        {
            i++;
            config->frames = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-runs"))
        {
            i++;
            config->runs = atoi(argv[i]);
        }
        else
        {
            printf("iter %d\n", i);
            printf("Wrong argument\n");
            exit(1);
        }
    }

    return 0;
}
