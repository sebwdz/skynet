//
// Created by sebastien on 10/17/16.
//

#include "Manager/Request.hpp"

namespace   Skynet {
    namespace   Manager {

        RequestManager::RequestManager(json11::Json const& pattern, Data::DbObject *obj) : AManager(pattern) {
            m_reader.setDb(obj);
        }

        void RequestManager::execute(json11::Json const &pattern, json11::Json const &var) {
            m_reader.setVariables(var);
            m_reader.execute(pattern);
        }
    }
}