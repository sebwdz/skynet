//
// Created by sebastien on 10/17/16.
//

#include    "Manager/MainManager.hpp"

namespace   Skynet {
    namespace   Manager {

        MainManager::MainManager(json11::Json const &pattern, Data::DbObject *db) : AManager (pattern) {
            m_db = db;
        }

    }
}