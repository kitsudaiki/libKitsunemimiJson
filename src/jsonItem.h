/**
 *  @file    jsonItem.h
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef JSONITEM_H
#define JSONITEM_H

#include <string>

namespace Kitsune
{
namespace Json
{
class AbstractJson;

class JsonItem
{
public:
    JsonItem(const JsonItem &otherItem);
    JsonItem(AbstractJson* item);
    ~JsonItem();

    // setter
    bool setValue(const std::string &value);
    bool setValue(const int &value);
    bool insert(const std::string &key,
                AbstractJson* value,
                bool force = false);
    bool append(AbstractJson* item);

    // getter
    JsonItem operator[](const std::string key);
    JsonItem operator[](const uint32_t index);
    JsonItem get(const std::string key);
    JsonItem get(const uint32_t index);

    std::string getString() const;
    int getInt() const;
    uint32_t getSize() const;

    // delete
    bool remove(const std::string& key);
    bool remove(const uint32_t index);

    // output
    void print(std::string *output);

private:
    AbstractJson* m_item = nullptr;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONITEM_H
