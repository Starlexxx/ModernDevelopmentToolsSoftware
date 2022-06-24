#ifndef HW_L3_DOMAIN_LAYER_H
#define HW_L3_DOMAIN_LAYER_H

#include "hw/l4_InfrastructureLayer.h"

const size_t MAX_NAME_LENGTH = 15;
const size_t MAX_BRAND_LENGTH = 10;
const size_t MAX_MODEL_LENGTH = 20;
const size_t MIN_COST = 1;
const size_t MAX_COST = 1000;

class Order {
  std::string _client_name;
  uint32_t _instrument_amount;

public:
  Order() = delete;
  Order(std::string client_name, uint32_t instrument_amount)
      : _client_name(client_name), _instrument_amount(instrument_amount) {}

  std::string getClientName() const { return _client_name; }
  uint32_t getAmount() const { return _instrument_amount; }
};

class Instrument : public ICollectable {
  std::string _name;
  std::string _brand;
  std::string _model;
  uint16_t _cost;
  uint32_t _is_available;
  std::vector<Order> _orders;

protected:
  bool invariant() const;

public:
  Instrument() = delete;
  Instrument(const Instrument &p) = delete;

  Instrument &operator=(const Instrument &p) = delete;

  Instrument(const std::string &name, const std::string &brand,
             const std::string &model, uint16_t cost, uint32_t is_available);
  Instrument(const std::string &name, const std::string &brand,
             const std::string &model, uint16_t cost, uint32_t is_available,
             std::vector<Order> orders);

  const std::string &getName() const;
  const std::string &getBrand() const;
  const std::string &getModel() const;
  uint16_t getCost() const;
  uint32_t getIsAvailable() const;
  const std::vector<Order> &getOrders() const;

  void setOrders(const std::vector<Order> &orders);

  virtual bool write(std::ostream &os) override;
};

class ItemCollector : public ACollector {
public:
  virtual std::shared_ptr<ICollectable> read(std::istream &is) override;

  Instrument &getInstrumentRef(size_t index);
};

#endif // HW_L3_DOMAIN_LAYER_H
