#include <iostream>

#include <cstring>

const int MAX_ROWS = 10;
const int MAX_COLS = 10;

class MatrixType {
  public: 
  MatrixType(); // constructor to initialize an empty matrix with 0 rows and 0 columns
  void SetSize(int rowsSize, int colSize); // function to set the number of rows and columns of a matrix
  void StoreItem(int item, int row, int col); // function to store an item in a specific row and column
  void Add(MatrixType otherOperand, MatrixType & result); // function to add two matrices
  void Sub(MatrixType otherOperand, MatrixType & result); // function to subtract two matrices
  void Mult(MatrixType otherOperand, MatrixType & result); // function to multiply two matrices
  void Print(); // function to print a matrix
  bool AddSubCompatible(MatrixType otherOperand); // function to check if two matrices are compatible for addition or subtraction
  bool MultCompatible(MatrixType otherOperand); // function to check if two matrices are compatible for multiplication

  private: 
  
  int values[MAX_ROWS][MAX_COLS]; // 2D array to store values of a matrix
  int numRows; // number of rows of a matrix
  int numCols; // number of columns of a matrix
};

MatrixType::MatrixType() {
  numRows = 0;
  numCols = 0;
  memset(values, 0, sizeof(values)); // initializing all values to 0
}

void MatrixType::SetSize(int rowsSize, int colSize) {
  numRows = rowsSize;
  numCols = colSize;
}

void MatrixType::StoreItem(int item, int row, int col) {
  values[row][col] = item;
}

void MatrixType::Add(MatrixType otherOperand, MatrixType & result) {
  if (!AddSubCompatible(otherOperand)) {
    std::cout << "Error: Matrices are not compatible for addition.\n";
    return;
  }
  result.SetSize(numRows, numCols);

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      result.values[i][j] = values[i][j] + otherOperand.values[i][j];
    }
  }
}

void MatrixType::Sub(MatrixType otherOperand, MatrixType & result) {
  if (!AddSubCompatible(otherOperand)) {
    std::cout << "Error: Matrices are not compatible for subtraction.\n";
    return;
  }
  result.SetSize(numRows, numCols);

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      result.values[i][j] = values[i][j] - otherOperand.values[i][j];
    }
  }
}

void MatrixType::Mult(MatrixType otherOperand, MatrixType & result) {
  if (!MultCompatible(otherOperand)) {
    std::cout << "Error: Matrices are not compatible for multiplication.\n";
    return;
  }
  result.SetSize(numRows, otherOperand.numCols);

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < otherOperand.numCols; j++) {
      int sum = 0;
      for (int k = 0; k < numCols; k++) {
        sum += values[i][k] * otherOperand.values[k][j];
      }
      result.values[i][j] = sum;
    }
  }
}

void MatrixType::Print() {
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      std::cout << values[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

bool MatrixType::AddSubCompatible(MatrixType otherOperand) {
  return (numRows == otherOperand.numRows && numCols == otherOperand.numCols);
}

bool MatrixType::MultCompatible(MatrixType otherOperand) {
  return (numCols == otherOperand.numRows);
}

int main() {
    
  MatrixType matrix1, matrix2, result;
  matrix1.SetSize(2, 3);
  matrix2.SetSize(3, 2);
  matrix1.StoreItem(1, 0, 0);
  matrix1.StoreItem(2, 0, 1);
  matrix1.StoreItem(3, 0, 2);
  matrix1.StoreItem(4, 1, 0);
  matrix1.StoreItem(5, 1, 1);
  matrix1.StoreItem(6, 1, 2);
  matrix2.StoreItem(1, 0, 0);
  matrix2.StoreItem(2, 0, 1);
  matrix2.StoreItem(3, 1, 0);
  matrix2.StoreItem(4, 1, 1);
  matrix2.StoreItem(5, 2, 0);
  matrix2.StoreItem(6, 2, 1);

  // test addition
  matrix1.Add(matrix2, result);
  result.Print();

  // test subtraction
  matrix1.Sub(matrix2, result);
  result.Print();

  // test multiplication
  matrix1.Mult(matrix2, result);
  result.Print();

  return 0;
}