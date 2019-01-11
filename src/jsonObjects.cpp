#include "jsonObjects.h"

namespace Kitsune
{
namespace Json
{

//===================================================================
// AbstractJson
//===================================================================
AbstractJson::AbstractJson()
{

}

AbstractJson::jsonTypes AbstractJson::getType() const
{
    return m_type;
}

//===================================================================
// JsonValue
//===================================================================
JsonValue::JsonValue(const std::string &text)
{
    m_type = STRING_TYPE;
    m_stringValue = text;
}

JsonValue::JsonValue(const int values)
{
    m_type = INT_TYPE;
    m_intValue = values;
}

AbstractJson*
JsonValue::operator[](const std::string &key)
{
    return nullptr;
}

uint32_t
JsonValue::getSize() const
{
    return 0;
}

void
JsonValue::setValue(const std::string &item)
{
    m_type = STRING_TYPE;
    m_intValue = 0;
    m_stringValue = item;
}

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
JsonObject::JsonObject()
{
    m_type = OBJECT_TYPE;
}

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

uint32_t
JsonObject::getSize() const
{
    return static_cast<uint32_t>(m_objects.size());
}

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
JsonArray::JsonArray()
{
    m_type = ARRAY_TYPE;
}

JsonArray::~JsonArray()
{
    for(uint32_t i = 0; i < m_array.size(); i++) {
        delete m_array[i];
    }
    m_array.clear();
}

AbstractJson*
JsonArray::operator[](const std::string &key)
{
    const uint32_t index = static_cast<uint32_t>(std::stoi(key));
    if(m_array.size() < index) {
        m_array[index];
    }

    return nullptr;
}

uint32_t
JsonArray::getSize() const
{
    return static_cast<uint32_t>(m_array.size());
}

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
