#include "path_image.hpp"

void PathImage::RowIsZero(int& next_middle, int& next_bottom, size_t& j, const ElevationDataset &dataset, int& curr_elevation, size_t& temp_row, Path& p) {
  next_middle = dataset.DatumAt(temp_row, j + 1);
  next_bottom = dataset.DatumAt(temp_row + 1, j + 1);

  const int kMiddleDiff = std::abs(curr_elevation - next_middle);
  const int kBottomDiff = std::abs(curr_elevation - next_bottom);

  if (kMiddleDiff <= kBottomDiff) {
    p.SetLoc(j + 1, temp_row);
    p.IncEleChange(kMiddleDiff);
  } else {
    p.SetLoc(j + 1, temp_row + 1);
    p.IncEleChange(kBottomDiff);
    temp_row++;
  }
}

void PathImage::RowIsLast(int& next_middle, int& next_top, size_t& j, const ElevationDataset &dataset, int& curr_elevation, size_t& temp_row, Path& p) {
  next_middle = dataset.DatumAt(temp_row, j + 1);
  next_top = dataset.DatumAt(temp_row - 1, j + 1);

  const int kTopDiff = std::abs(curr_elevation - next_top);
  const int kMiddleDiff = std::abs(curr_elevation - next_middle);

  if (kMiddleDiff <= kTopDiff) {
    p.SetLoc(j + 1, temp_row);
    p.IncEleChange(kMiddleDiff);
  } else {
    p.SetLoc(j + 1, temp_row - 1);
    p.IncEleChange(kTopDiff);
    temp_row--;
  }
}

void PathImage::RowIsMiddle(int& next_middle, int& next_top, int& next_bottom, size_t& j, const ElevationDataset &dataset, int& curr_elevation, size_t& temp_row, Path& p) {
  next_middle = dataset.DatumAt(temp_row, j + 1);
  next_top = dataset.DatumAt(temp_row - 1, j + 1);
  next_bottom = dataset.DatumAt(temp_row + 1, j + 1);

  const int kTopDiff = std::abs(curr_elevation - next_top);
  const int kMiddleDiff = std::abs(curr_elevation - next_middle);
  const int kBottomDiff = std::abs(curr_elevation - next_bottom);

  if (kTopDiff < kMiddleDiff && kTopDiff < kBottomDiff) {
    p.SetLoc(j + 1, temp_row - 1);
    p.IncEleChange(kTopDiff);
    temp_row--;
  } else if (kMiddleDiff < kTopDiff && kMiddleDiff < kBottomDiff) {
    p.SetLoc(j + 1, temp_row);
    p.IncEleChange(kMiddleDiff);
  } else if (kBottomDiff < kTopDiff && kBottomDiff < kMiddleDiff) {
    p.SetLoc(j + 1, temp_row + 1);
    p.IncEleChange(kBottomDiff);
    temp_row++;
  } else if (kTopDiff == kMiddleDiff) {
    p.SetLoc(j + 1, temp_row);
    p.IncEleChange(kMiddleDiff);
  } else if (kTopDiff == kBottomDiff) {
    p.SetLoc(j + 1, temp_row + 1);
    p.IncEleChange(kBottomDiff);
    temp_row++;
  } else if (kMiddleDiff == kBottomDiff) {
    p.SetLoc(j + 1, temp_row);
    p.IncEleChange(kMiddleDiff);
  } else {
    p.SetLoc(j + 1, temp_row);
    p.IncEleChange(kMiddleDiff);
  }
}

void PathImage::ColorPath(Path &best_path) {
  for (size_t i = 0; i < height_; i++) {
    std::vector<size_t> curr_path = paths_.at(i).GetPath();
    for (size_t j = 0; j < width_; j++) {
      path_image_[curr_path[j]][j] = Color(kGreenr, kGreeng, kGreenb);
    }
  }

  std::vector<size_t> best_path_vec = best_path.GetPath();
  for (size_t i = 0; i < width_; i++) {
    path_image_[best_path_vec[i]][i] = Color(kRedr, kRedg, kRedb);
  }
}

PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset) {
  
  width_ = dataset.Width();
  height_ = dataset.Height();
  path_image_ = image.GetImage();

  int curr_elevation = 0;
  int next_top = 0;
  int next_middle = 0;
  int next_bottom = 0;
  size_t temp_row = 0;
  Path best_path(width_, 0);

  for (size_t i = 0; i < height_; i++) {
    temp_row = i;
    Path p(width_, i); 
    for (size_t j = 0; j < width_ - 1; j++)  {
      curr_elevation = dataset.DatumAt(temp_row, j);
      if (j == 0) {
        p.SetLoc(j, temp_row);
      }
      if (temp_row == 0) {
        RowIsZero(next_middle, next_bottom, j, dataset, curr_elevation, temp_row, p);
      } else if (temp_row == height_ - 1) {
        RowIsLast(next_middle, next_top, j, dataset, curr_elevation, temp_row, p);
      } else {
        RowIsMiddle(next_middle, next_top, next_bottom, j, dataset, curr_elevation, temp_row, p);
      }
    }
    if (i == 0 || p.EleChange() < best_path.EleChange()) {
      best_path = p;
    }
    paths_.push_back(p);
  }
  ColorPath(best_path);
}

size_t PathImage::Width() const {
  return width_;
}
size_t PathImage::Height() const {
  return height_;
}
unsigned int PathImage::MaxColorValue() const {
  return kMaxColorValue;
}
const std::vector<Path>& PathImage::Paths() const {
  return paths_;
}
const std::vector<std::vector<Color> >& PathImage::GetPathImage() const {
  return path_image_;
}
void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << std::endl;
  ofs << Width() << " " << Height() << std::endl;
  ofs << MaxColorValue() << std::endl;
  for (size_t i = 0; i < Height(); i++) {
    for (size_t j = 0; j < Width(); j++) {
      ofs << path_image_[i][j].Red() << " " << path_image_[i][j].Green() << " " << path_image_[i][j].Blue() << " ";
    }
    ofs << std::endl;
  }
  ofs.close();
}