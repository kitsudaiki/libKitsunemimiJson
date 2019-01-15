/**
 *  @file    jsonItem.cpp
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#include <jsonItem.h>

#include <jsonObjects.h>

namespace Kitsune
{
namespace Json
{

/**
 * @brief JsonItem::JsonItem
 * @param otherItem
 */
JsonItem::JsonItem(const JsonItem &otherItem)
{
    m_item = otherItem.m_item->copy();
}

/**
 * @brief JsonItem::JsonItem
 * @param value
 */
JsonItem::JsonItem(std::map<std::string, JsonItem> &value)
{
    JsonObject* tempItem = new JsonObject();
    m_item = static_cast<AbstractJson*>(tempItem);

    std::map<std::string, JsonItem>::iterator it;
    for(it = value.begin(); it != value.end(); it++)
    {
        insert(it->first, it->second);
    }
}

/**
 * @brief JsonItem::JsonItem
 * @param value
 */
JsonItem::JsonItem(std::vector<JsonItem> &value)
{
    JsonArray* tempItem = new JsonArray();
    m_item = static_cast<AbstractJson*>(tempItem);

    std::vector<JsonItem>::iterator it;
    for(it = value.begin(); it != value.end(); it++)
    {
        append(*it);
    }
}

/**
 * @brief JsonItem::JsonItem
 * @param value
 */
JsonItem::JsonItem(std::string value)
{
    JsonValue* tempItem = new JsonValue();
    m_item = static_cast<AbstractJson*>(tempItem);

    setValue(value);
}

/**
 * @brief JsonItem::JsonItem
 * @param value
 */
JsonItem::JsonItem(int value)
{
    JsonValue* tempItem = new JsonValue();
    m_item = static_cast<AbstractJson*>(tempItem);

    setValue(value);
}

/**
 * @brief JsonItem::~JsonItem
 */
JsonItem::~JsonItem()
{
    clear();
}

/**
 * @brief JsonItem::operator =
 * @param other
 * @return
 */
JsonItem &JsonItem::operator=(const JsonItem &other)
{
    if(this != &other)
    {
        clear();
        m_item = other.m_item->copy();
    }
    return *this;
}

/**
 * @brief JsonItem::setValue
 * @param value
 */
bool
JsonItem::setValue(const std::string &value)
{
    if(m_item->getType() == AbstractJson::STRING_TYPE) {
        m_item->toValue()->setValue(value);
        return true;
    }
    return false;
}

/**
 * @brief JsonItem::setValue
 * @param value
 */
bool
JsonItem::setValue(const int &value)
{
    if(m_item->getType() == AbstractJson::INT_TYPE) {
        m_item->toValue()->setValue(value);
        return true;
    }
    return false;
}

/**
 * @brief JsonItem::insert
 * @param key
 * @param value
 * @param force
 * @return
 */
bool
JsonItem::insert(const std::string &key,
                 const JsonItem &value,
                 bool force)
{
    if(m_item->getType() == AbstractJson::OBJECT_TYPE) {
        return m_item->toObject()->insert(key, value.m_item->copy(), force);
    }
    return false;
}

/**
 * @brief JsonItem::append
 * @param item
 * @return
 */
bool
JsonItem::append(const JsonItem &value)
{
    if(m_item->getType() == AbstractJson::ARRAY_TYPE) {
        return m_item->toArray()->append(value.m_item->copy());
    }
    return false;
}

/**
 * @brief JsonItem::operator []
 * @param key
 * @return
 */
JsonItem
JsonItem::operator[](const std::string key)
{
    return JsonItem(m_item->get(key)->copy());
}

/**
 * @brief JsonItem::operator []
 * @param index
 * @return
 */
JsonItem
JsonItem::operator[](const uint32_t index)
{
    return JsonItem(m_item->get(index)->copy());
}

/**
 * @brief JsonItem::get
 * @param key
 * @return
 */
JsonItem
JsonItem::get(const std::string key)
{
    return JsonItem(m_item->get(key));
}

/**
 * @brief JsonItem::get
 * @param index
 * @return
 */
JsonItem
JsonItem::get(const uint32_t index)
{
    return JsonItem(m_item->get(index));
}

/**
 * @brief JsonItem::getString
 * @return
 */
std::string
JsonItem::getString() const
{
    if(m_item->getType() == AbstractJson::STRING_TYPE) {
        return m_item->toValue()->getString();
    }
    return "";
}

/**
 * @brief JsonItem::getInt
 * @return
 */
int
JsonItem::getInt() const
{
    if(m_item->getType() == AbstractJson::INT_TYPE) {
        return m_item->toValue()->getInt();
    }
    return 0;
}

/**
 * @brief JsonItem::getSize
 * @return
 */
uint32_t
JsonItem::getSize() const
{
    return m_item->getSize();
}

/**
 * @brief JsonItem::isObject
 * @return
 */
bool JsonItem::isObject() const
{
    if(m_item->getType() == AbstractJson::OBJECT_TYPE) {
        return true;
    }
    return false;
}

/**
 * @brief JsonItem::isArray
 * @return
 */
bool JsonItem::isArray() const
{
    if(m_item->getType() == AbstractJson::ARRAY_TYPE) {
        return true;
    }
    return false;
}

/**
 * @brief JsonItem::isValue
 * @return
 */
bool JsonItem::isValue() const
{
    if(m_item->getType() == AbstractJson::STRING_TYPE
            || m_item->getType() == AbstractJson::INT_TYPE) {
        return true;
    }
    return false;
}

/**
 * @brief JsonItem::remove
 * @param key
 * @return
 */
bool
JsonItem::remove(const std::string &key)
{
    return m_item->remove(key);
}

/**
 * @brief JsonItem::remove
 * @param index
 * @return
 */
bool
JsonItem::remove(const uint32_t index)
{
    return m_item->remove(index);
}

/**
 * @brief JsonItem::print
 * @param output
 */
void
JsonItem::print(std::string *output)
{
    m_item->print(output);
}

/**
 * @brief JsonItem::JsonItem
 * @param item
 */
JsonItem::JsonItem(AbstractJson *item)
{
    m_item = item;
}

/**
 * @brief JsonItem::clear
 */
void JsonItem::clear()
{
    if(m_item != nullptr)
    {
        delete m_item;
        m_item = nullptr;
    }
}

}  // namespace Json
}  // namespace Kitsune
