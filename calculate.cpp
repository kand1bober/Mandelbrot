#include "mandelbrot_header.h"
#include <SFML/Window/Keyboard.hpp>

int CalculateFrame (uint8_t* pixel_frame, Keys key_code)
{   
    //------------------------
    float x00 = -2.f;    
    float y00 = -1.25f;
    float x0 = 0.f;    
    float y0 = 0.f;

    static float scale = 400.f;
    float dx = 1/scale;
    float dy = 1/scale;
    int N_max = 256;
    //------------------------
    int x_center = 300;
    int y_center = 0;
    float r2_max = 4;

    uint32_t color = 0;
    //------------------------
    switch ((int)key_code)
    {   
        case kUp:
        {
            printf("Up\n");
            break;
        }   
        case kDown:
        {   

            break;
        }
        case kLeft:
        {
            
            break;
        }
        case kRight:
        {

            break;
        }
        case kPlus:
        {
            scale += 10.f;
            printf("Plus\n");
            break;
        }
        case kMinus:
        {

            break;
        }
        case kNoKey:
        {
            printf("No key\n");
            break;
        }
        default:
        {
            printf("Nothing\n");
            break;
        }
    }
    //-----------------------

    y0 = y00;
    for( int pix_y = 0; pix_y < kWindowHeight; pix_y++, y0 += dy )
    {
        x0 = x00;
        for( int pix_x = 0; pix_x < kWindowWidth; pix_x++, x0 += dx )
        {   
            float x = x0;
            float y = y0;
            
            int N = 0;
            for (; N < N_max; N++)
            {
                float x2 = x * x;
                float y2 = y * y;
                float xy = x * y;   
                float r2 = x2 + y2;

                if (r2 >= r2_max ) 
                    break;

                x = x2 - y2 + x0;
                y = 2 * xy + y0; 
            }

            if (N < (N_max - 1)) 
                color = kBlack;
            if(N < (100))
                color = kPink;
            else 
                color = kYellow;

            int true_y = pix_y;
            int true_x = pix_x;

            int base_pix_pos = ( kWindowWidth * true_y + true_x ) * 4;
            pixel_frame[base_pix_pos] = (uint8_t)(color >> 24);
            pixel_frame[base_pix_pos + 1] = (uint8_t)((color << 8) >> 24);
            pixel_frame[base_pix_pos + 2] = (uint8_t)((color << 16) >> 24);
            pixel_frame[base_pix_pos + 3] = (uint8_t)((color << 24) >> 24);
        }   
    }

    return 0;   
}  

