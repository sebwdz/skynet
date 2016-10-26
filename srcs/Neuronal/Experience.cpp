//
// Created by sebastien on 8/12/16.
//

#include            <iostream>
#include            "Neuronal/Experience.hpp"
#include            "Neuronal/Network/SupervisedNetwork.hpp"

namespace           Skynet {
    namespace           Neuronal {
        void                Experience::setInputs(std::vector<double> const &inputs) {
            m_inputs = inputs;
        }

        void                Experience::setExpected(std::vector<double> const &expect) {
            m_expected = expect;
        }

        std::vector<double> const& Experience::getExpected() const {
            return (m_expected);
        }
    }
}