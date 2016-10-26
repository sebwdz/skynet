//
// Created by sebastien on 10/12/16.
//

#include    <iostream>
#include    "Data/Extract.hpp"

namespace Skynet {
    namespace Data {

        void Extract::extract(json11::Json const &data, json11::Json const &patern) {
            json11::Json::array         values;
            std::string                 tmp;

            for (unsigned int it = 0; it < patern.array_items().size(); it++) {
                for (unsigned int from = 0; from < patern[it]["from"].array_items().size(); from++) {
                    if (patern[it]["type"].string_value() == "json") {
                        json11::Json    json = json11::Json::parse(data[patern[it]["from"][from]["column"].string_value()].string_value(), tmp);
                        for (unsigned int j = 0; j < patern[it]["from"][from]["fields"].array_items().size(); j++)
                            values.push_back(json[patern[it]["from"][from]["fields"][j].string_value()].number_value());
                    }
                    else if (patern[it]["type"].string_value() == "bool")
                        values.push_back(data[patern[it]["from"][from]["column"].string_value()].string_value() == "t" ? 1 : 0);
                    else
                        values.push_back(
                                std::stod(data[patern[it]["from"][from]["column"].string_value()].string_value()));
                }
            }
            m_result = values;
        }

        json11::Json const& Extract::getResult() const {
            return (m_result);
        }
    }
}