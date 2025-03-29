#ifndef CALCULATE_HEADER
#define CALCULATE_HEADER

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <stdint.h>

#define kBlue  (uint32_t)0x2a00ff 
#define kBlack (uint32_t)0x000000
#define kPink  (uint32_t)0xff54accc
#define kYellow (uint32_t)0xfff700cc
#define kPurple (uint32_t)0xbb06ff

int CalculateFrame( uint8_t* pixel_frame );

#endif 
