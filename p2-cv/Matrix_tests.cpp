#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
  Matrix *mat2 = new Matrix;
  Matrix_init(mat2, 1, 1);
  Matrix_fill(mat2, value);
  ASSERT_EQUAL(*Matrix_at(mat2, 0, 0), value);
  delete mat2;
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.
TEST(test_matrix_init) {
  Matrix *mat = new Matrix;
  Matrix_init (mat, 1,1);
  ASSERT_EQUAL(Matrix_width(mat), 1);
  ASSERT_EQUAL(Matrix_height(mat), 1);
  Matrix_init (mat, 500,500);
  ASSERT_EQUAL(Matrix_width(mat), 500);
  ASSERT_EQUAL(Matrix_height(mat), 500);
  delete mat;
}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
  delete mat;
}

TEST(test_matrix_width) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 5);
  ASSERT_EQUAL(Matrix_width(mat), 3);
  delete mat;
}

TEST(test_matrix_height) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 5);
  ASSERT_EQUAL(Matrix_height(mat), 5);
  delete mat;
}

TEST(test_matrix_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 5);
  int * ptr = Matrix_at (mat, 4, 3);
  int * first = Matrix_at(mat, 0, 0);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 4);
  ASSERT_EQUAL(Matrix_row(mat, first), 0);
  delete mat;
}

TEST(test_matrix_column) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 5);
  int * ptr = Matrix_at(mat, 4, 3);
  int * first = Matrix_at(mat, 0, 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 3);
  ASSERT_EQUAL(Matrix_column(mat, first), 0);
  delete mat;
}

TEST(test_matrix_at) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 5);
  int * ptr = Matrix_at(mat, 0, 0);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 0);
  int *last = Matrix_at(mat, 4, 3);
  ASSERT_EQUAL(Matrix_row(mat, last), 4);
  ASSERT_EQUAL(Matrix_column(mat, last), 3);
  delete mat;
}

TEST (test_matrix_fill_boarder) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 5);
  int value = 42;
  Matrix_fill_border(mat, value);
  for (int i = 0; i < Matrix_height(mat); i++) {
    for (int j = 0; j < Matrix_width(mat); j++) {
      if (i == 0 || i == Matrix_height(mat) - 1 || j == 0 || j == Matrix_width(mat) - 1) {
        ASSERT_EQUAL(*Matrix_at(mat, i,j),value);
      } else {
        ASSERT_NOT_EQUAL(*Matrix_at(mat, i,j),value);
      }
    }
  }
  delete mat;
  Matrix *mat2 = new Matrix;
  Matrix_init(mat2, 1, 1);
  Matrix_fill_border(mat2, value);
  ASSERT_EQUAL(*Matrix_at(mat2, 0, 0), value);
  delete mat2;
}

TEST (test_matrix_max) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 5);
  *Matrix_at(mat, 0, 1) = 41;
  *Matrix_at(mat, 1, 1) = 40;
  *Matrix_at(mat, 3, 3) = 54;
  ASSERT_EQUAL(Matrix_max(mat),54);

  Matrix_init(mat, 1, 1);
  *Matrix_at(mat, 0,0) = 0;
  ASSERT_EQUAL(Matrix_max(mat),0);

  delete mat;
}

TEST(test_matrix_column_of_min_value_in_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  *Matrix_at(mat, 0, 0) = 23;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 0), 0);
  
  Matrix_init(mat, 4, 5);
  *Matrix_at(mat, 1, 0) = 23;
  *Matrix_at(mat, 1, 1) = 13;
  *Matrix_at(mat, 1, 2) = 13;
  *Matrix_at(mat, 1, 3) = 32;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 3), 1);
  delete mat;
}

TEST(test_matrix_min_value_in_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  *Matrix_at(mat, 0, 0) = 23;
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 0), 23);


  Matrix_init(mat, 4, 5);
  *Matrix_at(mat, 1, 0) = 23;
  *Matrix_at(mat, 1, 1) = 13;
  *Matrix_at(mat, 1, 2) = 13;
  *Matrix_at(mat, 1, 3) = 32;
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 3), 13);
  delete mat;
}



// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
