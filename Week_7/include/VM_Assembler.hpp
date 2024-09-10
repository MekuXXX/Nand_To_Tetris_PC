#include <string>

#include "Parser.hpp"

enum class ARITHMETIC_TYPES { ADD, SUBTRACT };

class VM_Assembler {
 public:
  std::string& arithmetic(ARITHMETIC_TYPES type);
  std::string& push(const SEGMENT_TYPE segment, long unsigned int index);
  std::string& pop(const SEGMENT_TYPE segment, long unsigned int index);
};
