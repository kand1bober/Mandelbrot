#ifndef CALCULATE_HEADER
#define CALCULATE_HEADER

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <stdint.h>
#include <xmmintrin.h>

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

#define kBlack (uint32_t)0x000000
#define kPink  (uint32_t)0xff54accc

#define kRed (uint32_t)0xff0000ff
#define kYellow (uint32_t)0xffff00ff
#define kOrange1 (uint32_t)0xff6200ff
#define kOrange2 (uint32_t)0xff9b00ff


int CalculateFrame( uint8_t* pixel_frame, Keys key_code );

#endif 
