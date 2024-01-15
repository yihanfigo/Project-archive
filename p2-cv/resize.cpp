#include <iostream>
#include "processing.hpp"
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
  Image* img = new Image;
  if (argc !=4 && argc!=5) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
  }
  ifstream fin;
  fin.open(argv[1]);
  if (!fin.is_open()) {
    cout << "Error opening file: " << argv[1] << endl;
    return 1;
  }
  Image_init (img, fin);
  if (stoi(argv[3]) <= 0 || stoi(argv[3]) > Image_width(img)) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
  }
  if (argc == 5) {
    if (stoi(argv[4]) <= 0 || stoi(argv[4]) > Image_height(img)) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    }
  }

  if (argc == 4) {
    seam_carve(img, stoi(argv[3]), Image_height(img));
  } else if (argc ==5) {
    seam_carve(img, stoi(argv[3]), stoi(argv[4]));
  }
  ofstream fout;
  fout.open(argv[2]);
  if (!fout.is_open()) {
    cout << "Error opening file: " << argv[2] << endl;
    return 1;
  }
  Image_print(img, fout);
  delete img;
}