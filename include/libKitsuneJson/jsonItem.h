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
namespace Json
{
class AbstractJson;


class JsonItem
{
public:
    JsonItem(const JsonItem &otherItem);
    JsonItem(AbstractJson* abstract);
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
    JsonItem operator[](const std::string key);
    JsonItem operator[](const uint32_t index);
    JsonItem get(const std::string key);
    JsonItem get(const uint32_t index);
    std::string getString() const;
    int getInt() const;
    uint32_t getSize() const;

    bool isValid() const;
    bool isObject() const;
    bool isArray() const;
    bool isValue() const;

    // delete
    bool remove(const std::string& key);
    bool remove(const uint32_t index);

    // output
    void print(std::string *output);

private:
    void clear();

    AbstractJson* m_item = nullptr;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONITEM_H
