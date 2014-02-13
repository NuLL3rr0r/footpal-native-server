#ifndef PUBLIC_API_RESOURCE_HPP
#define PUBLIC_API_RESOURCE_HPP


#include "apiresource.hpp"

namespace Footpal {
    class PublicAPIResource;
}

class Footpal::PublicAPIResource : public Footpal::APIResource
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    explicit PublicAPIResource(WObject *parent = NULL);
    virtual ~PublicAPIResource();

public:
    virtual void handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response);
};


#endif /* PUBLIC_API_RESOURCE_HPP */

