//
// Created by sebastien on 10/17/16.
//

#ifndef SKYNET_IMANAGER_HPP_HPP
#define SKYNET_IMANAGER_HPP_HPP

#include    "json11/json11.hpp"

namespace   Skynet {
    namespace   Manager {
        class       AManager {
        public:
            AManager(json11::Json const&);

            json11::Json const  &getResults() const;

            virtual void                execute(json11::Json const&) = 0;

        protected:
            json11::Json        m_results;
            json11::Json        m_pattern;
        };
    }
}

#endif //SKYNET_IMANAGER_HPP_HPP
