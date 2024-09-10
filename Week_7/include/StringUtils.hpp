#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace StringUtils {
std::string ltrim(const std::string& str);
std::string rtrim(const std::string& str);
std::string trim(const std::string& str);

std::vector<std::string> split(const std::string& str, char delimiter);
};  // namespace StringUtils
