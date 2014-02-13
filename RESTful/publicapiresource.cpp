#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <Wt/Http/Request>
#include <Wt/Http/Response>
#include <Wt/WString>
#include <CoreLib/log.hpp>
#include <CoreLib/make_unique.hpp>
#include "publicapiresource.hpp"
#include "servicecontract.hpp"

#define     LoginUserJSON_URI_TEMPLATE              "Account/Login/JSON/{username}/{password}"
#define     LoginUserXML_URI_TEMPLATE               "Account/Login/XML/{username}/{password}"

using namespace std;
using namespace boost;
using namespace Wt;
using namespace Footpal;

struct PublicAPIResource::Impl
{
    std::unique_ptr<ServiceContract<Impl> > ServiceContractPtr;

    void LoginUserJSON(const std::wstring &username, const std::wstring &password, std::wstring &out_response);
    void LoginUserXML(const std::wstring &username, const std::wstring &password, std::wstring &out_response);

    Impl();
    ~Impl();
};


PublicAPIResource::PublicAPIResource(WObject *parent) :
    APIResource(parent),
    m_pimpl(std::make_unique<PublicAPIResource::Impl>())
{
    m_pimpl->ServiceContractPtr = std::make_unique<Footpal::ServiceContract<PublicAPIResource::Impl> >(m_pimpl.get());
    m_pimpl->ServiceContractPtr->Register(L"Account/Login/JSON/{username}/{password}");
    m_pimpl->ServiceContractPtr->Register(L"Account/Login/XML/{username}/{password}");
}

PublicAPIResource::~PublicAPIResource()
{
    beingDeleted();
}

void PublicAPIResource::handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{
    WString uri((boost::format("%1%%2%")
                 % request.path().substr(request.path().find_last_of("/") + 1)
                 % request.pathInfo()
                 ).str());
    wstring uriTemplate;
    vector<wstring> args;

    if (m_pimpl->ServiceContractPtr->Resolve(uri.value(), uriTemplate, args)) {
        wstring outResponse;

        if (uriTemplate == LoginUserJSON_URI_TEMPLATE) {
            m_pimpl->LoginUserJSON(args[0], args[1], outResponse);
        } else if (uriTemplate == LoginUserXML_URI_TEMPLATE) {
            m_pimpl->LoginUserXML(args[0], args[1], outResponse);
        }

        LOG_ERROR(WString(outResponse).toUTF8());
        response.out() << outResponse;
    } else {
        if (boost::algorithm::contains(uri.value(), L"/JSON")) {
            response.out() << GetHTTPStatusJSON(CoreLib::HTTPStatus::HTTPStatusCode::HTTP_400);
        } else if (boost::algorithm::contains(uri.value(), L"/XML")) {
            response.out() << GetHTTPStatusXML(CoreLib::HTTPStatus::HTTPStatusCode::HTTP_400);
        } else {
            response.out() << GetHTTPStatusPlain(CoreLib::HTTPStatus::HTTPStatusCode::HTTP_400);
        }
    }
}

PublicAPIResource::Impl::Impl()
{

}

PublicAPIResource::Impl::~Impl()
{

}

void PublicAPIResource::Impl::LoginUserJSON(const std::wstring &username,
                                            const std::wstring &password,
                                            std::wstring &out_response)
{
    std::wstringstream stream;
    boost::property_tree::wptree tree;

    tree.put(L"username", username);
    tree.put(L"password", password);

    boost::property_tree::write_json(stream, tree);

    out_response.assign(stream.str());
}

void PublicAPIResource::Impl::LoginUserXML(const std::wstring &username,
                                           const std::wstring &password,
                                           std::wstring &out_response)
{
    std::wstringstream stream;
    boost::property_tree::wptree tree;

    tree.put(L"user.username", username);
    tree.put(L"user.password", password);

    boost::property_tree::write_xml(stream, tree);

    out_response.assign(stream.str());
}

