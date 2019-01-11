#include "jsonObjects.h"

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
JsonValue::operator[](const std::string &key)
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
 * @brief JsonValue::print
 * @param output
 */
void
JsonValue::print(std::string *output)
{
    if(m_type == STRING_TYPE) {
        output->append(m_stringValue);
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
JsonObject::operator[](const std::string &key)
{
    std::map<std::string, AbstractJson*>::iterator it;
    it = m_objects.find(key);

    if(it != m_objects.end()) {
        return it->second;
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
 * @brief JsonObject::print
 * @param output
 */
void
JsonObject::print(std::string *output)
{
    output->append(" { ");
    std::map<std::string, AbstractJson*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        output->append(it->first);
        output->append(" : ");
        it->second->print(output);
    }
    output->append(" } ");
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
    for(uint32_t i = 0; i < m_array.size(); i++) {
        delete m_array[i];
    }
    m_array.clear();
}

/**
 * @brief JsonArray::operator []
 * @param key
 * @return
 */
AbstractJson*
JsonArray::operator[](const std::string &key)
{
    const uint32_t index = static_cast<uint32_t>(std::stoi(key));
    if(m_array.size() < index) {
        m_array[index];
    }

    return nullptr;
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
 * @brief JsonArray::print
 * @param output
 */
void
JsonArray::print(std::string *output)
{
    output->append(" [ ");
    std::vector<AbstractJson*>::iterator it;
    for(it = m_array.begin(); it != m_array.end(); it++)
    {
        (*it)->print(output);
    }
    output->append(" ] ");
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
