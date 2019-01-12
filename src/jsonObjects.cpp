/**
 *  @file    jsonObjects.cpp
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#include "jsonObjects.h"
#include <iostream>
#include <json_parsing/jsonParserInterface.h>

namespace Kitsune
{
namespace Json
{

//===================================================================
// AbstractJson
//===================================================================

/**
 * @brief AbstractJson::AbstractJson
 */
AbstractJson::AbstractJson()
{}

/**
 * @brief AbstractJson::parseString
 * @param input
 * @return
 */
AbstractJson*
AbstractJson::parseString(const std::string &input)
{
    JsonParserInterface parser;
    bool ret = parser.parse(input);
    if(ret == false) {
        return nullptr;
    }
    return parser.getOutput();
}

/**
 * @brief AbstractJson::getType
 * @return
 */
AbstractJson::jsonTypes AbstractJson::getType() const
{
    return m_type;
}

//===================================================================
// JsonValue
//===================================================================

/**
 * @brief JsonValue::JsonValue
 * @param text
 */
JsonValue::JsonValue(const std::string &text)
{
    m_type = STRING_TYPE;
    m_stringValue = text;
}

/**
 * @brief JsonValue::JsonValue
 * @param values
 */
JsonValue::JsonValue(const int values)
{
    m_type = INT_TYPE;
    m_intValue = values;
}

/**
 * @brief JsonValue::operator []
 * @param key
 * @return
 */
AbstractJson*
JsonValue::operator[](const std::string key)
{
    return nullptr;
}

/**
 * @brief JsonValue::operator []
 * @param index
 * @return
 */
AbstractJson*
JsonValue::operator[](const uint32_t index)
{
    return nullptr;
}

/**
 * @brief JsonValue::get
 * @param key
 * @return
 */
AbstractJson*
JsonValue::get(const std::string key)
{
    return nullptr;
}

/**
 * @brief JsonValue::get
 * @param index
 * @return
 */
AbstractJson*
JsonValue::get(const uint32_t index)
{
    return nullptr;
}

/**
 * @brief JsonValue::getSize
 * @return
 */
uint32_t
JsonValue::getSize() const
{
    return 0;
}

/**
 * @brief JsonValue::remove
 * @param key
 * @return
 */
bool
JsonValue::remove(const std::string &key)
{
    return false;
}

/**
 * @brief JsonValue::remove
 * @param index
 * @return
 */
bool
JsonValue::remove(const uint32_t index)
{
    return false;
}

/**
 * @brief JsonValue::print
 * @param output
 */
void
JsonValue::print(std::string *output)
{
    if(m_type == STRING_TYPE) {
        output->append("\"");
        output->append(m_stringValue);
        output->append("\"");
    } else {
        output->append(std::to_string(m_intValue));
    }
}

/**
 * @brief JsonValue::setValue
 * @param item
 */
void
JsonValue::setValue(const std::string &item)
{
    m_type = STRING_TYPE;
    m_intValue = 0;
    m_stringValue = item;
}

/**
 * @brief JsonValue::setValue
 * @param item
 */
void
JsonValue::setValue(const int &item)
{
    m_type = INT_TYPE;
    m_stringValue = "";
    m_intValue = item;
}

/**
 * @brief JsonValue::getString
 * @return
 */
std::string JsonValue::getString() const
{
    if(m_type == STRING_TYPE) {
        return m_stringValue;
    }
    return "";
}

/**
 * @brief JsonValue::getInt
 * @return
 */
int JsonValue::getInt() const
{
    if(m_type == INT_TYPE) {
        return m_intValue;
    }
    return 0;
}

//===================================================================
// JsonObject
//===================================================================

/**
 * @brief JsonObject::JsonObject
 */
JsonObject::JsonObject()
{
    m_type = OBJECT_TYPE;
}

/**
 * @brief JsonObject::~JsonObject
 */
JsonObject::~JsonObject()
{
    // std::cout<<"destructor object"<<std::endl;
    std::map<std::string, AbstractJson*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        AbstractJson* value = it->second;
        delete value;
    }
    m_objects.clear();
}

/**
 * @brief JsonObject::operator []
 * @param key
 * @return
 */
AbstractJson*
JsonObject::operator[](const std::string key)
{
    return get(key);
}

/**
 * @brief JsonObject::operator []
 * @param index
 * @return
 */
AbstractJson*
JsonObject::operator[](const uint32_t index)
{
    return get(index);
}

/**
 * @brief JsonObject::get
 * @param key
 * @return
 */
AbstractJson*
JsonObject::get(const std::string key)
{
    std::map<std::string, AbstractJson*>::iterator it;
    it = m_objects.find(key);

    if(it != m_objects.end()) {
        return it->second;
    }

    return nullptr;
}

/**
 * @brief JsonObject::get
 * @param index
 * @return
 */
AbstractJson*
JsonObject::get(const uint32_t index)
{
    if(m_objects.size() <= index) {
        return nullptr;
    }

    uint32_t counter = 0;
    std::map<std::string, AbstractJson*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        if(counter == index) {
            return it->second;
        }
        counter++;
    }

    return nullptr;
}

/**
 * @brief JsonObject::getSize
 * @return
 */
uint32_t
JsonObject::getSize() const
{
    return static_cast<uint32_t>(m_objects.size());
}

/**
 * @brief JsonObject::remove
 * @param key
 * @return
 */
bool
JsonObject::remove(const std::string &key)
{
    std::map<std::string, AbstractJson*>::iterator it;
    it = m_objects.find(key);

    if(it != m_objects.end())
    {
        m_objects.erase(it);
        return true;
    }

    return false;
}

/**
 * @brief JsonObject::remove
 * @param index
 * @return
 */
bool
JsonObject::remove(const uint32_t index)
{
    if(m_objects.size() <= index) {
        return false;
    }

    uint32_t counter = 0;
    std::map<std::string, AbstractJson*>::iterator it;
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
 * @brief JsonObject::print
 * @param output
 */
void
JsonObject::print(std::string *output)
{
    output->append("{");
    std::map<std::string, AbstractJson*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        if(it != m_objects.begin()) {
            output->append(",");
        }
        output->append("\"");
        output->append(it->first);
        output->append("\"");
        output->append(":");
        it->second->print(output);
    }
    output->append("}");
}

/**
 * @brief JsonObject::insert
 * @param key
 * @param value
 * @return
 */
bool
JsonObject::insert(const std::string &key,
                   AbstractJson *value)
{
    if(m_objects.find(key) != m_objects.end()) {
        return false;
    }

    m_objects.insert(std::pair<std::string, AbstractJson*>(key, value));
    return true;
}

//===================================================================
// JsonArray
//===================================================================

/**
 * @brief JsonArray::JsonArray
 */
JsonArray::JsonArray()
{
    m_type = ARRAY_TYPE;
}

/**
 * @brief JsonArray::~JsonArray
 */
JsonArray::~JsonArray()
{
    // std::cout<<"destructor array"<<std::endl;
    for(uint32_t i = 0; i < m_array.size(); i++)
    {
        AbstractJson* tempItem = m_array[i];
        delete tempItem;
    }
    m_array.clear();
}

/**
 * @brief JsonArray::operator []
 * @param key
 * @return
 */
AbstractJson*
JsonArray::operator[](const std::string key)
{
    return get(key);
}

/**
 * @brief JsonArray::operator []
 * @param index
 * @return
 */
AbstractJson*
JsonArray::operator[](const uint32_t index)
{
    return get(index);
}

/**
 * @brief JsonArray::get
 * @param key
 * @return
 */
AbstractJson*
JsonArray::get(const std::string key)
{
    const uint32_t index = static_cast<uint32_t>(std::stoi(key));
    if(m_array.size() <= index) {
        return nullptr;
    }

    return m_array[index];
}

/**
 * @brief JsonArray::get
 * @param index
 * @return
 */
AbstractJson*
JsonArray::get(const uint32_t index)
{
    if(m_array.size() <= index) {
        return nullptr;
    }

    return m_array[index];
}

/**
 * @brief JsonArray::getSize
 * @return
 */
uint32_t
JsonArray::getSize() const
{
    return static_cast<uint32_t>(m_array.size());
}

/**
 * @brief JsonArray::remove
 * @param key
 * @return
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
 * @brief JsonArray::remove
 * @param index
 * @return
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
 * @brief JsonArray::print
 * @param output
 */
void
JsonArray::print(std::string *output)
{
    output->append("[");
    std::vector<AbstractJson*>::iterator it;
    for(it = m_array.begin(); it != m_array.end(); it++)
    {
        if(it != m_array.begin()) {
            output->append(",");
        }
        (*it)->print(output);
    }
    output->append("]");
}

/**
 * @brief JsonArray::append
 * @param item
 * @return
 */
bool
JsonArray::append(AbstractJson *item)
{
    if(item == nullptr) {
        return false;
    }

    m_array.push_back(item);
    return true;
}


}  // namespace Json
}  // namespace Kitsune
