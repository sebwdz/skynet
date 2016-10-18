//
// Created by sebastien on 8/20/16.
//

#ifndef SKYNET_LEARINGSESSION_HPP
#define SKYNET_LEARINGSESSION_HPP

#include <vector>
#include "Network.hpp"
#include "Experience.hpp"

namespace       Skynet {
    namespace       Neuronal {
        class           LearningSession {
        public:
            void        setNetwork(Network*);
            void        setExperiences(std::vector<Experience*> const&);
            void        setTests(std::vector<Experience*> const&);

            virtual void        exec() = 0;
            virtual double      evaluate() = 0;

        protected:
            Network                         *m_network;
            std::vector<Experience*>        m_experiences;
            std::vector<Experience*>        m_tests;
        };
    }
}

#endif //SKYNET_LEARINGSESSION_HPP
