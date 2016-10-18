//
// Created by sebastien on 10/13/16.
//

#include        <iostream>
#include        "Data/Exporter.hpp"

namespace   Skynet {
    namespace  Data {

        void Exporter::setDb(DbObject *db) {
            m_db = db;
        }

        json11::Json const &Exporter::getValue(json11::Json const &data, json11::Json const &vars) {
            if (data.is_object()) {
                json11::Json::object obj;
                for (json11::Json::object::const_iterator it = data.object_items().begin();
                     it != data.object_items().end(); it++) {
                    obj[it->first] = getValue(it->second, vars);
                }
                m_tmp = json11::Json(obj);
            }
            else if (data.string_value()[0] == ':') {
                if (vars[data.string_value().substr(1)].is_object() || vars[data.string_value().substr(1)].is_array())
                    m_tmp = vars[data.string_value().substr(1)];
                else if (vars[data.string_value().substr(1)].is_number())
                    m_tmp = vars[data.string_value().substr(1)].number_value();
                else
                    m_tmp = vars[data.string_value().substr(1)].string_value();
            }
            else
                m_tmp = data.string_value();
            return (m_tmp);
        }

        void    Exporter::export_data(json11::Json const &vars, json11::Json const &patern) {
            std::string         request;
            std::string         values;
            unsigned int        x = 0;

            request = "INSERT INTO " + patern["database"].string_value() + "(";
            for (json11::Json::object::const_iterator it = patern["fields"].object_items().begin();
                    it != patern["fields"].object_items().end(); it++) {
                x++;
                json11::Json const &tmp = getValue(it->second, vars);
                if (tmp.is_object())
                    values += "'" + tmp.dump() + "'";
                else if (tmp.is_string())
                    values += "'" + tmp.string_value() + "'";
                else
                    values += tmp.dump();
                values += (x < patern["fields"].object_items().size() ? ", " : "");
                request += it->first + (x < patern["fields"].object_items().size() ? ", " : "");
            }
            request += ") VALUES(" + values + ")";
            m_db->execute(request);
        }
    }
}