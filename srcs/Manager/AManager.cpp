//
// Created by sebastien on 10/17/16.
//

#include <Manager/MainManager.hpp>
#include    "Manager/AManager.hpp"

namespace   Skynet {
    namespace   Manager {

        AManager::AManager(json11::Json const &pattern) {
            m_pattern = pattern;
        }

        const json11::Json & AManager::getResults() const {
            return (m_results);
        }
    }
}