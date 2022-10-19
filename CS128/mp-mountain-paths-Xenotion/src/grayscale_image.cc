#include "grayscale_image.hpp"
#include <iostream>
#define maxval 255.0
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();

  int max_ele = dataset.MaxEle();
  int min_ele = dataset.MinEle();

  for (size_t i = 0; i < height_; i++) {
    std::vector<Color> row;
    for (size_t j = 0; j < width_; j++) {
      int datum = dataset.DatumAt(i, j);
      double color = 0.0;
      if (max_ele == min_ele) {
        color = 0.0;
      } else {
        color = maxval * (datum - min_ele) / (max_ele - min_ele);
        color = std::round(color);
      }
      int color1 = static_cast<int>(color);
      Color c(color1, color1, color1);
      row.push_back(c);
    }
    image_.push_back(row);
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) {
  width_ = width;
  height_ = height;
  ElevationDataset data = ElevationDataset(filename, width, height);
  int max_ele = data.MaxEle();
  int min_ele = data.MinEle();

  for (size_t i = 0; i < height_; i++) {
    std::vector<Color> row;
    for (size_t j = 0; j < width_; j++) {
      int datum = data.DatumAt(i, j);
      double color = 0.0;
      if (max_ele == min_ele) {
        color = 0.0;
      } else {
        color = maxval * (datum - min_ele) / (max_ele - min_ele);
        color = std::round(color);
      }
      int color1 = static_cast<int>(color);
      Color c(color1, color1, color1);
      row.push_back(c);
    }
    image_.push_back(row);
  }
}

size_t GrayscaleImage::Width() const {
  return width_;
}

size_t GrayscaleImage::Height() const {
  return height_;
}

unsigned int GrayscaleImage::MaxColorValue() const {
  return kMaxColorValue;
}

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_[row][col];
}

const std::vector<std::vector<Color> >& GrayscaleImage::GetImage() const {
  return image_;
}

void GrayscaleImage::ToPpm( const std::string& name ) const {
  std::ofstream file(name);
  file << "P3" << std::endl;
  file << width_ << " " << height_ << std::endl;
  file << kMaxColorValue << std::endl;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      file << image_[i][j].Red() << " " << image_[i][j].Blue() << " " << image_[i][j].Green() << " ";
    }
    file << std::endl;
  }
}