//
// Created by sebastien on 8/12/16.
//

#include            "Neuronal/Neuron/Simple.hpp"

namespace       Skynet {
    namespace           Neuronal {

        SimpleNeuron::SimpleNeuron() {
            m_coef = 0.001;
        }

        void                    SimpleNeuron::exec() {
            m_potential = -m_biais;
            for (unsigned int it = 0; it < m_inputs.size(); it++)
                m_potential += m_inputs[it].first->getOutput() * m_inputs[it].second;
            m_output = (*m_activate)(m_potential , 1);
        }

        void                    SimpleNeuron::setCoef(double coef) {
            m_coef = coef;
        }

        void                    SimpleNeuron::setActivate(double (*activate)(double, double)) {
            m_activate = activate;
        }
    }
}
