#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

int main() {
  std::string test =
      "/home/vagrant/src/mp-mountain-paths-Xenotion/example-data/ex_input_data/sym-pos-in.dat";
  ElevationDataset test1 = ElevationDataset(test, 4, 4);
  std::cout << test1.MaxEle() << std::endl;
  std::cout << test1.MinEle() << std::endl;
  std::cout << test1.Width() << std::endl;
  std::cout << test1.Height() << std::endl;
  for (int i = 0; i < (int)test1.Height(); i++) {
    for (int j = 0; j < (int)test1.Width(); j++) {
      std::cout << test1.DatumAt(i, j) << " ";
    }
    std::cout << std::endl;
  }
  GrayscaleImage test2 = GrayscaleImage(test1);
  PathImage test3 = PathImage(test2, test1);
  test2.ToPpm("/home/vagrant/src/mp-mountain-paths-Xenotion/GreyScale.ppm");
  test3.ToPpm("/home/vagrant/src/mp-mountain-paths-Xenotion/FullPath.ppm");
}