#include <SFML/Graphics.hpp>

void MakeVideoAndPatch()
{
    sf::RenderWindow window(sf::VideoMode( 854, 480 ), "keygen_window");

    //-----------image work----------------------
    sf::Texture texture;
    texture.loadFromFile("src/trolpic.jpg");
    PicPos position_1 = {};
    position_1.width = 320;
    position_1.height = 180;
    position_1.UL = { 0.0f, 0.0f };
    position_1.delta_x = 2.0f;
    position_1.delta_y = 2.0f;
    position_1.move_to_right = true;
    position_1.move_down = true;

    sf::Sprite sprite1(texture);
    sprite1.setScale(0.5f, 0.5f);
    //-------------------------------------------

    //-------------------------------------------
    bool progress_ready = false;
    sf::Texture progress_frame;
    progress_frame.loadFromFile("src/frame.png");
    sf::Sprite sprite2(progress_frame);
    sprite2.setScale(1.0f, 1.0f);
    float x_position_2 = 139.5f, y_position_2 = 400.0f;
    //-------------------------------------------

    //-------------------------------------------
    sf::Texture progress_bar;
    progress_bar.loadFromFile("src/bar.png");
    sf::Sprite sprite3(progress_bar);
    float x_position_3 = 148.3f, y_position_3 = 408.0f;
    float x_scale_3 = 0.0f, y_scale_3 = 1.0f;
    sprite3.setScale( x_scale_3, y_scale_3 );
    //-------------------------------------------

    //-------------Text--------------------------
    sf::Font font;
    font.loadFromFile("src/PixelGame.otf");
    sf::Text text1("your code was cracked =)", font, 40);
    text1.move( 240.0f, 360.0f );

    bool music_is_playing = true;
    sf::Text text2("Space ->  play music\n"
                   "BackSpace -> stop  ", font, 20);
    text2.move( 20.0f, 280.0f );
    //-------------------------------------------

    //---------------Clock-----------------------
    sf::Clock clock;
    window.setFramerateLimit(60);
    //-------------------------------------------

    //---------------Music-----------------------
    sf::Music music;
    music.openFromFile("src/Cyberpunk_8_bit.mp3");
    //-------------------------------------------

    music.play();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed)
                window.close();
            
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    if( !music_is_playing )
                    {
                        music.play();
                        music_is_playing = true;
                    }   
                }
                if(event.key.code == sf::Keyboard::BackSpace)
                {
                    music.pause();
                    music_is_playing = false;
                }
                else 
                {
                    printf("key pressed\n");
                }
            }
        }

        //----------moving sprite1----------------
        ChangeDirection( &position_1 );
        sprite1.setPosition( position_1.UL.x, position_1.UL.y );

        //--------------sprite2-------------------
        sprite2.setPosition( x_position_2, y_position_2 );

        //-----------------sprite3----------------
        sprite3.setPosition( x_position_3, y_position_3 );
        sprite3.setScale( x_scale_3, y_scale_3 );

        if( !progress_ready )
        {
            x_scale_3 += 0.001f;    
        }
        if( x_scale_3 >= 0.999f ) 
        {
            progress_ready = true;
            
            patcher();
        }
        //---------------------------------------

        //clear previous frame
        window.clear();

        
        //-------draw---------
        window.draw(sprite1);
        window.draw(text2);
        window.draw(sprite2);
        window.draw(sprite3);
        //--------------------
        if( progress_ready )
        {
            window.draw(text1);
        }
        
        window.display();
    }
}


void ChangeDirection( PicPos *position )
{
    float monitor_width = 854.0f;
    float monitor_height = 480.0f;
    
    //Left corner 
    if( position->UL.x < 0.1f )
    {
        position->move_to_right = true;
    }
    else if( position->UL.x + position->width >= (monitor_width - 0.1f) )
    {
        position->move_to_right = false;
    }

    if( position->UL.y < 0.1f )
    {
        position->move_down = true;
    }
    else if( position->UL.y + position->height >= (monitor_height - 0.1f) )
    {
        position->move_down = false;
    }

    position->UL.x += position->delta_x;
    position->UL.y += position->delta_y;

    if( position->move_to_right )
    {
        position->delta_x = 4.0f;
    }
    else
    {
        position->delta_x = -4.0f;
    }

    if( position->move_down )
    {
        position->delta_y = 2.5f;
    }
    else 
    {
        position->delta_y = -2.5f;
    }
}

