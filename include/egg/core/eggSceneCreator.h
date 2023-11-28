#pragma once

namespace EGG {

class SceneCreator {
public:
    virtual Scene *create(s32 id);
    virtual void destroy(s32 id);
};

} // namespace EGG
