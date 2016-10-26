//
// Created by sebastien on 10/17/16.
//

#include <iostream>
#include "Manager/Request.hpp"

namespace   Skynet {
    namespace   Manager {

        RequestManager::RequestManager(json11::Json const& pattern, Data::DbObject *obj) : AManager(pattern) {
            m_db = obj;
            m_reader.setDb(obj);
        }

        void RequestManager::execute(json11::Json const &var, json11::Json const& save) {
            m_reader.setVariables(var);
            m_reader.execute(m_pattern["request"]);
            m_results = m_db->getResult();
        }
    }
}