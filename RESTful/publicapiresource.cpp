#include <functional>
#include <unordered_map>
#include <boost/any.hpp>
#include <Wt/Http/Request>
#include <Wt/Http/Response>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <CoreLib/log.hpp>
#include <CoreLib/make_unique.hpp>
#include "publicapiresource.hpp"

using namespace std;
using namespace Wt;
using namespace Footpal;

class PublicAPIResource::Impl
{
public:
    Impl();
    ~Impl();
};

PublicAPIResource::PublicAPIResource(WObject *parent) :
    WResource(parent),
    m_pimpl(std::make_unique<PublicAPIResource::Impl>())
{
}

PublicAPIResource::~PublicAPIResource()
{
    beingDeleted();
}

void PublicAPIResource::handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{

}

PublicAPIResource::Impl::Impl()
{

}

PublicAPIResource::Impl::~Impl()
{

}

