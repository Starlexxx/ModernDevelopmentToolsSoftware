#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

#include <sstream>

#include "collector.h"

const size_t MAX_NAME_LENGTH = 15;
const size_t MAX_BRAND_LENGTH = 10;
const size_t MAX_MODEL_LENGTH = 20;
const size_t MIN_COST = 1;
const size_t MAX_COST = 1000;

class Instrument : public ICollectable {
  std::string _name;
  std::string _brand;
  std::string _model;
  uint16_t _cost;
  bool _is_available;

protected:
  bool invariant() const {
    return _cost >= MIN_COST && _cost <= MAX_COST && !_name.empty() &&
           _name.size() <= MAX_NAME_LENGTH && !_brand.empty() &&
           _brand.size() <= MAX_BRAND_LENGTH && !_model.empty() &&
           _model.size() <= MAX_MODEL_LENGTH;
  }

public:
  Instrument() = delete;
  Instrument(const Instrument &p) = delete;

  Instrument &operator=(const Instrument &p) = delete;

  Instrument(const std::string &name, const std::string &brand,
             const std::string &model, uint16_t cost, bool is_available)
      : _name(name), _brand(brand), _model(model), _cost(cost),
        _is_available(is_available) {
    assert(invariant());
  }

  const std::string &getName() const { return _name; }
  const std::string &getBrand() const { return _brand; }
  const std::string &getModel() const { return _model; }
  uint16_t getCost() const { return _cost; }
  bool getIsAvailable() const { return _is_available; }

  virtual bool write(std::ostream &os) override {
    writeString(os, _name);
    writeString(os, _brand);
    writeString(os, _model);
    writeNumber(os, _cost);
    writeNumber(os, _is_available);

    return os.good();
  }
};

class ItemCollector : public ACollector {
public:
  virtual std::shared_ptr<ICollectable> read(std::istream &is) override {
    std::string name = readString(is, MAX_NAME_LENGTH);
    std::string brand = readString(is, MAX_BRAND_LENGTH);
    std::string model = readString(is, MAX_MODEL_LENGTH);
    uint16_t cost = readNumber<uint16_t>(is);
    bool is_available = readNumber<bool>(is);

    return std::make_shared<Instrument>(name, brand, model, cost, is_available);
  }
};

bool performCommand(const std::vector<std::string> &args, ItemCollector &col) {
  if (args.empty())
    return false;

  if (args[0] == "l" || args[0] == "load") {
    std::string filename = (args.size() == 1) ? "hw.data" : args[1];

    if (!col.loadCollection(filename)) {
      std::cerr << "Ошибка при загрузке файла '" << filename << "'"
                << std::endl;
      return false;
    }

    return true;
  }

  if (args[0] == "s" || args[0] == "save") {
    std::string filename = (args.size() == 1) ? "hw.data" : args[1];

    if (!col.saveCollection(filename)) {
      std::cerr << "Ошибка при сохранении файла '" << filename << "'"
                << std::endl;
      return false;
    }

    return true;
  }

  if (args[0] == "c" || args[0] == "clean") {
    if (args.size() != 1) {
      std::cerr << "Некорректное количество аргументов команды clean"
                << std::endl;
      return false;
    }

    col.clean();

    return true;
  }

  if (args[0] == "a" || args[0] == "add") {
    if (args.size() != 6) {
      std::cerr << "Некорректное количество аргументов команды add"
                << std::endl;
      return false;
    }

    col.addItem(std::make_shared<Instrument>(args[1].c_str(), args[2].c_str(),
                                             args[3].c_str(), stoul(args[4]),
                                             stoul(args[5])));
    return true;
  }

  if (args[0] == "r" || args[0] == "remove") {
    if (args.size() != 2) {
      std::cerr << "Некорректное количество аргументов команды remove"
                << std::endl;
      return false;
    }

    col.removeItem(stoul(args[1]));
    return true;
  }

  if (args[0] == "u" || args[0] == "update") {
    if (args.size() != 7) {
      std::cerr << "Некорректное количество аргументов команды update"
                << std::endl;
      return false;
    }

    col.updateItem(stoul(args[1]),
                   std::make_shared<Instrument>(
                       args[1].c_str(), args[2].c_str(), args[3].c_str(),
                       stoul(args[4]), stoi(args[5])));
    return true;
  }

  if (args[0] == "v" || args[0] == "view") {
    if (args.size() != 1) {
      std::cerr << "Некорректное количество аргументов команды view"
                << std::endl;
      return false;
    }

    size_t count = 0;
    for (size_t i = 0; i < col.getSize(); ++i) {
      const Instrument &item = static_cast<Instrument &>(*col.getItem(i));

      if (!col.isRemoved(i)) {
        std::cout << "[" << i << "] " << item.getName() << " "
                  << item.getBrand() << " " << item.getModel() << " "
                  << item.getCost() << " " << item.getIsAvailable()
                  << std::endl;
        count++;
      }
    }

    std::cout << "Количество элементов в коллекции: " << count << std::endl;

    return true;
  }

  std::cerr << "Недопустимая команда '" << args[0] << "'" << std::endl;
  return false;
}

int main(int, char **) {
  ItemCollector col;

  for (std::string line; getline(std::cin, line);) {
    if (line.empty())
      break;

    std::istringstream iss(line);
    std::vector<std::string> args;

    for (std::string str; iss.good();) {
      iss >> str;
      args.emplace_back(str);
    }

    if (!performCommand(args, col))
      return 1;
  }

  std::cout << "Выполнение завершено успешно" << std::endl;
  return 0;
}
