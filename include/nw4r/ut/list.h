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
void List_Insert(List *list, void *target, void *object);
void List_Remove(List *list, void *object);
void *List_GetNext(const List *list, const void *object);
void *List_GetPrev(const List *list, const void *object);
void *List_GetNth(const List *list, u16 n);

inline const void *List_GetNextConst(const List *list, const void *object) {
    return List_GetNext(list, object);
}

inline const void *List_GetPrevConst(const List *list, const void *object) {
    return List_GetPrev(list, object);
}

inline const void *List_GetNthConst(const List *list, u16 n) {
    return List_GetNth(list, n);
}

inline void *List_GetFirst(const List *list) {
    return List_GetNext(list, NULL);
}

inline const void *List_GetFirstConst(const List *list) {
    return List_GetNextConst(list, NULL);
}

inline void *List_GetLast(const List *list) {
    return List_GetPrev(list, NULL);
}

inline const void *List_GetLastConst(const List *list) {
    return List_GetPrevConst(list, NULL);
}

inline u16 List_GetSize(const List *list) {
    return list->numObjects;
}

} // namespace ut
} // namespace nw4r
