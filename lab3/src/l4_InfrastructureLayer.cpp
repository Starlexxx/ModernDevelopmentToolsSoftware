#include "hw/l4_InfrastructureLayer.h"


std::string readString(std::istream& is, size_t max_string_length)
{
    uint16_t len = readNumber<uint16_t>(is);

    assert(len <= max_string_length);

    char b[max_string_length+1];

    if (len > 0)
        is.read(b, len);

    b[len] = 0;

    return std::string(b);
}

void writeString(std::ostream& os, const std::string& s)
{
    uint16_t len = s.length();

    writeNumber(os, len);

    os.write(s.c_str(), len);
}

    std::shared_ptr<ICollectable> ACollector::getItem(size_t index) const
    {
        assert(index < _items.size());

        return _items[index];
    }

    bool ACollector::isRemoved(size_t index) const
    {
        assert(index < _removed_signs.size());

        return _removed_signs[index];
    }

    void ACollector::addItem(std::shared_ptr<ICollectable> item)
    {
        _items.emplace_back(item);
        _removed_signs.emplace_back(false);
    }

    void ACollector::removeItem(size_t index)
    {
        assert(index < _items.size());
        assert(index < _removed_signs.size());

        if (!_removed_signs[index])
        {
            _removed_signs[index] = true;
            _removed_count ++;
        }
    }

    void ACollector::updateItem(size_t index, const std::shared_ptr<ICollectable> & item)
    {
        assert(index < _items.size());

        _items[index] = item;
    }

    void ACollector::clean()
    {
        _items.clear();
        _removed_signs.clear();
        _removed_count = 0;
    }

    bool ACollector::loadCollection(const std::string file_name)
    {
        std::ifstream ifs (file_name, std::ios_base::binary);

        if (!ifs)
            return false;

        size_t count = readNumber<size_t>(ifs);

        _items.reserve(count);

        for(size_t i=0; i < count; ++i)
            addItem(read(ifs));

        assert(invariant());

        return ifs.good();
    }

    bool ACollector::saveCollection(const std::string file_name) const
    {
        assert(invariant());

        std::ofstream ofs (file_name, std::ios_base::binary);

        if (!ofs)
            return false;

        size_t count = _items.size() - _removed_count;

        writeNumber(ofs, count);

        for(size_t i=0; i < _items.size(); ++i)
            if (!_removed_signs[i])
                _items[i]->write(ofs);

        return ofs.good();
    }

