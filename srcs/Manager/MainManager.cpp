//
// Created by sebastien on 10/17/16.
//

#include    <iostream>
#include    "Manager/MainManager.hpp"
#include    "Manager/Request.hpp"
#include    "Manager/Network.hpp"
#include    "Manager/Interpreter.hpp"
#include    "Manager/Exporter.hpp"

namespace   Skynet {
    namespace Manager {

        MainManager::MainManager(json11::Json const &pattern, Data::DbObject *db) : AManager(pattern) {
            for (json11::Json::object::const_iterator it = m_pattern["managers"].object_items().begin();
                    it != m_pattern["managers"].object_items().end(); it++) {
                if (it->second["type"].string_value() == "request")
                    m_managers[it->first] = new RequestManager(it->second, db);
                else if (it->second["type"].string_value() == "network")
                    m_managers[it->first] = new Network(it->second);
                else if (it->second["type"].string_value() == "interpreter")
                    m_managers[it->first] = new Interpreter(it->second);
                else if (it->second["type"].string_value() == "exporter")
                    m_managers[it->first] = new Exporter(it->second, db);
            }
        }

        void    MainManager::execute(json11::Json const &av, json11::Json const&) {
            for (unsigned int it = 0; it < m_pattern["process"].array_items().size(); it++)
                process(m_pattern["process"][it], av);
        }

        void    MainManager::process(json11::Json const &proc, json11::Json const &vars) {
            json11::Json tmp;

            m_managers[proc["call"].string_value()]->execute(vars, m_save);
            tmp = m_managers[proc["call"].string_value()]->getResults();
            if (proc.object_items().find("to") != proc.object_items().end()) {
                for (unsigned int x = 0; x < proc["to"].array_items().size(); x++) {
                    if (proc["type"].string_value() == "forone") {
                        for (unsigned int it = 0; it < tmp.array_items().size(); it++)
                            process(proc["to"][x], tmp[it]);
                    } else
                        process(proc["to"][x], tmp);
                }
            } else if (proc["type"].string_value() == "return") {
                json11::Json::array         arr;
                arr.insert(arr.begin(), tmp.array_items().begin(), tmp.array_items().end());
                arr.insert(arr.begin(), m_results.array_items().begin(), m_results.array_items().end());
                m_results = arr;
            }
        }

        json11::Json::object const& MainManager::getSave() {
            return (m_save);
        }
    }
}