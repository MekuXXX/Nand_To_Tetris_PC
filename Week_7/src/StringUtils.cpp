#include "StringUtils.hpp"

namespace StringUtils {
std::string ltrim(const std::string& str) {
  std::string result = str;

  result.erase(result.begin(),
               std::find_if(result.begin(), result.end(),
                            [](unsigned char c) { return !std::isspace(c); }));

  return result;
}

std::string rtrim(const std::string& str) {
  std::string result = str;

  result.erase(std::find_if(result.rbegin(), result.rend(),
                            [](unsigned char c) { return !std::isspace(c); })
                   .base(),
               result.end());

  return result;
}

std::string trim(const std::string& str) { return ltrim(rtrim(str)); }

std::vector<std::string> split(const std::string& str, char delimiter) {
  std::vector<std::string> result;
  std::string token;
  std::istringstream iss(str);

  while (std::getline(iss, token, delimiter)) {
    result.push_back(token);
  }

  return result;
}
}  // namespace StringUtils
