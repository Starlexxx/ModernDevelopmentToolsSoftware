#include "hw/l3_DomainLayer.h"

bool Instrument::invariant() const {
  return _cost >= MIN_COST && _cost <= MAX_COST && !_name.empty() &&
         _name.size() <= MAX_NAME_LENGTH && !_brand.empty() &&
         _brand.size() <= MAX_BRAND_LENGTH && !_model.empty() &&
         _model.size() <= MAX_MODEL_LENGTH;
}

Instrument::Instrument(const std::string &name, const std::string &brand,
                       const std::string &model, uint16_t cost,
                       bool is_available)
    : _name(name), _brand(brand), _model(model), _cost(cost),
      _is_available(is_available) {
  assert(invariant());
}

const std::string &Instrument::getName() const { return _name; }
const std::string &Instrument::getBrand() const { return _brand; }
const std::string &Instrument::getModel() const { return _model; }
uint16_t Instrument::getCost() const { return _cost; }
bool Instrument::getIsAvailable() const { return _is_available; }

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
  bool is_available = readNumber<bool>(is);

  return std::make_shared<Instrument>(name, brand, model, cost, is_available);
}
