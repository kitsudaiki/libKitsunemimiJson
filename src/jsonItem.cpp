#include "jsonItem.h"

namespace Kitsune
{
namespace Json
{

JsonItem::JsonItem(AbstractJson *item)
{
    m_item = item;
}

JsonItem JsonItem::operator[](const std::string key)
{
    return JsonItem(m_item->get(key));
}

JsonItem JsonItem::operator[](const uint32_t index)
{
    return JsonItem(m_item->get(index));
}

}  // namespace Json
}  // namespace Kitsune
