#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "StringUtils.hpp"

enum class VM_COMMAND_TYPES {
  C_ARITHMETIC,
  C_PUSH,
  C_POP,
};

enum class SEGMENT_TYPES {
  LOCAL,
  ARGUMENT,
  THIS,
  THAT,
  CONSTANT,
  STATIC,
  TEMP,
  POINTER
};

enum class ARITHMETIC_TYPES {
  ADDITION,
  SUBTRACTION,
  NEGATION,
  EQUALITY,
  GREATER_THAN,
  LESS_THAN,
  AND,
  OR,
  NOT
};

enum class ARGUMENT_TYPES { FIRST, SECOND };

class Parser {
 public:
  Parser() = delete;
  Parser(const std::string& path);

  bool hasMoreLines() const;
  std::string currentLine() const;
  void advance();
  std::string arg1();
  std::string arg2();
  VM_COMMAND_TYPES commandType() const;
  SEGMENT_TYPES segmentType() const;
  ARITHMETIC_TYPES arithmeticType() const;

 private:
  std::ifstream file;
  std::string line;
  std::vector<std::string> tokens;

  static const std::unordered_map<std::string, ARITHMETIC_TYPES>
      arithmeticTable;
  static const std::unordered_map<std::string, SEGMENT_TYPES> segmentTable;

  void cleanLine();
  std::string handleArgs(ARGUMENT_TYPES index);
};
