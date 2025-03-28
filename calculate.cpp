#include "mandelbrot_header.h"

int CalculateFrame( uint8_t* pixel_frame )
{
    int N_max = 200;
    int max_start_iters = 1000;
    float r2_max = 4;


    // x, y = coordinates in unit intervals, 1 unit interval = 100 pixels 
    float x_center = 600, y_center = 500; // in pixels
    float x0 = 0.1, y0 = 0.1; // in unit intervals      
    float dx = 0.01;

    for( int start_iters = 0; start_iters < max_start_iters; start_iters++, x0 += dx )
    {   
        float x = x0,
              y = y0;

        int N = 0;
        for( ; N <= N_max; N++ ) // calculate one point 
        {
            float x2 = x*x;
            float y2 = y*y;
            float xy = x*y;

            float r2 = x2 + y2; // distance between point and beginning of coordianate plane

            if( r2 >= r2_max ) break;

            x = x2 - y2 + x0;
            y = 2 * xy + y0;
        }

        // float I = F(N);
        uint32_t color = 0;

        if( N < N_max ) color = kYellow;
        else if( N < ( N_max - 100 ) ) color = kPink;
        else color = kBlack;

        // pixel_frame[ ( 1920*(int)(y*100 + y_center) + (int)(x*100 + x_center) - ((int)(x*100 + x_center) % 4) ) * 4 ] = (uint8_t)(color >> 24);
        // pixel_frame[ ( 1920*(int)(y*100 + y_center) + (int)(x*100 + x_center) - ((int)(x*100 + x_center) % 4) ) * 4 + 1 ] = (uint8_t)((color << 8) >> 24);
        // pixel_frame[ ( 1920*(int)(y*100 + y_center) + (int)(x*100 + x_center) - ((int)(x*100 + x_center) % 4) ) * 4 + 2 ] = (uint8_t)((color << 16) >> 24);
        // pixel_frame[ ( 1920*(int)(y*100 + y_center) + (int)(x*100 + x_center) - ((int)(x*100 + x_center) % 4) ) * 4 + 3 ] = (uint8_t)((color << 24) >> 24);

        
    }   

    return 0;   
}   

