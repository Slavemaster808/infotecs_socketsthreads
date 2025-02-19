#include <libfuncs/funcs.hpp>

#include <algorithm>

namespace helper {
void strTransform(std::string& str) {
  std::sort(str.begin(), str.end(), std::greater<>());

  for (size_t i = 0; i < str.size();) {
    const unsigned int d = str[i] - '0';
    if (d % 2 == 0) {
      str.replace(i, 1, "KB");
      i += 2;
    } else {
      i++;
    }
  }
}

unsigned int strDigitSum(const std::string& str) {
  unsigned int sum = 0;
  for (const auto& c : str) {
    if (std::isdigit(c) != 0) {
      sum += c - '0';
    }
  }
  return sum;
}

bool checkDigit(const unsigned int sum) {
  return (sum > 2) && (sum % 32 == 0) ? true : false;
}
}  // namespace helper