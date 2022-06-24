#include "hw/l2_ApplicationLayer.h"
#include "iostream"

struct orderData {
  std::string name;
  std::string model;
  std::string brand;
  uint32_t amount;
};

bool Application::performCommand(const std::vector<std::string> &args) {
  if (args.empty())
    return false;

  if (args[0] == "l" || args[0] == "load") {
    std::string filename = (args.size() == 1) ? "hw.data" : args[1];

    if (!_col.loadCollection(filename)) {
      _out.Output("Ошибка при загрузке файла '" + filename + "'");
      return false;
    }

    return true;
  }

  if (args[0] == "s" || args[0] == "save") {
    std::string filename = (args.size() == 1) ? "hw.data" : args[1];

    if (!_col.saveCollection(filename)) {
      _out.Output("Ошибка при сохранении файла '" + filename + "'");
      return false;
    }

    return true;
  }

  if (args[0] == "c" || args[0] == "clean") {
    if (args.size() != 1) {
      _out.Output("Некорректное количество аргументов команды clean");
      return false;
    }

    _col.clean();

    return true;
  }

  if (args[0] == "a" || args[0] == "add") {
    if (args.size() != 6) {
      _out.Output("Некорректное количество аргументов команды add");
      return false;
    }
    if (args[0] == "ao" || args[0] == "add_order") {
      if (args.size() != 4) {
        _out.Output("Некорректное количество аргументов команды add_order");
        return false;
      }

      Instrument &i = _col.getInstrumentRef(stoul(args[1]));

      std::vector<Order> o = i.getOrders();
      o.push_back(Order(args[2], stod(args[3])));
      i.setOrders(o);

      return true;
    }

    _col.addItem(std::make_shared<Instrument>(args[1].c_str(), args[2].c_str(),
                                              args[3].c_str(), stoul(args[4]),
                                              stoul(args[5])));
    return true;
  }

  if (args[0] == "ao" || args[0] == "add_order") {
    if (args.size() != 4) {
      _out.Output("Некорректное количество аргументов команды add_order");
      return false;
    }

    Instrument &i = _col.getInstrumentRef(stoul(args[1]));

    std::vector<Order> o = i.getOrders();
    o.push_back(Order(args[2], stod(args[3])));
    i.setOrders(o);

    return true;
  }

  if (args[0] == "r" || args[0] == "remove") {
    if (args.size() != 2) {
      _out.Output("Некорректное количество аргументов команды remove");
      return false;
    }

    _col.removeItem(stoul(args[1]));
    return true;
  }

  if (args[0] == "u" || args[0] == "update") {
    if (args.size() != 7) {
      _out.Output("Некорректное количество аргументов команды update");
      return false;
    }

    _col.updateItem(stoul(args[1]),
                    std::make_shared<Instrument>(
                        args[1].c_str(), args[2].c_str(), args[3].c_str(),
                        stoul(args[4]), stoi(args[5])));
    return true;
  }

  if (args[0] == "v" || args[0] == "view") {
    if (args.size() != 1) {
      _out.Output("Некорректное количество аргументов команды view");
      return false;
    }

    size_t count = 0;
    for (size_t i = 0; i < _col.getSize(); ++i) {
      const Instrument &item = static_cast<Instrument &>(*_col.getItem(i));

      if (!_col.isRemoved(i)) {
        _out.Output("[" + std::to_string(i) + "] " + item.getName() + " " +
                    item.getBrand() + " " + item.getModel() + " " +
                    std::to_string(item.getCost()) + " " +
                    std::to_string(item.getIsAvailable()));
        count++;
      }
    }

    _out.Output("Количество элементов в коллекции: " + std::to_string(count));
    return true;
  }

  if (args[0] == "go" || args[0] == "generate_order") {
    if (args.size() != 1) {
      _out.Output("Некорректное количество аргументов команды generate_order");
      return false;
    }

    std::vector<orderData> report_set;

    for (size_t i = 0; i < _col.getSize(); i++) {
      if (!_col.isRemoved(i)) {
        const Instrument &p = _col.getInstrumentRef(i);

        if (p.getOrders().size() > 0) {
          uint32_t sum = 0;
          for (auto &order : p.getOrders()) {
            sum += order.getAmount();
          }
          if (p.getIsAvailable() < sum)
            report_set.push_back({p.getName(), p.getModel(), p.getBrand(),
                                  sum - p.getIsAvailable()});
        }
      }
    }

    for (auto &report : report_set) {
      _out.Output(report.name + " " + report.model + " " + report.brand + " " +
                  std::to_string(report.amount));
    }
    return true;
  }

  _out.Output("Недопустимая команда '" + args[0] + "'");
  return false;
}
