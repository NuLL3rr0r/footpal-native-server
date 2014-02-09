#include <boost/filesystem/path.hpp>
#include <CoreLib/make_unique.hpp>
#include "rt.hpp"

using namespace std;
using namespace Footpal;

class RT::Impl
{
public:
    typedef std::unique_ptr<StorageStruct> Storage_ptr;

public:
    std::mutex StorageMutex;
    Storage_ptr StorageInstance;

public:
    Impl();
    ~Impl();
};

std::unique_ptr<RT::Impl> RT::s_pimpl = std::make_unique<RT::Impl>();

RT::StorageStruct *RT::Storage()
{
    lock_guard<mutex> lock(s_pimpl->StorageMutex);
    (void)lock;

    if (s_pimpl->StorageInstance == nullptr) {
        s_pimpl->StorageInstance = std::make_unique<RT::StorageStruct>();
    }

    return s_pimpl->StorageInstance.get();
}

RT::Impl::Impl()
{

}

RT::Impl::~Impl()
{
    StorageInstance.reset();
}

