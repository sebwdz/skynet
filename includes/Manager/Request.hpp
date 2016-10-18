//
// Created by sebastien on 10/17/16.
//

#ifndef SKYNET_MANAGER_HPP
#define SKYNET_MANAGER_HPP

#include    "json11/json11.hpp"
#include    "AManager.hpp"
#include    "../Data/DbReader.hpp"

namespace Skynet {
    namespace Manager {
        class       RequestManager : AManager {
        public:
            RequestManager(json11::Json const&, Data::DbObject*);

            void                execute(json11::Json const&);

        private:
            Data::DbReader  m_reader;
        };
    }
}

#endif //SKYNET_MANAGER_HPP
