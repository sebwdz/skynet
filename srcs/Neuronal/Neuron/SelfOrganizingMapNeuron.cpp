//
// Created by sebastien on 10/2/16.
//

#include            <cmath>
#include            <iostream>
#include            "Neuronal/Neuron/SelfOrganizingMapNeuron.hpp"

namespace   Skynet {
    namespace   Neuronal {

        void        SelfOrganizingMapNeuron::setPos(std::pair<double, double> const &pos) {
            m_pos = pos;
        }

        void        SelfOrganizingMapNeuron::exec() {
            m_output = 0;
            for (unsigned int it = 0; it < m_inputs.size(); it++) {
                m_output += std::pow(m_inputs[it].first->getOutput() - m_inputs[it].second, 2);
            }
            m_output = std::sqrt(m_output);
        }

        void        SelfOrganizingMapNeuron::learn(double factor) {
            double  dist;

            for (unsigned int i = 0; i < m_inputs.size(); i++) {
                dist = factor * (m_inputs[i].first->getOutput() - m_inputs[i].second);
                m_inputs[i].second += dist;
            }
        }

        std::pair<double, double> const& SelfOrganizingMapNeuron::getPos() const {
            return (m_pos);
        }
    }
}