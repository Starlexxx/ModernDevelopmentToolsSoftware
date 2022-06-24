#ifndef HW_L4_INFRASTRUCTURE_LAYER_H
#define HW_L4_INFRASTRUCTURE_LAYER_H

#include <cassert>
#include <fstream>
#include <memory>
#include <vector>

using namespace std;

template <typename T> T readNumber(istream &is) {
  T result;
  is.read(reinterpret_cast<char *>(&result), sizeof(result));
  return result;
}

string readString(istream &is, size_t max_string_length);

template <typename T> void writeNumber(ostream &os, T i) {
  os.write(reinterpret_cast<char *>(&i), sizeof(i));
}

void writeString(ostream &os, const string &s);

class ICollectable {
public:
  virtual ~ICollectable() = default;

  virtual bool write(ostream &os) = 0;
};

class ACollector {
  vector<shared_ptr<ICollectable>> _items;
  vector<bool> _removed_signs;
  size_t _removed_count = 0;

  bool invariant() const {
    return _items.size() == _removed_signs.size() &&
           _removed_count <= _items.size();
  }

public:
  virtual ~ACollector() = default;

  virtual shared_ptr<ICollectable> read(istream &is) = 0;

  size_t getSize() const { return _items.size(); }

  shared_ptr<ICollectable> getItem(size_t index) const;

  bool isRemoved(size_t index) const;

  void addItem(shared_ptr<ICollectable> item);

  void removeItem(size_t index);

  void updateItem(size_t index, const shared_ptr<ICollectable> &item);

  void clean();

  bool loadCollection(const string file_name);

  bool saveCollection(const string file_name) const;
};

#endif // HW_L4_INFRASTRUCTURE_LAYER_H
