//
// Created by sebastien on 8/20/16.
//

#include    "Neuronal/LearningSession.hpp"

namespace   Skynet {
    namespace   Neuronal {
        void    LearningSession::setNetwork(Network *network) {
            m_network = network;
        }

       void     LearningSession::setExperiences(std::vector<Experience *> const &experiences) {
            m_experiences = experiences;
        }

        void    LearningSession::setTests(std::vector<Experience *> const &tests) {
            m_tests = tests;
        }
    }
}