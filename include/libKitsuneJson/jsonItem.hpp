/**
 *  @file    jsonItem.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONITEM_H
#define JSONITEM_H

#include <string>
#include <vector>
#include <map>

namespace Kitsune
{
namespace Common {
class DataItem;
}
namespace Json
{

class JsonItem
{
public:
    JsonItem();
    JsonItem(const JsonItem &otherItem);
    JsonItem(Common::DataItem* abstract);
    JsonItem(std::map<std::string, JsonItem> &value);
    JsonItem(std::vector<JsonItem> &value);
    JsonItem(std::string value);
    JsonItem(int value);

    ~JsonItem();

    static JsonItem parseString(const std::string &input);

    // setter
    JsonItem& operator=(const JsonItem& other);
    bool setValue(const std::string &value);
    bool setValue(const int &value);
    bool insert(const std::string &key,
                const JsonItem &value,
                bool force = false);
    bool append(const JsonItem &value);

    // getter
    Common::DataItem* getItemContent() const;
    JsonItem operator[](const std::string key);
    JsonItem operator[](const uint32_t index);
    JsonItem get(const std::string key) const;
    JsonItem get(const uint32_t index) const;
    std::string getString() const;
    int getInt() const;
    float getFloat() const;
    uint32_t getSize() const;
    std::vector<std::string> getKeys();

    // checks
    bool contains(const std::string &key);
    bool isValid() const;
    bool isObject() const;
    bool isArray() const;
    bool isValue() const;

    // delete
    bool remove(const std::string& key);
    bool remove(const uint32_t index);

    // output
    void print(std::string *output, bool indent=false);

private:
    void clear();

    Common::DataItem* m_item = nullptr;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONITEM_H