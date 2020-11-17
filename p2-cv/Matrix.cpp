// Project UID af1f95f547e44c8ea88730dfb185559ds

#include <cassert>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
    assert((width>0)& (width<=MAX_MATRIX_WIDTH));
    assert((height>0)& (height<=MAX_MATRIX_WIDTH));
    mat->width = width;
    mat->height = height;
  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
    os<< Matrix_width(mat)<<" "<<Matrix_height(mat)<<std::endl;
    for (int i = 0;i<Matrix_height(mat);i++){
        for(int j = 0;j<Matrix_width(mat);j++){
            os<<(mat->data)[i*Matrix_height(mat)+j]<<" ";
        }
        os<<std::endl;
    }
  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
    return mat->width;
  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
    return mat->height;
  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
    int diff_ptr = ptr - mat->data;
    return diff_ptr/Matrix_width(mat);
  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
    int diff_ptr = ptr- mat->data;
    return diff_ptr % Matrix_width(mat);
  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
    int * ptr = (mat->data)+row*Matrix_width(mat)+column;
    return ptr;
  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
    const int * ptr = (mat->data)+row*Matrix_width(mat)+column;
    return ptr;
  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
    for (int i = 0;i<Matrix_height(mat);i++){
        for(int j = 0;j<Matrix_width(mat);j++){
            mat->data[i*Matrix_width(mat)+j] = value;
        }
  //assert(false); // TODO Replace with your implementation!
    }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
    
void Matrix_fill_border(Matrix* mat, int value) {
    for(int j = 0;j<Matrix_width(mat);j++){
        mat->data[j] = value;
        mat->data[(Matrix_height(mat)-1)*Matrix_width(mat)+j] = value;
    }
    for (int i = 0;i<Matrix_height(mat);i++){
        mat->data[i*Matrix_width(mat)] = value;
        mat->data[i*Matrix_width(mat)+Matrix_width(mat)-1] = value;}
//  assert(false); // TODO Replace with your implementation!
        
    }

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
    int max_value = *(mat->data);
    for (int i =0;i<Matrix_height(mat);i++){
        for (int j = 0;j<Matrix_width(mat);j++){
            if(max_value<mat->data[i*Matrix_width(mat)+j]){
                max_value =mat->data[i*Matrix_width(mat)+j];
            }
        }
    }
    return max_value;
  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
    int column_value = column_start;
    
    int min_value = *(mat->data+row*Matrix_width(mat)+column_start);
    for (int j =column_start+1;j<column_end;j++){
        if (min_value> *(mat->data+row*Matrix_width(mat)+j)){
            min_value =*(mat->data+row*Matrix_width(mat)+j);
            column_value = j;
        }
    }
    return column_value;

  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
    int column_value = column_start;
    
    int min_value = *(mat->data+row*Matrix_width(mat)+column_start);
    for (int j =column_start+1;j<column_end;j++){
        if (min_value> *(mat->data+row*Matrix_width(mat)+j)){
            min_value =*(mat->data+row*Matrix_width(mat)+j);
            column_value = j;
        }
    }
    return min_value;
    

  //assert(false); // TODO Replace with your implementation!
}
