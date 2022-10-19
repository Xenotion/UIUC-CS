#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>
#include <iostream>

#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"

const int kGreenr = 252;
const int kGreeng = 25;
const int kGreenb = 63;

const int kRedr = 31;
const int kRedg = 253;
const int kRedb = 13;

class PathImage {
public:
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color> >& GetPathImage() const;
  void ToPpm(const std::string& name) const;
  void RowIsZero(int& next_middle, int& next_bottom, size_t& j, const ElevationDataset &dataset, int& curr_elevation, size_t& temp_row, Path& p);
  void RowIsLast(int& next_middle, int& next_top, size_t& j, const ElevationDataset &dataset, int& curr_elevation, size_t& temp_row, Path& p);
  void RowIsMiddle(int& next_middle, int& next_top, int& next_bottom, size_t& j, const ElevationDataset &dataset, int& curr_elevation, size_t& temp_row, Path& p);
  void ColorPath(Path &best_path);
private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
};

#endif