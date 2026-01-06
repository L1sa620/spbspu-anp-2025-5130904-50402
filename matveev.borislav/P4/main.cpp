#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>

namespace matveev
{
  char* getLine(std::istream& in, size_t* len);
  char* rmLat(char* dest, const char* src);
  int hasRep(const char* str);
}

int main()
{
  size_t len = 0;
  char* str = matveev::getLine(std::cin, &len);
  if (str == nullptr) {
    std::cerr << "Error memory\n";
    return 1;
  }
  char* res = static_cast< char* >(std::malloc(len + 1));
  if (res == nullptr) {
    std::free(str);
    std::cerr << "Error memory\n";
    return 1;
  }
  matveev::rmLat(res, str);
  std::cout << res << "\n";
  std::cout << matveev::hasRep(str) << "\n";
  std::free(res);
  std::free(str);
  return 0;
}

char* matveev::getLine(std::istream& in, size_t* len)
{
  size_t cap = 16;
  size_t size = 0;
  char* buf = static_cast< char* >(std::malloc(cap));
  if (buf == nullptr) {
    return nullptr;
  }
  bool wasSkip = (in.flags() & std::ios_base::skipws);
  if (wasSkip) {
    in >> std::noskipws;
  }
  char c = '\0';
  while (in >> c && c != '\n') {
    if (size + 1 >= cap) {
      size_t newCap = cap * 2;
      char* newBuf = static_cast< char* >(std::realloc(buf, newCap));
      if (newBuf == nullptr) {
        std::free(buf);
        if (wasSkip) {
          in >> std::skipws;
        }
        return nullptr;
      }
      buf = newBuf;
      cap = newCap;
    }
    buf[size] = c;
    size++;
  }
  buf[size] = '\0';
  if (len != nullptr) {
    *len = size;
  }
  if (wasSkip) {
    in >> std::skipws;
  }
  return buf;
}

char* matveev::rmLat(char* dest, const char* src)
{
  size_t j = 0;
  for (size_t i = 0; src[i] != '\0'; ++i) {
    if (!std::isalpha(static_cast< unsigned char >(src[i]))) {
      dest[j] = src[i];
      j++;
    }
  }
  dest[j] = '\0';
  return dest;
}

int matveev::hasRep(const char* str)
{
  size_t len = std::strlen(str);
  for (size_t i = 0; i < len; ++i) {
    for (size_t j = i + 1; j < len; ++j) {
      if (str[i] == str[j]) {
        return 1;
      }
    }
  }
  return 0;
}
