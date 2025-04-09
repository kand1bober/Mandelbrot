#include "mandelbrot_header.h"

inline void mm_set_ps(float* res, float f0, float f1, float f2, float f3) { res[0] = f0; res[1] = f1; res[2] = f2; res[3] = f3; }

inline void mm_set_ps1(float* res, float f) { for(int i = 0; i < 4; i++) {res[i] = f;} }

inline void mm_cpy_ps(float* res, float* src) { for(int i = 0; i < 4; i++) {res[i] = src[i];} }

inline void mm_add_ps(float* res, float* a, float* b) { for(int i = 0; i < 4; i++) {res[i] = a[i] + b[i];} }

inline void mm_add_epi32(int* res, int* a, int* b) { for(int i = 0; i < 4; i++) {res[i] = a[i] + b[i];} }

inline void mm_sub_ps(float* res, float* a, float* b) { for(int i = 0; i < 4; i++) {res[i] = a[i] - b[i];} }

inline void mm_mul_ps(float* res, float* a, float* b) { for(int i = 0; i < 4; i++) {res[i] = a[i] * b[i];} }

inline void mm_cmple_ps(int* cmp, float* a, float* b )
{ 
    for(int i = 0; i < 4; i++) 
        { 
            cmp[i] = (int)( a[i] <= b[i] );
        } 
}

inline int mm_movemask_ps(int* cmp) 
{ 
    int mask = 0;
    for(int i = 0; i < 4; i++) 
    {
        mask |= (!!cmp << i); // '<<' has bigger priority than '!'
    } 
    return mask;
}
//-----------------------------------------------

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
    float r2_max[4] = {2.f, 2.f, 2.f, 2.f};

    uint32_t color[4] = {0};
    //------------------------
    switch ((int)key_code)
    {   
        case kUp:
            y00 += 0.01;
            break;
        case kDown:  
            y00 -= 0.01;
            break;
        case kLeft:
            x00 += 0.01;
            break;
        case kRight:
            x00 -= 0.01;
            break;
        case kPlus:
            scale += 100.f;
            break;
        case kMinus:
            scale -= 100.f;
            break;
        case kNoKey:
            break;
        default:
            break;
    }
    //-----------------------

    y0 = y00;
    for( int yi = 0; yi < kWindowHeight; yi += 1, y0 += dy )
    {
        x0 = x00;
        for( int xi = 0; xi < kWindowWidth - 4; xi += 4, x0 += 4*dx )
        {   
            float x_0_arr[4] = {}; mm_set_ps(x_0_arr, x0, x0 + dx, x0 + 2*dx, x0 + 3*dx);
            float y_0_arr[4] = {}; mm_set_ps1(y_0_arr, y0);

            float x[4] = {}; mm_cpy_ps(x, x_0_arr);
            float y[4] = {}; mm_cpy_ps(y, y_0_arr);
            
            
            int N[4] = {0};
            for (int n = 0; n < n_max; n++)
            {
                float x2[4] = {}; mm_mul_ps(x2, x, x);
                float y2[4] = {}; mm_mul_ps(y2, y, y);
                float xy[4] = {}; mm_mul_ps(xy, x, y);   
    
                float r2[4] = {}; mm_add_ps(r2, x2, y2); 

                int cmp[4] = {0};
                mm_cmple_ps(cmp, r2, r2_max );

                int mask = 0;
                mask = mm_movemask_ps(cmp);
                if( !mask ) break;

                mm_add_epi32(N, N, cmp);

                mm_sub_ps(x, x2, y2);
                mm_add_ps(x, x, x_0_arr);

                float const_two[4] = {2.f, 2.f, 2.f, 2.f};
                mm_mul_ps(y, xy, const_two); 
                mm_add_ps(y, y, y_0_arr);                      
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

    