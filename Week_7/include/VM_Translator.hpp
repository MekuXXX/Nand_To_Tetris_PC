#include <fstream>
#include <string>

class VM_Translator {
 public:
  void translate(const std::string& input, const std::string& output = "");

 private:
  std::ofstream file;
};
