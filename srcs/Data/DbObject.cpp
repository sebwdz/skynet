//
// Created by sebastien on 10/12/16.
//

#include        <pqxx/pqxx>
#include        "Data/DbObject.hpp"

namespace Skynet {
    namespace Data {

        void DbObject::connect(const std::string &str) {
            m_connection = new pqxx::connection(str);
            m_work = new pqxx::work(*m_connection);
        }

        void DbObject::execute(const std::string &str) {
            json11::Json::array     results;

            pqxx::result r(m_work->exec(str));
            for (unsigned int it = 0; it < r.size(); it++) {
                json11::Json::object        result;

                for (unsigned int x = 0; x < r[it].size(); x++)
                    result[r[it][x].name()] = r[it][x].c_str();
                results.push_back(result);
            }
            m_result = results;
        }

        void DbObject::commit() {
            m_work->commit();
        }

        json11::Json const& DbObject::getResult() {
            return (m_result);
        }
    }
}