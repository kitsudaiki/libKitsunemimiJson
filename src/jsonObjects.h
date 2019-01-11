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
    virtual ~AbstractJson() = 0;

    virtual AbstractJson* operator[](const std::string &key) = 0;
    virtual uint32_t getSize() const = 0;

    enum jsonTypes {
        UNINIT_TYPE = 0,
        STRING_TYPE = 1,
        INT_TYPE = 2,
        ARRAY_TYPE = 3,
        OBJECT_TYPE = 4
    };

    jsonTypes getType() const;

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
    JsonValue(const int values);
    ~JsonValue() {}

    AbstractJson* operator[](const std::string &key);
    uint32_t getSize() const;

    void setValue(const std::string &item);
    void setValue(const int &item);

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

    AbstractJson* operator[](const std::string &key);
    uint32_t getSize() const;

    bool insert(const std::string &key,
                AbstractJson* value);

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

    AbstractJson* operator[](const std::string &key);
    uint32_t getSize() const;

    bool append(AbstractJson* item);

private:
    std::vector<AbstractJson*> m_array;
};


}  // namespace Json
}  // namespace Kitsune

#endif // JSONOBJECT_H
