//
// Created by sebastien on 9/1/16.
//

#include        "Neuronal/Network/SupervisedNetwork.hpp"

namespace           Skynet {
    namespace Neuronal {
        std::vector<double> const &SupervisedNetwork::getOutputs() const {
            return (m_outputs);
        }
    }
}