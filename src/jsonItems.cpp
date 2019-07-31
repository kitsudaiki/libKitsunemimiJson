/**
 *  @file    jsonObjects.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonItems.hpp"
#include <iostream>
#include <json_parsing/jsonParserInterface.hpp>

namespace Kitsune
{
namespace Json
{

//===================================================================
// AbstractJson
//===================================================================

JsonItem::~JsonItem()
{
    //std::cout<<"AbstractJson: "<<this<<std::endl;
}

/**
 * static-method which calls the parser to convert a json-formated string into a json-object-tree
 *
 * @return nullptr, if parsing was not successful, else the root-object of the new json-tree
 */
JsonItem*
JsonItem::parseString(const std::string &input)
{
    JsonParserInterface parser;
    bool ret = parser.parse(input);
    if(ret == false) {
        return nullptr;
    }
    return parser.getOutput();
}

/**
 * request type, of the current json-object
 *
 * @return object-specific entry of the jsonTypes-enumeration
 */
JsonItem::jsonTypes
JsonItem::getType() const
{
    return m_type;
}

/**
 * TODO
 */
bool
JsonItem::isValue() const
{
    if(m_type == INT_TYPE
            || m_type == STRING_TYPE
            || m_type == FLOAT_TYPE)
    {
        return true;
    }
    return false;
}

/**
 * TODO
 */
bool
JsonItem::isObject() const
{
    if(m_type == OBJECT_TYPE) {
        return true;
    }
    return false;
}

/**
 * TODO
 */
bool
JsonItem::isArray() const
{
    if(m_type == ARRAY_TYPE) {
        return true;
    }
    return false;
}

/**
 * @brief AbstractJson::toArray
 * @return
 */
JsonArray*
JsonItem::toArray()
{
    if(m_type == ARRAY_TYPE) {
        return static_cast<JsonArray*>(this);
    }
    return nullptr;
}

/**
 * @brief AbstractJson::toObject
 * @return
 */
JsonObject*
JsonItem::toObject()
{
    if(m_type == OBJECT_TYPE) {
        return static_cast<JsonObject*>(this);
    }
    return nullptr;
}

/**
 * @brief AbstractJson::toValue
 * @return
 */
JsonValue*
JsonItem::toValue()
{
    if(m_type == STRING_TYPE
            || m_type == INT_TYPE
            || m_type == FLOAT_TYPE)
    {
        return static_cast<JsonValue*>(this);
    }
    return nullptr;
}

/**
 * request the string of the json-value, if it is from string-type
 *
 * @return string of the json-value, if json-value is from string-type, else empty string
 */
std::string
JsonItem::toString()
{
    if(m_type == STRING_TYPE)
    {
        JsonValue* value = dynamic_cast<JsonValue*>(this);
        return value->m_stringValue;
    }
    if(m_type == INT_TYPE)
    {
        JsonValue* value = dynamic_cast<JsonValue*>(this);
        return std::to_string(value->m_intValue);;
    }
    if(m_type == FLOAT_TYPE)
    {
        JsonValue* value = dynamic_cast<JsonValue*>(this);
        return std::to_string(value->m_floatValue);;
    }
    return "";
}

/**
 * request the integer of the json-value, if it is from int-type
 *
 * @return integer of the json-value, if json-value is from int-type, else empty 0
 */
int
JsonItem::toInt()
{
    if(m_type == INT_TYPE)
    {
        JsonValue* value = dynamic_cast<JsonValue*>(this);
        return value->m_intValue;
    }
    return 0;
}


/**
 * request the flaot of the json-value, if it is from float-type
 *
 * @return float of the json-value, if json-value is from float-type, else empty 0.0
 */
float
JsonItem::toFloat()
{
    if(m_type == FLOAT_TYPE)
    {
        JsonValue* value = dynamic_cast<JsonValue*>(this);
        return value->m_floatValue;
    }
    return 0.0f;
}

/**
 * TODO
 */
void
JsonItem::addIndent(std::string *output,
                        const bool indent,
                        const uint32_t level)
{
    if(indent == true)
    {
        output->append("\n");
        for(uint32_t i = 0; i < level; i++)
        {
            output->append("    ");
        }
    }
}

//===================================================================
// JsonValue
//===================================================================

/**
 * @brief JsonValue::JsonValue
 */
JsonValue::JsonValue()
{
    m_type = STRING_TYPE;
}

/**
 * json-value for strings
 */
JsonValue::JsonValue(const std::string &text)
{
    m_type = STRING_TYPE;
    m_stringValue = text;
}

/**
 * json-value for integers
 */
JsonValue::JsonValue(const int value)
{
    m_type = INT_TYPE;
    m_intValue = value;
}

/**
 * json-value for float
 */
JsonValue::JsonValue(const float value)
{
    m_type = FLOAT_TYPE;
    m_floatValue = value;
}

/**
 * @brief JsonValue::~JsonValue
 */
JsonValue::~JsonValue()
{
    //std::cout<<"JsonValue: "<<this<<std::endl;
}

/**
 * fake-method which exist here only for the inheritance and returns everytime nullptr
 */
JsonItem*
JsonValue::operator[](const std::string)
{
    return nullptr;
}

/**
 * fake-method which exist here only for the inheritance and returns everytime nullptr
 */
JsonItem*
JsonValue::operator[](const uint32_t)
{
    return nullptr;
}

/**
 * fake-method which exist here only for the inheritance and returns everytime nullptr
 */
JsonItem*
JsonValue::get(const std::string)
{
    return nullptr;
}

/**
 * fake-method which exist here only for the inheritance and returns everytime nullptr
 */
JsonItem*
JsonValue::get(const uint32_t)
{
    return nullptr;
}

/**
 * fake-method which exist here only for the inheritance and returns everytime 0
 */
uint32_t
JsonValue::getSize() const
{
    return 0;
}

/**
 * fake-method which exist here only for the inheritance and returns everytime false
 */
bool
JsonValue::remove(const std::string&)
{
    return false;
}

/**
 * fake-method which exist here only for the inheritance and returns everytime false
 */
bool
JsonValue::remove(const uint32_t)
{
    return false;
}

/**
 * @brief JsonValue::copy
 * @return
 */
JsonItem*
JsonValue::copy()
{
    JsonValue *tempItem = nullptr;
    if(m_type == STRING_TYPE) {
        tempItem = new JsonValue(m_stringValue);
    }
    if(m_type == INT_TYPE) {
        tempItem = new JsonValue(m_intValue);
    }
    if(m_type == FLOAT_TYPE) {
        tempItem = new JsonValue(m_floatValue);
    }
    return tempItem;
}

/**
 * prints the content of the object
 */
std::string
JsonValue::print(std::string *output,
                 const bool indent,
                 const uint32_t level)
{
    std::string out = "";
    if(output == nullptr) {
        output = &out;
    }

    if(m_type == STRING_TYPE)
    {
        output->append("\"");
        output->append(m_stringValue);
        output->append("\"");
    }
    if(m_type == INT_TYPE) {
        output->append(std::to_string(m_intValue));
    }
    if(m_type == FLOAT_TYPE) {
        output->append(std::to_string(m_floatValue));
    }

    return out;
}

/**
 * writes a new string into the json-value
 */
void
JsonValue::setValue(const std::string &item)
{
    m_type = STRING_TYPE;
    m_intValue = 0;
    m_floatValue = 0.0f;
    m_stringValue = item;
}

/**
 * writes a new integer into the json-value
 */
void
JsonValue::setValue(const int &item)
{
    m_type = INT_TYPE;
    m_stringValue = "";
    m_floatValue = 0.0f;
    m_intValue = item;
}

/**
 * writes a new integer into the json-value
 */
void
JsonValue::setValue(const float &item)
{
    m_type = FLOAT_TYPE;
    m_stringValue = "";
    m_intValue = 0;
    m_floatValue = item;
}

//===================================================================
// JsonObject
//===================================================================

/**
 * object for key-value-pairs
 */
JsonObject::JsonObject()
{
    m_type = OBJECT_TYPE;
}

/**
 * delete all items in the key-value-list
 */
JsonObject::~JsonObject()
{
    //std::cout<<"JsonObject: "<<this<<std::endl;
    std::map<std::string, JsonItem*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        JsonItem* tempItem = it->second;
        delete tempItem;
    }
    m_objects.clear();
}

/**
 * get a specific item of the object
 *
 * @return nullptr if index in key is to high, else object
 */
JsonItem*
JsonObject::operator[](const std::string key)
{
    return get(key);
}

/**
 * get a specific item of the object
 *
 * @return nullptr if index is to high, else object
 */
JsonItem*
JsonObject::operator[](const uint32_t index)
{
    return get(index);
}

/**
 * get a specific item of the object
 *
 * @return nullptr if index in key is to high, else object
 */
JsonItem*
JsonObject::get(const std::string key)
{
    std::map<std::string, JsonItem*>::iterator it;
    it = m_objects.find(key);

    if(it != m_objects.end()) {
        return it->second;
    }

    return nullptr;
}

/**
 * get a specific item of the object
 *
 * @return nullptr if index is to high, else object
 */
JsonItem*
JsonObject::get(const uint32_t index)
{
    if(m_objects.size() <= index) {
        return nullptr;
    }

    uint32_t counter = 0;
    std::map<std::string, JsonItem*>::iterator it;
    for(it = m_objects.begin();
        it != m_objects.end();
        it++)
    {
        if(counter == index) {
            return it->second;
        }
        counter++;
    }

    return nullptr;
}

/**
 * getter for the number of elements in the key-value-list
 *
 * @return number of elements in the key-value-list
 */
uint32_t
JsonObject::getSize() const
{
    return static_cast<uint32_t>(m_objects.size());
}

/**
 * get list of keys of the objects-map
 *
 * @return string-list with the keys of the map
 */
std::vector<std::string>
JsonObject::getKeys()
{
    std::vector<std::string> result;
    std::map<std::string, JsonItem*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        result.push_back(it->first);
    }
    return result;
}

/**
 * @brief JsonObject::getValues
 * @return
 */
std::vector<JsonItem *>
JsonObject::getValues()
{
    std::vector<JsonItem*> result;
    std::map<std::string, JsonItem*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        result.push_back(it->second);
    }
    return result;
}

/**
 * @brief JsonObject::getComplete
 * @return
 */
std::map<std::string, JsonItem *>
JsonObject::getComplete()
{
    return m_objects;
}

/**
 * check if a key is in the object-map
 *
 * @return false if the key doesn't exist, else true
 */
bool
JsonObject::contains(const std::string &key)
{
    std::map<std::string, JsonItem*>::iterator it;
    it = m_objects.find(key);

    if(it != m_objects.end())
    {
        return true;
    }
    return false;
}

/**
 * TODO
 */
std::string
JsonObject::getString(const std::string &key)
{
    JsonItem* abstractValue = get(key);
    return abstractValue->toString();
}

/**
 * TODO
 */
int
JsonObject::getInt(const std::string &key)
{
    JsonItem* abstractValue = get(key);
    return abstractValue->toInt();
}

/**
 * TODO
 */
float
JsonObject::getFloat(const std::string &key)
{
    JsonItem* abstractValue = get(key);
    return abstractValue->toFloat();
}

/**
 * remove an item from the key-value-list
 *
 * @return false if the key doesn't exist, else true
 */
bool
JsonObject::remove(const std::string &key)
{
    std::map<std::string, JsonItem*>::iterator it;
    it = m_objects.find(key);

    if(it != m_objects.end())
    {
        m_objects.erase(it);
        return true;
    }

    return false;
}

/**
 * remove an item from the object
 *
 * @return false if index is to high, else true
 */
bool
JsonObject::remove(const uint32_t index)
{
    if(m_objects.size() <= index) {
        return false;
    }

    uint32_t counter = 0;
    std::map<std::string, JsonItem*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        if(counter == index)
        {
            m_objects.erase(it);
            return true;
        }
        counter++;
    }
    return false;
}

/**
 * @brief JsonObject::copy
 * @return
 */
JsonItem*
JsonObject::copy()
{
    JsonObject* tempItem = new JsonObject();
    std::map<std::string, JsonItem*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        tempItem->insert(it->first, it->second->copy());
    }
    return tempItem;
}

/**
 * prints the content of the object
 */
std::string
JsonObject::print(std::string *output,
                  const bool indent,
                  const uint32_t level)
{
    std::string out = "";
    if(output == nullptr) {
        output = &out;
    }

    bool firstPring = false;
    output->append("{");

    for(uint8_t typeCounter = 1; typeCounter < 6; typeCounter++)
    {
        std::map<std::string, JsonItem*>::iterator it;
        for(it = m_objects.begin(); it != m_objects.end(); it++)
        {
            if(it->second != nullptr
                    && it->second->getType() != typeCounter)
            {
                continue;
            }

            if(firstPring) {
                output->append(",");
            }
            firstPring = true;

            addIndent(output, indent, level+1);

            output->append("\"");
            output->append(it->first);
            output->append("\"");
            output->append(":");

            if(indent == true) {
                output->append(" ");
            }

            // TODO: add unit-tests for nullptr-case
            if(it->second == nullptr) {
                output->append("NULL");
            } else {
                it->second->print(output, indent, level+1);
            }
        }
    }

    addIndent(output, indent, level);
    output->append("}");

    return out;
}

/**
 * add new key-value-pair to the object
 *
 * @return false if key already exist, else true
 */
bool
JsonObject::insert(const std::string &key,
                   JsonItem *value,
                   bool force)
{


    std::map<std::string, JsonItem*>::iterator it;
    it = m_objects.find(key);

    if((it != m_objects.end())
            && force == false)
    {
        return false;
    }

    if(it != m_objects.end()) {
        it->second = value;
    } else {
        m_objects.insert(std::pair<std::string, JsonItem*>(key, value));
    }
    return true;
}

//===================================================================
// JsonArray
//===================================================================

/**
 * array for items in json-style
 */
JsonArray::JsonArray()
{
    m_type = ARRAY_TYPE;
}

/**
 * delete all items in the array
 */
JsonArray::~JsonArray()
{
    //std::cout<<"JsonArray: "<<this<<std::endl;
    for(uint32_t i = 0; i < m_array.size(); i++)
    {
        JsonItem* tempItem = m_array[i];
        delete tempItem;
    }
    m_array.clear();
}

/**
 * get a specific item of the array
 *
 * @return nullptr if index in key is to high, else true
 */
JsonItem*
JsonArray::operator[](const std::string key)
{
    return get(key);
}

/**
 * get a specific item of the array
 *
 * @return nullptr if index is to high, else true
 */
JsonItem*
JsonArray::operator[](const uint32_t index)
{
    return get(index);
}

/**
 * get a specific item of the array
 *
 * @return nullptr if index in key is to high, else object
 */
JsonItem*
JsonArray::get(const std::string key)
{
    const uint32_t index = static_cast<uint32_t>(std::stoi(key));
    if(m_array.size() <= index) {
        return nullptr;
    }

    return m_array[index];
}

/**
 * get a specific item of the array
 *
 * @return nullptr if index is to high, else the object
 */
JsonItem*
JsonArray::get(const uint32_t index)
{
    if(m_array.size() <= index) {
        return nullptr;
    }

    return m_array[index];
}

/**
 * getter for the number of elements in the array
 *
 * @return number of elements in the array
 */
uint32_t
JsonArray::getSize() const
{
    return static_cast<uint32_t>(m_array.size());
}

/**
 * @brief JsonArray::getComplete
 * @return
 */
std::vector<JsonItem *>
JsonArray::getComplete()
{
    return m_array;
}

/**
 * remove an item from the array
 *
 * @return false if index in key is to high, else true
 */
bool
JsonArray::remove(const std::string &key)
{
    const uint32_t index = static_cast<uint32_t>(std::stoi(key));
    if(m_array.size() <= index) {
        return false;
    }
    m_array.erase(m_array.begin() + index);
    return true;
}

/**
 * remove an item from the array
 *
 * @return false if index is to high, else true
 */
bool
JsonArray::remove(const uint32_t index)
{
    if(m_array.size() <= index) {
        return false;
    }
    m_array.erase(m_array.begin() + index);
    return true;
}

/**
 * @brief JsonArray::copy
 * @return
 */
JsonItem*
JsonArray::copy()
{
    JsonArray* tempItem = new JsonArray();
    for(uint32_t i = 0; i < m_array.size(); i++)
    {
        tempItem->append(m_array[i]->copy());
    }
    return tempItem;
}

/**
 * prints the content of the object
 */
std::string
JsonArray::print(std::string *output,
                 const bool indent,
                 const uint32_t level)
{
    std::string out = "";
    if(output == nullptr) {
        output = &out;
    }

    output->append("[");
    addIndent(output, indent, level+1);

    std::vector<JsonItem*>::iterator it;
    for(it = m_array.begin(); it != m_array.end(); it++)
    {
        if(it != m_array.begin())
        {
            output->append(",");
            addIndent(output, indent, level+1);
        }

        if((*it) == nullptr) {
            continue;
        }

        (*it)->print(output, indent, level+1);
    }

    addIndent(output, indent, level);
    output->append("]");

    return out;
}

/**
 * add a new item to the array
 *
 * @return false, if new item-pointer is nullptr, else true
 */
bool
JsonArray::append(JsonItem *item)
{
    if(item == nullptr) {
        return false;
    }

    m_array.push_back(item);
    return true;
}


}  // namespace Json
}  // namespace Kitsune
