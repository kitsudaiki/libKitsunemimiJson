/**
 *  @file    jsonItem.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <jsonItem.hpp>

#include <data_structure/dataItems.hpp>
#include <json_parsing/jsonParserInterface.hpp>

using Kitsune::Common::DataItem;
using Kitsune::Common::DataArray;
using Kitsune::Common::DataValue;
using Kitsune::Common::DataObject;

namespace Kitsune
{
namespace Json
{

/**
 * @brief JsonItem::JsonItem
 */
JsonItem::JsonItem()
{
    m_item = nullptr;
}

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
JsonItem::JsonItem(DataItem *abstract)
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
    DataObject* tempItem = new DataObject();
    m_item = static_cast<DataItem*>(tempItem);

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
    DataArray* tempItem = new DataArray();
    m_item = static_cast<DataItem*>(tempItem);

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
    DataValue* tempItem = new DataValue();
    m_item = static_cast<DataItem*>(tempItem);

    setValue(value);
}

/**
 * creates an value-item
 *
 * @param value int-value of the new item
 */
JsonItem::JsonItem(int value)
{
    DataValue* tempItem = new DataValue();
    m_item = static_cast<DataItem*>(tempItem);

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

    DataItem* output = parser.getOutput();
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
    if(m_item == nullptr) {
        return false;
    }

    if(m_item->getType() == DataItem::VALUE_TYPE)
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
    if(m_item == nullptr) {
        return false;
    }

    if(m_item->getType() == DataItem::VALUE_TYPE)
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
    if(m_item == nullptr) {
        return false;
    }

    if(m_item->getType() == DataItem::OBJECT_TYPE) {
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
    if(m_item == nullptr) {
        return false;
    }

    if(m_item->getType() == DataItem::ARRAY_TYPE) {
        return m_item->toArray()->append(value.m_item->copy());
    }

    return false;
}

/**
 * @brief JsonItem::getItemContent
 * @return
 */
DataItem*
JsonItem::getItemContent() const
{
    return m_item;
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
    if(m_item == nullptr) {
        return JsonItem();
    }

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
    if(m_item == nullptr) {
        return JsonItem();
    }

    return JsonItem(m_item->get(index)->copy());
}

/**
 * get a specific entry of the item
 *
 * @param key key of the requested value
 * @return nullptr if index in key is to high, else object
 */
JsonItem
JsonItem::get(const std::string key) const
{
    if(m_item == nullptr) {
        return JsonItem();
    }

    return JsonItem(m_item->get(key));
}

/**
 * get a specific item of the object
 *
 * @param index index of the item
 * @return nullptr if index is to high, else object
 */
JsonItem
JsonItem::get(const uint32_t index) const
{
    if(m_item == nullptr) {
        return JsonItem();
    }

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
    if(m_item == nullptr) {
        return "";
    }

    if(m_item->toValue()->getValueType() == DataItem::STRING_TYPE) {
        return m_item->toValue()->toString();
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
    if(m_item == nullptr) {
        return 0;
    }

    if(m_item->toValue()->getValueType() == DataItem::INT_TYPE) {
        return m_item->toValue()->toInt();
    }

    return 0;
}

/**
 * get float-value of the item
 *
 * @return float-value, of the item if float-type, else 0
 */
float
JsonItem::getFloat() const
{
    if(m_item == nullptr) {
        return 0;
    }

    if(m_item->toValue()->getValueType() == DataItem::FLOAT_TYPE) {
        return m_item->toValue()->toFloat();
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
    if(m_item == nullptr) {
        return 0;
    }

    return m_item->getSize();
}

/**
 * get list of keys if the json-item is an json-object
 *
 * @return string-list with the keys of the map
 */
std::vector<std::string>
JsonItem::getKeys()
{
    if(m_item == nullptr) {
        return std::vector<std::string>();
    }

    if(m_item->getType() == DataItem::OBJECT_TYPE)
    {
        DataObject* obj = static_cast<DataObject*>(m_item);
        return obj->getKeys();
    }

    std::vector<std::string> emptyResult;
    return emptyResult;
}

/**
 * check if a key is in the object-map
 *
 * @param key key-string which should be searched in the map of the object-item
 * @return false if the key doesn't exist or the item is no json-object, else true
 */
bool
JsonItem::contains(const std::string &key)
{
    if(m_item == nullptr) {
        return false;
    }

    if(m_item->getType() == DataItem::OBJECT_TYPE)
    {
        DataObject* obj = static_cast<DataObject*>(m_item);
        return obj->contains(key);
    }

    return false;
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
    if(m_item == nullptr) {
        return false;
    }

    if(m_item->getType() == DataItem::OBJECT_TYPE) {
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
    if(m_item == nullptr) {
        return false;
    }

    if(m_item->getType() == DataItem::ARRAY_TYPE) {
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
    if(m_item == nullptr) {
        return false;
    }

    if(m_item->getType() == DataItem::VALUE_TYPE) {
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
    if(m_item != nullptr) {
        return m_item->remove(key);
    }

    return false;
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
    if(m_item != nullptr) {
        return m_item->remove(index);
    }
    return false;
}

/**
 * prints the content of the object
 *
 * @param output pointer to the output-string on which the object-content as string will be appended
 */
std::string JsonItem::print(bool indent)
{
    return m_item->print(nullptr, indent);
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
