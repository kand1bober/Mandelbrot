#include "mandelbrot_header.h"
#include <SFML/Window/Keyboard.hpp>

int CalculateFrame (uint8_t* pixel_frame, Keys key_code)
{   
    //------------------------
    static float x00 = -2.f;    
    static float y00 = -1.25f;
    float x0 = 0.f;    
    float y0 = 0.f;

    static float scale = 400.f;
    float dx = 1/scale;
    float dy = 1/scale;
    int n_max = 256;
    //------------------------
    float r2_max = 4;

    uint32_t color[4] = {0};
    //------------------------
    switch ((int)key_code)
    {   
        case kUp:
        {
            y00 += 0.01;
            break;
        }   
        case kDown:
        {   
            y00 -= 0.01;
            break;
        }
        case kLeft:
        {
            x00 += 0.01;
            break;
        }
        case kRight:
        {
            x00 -= 0.01;
            break;
        }
        case kPlus:
        {
            scale += 100.f;
            break;
        }
        case kMinus:
        {
            scale -= 20.f;
            break;
        }
        case kNoKey:
        {
            break;
        }
        default:
        {
            break;
        }
    }
    //-----------------------

    y0 = y00;
    for( int yi = 0; yi < kWindowHeight; yi += 1, y0 += dy )
    {
        x0 = x00;
        for( int xi = 0; xi < kWindowWidth - 4; xi += 4, x0 += 4*dx )
        {   
            float x_0_arr[4] = {x0, x0 + dx, x0 + 2*dx, x0 + 3*dx};
            float y_0_arr[4] = {y0, y0,      y0,        y0};

            float x[4] = {}; for(int i = 0; i < 4; i++) { x[i] = x_0_arr[i]; }
            float y[4] = {}; for(int i = 0; i < 4; i++) { y[i] = y_0_arr[i]; }
            
            int N[4] = {0};
            for (int n = 0; n < n_max; n++)
            {
                float x2[4] = {}; for(int i = 0; i < 4; i++) { x2[i] = x[i] * x[i]; }
                float y2[4] = {}; for(int i = 0; i < 4; i++) { y2[i] = y[i] * y[i]; }
                float xy[4] = {}; for(int i = 0; i < 4; i++) { xy[i] = x[i] * y[i]; }   
                float r2[4] = {}; for(int i = 0; i < 4; i++) { r2[i] = x2[i] + y2[i]; } 

                int cmp[4] = {0};
                for(int i = 0; i < 4; i++) { if (r2[i] <= r2_max) cmp[i] = 1; }

                int mask = 0;
                for(int i = 0; i < 4; i++) { mask |= (!!cmp[i] << i); }
                if( !mask ) break;

                for(int i = 0; i < 4; i++) { N[i] = N[i] + cmp[i]; }
                for(int i = 0; i < 4; i++) { x[i] = x2[i] - y2[i] + x_0_arr[i]; }
                for(int i = 0; i < 4; i++) { y[i] = 2 * xy[i] + y_0_arr[i]; } 
                       
            }
    
            int base_pix_pos = 0;
            for(int i = 0; i < 4; i++)
            {
                if (N[i] < (n_max - 1)) 
                    color[i] = kBlack;
                else if (N[i] < (100))
                    color[i] = kPink;
                else 
                    color[i] = kYellow;


                base_pix_pos = ( kWindowWidth * yi + xi + i ) * 4;

                for(int j = 0; j < 4; j++)
                {
                    pixel_frame[base_pix_pos + j] = (uint8_t)((color[i] << (8*j) ) >> 24);
                }
            }
        }   
    }

    return 0;   
}  

