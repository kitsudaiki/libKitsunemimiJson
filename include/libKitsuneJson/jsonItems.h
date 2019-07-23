/**
 *  @file    jsonItem.h
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
    union jsonContent {
        int intValue;
        float floatValue;
        std::string stringValue;
        std::vector<JsonItem> array;
        std::map<std::string, JsonItem> object;

        jsonContent() {}
        ~jsonContent() {}
    };

public:
    enum jsonTypes {
        UNINIT_TYPE = 0,
        STRING_TYPE = 1,
        INT_TYPE = 2,
        FLOAT_TYPE = 3,
        OBJECT_TYPE = 4,
        ARRAY_TYPE = 5
    };

    JsonItem();
    JsonItem(jsonTypes type);
    JsonItem(const JsonItem &other);
    JsonItem &operator =(const JsonItem &other);

    JsonItem(const std::string &text);
    JsonItem(const int value);
    JsonItem(const float value);

    ~JsonItem();

    static JsonItem parseString(const std::string &input);


    // add and set
    void setValue(const std::string &item);
    void setValue(const int &item);
    void setValue(const float &item);
    bool insert(const std::string &key,
                JsonItem value,
                bool force = false);
    bool append(JsonItem item);

    // getter
    JsonItem operator[](const std::string key);
    JsonItem operator[](const uint32_t index);
    JsonItem get(const std::string key);
    JsonItem get(const uint32_t index);
    uint64_t getSize() const;
    bool contains(const std::string &key);
    std::vector<std::string> getKeys();

    jsonTypes getType() const;
    bool isValue() const;
    bool isObject() const;
    bool isArray() const;

    std::string toString();
    int toInt();
    float toFloat();

    // delete
    bool remove(const std::string &key);
    bool remove(const uint64_t index);

    // output
    void print(std::string *output, bool indent=false, uint32_t level=0);

private:
    jsonTypes m_type = UNINIT_TYPE;
    jsonContent m_content;

    void addIndent(std::string *output,
                   const bool indent,
                   const uint32_t level);
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONOBJECT_H
