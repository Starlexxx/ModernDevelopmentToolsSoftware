#include "hw/l3_DomainLayer.h"
#include <vector>

bool Instrument::invariant() const {
  return _cost >= MIN_COST && _cost <= MAX_COST && !_name.empty() &&
         _name.size() <= MAX_NAME_LENGTH && !_brand.empty() &&
         _brand.size() <= MAX_BRAND_LENGTH && !_model.empty() &&
         _model.size() <= MAX_MODEL_LENGTH;
}

Instrument::Instrument(const std::string &name, const std::string &brand,
                       const std::string &model, uint16_t cost,
                       uint32_t is_available)
    : _name(name), _brand(brand), _model(model), _cost(cost),
      _is_available(is_available) {
  assert(invariant());
}

Instrument::Instrument(const std::string &name, const std::string &brand,
                       const std::string &model, uint16_t cost,
                       uint32_t is_available, std::vector<Order> orders)
    : _name(name), _brand(brand), _model(model), _cost(cost),
      _is_available(is_available), _orders(orders) {
  assert(invariant());
}

const std::string &Instrument::getName() const { return _name; }
const std::string &Instrument::getBrand() const { return _brand; }
const std::string &Instrument::getModel() const { return _model; }
uint16_t Instrument::getCost() const { return _cost; }
uint32_t Instrument::getIsAvailable() const { return _is_available; }

const std::vector<Order> &Instrument::getOrders() const { return _orders; }

void Instrument::setOrders(const std::vector<Order> &orders) {
  _orders = orders;
}

bool Instrument::write(std::ostream &os) {
  writeString(os, _name);
  writeString(os, _brand);
  writeString(os, _model);
  writeNumber(os, _cost);
  writeNumber(os, _is_available);
  return os.good();
}

std::shared_ptr<ICollectable> ItemCollector::read(std::istream &is) {
  std::string name = readString(is, MAX_NAME_LENGTH);
  std::string brand = readString(is, MAX_BRAND_LENGTH);
  std::string model = readString(is, MAX_MODEL_LENGTH);
  uint16_t cost = readNumber<uint16_t>(is);
  uint32_t is_available = readNumber<uint32_t>(is);

  size_t order_count = readNumber<size_t>(is);
  std::vector<Order> o;

  o.reserve(order_count);
  for (size_t i = 0; i < order_count; ++i) {
    std::string client_name = readString(is, MAX_NAME_LENGTH);
    uint32_t instrument_amount = readNumber<uint32_t>(is);

    o.push_back(Order(client_name, instrument_amount));
  }
  return std::make_shared<Instrument>(name, brand, model, cost, is_available);
}

Instrument &ItemCollector::getInstrumentRef(size_t index) {
  Instrument &i = *static_cast<Instrument *>(getItem(index).get());

  return i;
}
