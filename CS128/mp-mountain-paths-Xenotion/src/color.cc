#include "color.hpp"

#define kMaxColorValue 255

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (r < 0 || r > kMaxColorValue) {
    throw std::invalid_argument("red value out of range");
  } 
  if (g < 0 || g > kMaxColorValue) {
    throw std::invalid_argument("green value out of range");
  } 
  if (b < 0 || b > kMaxColorValue) {
    throw std::invalid_argument("blue value out of range");
  } 

  red_ = r;
  green_ = g;
  blue_ = b;
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}