/**
 *  @file    jsonObjects.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Kitsune
{
namespace Json
{
class JsonArray;
class JsonObject;
class JsonValue;

//===================================================================
// JsonItem
//===================================================================
class JsonItem
{
public:
    virtual ~JsonItem();

    static JsonItem* parseString(const std::string &input);

    enum jsonTypes {
        UNINIT_TYPE = 0,
        VALUE_TYPE = 1,
        OBJECT_TYPE = 2,
        ARRAY_TYPE = 3
    };

    enum jsonValueTypes {
        UNINIT_VALUE_TYPE = 0,
        STRING_TYPE = 1,
        INT_TYPE = 2,
        FLOAT_TYPE = 3,
    };

    // getter
    virtual JsonItem* operator[](const std::string key) = 0;
    virtual JsonItem* operator[](const uint32_t index) = 0;
    virtual JsonItem* get(const std::string key) = 0;
    virtual JsonItem* get(const uint32_t index) = 0;
    virtual uint32_t getSize() const = 0;

    // delete
    virtual bool remove(const std::string &key) = 0;
    virtual bool remove(const uint32_t index) = 0;

    // output
    virtual JsonItem* copy() = 0;
    virtual std::string print(std::string *output=nullptr,
                              bool indent=false,
                              uint32_t step=0) = 0;

    jsonTypes getType() const;
    bool isValue() const;
    bool isObject() const;
    bool isArray() const;

    JsonArray* toArray();
    JsonObject* toObject();
    JsonValue* toValue();

    std::string toString();
    int toInt();
    float toFloat();

protected:
    jsonTypes m_type = UNINIT_TYPE;
    jsonValueTypes m_valueType = UNINIT_VALUE_TYPE;

    void addIndent(std::string *output,
                   const bool indent,
                   const uint32_t level);
};

//===================================================================
// JsonValue
//===================================================================
class JsonValue : public JsonItem
{
public:
    JsonValue();
    JsonValue(const std::string &text);
    JsonValue(const int value);
    JsonValue(const float value);
    ~JsonValue();

    // setter
    jsonValueTypes getValueType();
    void setValue(const std::string &item);
    void setValue(const int &item);
    void setValue(const float &item);

    // getter
    JsonItem* operator[](const std::string);
    JsonItem* operator[](const uint32_t);
    JsonItem* get(const std::string);
    JsonItem* get(const uint32_t);
    uint32_t getSize() const;

    // delete
    bool remove(const std::string&);
    bool remove(const uint32_t);

    // output
    JsonItem* copy();
    std::string print(std::string *output=nullptr,
                      const bool indent=false,
                      const uint32_t level=0);

    // content
    std::string m_stringValue = "";
    int m_intValue = 0;
    float m_floatValue = 0.0f;
};

//===================================================================
// JsonObject
//===================================================================
class JsonObject : public JsonItem
{
public:
    JsonObject();
    ~JsonObject();

    // add
    bool insert(const std::string &key,
                JsonItem* value,
                bool force = false);

    // getter
    JsonItem* operator[](const std::string key);
    JsonItem* operator[](const uint32_t index);
    JsonItem* get(const std::string key);
    JsonItem* get(const uint32_t index);
    uint32_t getSize() const;

    std::vector<std::string> getKeys();
    std::vector<JsonItem*> getValues();
    std::map<std::string, JsonItem*> getComplete();
    bool contains(const std::string &key);

    std::string getString(const std::string &key);
    int getInt(const std::string &key);
    float getFloat(const std::string &key);

    // delete
    bool remove(const std::string &key);
    bool remove(const uint32_t index);

    // output
    JsonItem* copy();
    std::string print(std::string *output=nullptr,
                      const bool indent=false,
                      const uint32_t level=0);

    // content
    std::map<std::string, JsonItem*> m_objects;
};

//===================================================================
// JsonArray
//===================================================================
class JsonArray : public JsonItem
{
public:
    JsonArray();
    ~JsonArray();

    // add
    bool append(JsonItem* item);

    // getter
    JsonItem* operator[](const std::string key);
    JsonItem* operator[](const uint32_t index);
    JsonItem* get(const std::string key);
    JsonItem* get(const uint32_t index);
    uint32_t getSize() const;

    std::vector<JsonItem*> getComplete();

    // delete
    bool remove(const std::string &key);
    bool remove(const uint32_t index);

    // output
    JsonItem* copy();
    std::string print(std::string *output,
                      const bool indent=false,
                      const uint32_t level=0);

    // content
    std::vector<JsonItem*> m_array;
};


}  // namespace Json
}  // namespace Kitsune

#endif // JSONOBJECT_H
