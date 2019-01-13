#ifndef JSONITEM_H
#define JSONITEM_H

#include <jsonObjects.h>

namespace Kitsune
{
namespace Json
{

class JsonItem
{
public:
    JsonItem();
    JsonItem(AbstractJson *item);
    ~JsonItem();

    JsonItem operator[](const std::string key);
    JsonItem operator[](const uint32_t index);

private:
    AbstractJson* m_item = nullptr;

};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONITEM_H
