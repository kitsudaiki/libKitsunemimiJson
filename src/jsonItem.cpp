/**
 *  @file    jsonItem.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <jsonItem.h>

#include <jsonObjects.h>
#include <json_parsing/jsonParserInterface.h>

namespace Kitsune
{
namespace Json
{

/**
 *  creates a new item based on an already existring item
 *
 * @param otherItem other item, which have to be copied
 */
JsonItem::JsonItem(const JsonItem &otherItem)
{
    m_item = otherItem.m_item->copy();
}

/**
 * creates a new item
 *
 * @param abstract pointer to an already existring abstract-json
 */
JsonItem::JsonItem(AbstractJson *abstract)
{
    m_item = abstract;
}

/**
 * creates an object-item
 *
 * @param value map for the new object, which can be empty
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
 * creates an array-item
 *
 * @param value vector for the new object, which can be empty
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
 * creates an value-item
 *
 * @param value string of the new item
 */
JsonItem::JsonItem(std::string value)
{
    JsonValue* tempItem = new JsonValue();
    m_item = static_cast<AbstractJson*>(tempItem);

    setValue(value);
}

/**
 * creates an value-item
 *
 * @param value int-value of the new item
 */
JsonItem::JsonItem(int value)
{
    JsonValue* tempItem = new JsonValue();
    m_item = static_cast<AbstractJson*>(tempItem);

    setValue(value);
}

/**
 * destructor
 */
JsonItem::~JsonItem()
{
    clear();
}

/**
 * static-method which calls the parser to convert a json-formated string into a json-object-tree
 *
 * @param input json-formated string, which should be parsed
 * @return nullptr, if parsing was not successful, else the root-object of the new json-tree
 */
JsonItem
JsonItem::parseString(const std::string &input)
{
    JsonParserInterface parser;
    bool ret = parser.parse(input);
    if(ret == false) {
        return nullptr;
    }
    AbstractJson* output = parser.getOutput();
    JsonItem result(output);
    return result;
}

/**
 * replace the content of the item with the content of another item
 *
 * @param other other item, which have to be copied
 * @return pointer to this current item
 */
JsonItem&
JsonItem::operator=(const JsonItem &other)
{
    if(this != &other)
    {
        clear();
        m_item = other.m_item->copy();
    }
    return *this;
}

/**
 * writes a new string into the json-value
 *
 * @param value new string to store
 */
bool
JsonItem::setValue(const std::string &value)
{
    if(m_item->getType() == AbstractJson::INT_TYPE
            || m_item->getType() == AbstractJson::STRING_TYPE)
    {
        m_item->toValue()->setValue(value);
        return true;
    }
    return false;
}

/**
 * writes a new integer into the json-value
 *
 * @param value new number to store
 */
bool
JsonItem::setValue(const int &value)
{
    if(m_item->getType() == AbstractJson::INT_TYPE
            || m_item->getType() == AbstractJson::STRING_TYPE)
    {
        m_item->toValue()->setValue(value);
        return true;
    }
    return false;
}

/**
 * insert a key-value-pair if the current item is a json-object
 *
 * @param key key of the new pair
 * @param value value of the new pair
 * @param force true to overwrite an existing key (default: false)
 * @return false, if item is not a json-object, else true
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
 * add a new item, if the current item is a json-array
 *
 * @param item new item
 * @return false, if item is not a json-array, else true
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
 * get a specific entry of the item
 *
 * @param key key of the requested value
 * @return nullptr if index in key is to high, else object
 */
JsonItem
JsonItem::operator[](const std::string key)
{
    return JsonItem(m_item->get(key)->copy());
}

/**
 * get a specific item of the object
 *
 * @param index index of the item
 * @return nullptr if index is to high, else object
 */
JsonItem
JsonItem::operator[](const uint32_t index)
{
    return JsonItem(m_item->get(index)->copy());
}

/**
 * get a specific entry of the item
 *
 * @param key key of the requested value
 * @return nullptr if index in key is to high, else object
 */
JsonItem
JsonItem::get(const std::string key)
{
    return JsonItem(m_item->get(key));
}

/**
 * get a specific item of the object
 *
 * @param index index of the item
 * @return nullptr if index is to high, else object
 */
JsonItem
JsonItem::get(const uint32_t index)
{
    return JsonItem(m_item->get(index));
}

/**
 * get string of the item
 *
 * @return string, of the item if int-type, else empty string
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
 * get int-value of the item
 *
 * @return int-value, of the item if int-type, else 0
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
 * getter for the number of elements in the item
 *
 * @return number of elements in the item
 */
uint32_t
JsonItem::getSize() const
{
    return m_item->getSize();
}

/**
 * check if the current item is valid
 *
 * @return false, if the item is a null-pointer, else true
 */
bool JsonItem::isValid() const
{
    if(m_item != nullptr) {
        return true;
    }
    return false;
}

/**
 * check if current item is a object
 *
 * @return true if current item is a json-object, else false
 */
bool JsonItem::isObject() const
{
    if(m_item->getType() == AbstractJson::OBJECT_TYPE) {
        return true;
    }
    return false;
}

/**
 * check if current item is a array
 *
 * @return true if current item is a json-array, else false
 */
bool JsonItem::isArray() const
{
    if(m_item->getType() == AbstractJson::ARRAY_TYPE) {
        return true;
    }
    return false;
}

/**
 * check if current item is a value
 *
 * @return true if current item is a json-value, else false
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
 * remove an item from the key-value-list
 *
 * @param key key of the pair, which should be deleted
 * @return false if the key doesn't exist, else true
 */
bool
JsonItem::remove(const std::string &key)
{
    return m_item->remove(key);
}

/**
 * remove an item from the object
 *
 * @param index index of the item
 * @return false if index is to high, else true
 */
bool
JsonItem::remove(const uint32_t index)
{
    return m_item->remove(index);
}

/**
 * prints the content of the object
 *
 * @param output pointer to the output-string on which the object-content as string will be appended
 */
void
JsonItem::print(std::string *output)
{
    m_item->print(output);
}

/**
 * delete the underlaying json-object
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
