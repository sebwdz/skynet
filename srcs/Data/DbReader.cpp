//
// Created by sebastien on 10/12/16.
//

#include        <iostream>
#include        "Data/DbReader.hpp"

namespace Skynet {
    namespace Data {

        void DbReader::setDb(DbObject *db) {
            m_db = db;
        }

        void    DbReader::setVariables(json11::Json const& variables) {
            m_vars = variables;
        }

        void    DbReader::list(std::string &request, json11::Json const& json) {
            for (unsigned int it = 0; it < json.array_items().size(); it++)
                request += (it ? "," : "") + json[it].string_value() + " ";
        }

        void DbReader::condition(std::string &request, json11::Json const& json) {
            if (json["type"] == "and" || json["type"] == "or") {

            } else {
                request += json["left"].string_value();
                if (json["type"].string_value() == "equal")
                    request += " = ";
                if (json["right"].string_value()[0] == ':')
                    request += m_vars[json["right"].string_value().substr(1)].string_value();
                else
                    request += json["right"].string_value();
                request += " ";
            }
        }

        void DbReader::execute(json11::Json const &json) {
            std::string             request;

            request = "SELECT ";
            list(request, json["select"]);
            request += " FROM ";
            list(request, json["from"]);
            if (json.object_items().find("joins") != json.object_items().end() && json["joins"].array_items().size()) {
                for (json11::Json::array::const_iterator it = json["joins"].array_items().begin(); it != json["joins"].array_items().end(); it++) {
                    request += "INNER JOIN " + (*it)["database"].string_value() + " ON ";
                    condition(request, (*it)["on"]);
                }
            }
            if (json.object_items().find("where") != json.object_items().end()) {
                request += "WHERE ";
                condition(request, json["where"]);
            }
            m_db->execute(request);
        }
    }
}