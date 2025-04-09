#include "mandelbrot_header.h"
    
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
    uint64_t n_max = 256;
    int mask = 0;
    //------------------------
    __m256 r2_max = _mm256_set1_ps(4.f);
    uint32_t N_ptr[8] = {0};
    //------------------------
    int k = 0;
    int base_pix_pos = 0;
    uint32_t color[8] = {0};
    uint32_t color_mod = 0x00000000;
    //------------------------

    NO_TESTS
    (
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
    )
    //-----------------------

    y0 = y00;
    for( int yi = 0; yi < kWindowHeight; yi += 1, y0 += dy )
    {
        x0 = x00;
        for( int xi = 0; xi < kWindowWidth - 8; xi += 8, x0 += 8*dx )
        {   
            __m256 x_0_arr = _mm256_set_ps(x0, x0 + dx, x0 + 2*dx, x0 + 3*dx, x0+4*dx, x0+5*dx, x0+6*dx, x0+7*dx);
            __m256 y_0_arr = _mm256_set1_ps(y0);

            __m256 x = x_0_arr;
            __m256 y = y_0_arr;            
        
            __m256i N = _mm256_set1_epi32(0);          //integer
            for (int n = 0; n < n_max; n++)
            {
                __m256 x2 = _mm256_mul_ps(x, x);
                __m256 y2 = _mm256_mul_ps(y, y);
                __m256 xy = _mm256_mul_ps(x, y);
                __m256 r2 = _mm256_add_ps(x2, y2);

                __m256 cmp = _mm256_cmp_ps(r2, r2_max, _CMP_LE_OS);
                
                mask = 0;
                mask = _mm256_movemask_ps(cmp);
                if(!mask) break;

                N = _mm256_sub_epi32(N, _mm256_castps_si256(cmp));

                x = _mm256_add_ps(_mm256_sub_ps(x2, y2), x_0_arr);

                __m256 const_two = _mm256_set1_ps(2.f);
                y = _mm256_add_ps(_mm256_mul_ps(xy, const_two), y_0_arr);
            }
    
            _mm256_store_si256((__m256i*)N_ptr, N);
            
            for(int i = 0; i < 8; i++)
            {   
                k = 7 - i;
                if (N_ptr[k] <= 20)
                {
                    color[i] = kBlack;
                }
                else if (N_ptr[k] <= 85)
                {
                    color[i] = kBlue;
                    color_mod = (((3*N_ptr[k]) << 24) & 0xff000000);
                    color[i] &= 0x00ffffff;
                    color[i] |= color_mod;
                }
                else if (N_ptr[k] <= 170)
                {
                    color[i] = kRed;
                    color_mod = (((3*N_ptr[k]) << 16) & 0x00ff0000); // setting 1st byte 
                    color[i] &= 0xff00ffff; // clear space for insertion
                    color[i] |= color_mod; // insert 1st byte
                }
                else if(N_ptr[k] <= 250)
                {
                    color[i] = kPink;
                    color_mod = (((256 - 4*N_ptr[k]) << 8) & 0xff000000); 
                    color[i] &= 0x00ffffff; 
                    color[i] |= color_mod; 
                }   
                else 
                {
                    color[i] = kBlack;
                }

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

