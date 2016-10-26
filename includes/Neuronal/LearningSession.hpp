//
// Created by sebastien on 8/20/16.
//

#ifndef SKYNET_LEARINGSESSION_HPP
#define SKYNET_LEARINGSESSION_HPP

#include <vector>
#include "Network.hpp"

namespace       Skynet {
    namespace       Neuronal {
        class           LearningSession {
        public:
            void        setNetwork(Network*);

            virtual void        exec() = 0;
            virtual double      evaluate() = 0;
            virtual void        load(json11::Json const&) = 0;
            virtual void        loadExperiences(json11::Json const&) = 0;
        protected:
            Network                         *m_network;
        };
    }
}

#endif //SKYNET_LEARINGSESSION_HPP
