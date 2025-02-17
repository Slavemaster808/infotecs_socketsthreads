#pragma once

#include <string>

namespace helper {
void strTransform(std::string& str);

unsigned int strDigitSum(const std::string& str);

bool checkDigit(const unsigned int sum);
}  // namespace helper