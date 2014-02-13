#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <CoreLib/make_unique.hpp>
#include "apiresource.hpp"

using namespace std;
using namespace boost;
using namespace Wt;
using namespace CoreLib;
using namespace Footpal;

APIResource::APIResource(WObject *parent) :
    WResource(parent)
{

}

APIResource::~APIResource()
{

}

std::string APIResource::GetHTTPStatusPlain(const CoreLib::HTTPStatus::HTTPStatusCode &code) const
{
    return HTTPStatus::GetHTTPResponse(code);
}

std::string APIResource::GetHTTPStatusJSON(const CoreLib::HTTPStatus::HTTPStatusCode &code) const
{
    std::stringstream stream;
    boost::property_tree::ptree tree;

    tree.put("error", HTTPStatus::GetHTTPResponse(code));

    boost::property_tree::write_json(stream, tree);

    return stream.str();
}

std::string APIResource::GetHTTPStatusXML(const CoreLib::HTTPStatus::HTTPStatusCode &code) const
{
    std::stringstream stream;
    boost::property_tree::ptree tree;

    tree.put("error", HTTPStatus::GetHTTPResponse(code));

    boost::property_tree::write_xml(stream, tree);

    return stream.str();
}

