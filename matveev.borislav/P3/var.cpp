#include <iostream>
#include <fstream>

namespace matveev {
constexpr size_t max_size = 100;
void wMatrix(int** matrix, size_t rows, size_t cols, const char* filename);
int** allocMatrix(size_t rows, size_t cols);
void rm(int** matrix, size_t rows);
void spiral(int** matrix, size_t rows, size_t cols);
void wMatrixDin(int matrix[][max_size], size_t rows, size_t cols, const char* filename);
void spiralDin(int matrix[][max_size], size_t rows, size_t cols);
int find(int** matrix, size_t rows, size_t cols);
int findDin(int matrix[][100], size_t rows, size_t cols);
void processMatrix(size_t num, std::ifstream& file, size_t rows, size_t cols, const char* output);
void rMatrix(std::ifstream& file, int** matrix, size_t rows, size_t cols);
void rMatrixDin(std::ifstream& file, int matrix[][max_size], size_t rows, size_t cols);
void fillMatrix(std::istream& input, int** matrix, size_t rows, size_t cols);
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Error ./lab num input output\n";
    return 1;
  }

  if (argv[1][0] < '1' || argv[1][0] > '2' || argv[1][1] != '\0') {
    std::cerr << "Error first argument\n";
    return 1;
  }

  int num = argv[1][0] - '0';
  const char* input = argv[2];
  const char* output = argv[3];

  std::ifstream file(input);
  if (!file.is_open()) {
    std::cerr << "Error cannot open file\n";
    return 1;
  }

  size_t trows = 0, tcols = 0;
  if (!(file >> trows >> tcols)) {
    std::cerr << "Error empty or invalid file\n";
    return 1;
  }

  if (trows == 0 && tcols == 0) {
    std::ofstream out(output);
    return 0;
  }

  if (trows <= 0 || tcols <= 0) {
    std::cerr << "Error invalid dimensions\n";
    return 1;
  }

  matveev::processMatrix(num, file, trows, tcols, output);

  return 0;
}

namespace matveev {

void rMatrix(std::ifstream& file, int** matrix, size_t rows, size_t cols) {
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (!(file >> matrix[i][j])) {
        std::cerr << "Error not enough data\n";
        matveev::rm(matrix, rows);
        exit(1);
      }
    }
  }
}

void wMatrix(int** matrix, size_t rows, size_t cols, const char* filename) {
  std::ofstream file(filename);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (j > 0) {
        file << " ";
      }
      file << matrix[i][j];
    }
    file << "\n";
  }
}

int** allocMatrix(size_t rows, size_t cols) {
  int** matrix = new int*[rows];
  try {
    for (size_t i = 0; i < rows; ++i) {
      matrix[i] = new int[cols];
    }
  } catch (...) {
    for (size_t i = 0; i < rows; ++i) {
      if (matrix[i] != nullptr) {
        delete[] matrix[i];
      }
    }
    delete[] matrix;
    throw;
  }
  return matrix;
}

void rm(int** matrix, size_t rows) {
  for (size_t i = 0; i < rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

void spiral(int** matrix, size_t rows, size_t cols) {
  int up_r = 0, left_c = 0;
  int down_r = rows - 1, right_c = cols - 1;
  int counter = 1;

  while (up_r <= down_r && left_c <= right_c) {
    for (int i = left_c; i <= right_c; ++i) {
      matrix[down_r][i] += counter++;
    }
    down_r--;

    if (left_c <= right_c) {
      for (int i = down_r; i >= up_r; --i) {
        matrix[i][right_c] += counter++;
      }
      right_c--;
    }

    if (up_r <= down_r) {
      for (int i = right_c; i >= left_c; --i) {
        matrix[up_r][i] += counter++;
      }
      up_r++;
    }

    if (left_c <= right_c) {
      for (int i = up_r; i <= down_r; ++i) {
        matrix[i][left_c] += counter++;
      }
      left_c++;
    }
  }
}

void rMatrixDin(std::ifstream& file, int matrix[][max_size], size_t rows, size_t cols) {
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (!(file >> matrix[i][j])) {
        std::cerr << "Error not enough data\n";
        exit(1);
      }
    }
  }
}

void wMatrixDin(int matrix[][max_size], size_t rows, size_t cols, const char* filename) {
  std::ofstream file(filename);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (j > 0) {
        file << " ";
      }
      file << matrix[i][j];
    }
    file << "\n";
  }
}

void spiralDin(int matrix[][max_size], size_t rows, size_t cols) {
  int up_r = 0, left_c = 0;
  int down_r = rows - 1, right_c = cols - 1;
  int counter = 1;

  while (up_r <= down_r && left_c <= right_c) {
    for (int i = left_c; i <= right_c; ++i) {
      matrix[down_r][i] += counter++;
    }
    down_r--;

    if (left_c <= right_c) {
      for (int i = down_r; i >= up_r; --i) {
        matrix[i][right_c] += counter++;
      }
      right_c--;
    }

    if (up_r <= down_r) {
      for (int i = right_c; i >= left_c; --i) {
        matrix[up_r][i] += counter++;
      }
      up_r++;
    }

    if (left_c <= right_c) {
      for (int i = up_r; i <= down_r; ++i) {
        matrix[i][left_c] += counter++;
      }
      left_c++;
    }
  }
}

int find(int** matrix, size_t rows, size_t cols) {
  if (rows == 0 || cols == 0) {
    return 0;
  }

  int max = 0;
  int result = 0;

  for (size_t col = 0; col < cols; ++col) {
    int series = 1;
    for (size_t row = 1; row < rows; ++row) {
      if (matrix[row][col] == matrix[row - 1][col]) {
        series++;
      } else {
        if (series > max) {
          max = series;
          result = col;
        }
        series = 1;
      }
    }
    if (series > max) {
      max = series;
      result = col;
    }
  }

  return result;
}

int findDin(int matrix[][100], size_t rows, size_t cols) {
  if (rows == 0 || cols == 0) {
    return 0;
  }

  int max = 0;
  int result = 0;

  for (size_t col = 0; col < cols; ++col) {
    int series = 1;
    for (size_t row = 1; row < rows; ++row) {
      if (matrix[row][col] == matrix[row - 1][col]) {
        series++;
      } else {
        if (series > max) {
          max = series;
          result = col;
        }
        series = 1;
      }
    }
    if (series > max) {
      max = series;
      result = col;
    }
  }

  return result;
}

void processMatrix(size_t num, std::ifstream& file, size_t rows, size_t cols, const char* output) {
  if (num == 1) {
    int matrix[max_size][max_size] = {0};
    matveev::rMatrixDin(file, matrix, rows, cols);
    matveev::spiralDin(matrix, rows, cols);
    matveev::findDin(matrix, rows, cols);
    matveev::wMatrixDin(matrix, rows, cols, output);
  } else if (num == 2) {
    int** matrix = matveev::allocMatrix(rows, cols);
    matveev::fillMatrix(file, matrix, rows, cols);
    matveev::spiral(matrix, rows, cols);
    matveev::find(matrix, rows, cols);
    matveev::wMatrix(matrix, rows, cols, output);
    matveev::rm(matrix, rows);
}

}

void fillMatrix(std::istream& input, int** matrix, size_t rows, size_t cols) {
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      input >> matrix[i][j];
    }
  }
}

}
