#include <cstddef>
#include <exception>
#include <iostream>
#include <map>
#include <string>

class Instrument {

private:
  std::map<std::string, std::string> _innerProperties = {};

public:
  void setProperty(std::string name, std::string value) {
    if (name.empty())
      return;
    _innerProperties.insert(std::pair<std::string, std::string>(name, value));
  }

  std::string getProperty(std::string name) {
    if (name.empty())
      return nullptr;
    return _innerProperties.find(name)->second;
  }

  void removeProperty(std::string name) {
    if (name.empty())
      return;
    _innerProperties.erase(name);
  }
};

int main(int argc, char **argv) {
  try {
    Instrument guitar;

    guitar.setProperty("name", argv[1]);
    guitar.setProperty("brand", argv[2]);
    guitar.setProperty("model", argv[3]);
    guitar.setProperty("cost", argv[4]);
    guitar.setProperty("isAvailable", argv[5]);

    std::cout << guitar.getProperty("name") << " "
              << guitar.getProperty("brand") << " "
              << guitar.getProperty("model") << " "
              << guitar.getProperty("cost") << " "
              << guitar.getProperty("isAvailable");

    return 0;

    std::cout << "*** Недопустимое количество аргументов" << std::endl;
    return 1;
  }

  catch (std::exception &e) {
    std::cout << "*** " << e.what() << std::endl;
    return 1;
  }
}
