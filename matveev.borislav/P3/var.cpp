#include <iostream>
#include <fstream>
#include <cstdlib>

namespace matveev {
  std::istream& rMatrix(std::istream& in, int* matrix, size_t rows, size_t cols);
  std::ostream& wMatrix(std::ostream& out, const int* matrix, size_t rows, size_t cols);
  int* allocMatrix(size_t rows, size_t cols);
  void rm(int* matrix);
  void spiral(int* matrix, size_t rows, size_t cols);
  size_t find(const int* matrix, size_t rows, size_t cols);
}

int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "Error ./lab num input output\n";
    return 1;
  }

  char* ePtr = nullptr;
  long num = std::strtol(argv[1], &ePtr, 10);
  if (*ePtr != '\0' || (num != 1 && num != 2)) {
    std::cerr << "Error first argument\n";
    return 1;
  }

  const char* in = argv[2];
  const char* out = argv[3];

  std::ifstream file(in);
  if (!file.is_open()) {
    std::cerr << "Error cannot open file\n";
    return 1;
  }

  size_t rows = 0;
  size_t cols = 0;
  if (!(file >> rows >> cols)) {
    std::cerr << "Error empty or invalid file\n";
    return 1;
  }

  if (rows == 0 || cols == 0) {
    std::ofstream oFile(out);
    return 0;
  }

  constexpr size_t maxSize = 10000;
  int fMatrix[maxSize] = {0};
  int* matrix = nullptr;

  if (num == 1) {
    if (rows * cols > maxSize) {
      std::cerr << "Error matrix too large for fixed array\n";
      return 1;
    }
    matrix = fMatrix;
  } else {
    matrix = matveev::allocMatrix(rows, cols);
    if (matrix == nullptr) {
      std::cerr << "Error memory allocation failed\n";
      return 1;
    }
  }

  if (!matveev::rMatrix(file, matrix, rows, cols)) {
    std::cerr << "Error not enough data\n";
    if (num == 2) {
      matveev::rm(matrix);
    }
    return 1;
  }

  matveev::spiral(matrix, rows, cols);
  matveev::find(matrix, rows, cols);

  std::ofstream oFile(out);
  if (!oFile.is_open()) {
    std::cerr << "Error cannot open output file\n";
    if (num == 2) {
      matveev::rm(matrix);
    }
    return 1;
  }

  matveev::wMatrix(oFile, matrix, rows, cols);

  if (num == 2) {
    matveev::rm(matrix);
  }

  return 0;
}

namespace matveev {

  std::istream& rMatrix(std::istream& in, int* matrix, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        if (!(in >> matrix[i * cols + j])) {
          return in;
        }
      }
    }
    return in;
  }

  std::ostream& wMatrix(std::ostream& out, const int* matrix, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows; ++i) {
      out << matrix[i * cols];
      for (size_t j = 1; j < cols; ++j) {
        out << " " << matrix[i * cols + j];
      }
      if (i < rows - 1) {
        out << "\n";
      }
    }
    return out;
  }

  int* allocMatrix(size_t rows, size_t cols)
  {
    return new(std::nothrow) int[rows * cols];
  }

  void rm(int* matrix)
  {
    delete[] matrix;
  }

  void spiral(int* matrix, size_t rows, size_t cols)
  {
    size_t upR = 0;
    size_t lC = 0;
    size_t dR = rows - 1;
    size_t rC = cols - 1;
    int cnt = 1;

    while (upR <= dR && lC <= rC) {
      for (size_t i = lC; i <= rC; ++i) {
        matrix[dR * cols + i] += cnt++;
      }
      if (dR == 0) {
        break;
      }
      dR--;

      if (lC <= rC) {
        for (size_t i = dR; i >= upR && i < rows; --i) {
          matrix[i * cols + rC] += cnt++;
          if (i == 0) {
            break;
          }
        }
        if (rC == 0) {
          break;
        }
        rC--;
      }

      if (upR <= dR) {
        for (size_t i = rC; i >= lC && i < cols; --i) {
          matrix[upR * cols + i] += cnt++;
          if (i == 0) {
            break;
          }
        }
        upR++;
      }

      if (lC <= rC) {
        for (size_t i = upR; i <= dR; ++i) {
          matrix[i * cols + lC] += cnt++;
        }
        lC++;
      }
    }
  }

  size_t find(const int* matrix, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }

    size_t maxLen = 0;
    size_t res = 0;

    for (size_t col = 0; col < cols; ++col) {
      size_t ser = 1;
      for (size_t row = 1; row < rows; ++row) {
        if (matrix[row * cols + col] == matrix[(row - 1) * cols + col]) {
          ser++;
        } else {
          if (ser > maxLen) {
            maxLen = ser;
            res = col;
          }
          ser = 1;
        }
      }
      if (ser > maxLen) {
        maxLen = ser;
        res = col;
      }
    }

    return res;
  }

}

