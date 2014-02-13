#ifndef API_RESOURCE_HPP
#define API_RESOURCE_HPP


#include <Wt/WResource>

namespace Wt {
    namespace Http {
        class Request;
        class Response;
    }
}

#include <CoreLib/httpstatus.hpp>

namespace Footpal {
    class APIResource;
}

class Footpal::APIResource : public Wt::WResource
{
public:
    explicit APIResource(WObject *parent = NULL);
    virtual ~APIResource() = 0;

public:
    virtual void handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response) = 0;

protected:
    std::string GetHTTPStatusPlain(const CoreLib::HTTPStatus::HTTPStatusCode &code) const;
    std::string GetHTTPStatusJSON(const CoreLib::HTTPStatus::HTTPStatusCode &code) const;
    std::string GetHTTPStatusXML(const CoreLib::HTTPStatus::HTTPStatusCode &code) const;
};


#endif /* API_RESOURCE_HPP */

