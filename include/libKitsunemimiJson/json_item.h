/**
 *  @file    json_item.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef JSON_ITEM_H
#define JSON_ITEM_H

#include <string>
#include <vector>
#include <map>

namespace Kitsunemimi
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
    JsonItem(Common::DataItem* dataItem, const bool copy=false);
    JsonItem(std::map<std::string, JsonItem> &value);
    JsonItem(std::vector<JsonItem> &value);
    JsonItem(const char* value);
    JsonItem(const std::string &value);
    JsonItem(const int value);
    JsonItem(const float value);
    JsonItem(const long value);
    JsonItem(const double value);
    JsonItem(const bool value);

    ~JsonItem();

    std::pair<bool, std::string> parse(const std::string &input,
                                       const bool traceParsing = false);

    // setter
    JsonItem& operator=(const JsonItem& other);
    bool setValue(const char* value);
    bool setValue(const std::string &value);
    bool setValue(const int &value);
    bool setValue(const float &value);
    bool setValue(const long &value);
    bool setValue(const double &value);
    bool setValue(const bool &value);
    bool insert(const std::string &key,
                const JsonItem &value,
                bool force = false);
    bool append(const JsonItem &value);
    bool replaceItem(const uint32_t index,
                     const JsonItem &value);
    bool deleteContent();

    // getter
    Common::DataItem* getItemContent() const;
    JsonItem operator[](const std::string key);
    JsonItem operator[](const uint32_t index);
    JsonItem get(const std::string key, const bool copy=false) const;
    JsonItem get(const uint32_t index, const bool copy=false) const;
    const std::string getString() const;
    int getInt() const;
    float getFloat() const;
    long getLong() const;
    double getDouble() const;
    bool getBool() const;
    uint64_t size() const;
    const std::vector<std::string> getKeys() const;

    // checks
    bool contains(const std::string &key) const;
    bool isValid() const;
    bool isNull() const;
    bool isMap() const;
    bool isArray() const;
    bool isValue() const;
    bool isString() const;
    bool isFloat() const;
    bool isInteger() const;
    bool isBool() const;

    // delete
    bool remove(const std::string& key);
    bool remove(const uint32_t index);

    // output
    std::string toString(bool indent=false) const;

private:
    void clear();

    bool m_deletable = true;
    Common::DataItem* m_content = nullptr;
};

}  // namespace Json
}  // namespace Kitsunemimi

#endif // JSON_ITEM_H
