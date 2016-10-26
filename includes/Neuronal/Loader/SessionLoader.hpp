//
// Created by sebastien on 10/21/16.
//

#ifndef SKYNET_SESSIONLOADER_HPP
#define SKYNET_SESSIONLOADER_HPP

#include    <json11/json11.hpp>
#include    "Neuronal/LearningSession.hpp"

namespace       Skynet {
    namespace       Neuronal {

        class           SessionLoader {
        public:
            LearningSession         *getSession(std::string const&);
            static SessionLoader    &getInstance();

        private:
            SessionLoader() {}
        };
    }
}

#endif //SKYNET_SESSIONLOADER_HPP
