#pragma once

#include <Common.h>

namespace nw4r {
namespace ut {

struct List {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
};

struct Link {
    void *prevObject;
    void *nextObject;
};

void List_Init(List *list, u16 offset);
void List_Append(List *list, void *object);
void List_Remove(List *list, void *object);
void *List_GetNext(const List *list, const void *object);

inline void *List_GetFirst(List *list) {
    return List_GetNext(list, NULL);
}

} // namespace ut
} // namespace nw4r
