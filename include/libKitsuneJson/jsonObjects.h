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
// AbstractJson
//===================================================================
class AbstractJson
{
public:
    virtual ~AbstractJson();

    static AbstractJson* parseString(const std::string &input);

    enum jsonTypes {
        UNINIT_TYPE = 0,
        STRING_TYPE = 1,
        INT_TYPE = 2,
        FLOAT_TYPE = 3,
        ARRAY_TYPE = 4,
        OBJECT_TYPE = 5
    };

    // getter
    virtual AbstractJson* operator[](const std::string key) = 0;
    virtual AbstractJson* operator[](const uint32_t index) = 0;
    virtual AbstractJson* get(const std::string key) = 0;
    virtual AbstractJson* get(const uint32_t index) = 0;
    virtual uint32_t getSize() const = 0;
    jsonTypes getType() const;

    JsonArray* toArray();
    JsonObject* toObject();
    JsonValue* toValue();

    // delete
    virtual bool remove(const std::string &key) = 0;
    virtual bool remove(const uint32_t index) = 0;

    // output
    virtual AbstractJson* copy() = 0;
    virtual void print(std::string *output) = 0;

protected:
    jsonTypes m_type = UNINIT_TYPE;
};

//===================================================================
// JsonValue
//===================================================================
class JsonValue : public AbstractJson
{
public:
    JsonValue();
    JsonValue(const std::string &text);
    JsonValue(const int value);
    ~JsonValue();

    // setter
    void setValue(const std::string &item);
    void setValue(const int &item);
    void setValue(const float &item);

    // getter
    AbstractJson* operator[](const std::string);
    AbstractJson* operator[](const uint32_t);
    AbstractJson* get(const std::string);
    AbstractJson* get(const uint32_t);
    std::string getString() const;
    int getInt() const;
    float getFloat() const;
    uint32_t getSize() const;

    // delete
    bool remove(const std::string&);
    bool remove(const uint32_t);

    // output
    AbstractJson* copy();
    void print(std::string *output);

private:
    std::string m_stringValue = "";
    int m_intValue = 0;
    float m_floatValue = 0.0f;
};

//===================================================================
// JsonObject
//===================================================================
class JsonObject : public AbstractJson
{
public:
    JsonObject();
    ~JsonObject();

    // add
    bool insert(const std::string &key,
                AbstractJson* value,
                bool force = false);

    // getter
    AbstractJson* operator[](const std::string key);
    AbstractJson* operator[](const uint32_t index);
    AbstractJson* get(const std::string key);
    AbstractJson* get(const uint32_t index);
    uint32_t getSize() const;
    std::vector<std::string> getKeys();
    bool contains(const std::string &key);

    // delete
    bool remove(const std::string &key);
    bool remove(const uint32_t index);

    // output
    AbstractJson* copy();
    void print(std::string *output);

private:
    std::map<std::string, AbstractJson*> m_objects;
};

//===================================================================
// JsonArray
//===================================================================
class JsonArray : public AbstractJson
{
public:
    JsonArray();
    ~JsonArray();

    // add
    bool append(AbstractJson* item);

    // getter
    AbstractJson* operator[](const std::string key);
    AbstractJson* operator[](const uint32_t index);
    AbstractJson* get(const std::string key);
    AbstractJson* get(const uint32_t index);
    uint32_t getSize() const;

    // delete
    bool remove(const std::string &key);
    bool remove(const uint32_t index);

    // output
    AbstractJson* copy();
    void print(std::string *output);

private:
    std::vector<AbstractJson*> m_array;
};


}  // namespace Json
}  // namespace Kitsune

#endif // JSONOBJECT_H
