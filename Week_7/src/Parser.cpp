#include "Parser.hpp"

const std::unordered_map<std::string, SEGMENT_TYPES> Parser::segmentTable = {
    {"local", SEGMENT_TYPES::LOCAL},
    {"argument", SEGMENT_TYPES::ARGUMENT},
    {"this", SEGMENT_TYPES::THIS},
    {"that", SEGMENT_TYPES::THAT},
    {"constant", SEGMENT_TYPES::CONSTANT},
    {"static", SEGMENT_TYPES::STATIC},
    {"temp", SEGMENT_TYPES::TEMP},
    {"pointer", SEGMENT_TYPES::POINTER}};

const std::unordered_map<std::string, ARITHMETIC_TYPES>
    Parser::arithmeticTable = {{"add", ARITHMETIC_TYPES::ADDITION},
                               {"sub", ARITHMETIC_TYPES::SUBTRACTION},
                               {"neg", ARITHMETIC_TYPES::NEGATION},
                               {"eq", ARITHMETIC_TYPES::EQUALITY},
                               {"gt", ARITHMETIC_TYPES::GREATER_THAN},
                               {"lt", ARITHMETIC_TYPES::LESS_THAN},
                               {"and", ARITHMETIC_TYPES::AND},
                               {"or", ARITHMETIC_TYPES::OR},
                               {"not", ARITHMETIC_TYPES::NOT}};

Parser::Parser(const std::string& path) {
  this->file.open(path);

  if (!this->file.is_open()) {
    throw std::ios_base::failure("Failed to open the file");
  }

  this->advance();
}

bool Parser::hasMoreLines() const {
  return !this->file.eof() || !this->line.empty();
}

std::string Parser::currentLine() const { return this->line; }

void Parser::cleanLine() {
  size_t commentPos = this->line.find("//");

  if (commentPos != std::string::npos) {
    this->line.erase(commentPos);
  }

  this->line = StringUtils::trim(this->line);
}

void Parser::advance() {
  while (std::getline(this->file, this->line)) {
    this->cleanLine();
    if (!this->line.empty()) {
      this->tokens = StringUtils::split(this->line, ' ');
      return;
    }
  }
}

VM_COMMAND_TYPES Parser::commandType() const {
  std::string command = this->tokens.at(0);

  if (command == "push") {
    return VM_COMMAND_TYPES::C_PUSH;
  } else if (command == "pop") {
    return VM_COMMAND_TYPES::C_POP;
  } else if (Parser::arithmeticTable.find(command) !=
             Parser::arithmeticTable.end()) {
    return VM_COMMAND_TYPES::C_ARITHMETIC;
  } else {
    throw std::invalid_argument("Unknown command: " + command);
  }
}

std::string Parser::handleArgs(ARGUMENT_TYPES index) {
  VM_COMMAND_TYPES type = this->commandType();
  size_t val = ARGUMENT_TYPES::FIRST == index ? 0 : 1;

  switch (type) {
    case VM_COMMAND_TYPES ::C_ARITHMETIC:
      return tokens.at(0);

    case VM_COMMAND_TYPES::C_PUSH:
    case VM_COMMAND_TYPES::C_POP:
      if (tokens.size() <= (1 + val)) {
        throw std::out_of_range("Not enough tokens for arguments");
      }

      return tokens.at(1 + val);
  }

  throw std::invalid_argument("Unknown command: " + tokens.at(0));
}

std::string Parser::arg1() { return this->handleArgs(ARGUMENT_TYPES::FIRST); }
std::string Parser::arg2() { return this->handleArgs(ARGUMENT_TYPES::SECOND); }

SEGMENT_TYPES Parser::segmentType() const {
  VM_COMMAND_TYPES type = this->commandType();
  if (type != VM_COMMAND_TYPES::C_PUSH && type != VM_COMMAND_TYPES::C_POP) {
    throw std::domain_error("Function must be called in push or pop command");
  }

  auto it = this->segmentTable.find(this->tokens.at(1));

  if (it != this->segmentTable.end()) {
    return it->second;
  }

  throw std::invalid_argument("Unknown segment name: " + this->tokens.at(1));
}

ARITHMETIC_TYPES Parser::arithmeticType() const {
  VM_COMMAND_TYPES type = this->commandType();
  if (type != VM_COMMAND_TYPES::C_ARITHMETIC) {
    throw std::domain_error("Function must be called in arithmetic command");
  }
  auto it = this->arithmeticTable.find(this->tokens.at(0));

  if (it != this->arithmeticTable.end()) {
    return it->second;
  }

  throw std::invalid_argument("Unknown arithmetic command: " +
                              this->tokens.at(0));
}
