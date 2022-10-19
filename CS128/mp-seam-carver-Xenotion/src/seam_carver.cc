#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here
const ImagePPM& SeamCarver::GetImage() const { return image_; }

int SeamCarver::GetHeight() const { return height_; }

int SeamCarver::GetWidth() const { return width_; }

void SeamCarver::RowIsZero(int& col, int&row, int& leftr, int& leftg, int& leftb, int& rightr, int& rightg, int& rightb) const {
    if (col == 0) {
      leftr = image_.GetPixel(row, GetWidth() - 1).GetRed();
      leftg = image_.GetPixel(row, GetWidth() - 1).GetGreen();
      leftb = image_.GetPixel(row, GetWidth() - 1).GetBlue();
      rightr = image_.GetPixel(row, col + 1).GetRed();
      rightg = image_.GetPixel(row, col + 1).GetGreen();
      rightb = image_.GetPixel(row, col + 1).GetBlue();

    } else if (col == GetWidth() - 1) {
      leftr = image_.GetPixel(row, col - 1).GetRed();
      leftg = image_.GetPixel(row, col - 1).GetGreen();
      leftb = image_.GetPixel(row, col - 1).GetBlue();
      rightr = image_.GetPixel(row, 0).GetRed();
      rightg = image_.GetPixel(row, 0).GetGreen();
      rightb = image_.GetPixel(row, 0).GetBlue();

    } else {
      leftr = image_.GetPixel(row, col - 1).GetRed();
      leftg = image_.GetPixel(row, col - 1).GetGreen();
      leftb = image_.GetPixel(row, col - 1).GetBlue();
      rightr = image_.GetPixel(row, col + 1).GetRed();
      rightg = image_.GetPixel(row, col + 1).GetGreen();
      rightb = image_.GetPixel(row, col + 1).GetBlue();
    }
}

void SeamCarver::RowIsLast(int& col, int&row, int& leftr, int& leftg, int& leftb, int& rightr, int& rightg, int& rightb) const {
  if (col == 0) {
      leftr = image_.GetPixel(row, GetWidth() - 1).GetRed();
      leftg = image_.GetPixel(row, GetWidth() - 1).GetGreen();
      leftb = image_.GetPixel(row, GetWidth() - 1).GetBlue();
      rightr = image_.GetPixel(row, col + 1).GetRed();
      rightg = image_.GetPixel(row, col + 1).GetGreen();
      rightb = image_.GetPixel(row, col + 1).GetBlue();

    } else if (col == GetWidth() - 1) {
      leftr = image_.GetPixel(row, col - 1).GetRed();
      leftg = image_.GetPixel(row, col - 1).GetGreen();
      leftb = image_.GetPixel(row, col - 1).GetBlue();
      rightr = image_.GetPixel(row, 0).GetRed();
      rightg = image_.GetPixel(row, 0).GetGreen();
      rightb = image_.GetPixel(row, 0).GetBlue();

    } else {
      leftr = image_.GetPixel(row, col - 1).GetRed();
      leftg = image_.GetPixel(row, col - 1).GetGreen();
      leftb = image_.GetPixel(row, col - 1).GetBlue();
      rightr = image_.GetPixel(row, col + 1).GetRed();
      rightg = image_.GetPixel(row, col + 1).GetGreen();
      rightb = image_.GetPixel(row, col + 1).GetBlue();
    }
}

void SeamCarver::RowIsMiddle(int& col, int&row, int& leftr, int& leftg, int& leftb, int& rightr, int& rightg, int& rightb) const {
  if (col == 0) {
      leftr = image_.GetPixel(row, GetWidth() - 1).GetRed();
      leftg = image_.GetPixel(row, GetWidth() - 1).GetGreen();
      leftb = image_.GetPixel(row, GetWidth() - 1).GetBlue();
      rightr = image_.GetPixel(row, col + 1).GetRed();
      rightg = image_.GetPixel(row, col + 1).GetGreen();
      rightb = image_.GetPixel(row, col + 1).GetBlue();

    } else if (col == GetWidth() - 1) {
      leftr = image_.GetPixel(row, col - 1).GetRed();
      leftg = image_.GetPixel(row, col - 1).GetGreen();
      leftb = image_.GetPixel(row, col - 1).GetBlue();
      rightr = image_.GetPixel(row, 0).GetRed();
      rightg = image_.GetPixel(row, 0).GetGreen();
      rightb = image_.GetPixel(row, 0).GetBlue();

    } else {
      leftr = image_.GetPixel(row, col - 1).GetRed();
      leftg = image_.GetPixel(row, col - 1).GetGreen();
      leftb = image_.GetPixel(row, col - 1).GetBlue();
      rightr = image_.GetPixel(row, col + 1).GetRed();
      rightg = image_.GetPixel(row, col + 1).GetGreen();
      rightb = image_.GetPixel(row, col + 1).GetBlue();
    }
}

int SeamCarver::GetEnergy(int row, int col) const {
  int leftr = 0, leftg = 0, leftb = 0, rightr = 0, rightg = 0, rightb = 0, topr = 0, topg = 0, topb = 0, bottomr = 0, bottomg = 0, bottomb = 0, energy = 0;

  if (row == 0) {
    topr = image_.GetPixel(GetHeight() - 1, col).GetRed();
    topg = image_.GetPixel(GetHeight() - 1, col).GetGreen();
    topb = image_.GetPixel(GetHeight() - 1, col).GetBlue();
    bottomr = image_.GetPixel(row + 1, col).GetRed();
    bottomg = image_.GetPixel(row + 1, col).GetGreen();
    bottomb = image_.GetPixel(row + 1, col).GetBlue();

    RowIsZero(col, row, leftr, leftg, leftb, rightr, rightg, rightb);

  } else if (row == GetHeight() - 1) {
    topr = image_.GetPixel(row - 1, col).GetRed();
    topg = image_.GetPixel(row - 1, col).GetGreen();
    topb = image_.GetPixel(row - 1, col).GetBlue();
    bottomr = image_.GetPixel(0, col).GetRed();
    bottomg = image_.GetPixel(0, col).GetGreen();
    bottomb = image_.GetPixel(0, col).GetBlue();

    RowIsLast(col, row, leftr, leftg, leftb, rightr, rightg, rightb);
    
  } else {
    topr = image_.GetPixel(row - 1, col).GetRed();
    topg = image_.GetPixel(row - 1, col).GetGreen();
    topb = image_.GetPixel(row - 1, col).GetBlue();
    bottomr = image_.GetPixel(row + 1, col).GetRed();
    bottomg = image_.GetPixel(row + 1, col).GetGreen();
    bottomb = image_.GetPixel(row + 1, col).GetBlue();

    RowIsMiddle(col, row, leftr, leftg, leftb, rightr, rightg, rightb);
  }

  energy = (leftr - rightr) * (leftr - rightr) + (leftg - rightg) * (leftg - rightg) + (leftb - rightb) * (leftb - rightb) + (topr - bottomr) * (topr - bottomr) + (topg - bottomg) * (topg - bottomg) + (topb - bottomb) * (topb - bottomb);
  return energy;
}

void SeamCarver::HelperHorizontal(int* seam, int& min_index, int** arr) const {
  for (int i = 0; i < GetWidth() - 1; i++) {
    if (min_index == 0) {
      if (arr[min_index][i + 1] == arr[min_index + 1][i + 1]) {
        seam[i + 1] = min_index;
      } else if (arr[min_index][i + 1] < arr[min_index + 1][i + 1]) {
        seam[i + 1] = min_index;
      } else {
        seam[i + 1] = min_index + 1; min_index++;
      }
    } else if (min_index == GetHeight() - 1) {
      if (arr[min_index][i + 1] == arr[min_index - 1][i + 1]) {
        seam[i + 1] = min_index;
      } else if (arr[min_index][i + 1] < arr[min_index - 1][i + 1]) {
        seam[i + 1] = min_index;
      } else {
        seam[i + 1] = min_index - 1; min_index--;
      }
    } else {
      if (arr[min_index][i + 1] == arr[min_index - 1][i + 1] && arr[min_index][i + 1] == arr[min_index + 1][i + 1]) {
        seam[i + 1] = min_index;
      } else if (arr[min_index][i + 1] == arr[min_index - 1][i + 1] && arr[min_index][i + 1] < arr[min_index + 1][i + 1]) {
        seam[i + 1] = min_index;
      } else if (arr[min_index][i + 1] == arr[min_index + 1][i + 1] && arr[min_index][i + 1] < arr[min_index - 1][i + 1]) {
        seam[i + 1] = min_index;
      } else if (arr[min_index - 1][i + 1] == arr[min_index + 1][i + 1] && arr[min_index - 1][i + 1] < arr[min_index][i + 1]) {
        seam[i + 1] = min_index - 1; min_index = min_index - 1;
      } else if (arr[min_index][i + 1] < arr[min_index - 1][i + 1] && arr[min_index][i + 1] < arr[min_index + 1][i + 1]) {
        seam[i + 1] = min_index;
      } else if (arr[min_index - 1][i + 1] < arr[min_index][i + 1] && arr[min_index - 1][i + 1] < arr[min_index + 1][i + 1]) {
        seam[i + 1] = min_index - 1; min_index = min_index - 1;
      } else {
        seam[i + 1] = min_index + 1; min_index = min_index + 1;
      }
    }
  }
}

int* SeamCarver::GetHorizontalSeam() const {
  int** arr = new int*[GetHeight()];
  for (int i = 0; i < GetHeight(); i++) {
    arr[i] = new int[GetWidth()];
  }
  for (int i = 0; i < GetHeight(); i++) {
    arr[i][GetWidth() - 1] = GetEnergy(i, GetWidth() - 1);
  }
  for (int j = GetWidth() - 2; j >= 0; j--) {
    for (int i = 0; i < GetHeight(); i++) {
      if (i == 0) {
        arr[i][j] = GetEnergy(i, j) + std::min(arr[i][j + 1], arr[i + 1][j + 1]);
      } else if (i == GetHeight() - 1) {
        arr[i][j] = GetEnergy(i, j) + std::min(arr[i - 1][j + 1], arr[i][j + 1]);
      } else {
        arr[i][j] = GetEnergy(i, j) + std::min(arr[i - 1][j + 1], std::min(arr[i][j + 1], arr[i + 1][j + 1]));
      }
    }
  }
  int* seam = new int[GetWidth()];
  int min = arr[0][0];
  int min_index = 0;
  for (int i = 1; i < GetHeight(); i++) {
    if (arr[i][0] < min) {
      min = arr[i][0];
      min_index = i;
    }
  }
  seam[0] = min_index;
  HelperHorizontal(seam, min_index, arr);
  for (int i = 0; i < GetHeight(); i++) {
    delete[] arr[i];
  }
  delete[] arr;
  arr = nullptr;
  return seam;
}

void SeamCarver::HelperVertical(int* seam, int& minindex, int** arr) const {
  for (int i = 0; i < GetHeight() - 1; i++) {
    if (minindex == 0) {
      if (arr[i + 1][minindex] == arr[i + 1][minindex + 1]) {
        seam[i + 1] = minindex;
      } else if (arr[i + 1][minindex] < arr[i + 1][minindex + 1]) {
        seam[i + 1] = minindex;
      } else {
        seam[i + 1] = minindex + 1; minindex = minindex + 1;
      }
    } else if (minindex == GetWidth() - 1) {
      if (arr[i + 1][minindex] == arr[i + 1][minindex - 1]) {
        seam[i + 1] = minindex;
      } else if (arr[i + 1][minindex] < arr[i + 1][minindex - 1]) {
        seam[i + 1] = minindex;
      } else {
        seam[i + 1] = minindex - 1; minindex = minindex - 1;
      }
    } else {
      if (arr[i + 1][minindex] == arr[i + 1][minindex - 1] && arr[i + 1][minindex] == arr[i + 1][minindex + 1]) {
        seam[i + 1] = minindex;
      } else if (arr[i + 1][minindex] == arr[i + 1][minindex - 1] && arr[i + 1][minindex] < arr[i + 1][minindex + 1]) {
        seam[i + 1] = minindex;
      } else if (arr[i + 1][minindex] == arr[i + 1][minindex + 1] && arr[i + 1][minindex] < arr[i + 1][minindex - 1]) {
        seam[i + 1] = minindex;
      } else if (arr[i + 1][minindex - 1] == arr[i + 1][minindex + 1] && arr[i + 1][minindex - 1] < arr[i + 1][minindex]) {
        seam[i + 1] = minindex - 1; minindex = minindex - 1;
      } else if (arr[i + 1][minindex] < arr[i + 1][minindex - 1] && arr[i + 1][minindex] < arr[i + 1][minindex + 1]) {
        seam[i + 1] = minindex;
      } else if (arr[i + 1][minindex - 1] < arr[i + 1][minindex] && arr[i + 1][minindex - 1] < arr[i + 1][minindex + 1]) {
        seam[i + 1] = minindex - 1; minindex = minindex - 1;
      } else {
        seam[i + 1] = minindex + 1; minindex = minindex + 1;
      }
    }
  }
}

int* SeamCarver::GetVerticalSeam() const {
  int** arr = new int*[GetHeight()];
  for (int i = 0; i < GetHeight(); i++) {
    arr[i] = new int[GetWidth()];
  }
  for (int i = 0; i < GetWidth(); i++) {
    arr[GetHeight() - 1][i] = GetEnergy(GetHeight() - 1, i);
  }
  for (int i = GetHeight() - 2; i >= 0; i--) {
    for (int j = 0; j < GetWidth(); j++) {
      if (j == 0) {
        arr[i][j] = GetEnergy(i, j) + std::min(arr[i + 1][j], arr[i + 1][j + 1]);

      } else if (j == GetWidth() - 1) {
        arr[i][j] = GetEnergy(i, j) + std::min(arr[i + 1][j], arr[i + 1][j - 1]);

      } else {
        arr[i][j] = GetEnergy(i, j) + std::min(arr[i + 1][j], std::min(arr[i + 1][j - 1], arr[i + 1][j + 1]));
      }
    }
  }
  int* seam = new int[GetHeight()];
  int min = arr[0][0];
  int minindex = 0;
  for (int i = 1; i < GetWidth(); i++) {
    if (arr[0][i] < min) {
      min = arr[0][i];
      minindex = i;
    }
  }
  seam[0] = minindex;
  HelperVertical(seam, minindex, arr);
  for (int i = 0; i < GetHeight(); i++) {
    delete[] arr[i];
  }
  delete[] arr;
  arr = nullptr;
  return seam;
}

void SeamCarver::RemoveHorizontalSeam() {
  int* row_index = GetHorizontalSeam();
  image_.RemoveHorizontalSeam(row_index);

  height_ = GetHeight() - 1;
  
  delete[] row_index;
  row_index = nullptr;
}

void SeamCarver::RemoveVerticalSeam() { 
  int* col_index = GetVerticalSeam();
  image_.RemoveVerticalSeam(col_index);

  width_ = GetWidth() - 1;

  delete[] col_index;
  col_index = nullptr;
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
