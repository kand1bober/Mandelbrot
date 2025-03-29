#include "mandelbrot_header.h"

typedef struct frameinfo
{
    int max_iters;
    int N_max;
    int scale;
    float r2_max;
    float x0;
    float y0;
    float dx;
    int x_centre;
    int y_centre;

} FrameInfo;

int CalculateFrame( uint8_t* pixel_frame )
{   
    FrameInfo info = {};
    info.N_max = 256;
    info.scale = 100;
    info.r2_max = 2.25;
    info.max_iters = 1000000;
    info.x_centre = 600; // in pixels
    info.y_centre = 500; // in pixels
    
    // x, y = coordinates in unit intervals, 1 unit interval = 100 pixels 
    info.x0 = 0.15;
    info.y0 = 0.13;      // in unit intervals      
    float dx = 0.000005;

    for( int start_iters = 0; start_iters < info.max_iters; start_iters++, info.x0 += dx )
    {   
        float x = info.x0,
              y = info.y0;

        int N = 0;
        for( ; N <= info.N_max; N++ ) // calculate one point 
        {
            float x2 = x*x;
            float y2 = y*y;
            float xy = x*y;

            float r2 = x2 + y2; // distance between point and beginning of coordianate plane

            if( r2 >= info.r2_max ) 
                break;

            x = x2 - y2 + info.x0;
            y = 2 * xy + info.y0;
        }

        // float I = F(N);
        uint32_t color = 0;

        if( N < info.N_max ) color = kYellow;
        else if( N < (int)(info.N_max / 2) ) color = kPurple;
        else color = kPink;

        int pix_base_pos = ( 1920 * (int)(y * info.scale + info.y_centre) + (int)(x * info.scale + info.x_centre) - ((int)(x * info.scale + info.x_centre) % 4) ) * 4;
        pixel_frame[ pix_base_pos ] = (uint8_t)(color >> 24);
        pixel_frame[ pix_base_pos + 1 ] = (uint8_t)((color << 8) >> 24);
        pixel_frame[ pix_base_pos + 2 ] = (uint8_t)((color << 16) >> 24);
        pixel_frame[ pix_base_pos + 3 ] = (uint8_t)((color << 24) >> 24);
    }   

    return 0;   
}  

