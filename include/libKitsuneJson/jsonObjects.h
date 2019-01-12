/**
 *  @file    jsonObjects.h
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
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

//===================================================================
// AbstractJson
//===================================================================
class AbstractJson
{
public:
    AbstractJson();

    static AbstractJson* parseString(const std::string &input);
    virtual ~AbstractJson() {}

    enum jsonTypes {
        UNINIT_TYPE = 0,
        STRING_TYPE = 1,
        INT_TYPE = 2,
        ARRAY_TYPE = 3,
        OBJECT_TYPE = 4
    };

    // getter
    virtual AbstractJson* operator[](const std::string key) = 0;
    virtual AbstractJson* operator[](const uint32_t index) = 0;
    virtual AbstractJson* get(const std::string key) = 0;
    virtual AbstractJson* get(const uint32_t index) = 0;
    virtual uint32_t getSize() const = 0;
    jsonTypes getType() const;

    // delete
    virtual bool remove(const std::string &key) = 0;
    virtual bool remove(const uint32_t index) = 0;

    // output
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
    JsonValue(const std::string &text);
    JsonValue(const int value);
    ~JsonValue() {}

    // setter
    void setValue(const std::string &item);
    void setValue(const int &item);

    // getter
    AbstractJson* operator[](const std::string key);
    AbstractJson* operator[](const uint32_t index);
    AbstractJson* get(const std::string key);
    AbstractJson* get(const uint32_t index);
    std::string getString() const;
    int getInt() const;
    uint32_t getSize() const;

    // delete
    bool remove(const std::string &key);
    bool remove(const uint32_t index);

    // output
    void print(std::string *output);

private:
    std::string m_stringValue = "";
    int m_intValue = 0;
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
                AbstractJson* value);

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
    void print(std::string *output);

private:
    std::vector<AbstractJson*> m_array;
};


}  // namespace Json
}  // namespace Kitsune

#endif // JSONOBJECT_H
