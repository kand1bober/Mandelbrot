#include "mandelbrot_header.h"
#include <emmintrin.h>
#include <xmmintrin.h>

/* *************** INTEGERS *********************
*
* __m128i _mm_add_epi32 (__m128i a, __m128i b)      //add 4 packed 32-bit integer numbers 
* __m128i _mm_add_epi64 (__m128i a, __m128i b)      //add 4 packed 64-bit integer numbers 
*
* __m256i _mm256_add_epi32 (__m256i a, __m256i b)   //add 8 packed 32-bit integer numbers 
* __m256i _mm256_add_epi64 (__m256i a, __m256i b)   //add 8 packed 64-bit integer numbers
*
* __m128i _mm_sub_epi32 (__m128i a, __m128i b)      //sub 4 packed 32-bit integer numbers 
* __m128i _mm_sub_epi64 (__m128i a, __m128i b)      //sub 4 packed 64-bit integer numbers 
*
* __m256i _mm256_sub_epi32 (__m256i a, __m256i b)   //sub 8 packed 32-bit integer numbers
* __m256i _mm256_sub_epi64 (__m256i a, __m256i b)   //sub 8 packed 32-bit integer numbers
*
******************* FLOATS **********************
*
* __m128 _mm_mul_ps (__m128 a, __m128 b)            //Multiply packed single-precision (32-bit) floating-point elements in a and b
* __m128 _mm_add_ps (__m128 a, __m128 b)            //add Add packed single-precision (32-bit) floating-point elements in a and b
* 
* __m128 _mm_sub_ps (__m128 a, __m128 b)            //Subtract packed single-precision (32-bit) floating-point elements in b from packed single-precision (32-bit) floating-point elements in a
* 
* __m128 _mm_set_ps (float e3, float e2, float e1, float e0) //Set packed single-precision (32-bit) floating-point elements in dst with the supplied values
* __m128 _mm_set_ps1 (float a)                      //Broadcast single-precision (32-bit) floating-point value a to all elements of dst
* 
* int _mm_movemask_ps (__m128 a)                    //  FOR j := 0 to 3
*                                                                i := j*32
*                                                                IF a[i+31]
*                                                                    dst[j] := 1
*                                                                ELSE
*                                                                    dst[j] := 0   
*
* __m128 _mm_cmple_ps (__m128 a, __m128 b)          // FOR j := 0 to 3
*                                                               i := j*32
*                                                               dst[i+31:i] := ( a[i+31:i] <= b[i+31:i] ) ? 0xFFFFFFFF : 0
*
* __m128i _mm_castps_si128 (__m128 a)               // Cast vector of type __m128 to type __m128i. ( does not generate any instructions, thus it has zero latency. )
*
* void _mm_store_si128 (__m128i* mem_addr, __m128i a) // Store 128-bits of integer data from a into memory
*
* __m128i _mm_xor_si128 (__m128i a, __m128i b)      // Compute the bitwise XOR of 128 bits (representing integer data) in a and b, and store the result in dst
*
************************************************/

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
    int mask = 0;
    //------------------------
    __m128 r2_max = _mm_set_ps1(2.f);

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
            __m128 x_0_arr = _mm_set_ps(x0, x0 + dx, x0 + 2*dx, x0 + 3*dx);
            __m128 y_0_arr = _mm_set_ps1(y0);

            __m128 x = x_0_arr;
            __m128 y = y_0_arr;            
        
            __m128i N = _mm_set1_epi32(0);          //integer
            for (int n = 0; n < n_max; n++)
            {
                __m128 x2 = _mm_mul_ps(x, x);
                __m128 y2 = _mm_mul_ps(y, y);
                __m128 xy = _mm_mul_ps(x, y);
                __m128 r2 = _mm_add_ps(x2, y2);

                __m128 cmp = _mm_cmple_ps(r2, r2_max);
                
                mask = 0;
                mask = _mm_movemask_ps(cmp);
                if(!mask) break;

                N = _mm_sub_epi32(N, _mm_castps_si128(cmp));

                x = _mm_add_ps(_mm_sub_ps(x2, y2), x_0_arr);

                __m128 const_two = _mm_set_ps1(2.f);
                y = _mm_add_ps(_mm_mul_ps(xy, const_two), y_0_arr);
            }
    
            int base_pix_pos = 0;

            int N_ptr[4] = {0};
            _mm_store_si128((__m128i*)N_ptr, N);

            for(int i = 0; i < 4; i++)
            {   
                if (N_ptr[3-i] < (n_max - 1)) 
                    color[i] = kBlack;
                else if (N_ptr[i] < (100))
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

