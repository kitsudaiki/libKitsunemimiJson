/**
 *  @file    jsonItem.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonItems.h"
#include <iostream>
#include <json_parsing/jsonParserInterface.h>

namespace Kitsune
{
namespace Json
{

/**
 * @brief JsonItem::JsonItem
 */
JsonItem::JsonItem()
{
}

/**
 * @brief JsonItem::JsonItem
 * @param type
 */
JsonItem::JsonItem(JsonItem::jsonTypes type)
{
    m_type = type;
    switch(m_type)
    {
        case STRING_TYPE:
            m_content.stringValue = "";
            break;
        case INT_TYPE:
            m_content.intValue = 0;
            break;
        case FLOAT_TYPE:
            m_content.floatValue = 0.0f;
            break;
        case OBJECT_TYPE:
            m_content.object = std::map<std::string, JsonItem>();
            break;
        case ARRAY_TYPE:
            m_content.array = std::vector<JsonItem>();
            break;
        default:
            break;
    }
}

/**
 * @brief JsonItem::operator =
 * @param other
 * @return
 */
JsonItem&
JsonItem::operator=(const JsonItem& other)
{
    m_type = other.m_type;
    switch(m_type)
    {
        case STRING_TYPE:
            m_content.stringValue = other.m_content.stringValue;
            break;
        case INT_TYPE:
            m_content.intValue = other.m_content.intValue;
            break;
        case FLOAT_TYPE:
            m_content.floatValue = other.m_content.floatValue;
            break;
        case OBJECT_TYPE:
            m_content.object = other.m_content.object;
            break;
        case ARRAY_TYPE:
            m_content.array = other.m_content.array;
            break;
        default:
            break;
    }
    return *this;
}

/**
 * @brief JsonItem::JsonItem
 * @param other
 */
JsonItem::JsonItem(const JsonItem &other)
{
    m_type = other.m_type;
    switch(m_type)
    {
        case STRING_TYPE:
            m_content.stringValue = other.m_content.stringValue;
            break;
        case INT_TYPE:
            m_content.intValue = other.m_content.intValue;
            break;
        case FLOAT_TYPE:
            m_content.floatValue = other.m_content.floatValue;
            break;
        case OBJECT_TYPE:
            m_content.object = other.m_content.object;
            break;
        case ARRAY_TYPE:
            m_content.array = other.m_content.array;
            break;
        default:
            break;
    }
}

/**
 * @brief JsonItem::JsonItem
 * @param text
 */
JsonItem::JsonItem(const std::string &text)
{
    m_type = STRING_TYPE;
    m_content.stringValue = text;
}

/**
 * @brief JsonItem::JsonItem
 * @param value
 */
JsonItem::JsonItem(const int value)
{
    m_type = INT_TYPE;
    m_content.intValue = value;
}

/**
 * @brief JsonItem::JsonItem
 * @param value
 */
JsonItem::JsonItem(const float value)
{
    m_type = FLOAT_TYPE;
    m_content.floatValue = value;
}

/**
 * @brief JsonItem::~JsonItem
 */
JsonItem::~JsonItem()
{
}

/**
 * static-method which calls the parser to convert a json-formated string into a json-object-tree
 *
 * @return nullptr, if parsing was not successful, else the root-object of the new json-tree
 */
JsonItem
JsonItem::parseString(const std::string &input)
{
    JsonParserInterface parser;
    bool ret = parser.parse(input);
    if(ret == false) {
        return JsonItem();
    }
    return parser.getOutput();
}

/**
 * @brief JsonItem::setValue
 * @param item
 */
void
JsonItem::setValue(const std::string &item)
{
    m_type = STRING_TYPE;
    m_content.stringValue = item;
}

/**
 * @brief JsonItem::setValue
 * @param item
 */
void
JsonItem::setValue(const int &item)
{
    m_type = INT_TYPE;
    m_content.intValue = item;
}

/**
 * @brief JsonItem::setValue
 * @param item
 */
void
JsonItem::setValue(const float &item)
{
    m_type = FLOAT_TYPE;
    m_content.floatValue = item;
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
                 JsonItem value,
                 bool force)
{
    if(m_type == OBJECT_TYPE)
    {
        std::map<std::string, JsonItem>::iterator it;
        it = m_content.object.find(key);

        if(it != m_content.object.end()
                && force == false)
        {
            return false;
        }

        if(it != m_content.object.end()) {
            it->second = value;
        } else {
            m_content.object.insert(std::pair<std::string, JsonItem>(key, value));
        }

        return true;
    }

    return false;
}

/**
 * @brief JsonItem::append
 * @param item
 * @return
 */
bool
JsonItem::append(JsonItem item)
{
    if(m_type == ARRAY_TYPE)
    {
        m_content.array.push_back(item);
        return true;
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
    return get(key);
}

/**
 * @brief JsonItem::operator []
 * @param index
 * @return
 */
JsonItem
JsonItem::operator[](const uint32_t index)
{
    return get(index);
}

/**
 * @brief JsonItem::get
 * @param key
 * @return
 */
JsonItem
JsonItem::get(const std::string key)
{
    if(m_type == OBJECT_TYPE)
    {
        std::map<std::string, JsonItem>::iterator it;
        it = m_content.object.find(key);

        if(it != m_content.object.end()) {
            return it->second;
        }
    }
    return JsonItem();
}

/**
 * @brief JsonItem::get
 * @param index
 * @return
 */
JsonItem
JsonItem::get(const uint32_t index)
{
    if(m_type == ARRAY_TYPE)
    {
        if(m_content.array.size() <= index) {
            return JsonItem();
        }
        return m_content.array[index];
    }

    if(m_type == OBJECT_TYPE)
    {
        if(m_content.object.size() <= index) {
            return JsonItem();
        }

        uint32_t counter = 0;
        std::map<std::string, JsonItem>::iterator it;
        for(it = m_content.object.begin();
            it != m_content.object.end();
            it++)
        {
            if(counter == index) {
                return it->second;
            }
            counter++;
        }
    }

    return JsonItem();
}

/**
 * @brief JsonItem::getSize
 * @return
 */
uint64_t
JsonItem::getSize() const
{
    if(m_type == ARRAY_TYPE) {
        return m_content.array.size();
    }

    if(m_type == OBJECT_TYPE)
    {

    }
}

/**
 * check if a key is in the object-map
 *
 * @return false if the key doesn't exist, else true
 */
bool
JsonItem::contains(const std::string &key)
{
    if(m_type == OBJECT_TYPE)
    {
        std::map<std::string, JsonItem>::iterator it;
        it = m_content.object.find(key);

        if(it != m_content.object.end()) {
            return true;
        }
    }

    return false;
}

/**
 * get list of keys of the objects-map
 *
 * @return string-list with the keys of the map
 */
std::vector<std::string>
JsonItem::getKeys()
{
    if(m_type == OBJECT_TYPE)
    {
        std::vector<std::string> result;
        std::map<std::string, JsonItem>::iterator it;

        for(it = m_content.object.begin(); it != m_content.object.end(); it++)
        {
            result.push_back(it->first);
        }

        return result;
    }

    return std::vector<std::string>();
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
 * request the string of the json-value, if it is from string-type
 *
 * @return string of the json-value, if json-value is from string-type, else empty string
 */
std::string
JsonItem::toString()
{
    if(m_type == STRING_TYPE)
    {
        return m_content.stringValue;
    }
    if(m_type == INT_TYPE)
    {
        return std::to_string(m_content.intValue);
    }
    if(m_type == FLOAT_TYPE)
    {
        return std::to_string(m_content.floatValue);
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
    if(m_type == INT_TYPE) {
        return m_content.intValue;
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
    if(m_type == FLOAT_TYPE) {
        return m_content.floatValue;
    }

    return 0.0f;
}

/**
 * @brief JsonItem::remove
 * @param key
 * @return
 */
bool
JsonItem::remove(const std::string &key)
{
    std::map<std::string, JsonItem>::iterator it;
    it = m_content.object.find(key);

    if(it != m_content.object.end())
    {
        m_content.object.erase(it);
        return true;
    }

    return false;
}

/**
 * @brief JsonItem::remove
 * @param index
 * @return
 */
bool
JsonItem::remove(const uint64_t index)
{
    if(m_content.array.size() <= index) {
        return false;
    }
    m_content.array.erase(m_content.array.begin() + index);
    return true;
}

/**
 * @brief JsonItem::print
 * @param output
 * @param indent
 * @param level
 */
void
JsonItem::print(std::string *output,
                bool indent,
                uint32_t level)
{
    switch(m_type)
    {
        case STRING_TYPE:
        {
            output->append("\"");
            output->append(m_content.stringValue);
            output->append("\"");
            break;
        }
        case INT_TYPE:
        {
            output->append(std::to_string(m_content.intValue));
            break;
        }
        case FLOAT_TYPE:
        {
            output->append(std::to_string(m_content.floatValue));
            break;
        }
        case OBJECT_TYPE:
        {
            bool firstPring = false;
            output->append("{");

            for(uint8_t typeCounter = 1; typeCounter < 6; typeCounter++)
            {
                std::map<std::string, JsonItem>::iterator it;
                for(it = m_content.object.begin(); it != m_content.object.end(); it++)
                {
                    if(it->second.getType() != typeCounter)
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

                    it->second.print(output, indent, level+1);
                }
            }

            addIndent(output, indent, level);
            output->append("}");
            break;
        }
        case ARRAY_TYPE:
        {
            output->append("[");
            addIndent(output, indent, level+1);

            std::vector<JsonItem>::iterator it;
            for(it = m_content.array.begin(); it != m_content.array.end(); it++)
            {
                if(it != m_content.array.begin())
                {
                    output->append(",");
                    addIndent(output, indent, level+1);
                }

                (*it).print(output, indent, level+1);
            }

            addIndent(output, indent, level);
            output->append("]");
            break;
        }
        default:
            break;
    }
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

}  // namespace Json
}  // namespace Kitsune
