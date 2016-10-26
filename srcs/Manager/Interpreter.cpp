//
// Created by sebastien on 10/22/16.
//

#include    <iostream>
#include    "Manager/Interpreter.hpp"

namespace   Skynet {
    namespace   Manager {

        Interpreter::Interpreter(json11::Json const &pattern) : AManager(pattern) {
        }

        void Interpreter::execute(json11::Json const &vars, json11::Json const&) {
            json11::Json::array     arr;

            for (unsigned int x = 0; x < vars.array_items().size(); x++) {
                json11::Json::object    obj;
                for (json11::Json::object::const_iterator it = m_pattern["fields"].object_items().begin();
                     it != m_pattern["fields"].object_items().end(); it++) {
                    m_extracter.extract(vars[x], it->second);
                    obj[it->first] = m_extracter.getResult();
                }
                arr.push_back(obj);
            }
            m_results = arr;
        }
    }
}