#ifndef HW_L3_DOMAIN_LAYER_H
#define HW_L3_DOMAIN_LAYER_H

#include "hw/l4_InfrastructureLayer.h"

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
  bool invariant() const;

public:
  Instrument() = delete;
  Instrument(const Instrument &p) = delete;

  Instrument &operator=(const Instrument &p) = delete;

  Instrument(const std::string &name, const std::string &brand,
             const std::string &model, uint16_t cost, bool is_available);

  const std::string &getName() const;
  const std::string &getBrand() const;
  const std::string &getModel() const;
  uint16_t getCost() const;
  bool getIsAvailable() const;

  virtual bool write(std::ostream &os) override;
};

class ItemCollector : public ACollector {
public:
  virtual std::shared_ptr<ICollectable> read(std::istream &is) override;
};

#endif // HW_L3_DOMAIN_LAYER_H
