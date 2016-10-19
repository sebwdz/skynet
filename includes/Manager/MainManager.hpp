//
// Created by sebastien on 10/17/16.
//

#ifndef SKYNET_MAINMANAGER_HPP
#define SKYNET_MAINMANAGER_HPP

#include    "json11/json11.hpp"
#include    "Data/DbObject.hpp"
#include    "AManager.hpp"

namespace   Skynet {
    namespace   Manager {
        class       MainManager : public AManager {
        public:
            MainManager(json11::Json const&, Data::DbObject*);
            void                                    execute(json11::Json const&);
            void                                    process(json11::Json const&, json11::Json const&);
        private:
            std::map<std::string, AManager*>        m_managers;
        };
    }
}

#endif //SKYNET_MAINMANAGER_HPP
