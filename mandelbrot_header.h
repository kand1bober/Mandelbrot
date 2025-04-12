#ifndef CALCULATE_HEADER
#define CALCULATE_HEADER

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <x86intrin.h>
#pragma intrinsic(__rdtsc)


#ifdef TESTS   
    #define TESTS(expr) expr 
    #define NO_TESTS(expr) 
#else 
    #define TESTS(expr)
    #define NO_TESTS(expr) expr
#endif 

#ifdef GRAPHICS
    #define GRAPHICS(expr) expr
#else  
    #define GRAPHICS(expr) 
#endif

#define kWindowWidth 1920
#define kWindowHeight 1080

typedef enum
{   
    kNoKey = 0,
    kUp,
    kDown,
    kLeft,
    kRight,
    kPlus,
    kMinus, 
} Keys;

typedef enum
{
    kYes= 1,
    kNo = 2,
} Condition;

typedef struct
{
    int frames;
    int runs;
}ProgConfig;

#define kBlack  (uint32_t)0x000000
#define kRed    (uint32_t)0xff0000ff
#define kYellow (uint32_t)0xffff00ff
#define kBlue   (uint32_t)0x0000ff
#define kGreen  (uint32_t)0x00ff0000
#define kAzure  (uint32_t)0x00ffffff
#define kPink   (uint32_t)0xff00ff00

int GetArgs(int argc, char* argv[], ProgConfig* config);
int CalculateFrame( uint8_t* pixel_frame, Keys key_code );

#endif 
