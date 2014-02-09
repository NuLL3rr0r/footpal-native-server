#ifndef PUBLIC_API_RESOURCE_HPP
#define PUBLIC_API_RESOURCE_HPP


#include <Wt/WResource>

namespace Wt {
    namespace Http {
        class Request;
        class Response;
    }
}

namespace Footpal {
    class PublicAPIResource;
}

class Footpal::PublicAPIResource : public Wt::WResource
{
private:
    class Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    PublicAPIResource(WObject *parent = NULL);
    ~PublicAPIResource();

public:
    virtual void handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response);
};


#endif /* PUBLIC_API_RESOURCE_HPP */

