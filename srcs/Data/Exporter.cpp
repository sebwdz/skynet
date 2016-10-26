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

        json11::Json        Exporter::getValue(json11::Json const &data, json11::Json const &vars, json11::Json const& save) {
            if (data.is_object()) {
                json11::Json::object obj;

                for (json11::Json::object::const_iterator it = data.object_items().begin(); it != data.object_items().end(); it++)
                    obj[it->first] = getValue(it->second, vars, save);
                return (json11::Json(obj));
            }
            else if (data.is_string() && data.string_value().size() > 1 && data.string_value()[0] == ':') {
                json11::Json        tmp;

                if (vars.object_items().find(data.string_value().substr(1)) != vars.object_items().end())
                    tmp = vars;
                else
                    tmp = save;
                if (tmp[data.string_value().substr(1)].is_object() || tmp[data.string_value().substr(1)].is_array())
                    return (tmp[data.string_value().substr(1)]);
                else if (tmp[data.string_value().substr(1)].is_number())
                    return (tmp[data.string_value().substr(1)].number_value());
                else
                    return (tmp[data.string_value().substr(1)].string_value());
            }
            else if (data.is_string())
                return (json11::Json(data.string_value()));
            return (json11::Json(data.number_value()));
        }

        /*bool    Exporter::remove(json11::Json const &vars, json11::Json const& save, json11::Json const &pattern) {
            std::string         request;
            unsigned int        it;

            request += "SELECT id FROM " + pattern["table"].string_value() + " WHERE ";
            for (it = 0; it < pattern["main_keys"].array_items().size(); it++) {
                request += pattern["main_keys"][it].string_value() + " = ";
                request += getValue(pattern["fields"][pattern["main_keys"][it].string_value()], vars, save).string_value() + " ";
            }
        }*/

        void    Exporter::export_data(json11::Json const &vars, json11::Json const& save, json11::Json const &pattern) {
            std::string         request;
            std::string         values;
            unsigned int        x = 0;

            request = "INSERT INTO " + pattern["table"].string_value() + "(";
            for (json11::Json::object::const_iterator it = pattern["fields"].object_items().begin();
                    it != pattern["fields"].object_items().end(); it++) {
                json11::Json tmp = getValue(it->second, vars, save);
                if (tmp.is_object())
                    values += "'" + tmp.dump() + "'";
                else if (tmp.is_string())
                    values += "'" + tmp.string_value() + "'";
                else
                    values += tmp.dump();
                values += (++x < pattern["fields"].object_items().size() ? ", " : "");
                request += it->first + (x < pattern["fields"].object_items().size() ? ", " : "");
            }
            request += ") VALUES(" + values + ")";
            m_db->execute(request);
        }
    }
}