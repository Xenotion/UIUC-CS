#include "elevation_dataset.hpp"
#include <iostream>

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) {
  std::ifstream file;
  file.open(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file");
  } 
  if (file.bad()) {
    throw std::runtime_error("File is bad");
  }
  if (width == 0 || height == 0) {
    throw std::runtime_error("Width or height is 0");
  }
  int datum = 0;
  int count = 0;
  width_ = width;
  height_ = height;
  size_t total = width * height;
  std::vector<int> data;
  while (file >> datum) {
    count++;
    data.push_back(datum);
    if (count % width == 0) {
      data_.push_back(data);
      data.clear();
    }
  }
  if (count > static_cast<int>(total)) { throw std::runtime_error("Too many values"); }
  if (count < static_cast<int>(total)) { throw std::runtime_error("Too few values"); }
  max_ele_ = data_[0][0];
  min_ele_ = data_[0][0];
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      if (data_[i][j] > max_ele_) { max_ele_ = data_[i][j]; }
      if (data_[i][j] < min_ele_) { min_ele_ = data_[i][j]; }
    }
  }
}

size_t ElevationDataset::Width() const {
  return width_;
}

size_t ElevationDataset::Height() const {
  return height_;
}

int ElevationDataset::MaxEle() const {
  return max_ele_;
}

int ElevationDataset::MinEle() const {
  return min_ele_;
}

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_[row][col];
}

const std::vector<std::vector<int> >& ElevationDataset::GetData() const {
  return data_;
}