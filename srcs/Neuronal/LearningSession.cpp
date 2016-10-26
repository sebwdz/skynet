//
// Created by sebastien on 8/20/16.
//

#include    "Neuronal/LearningSession.hpp"

namespace   Skynet {
    namespace   Neuronal {
        void    LearningSession::setNetwork(Network *network) {
            m_network = network;
        }
    }
}