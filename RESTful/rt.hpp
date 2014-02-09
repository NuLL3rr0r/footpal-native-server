#ifndef RT_HPP
#define RT_HPP


#include <memory>
#include <mutex>

namespace Footpal {
    class RT;
}

class Footpal::RT
{
public:
    struct StorageStruct
    {
        std::string AppPath;
    };

private:
    class Impl;
    static std::unique_ptr<Impl> s_pimpl;

public:
    static StorageStruct *Storage();
};


#endif /* RT_HPP */

