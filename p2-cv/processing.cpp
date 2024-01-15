#include <cassert>
#include "processing.hpp"
#include "Matrix.hpp"
#include <iostream> 
#include <fstream> 
#include <cstdlib> 
#include <sstream>
#include <cassert>
#include <string>

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
/*void compute_energy_matrix(const Image* img, Matrix* energy) {
    energy ->width = img ->width;
    energy ->height =img ->height;
    auto get_pixel_or_black = [&img](int row, int col) -> Pixel { 
    if (row < 0 || row >= img->height || col < 0 || col >= img->width) {
      return {0, 0, 0};
    }
    return Image_get_pixel(img, row, col);
  };

    int max_energy = 0;

    for (int row = 1; row < img->height-1; ++row) {
        for (int col = 1; col < img->width-1; ++col) {
            Pixel N = get_pixel_or_black(row - 1, col);  
            Pixel S = get_pixel_or_black(row + 1, col);  
            Pixel W = get_pixel_or_black(row, col - 1);  
            Pixel E = get_pixel_or_black(row, col + 1);  

            int energy_val = squared_difference(N, S) + squared_difference(W, E);
       if (energy_val > max_energy) {
                max_energy = energy_val;
            }

            energy->data[row * img->width + col] = energy_val;
        }
    }
    for (int row = 0; row < img->height; ++row) {
        energy->data[row * img->width] = max_energy;
        energy->data[row * img->width + img->width - 1] = max_energy;
    }
    for (int col = 0; col < img->width; ++col) {
        energy->data[col] = max_energy;
        energy->data[(img->height - 1) * img->width + col] = max_energy;
    }


}*/


// void compute_energy_matrix(const Image* img, Matrix* energy) {
//     energy ->width = Image_width(img);
//     energy ->height =Image_height(img);
//     int max_energy = 0;

//     for (int row = 1; row < img->height-1; ++row) {
//         for (int col = 1; col < img->width-1; ++col) {
//             Pixel N = Image_get_pixel(img, row - 1, col);  
//             Pixel S = Image_get_pixel(img, row + 1, col);  
//             Pixel W = Image_get_pixel(img, row, col - 1);  
//             Pixel E = Image_get_pixel(img, row, col + 1);  

//             int energy_val = squared_difference(N, S) + squared_difference(W, E);
//        if (energy_val > max_energy) {
//                 max_energy = energy_val;
//             }

//             energy->data[row * img->width + col] = energy_val;
//         }
//     }
//     for (int row = 0; row < img->height; ++row) {
//         energy->data[row * img->width] = max_energy;
//         energy->data[row * img->width + img->width - 1] = max_energy;
//     }
//     for (int col = 0; col < img->width; ++col) {
//         energy->data[col] = max_energy;
//         energy->data[(img->height - 1) * img->width + col] = max_energy;
//     }


// }


void compute_energy_matrix(const Image* img, Matrix* energy) {
    Matrix_init(energy, Image_width(img), Image_height(img));
    int max_energy = 0;

    int imgWidth = Image_width(img);
    int imgHeight = Image_height(img);

    for (int row = 1; row < imgHeight - 1; ++row) {
        for (int col = 1; col < imgWidth - 1; ++col) {
            Pixel N = Image_get_pixel(img, row - 1, col);  
            Pixel S = Image_get_pixel(img, row + 1, col);  
            Pixel W = Image_get_pixel(img, row, col - 1);  
            Pixel E = Image_get_pixel(img, row, col + 1);  

            int energy_val = squared_difference(N, S) + squared_difference(W, E);
            if (energy_val > max_energy) {
                max_energy = energy_val;
            }

            *Matrix_at(energy, row, col) = energy_val;
        }
    }

    for (int row = 0; row < imgHeight; ++row) {
        *Matrix_at(energy, row, 0) = max_energy;
        *Matrix_at(energy, row, imgWidth - 1) = max_energy;
    }

    for (int col = 0; col < imgWidth; ++col) {
        *Matrix_at(energy, 0, col) = max_energy;
        *Matrix_at(energy, imgHeight - 1, col) = max_energy;
    }
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.



void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
    Matrix_init(cost, Matrix_width(energy), Matrix_height(energy));
    for (int i = 0; i < Matrix_width(energy); i++) {
        *Matrix_at(cost, 0, i) = *Matrix_at(energy, 0, i);
    }
    for (int r = 1; r < Matrix_height(energy); r++) {
        for (int c = 0; c < Matrix_width(energy); c++) {
            int upperMiddle = *Matrix_at(cost, r - 1, c);
            
            int upperLeft = (c > 0) 
                            ? *Matrix_at(cost, r - 1, c - 1)
                            : upperMiddle;

            int upperRight = (c < Matrix_width(energy) - 1) 
                             ? *Matrix_at(cost, r - 1, c + 1)
                             : upperMiddle;

            int minUpper = upperMiddle;
            if (upperLeft < minUpper) {
                minUpper = upperLeft;
            }
            if (upperRight < minUpper) {
                minUpper = upperRight;
            }
            *Matrix_at(cost, r, c) = *Matrix_at(energy, r, c) + minUpper;
        }
    }
}



// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
    int height = Matrix_height(cost);
    int width = Matrix_width(cost);
    seam[height - 1] = Matrix_column_of_min_value_in_row(cost, height - 1, 0, width);
     for (int r = height - 2; r >= 0; --r) {
        int c = seam[r + 1]; 
        int start, end;
        if (c == 0) {
            start = c;
            end = c + 2;
        } else if (c == width - 1) {
            start = c - 1;
            end = c + 1;
        } else {
            start = c - 1;
            end = c + 2;
        }
        seam[r] = Matrix_column_of_min_value_in_row(cost, r, start, end);
    }
    

}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel 
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.


// void remove_vertical_seam(Image *img, const int seam[]) {
//     // Allocate memory for the auxiliary image with width smaller by 1
//     Image *aux = new Image;
//     aux->width = img->width - 1;
//     aux->height = img->height;

//     // Allocate memory for the red, green, and blue channels
//     aux->red_channel.width = aux->width;
//     aux->red_channel.height = aux->height;
//     aux->green_channel.width = aux->width;
//     aux->green_channel.height = aux->height;
//     aux->blue_channel.width = aux->width;
//     aux->blue_channel.height = aux->height;

//     for (int row = 0; row < img->height; ++row) {
//         int seam_col = seam[row];
//         for (int col = 0, aux_col = 0; col < img->width; ++col) {
//             // If the column matches the seam for this row, skip copying
//             if (col == seam_col) continue;

//             // Calculate indices for the matrices
//             int orig_idx = row * img->width + col;
//             int aux_idx = row * aux->width + aux_col;

//             // Copy red, green, and blue channels
//             aux->red_channel.data[aux_idx] = img->red_channel.data[orig_idx];
//             aux->green_channel.data[aux_idx] = img->green_channel.data[orig_idx];
//             aux->blue_channel.data[aux_idx] = img->blue_channel.data[orig_idx];

//             // Increment the auxiliary column counter
//             aux_col++;
//         }
//     }

//     // Update the original image with the auxiliary image's data
//     img->width = aux->width;
//     img->height = aux->height; // though height remains unchanged, added for clarity
//     img->red_channel = aux->red_channel;
//     img->green_channel = aux->green_channel;
//     img->blue_channel = aux->blue_channel;

//     // Free the dynamically allocated memory for the auxiliary image
//     delete aux;
// }
void remove_vertical_seam(Image* img, const int seam[]) {
    Image aux;
    Image_init(&aux, Image_width(img) - 1, Image_height(img));
    for (int row = 0; row < Image_height(img); ++row) {
        int seam_col = seam[row];
        for (int col = 0, aux_col = 0; col < Image_width(img); ++col) {
            if (col == seam_col) continue;
            Pixel current_pixel = Image_get_pixel(img, row, col);
            Image_set_pixel(&aux, row, aux_col, current_pixel);
            aux_col++;
        }
    }

    (*img) = aux;
}



// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
// NOTE:     The size of an array local variable must be a compile-time
//           constant. You can use MAX_MATRIX_HEIGHT as the constant,
//           since an image's height can be no larger than that.

void seam_carve_width(Image *img, int newWidth) {
    while (Image_width(img) > newWidth && newWidth > 0) {
        Matrix energy;
        Matrix_init(&energy, Image_width(img), Image_height(img));
        compute_energy_matrix(img, &energy);
        
        Matrix cost;
        Matrix_init(&cost, Image_width(img), Image_height(img));
        compute_vertical_cost_matrix(&energy, &cost);

        int seam[MAX_MATRIX_HEIGHT];
        find_minimal_vertical_seam(&cost, seam);
        remove_vertical_seam(img, seam);
    }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
    rotate_left(img);
    seam_carve_width(img, newHeight);
    rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
    while (Image_width(img) > newWidth) {
        seam_carve_width(img, newWidth); 
    }
    while (Image_height(img) > newHeight) {
        seam_carve_height(img, newHeight);
    }
    
  }
