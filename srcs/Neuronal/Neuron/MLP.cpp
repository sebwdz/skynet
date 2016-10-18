//
// Created by sebastien on 8/12/16.
//

#include <iostream>
#include "Tools/Math/Function.hpp"
#include "Tools/Utils.hpp"
#include "Neuronal/Neuron/MLP.hpp"

namespace       Skynet
{
    namespace           Neuronal {
        MLPNeuron::MLPNeuron() {
            m_gradient = 0;
            setActivate(Skynet::Tools::Functions::tanh);
            setDerived(Skynet::Tools::Functions::tanhdev);
        }

        void            MLPNeuron::setDerived(double (*derived)(double, double)) {
            m_derived = derived;
        }

        void            MLPNeuron::addGradient(double gradient) {
            m_gradient += gradient;
        }

        void           MLPNeuron::learn() {
            MLPNeuron               *neuron;
            double                  momentum;

            m_gradient *= (*m_derived)(m_potential, 1);
            m_biais -= m_gradient * m_coef;
            m_momentum.resize(m_inputs.size(), 0);
            if ((m_gradient > 0 ? m_gradient : -m_gradient) < 0.0005)
                m_gradient += Tools::rand() / 1000;
            for (unsigned int it = 0; it < m_inputs.size(); it++) {
                momentum = m_momentum[it];
                if ((neuron = dynamic_cast<MLPNeuron*>(m_inputs[it].first)))
                    neuron->addGradient(m_gradient * m_inputs[it].second);
                m_momentum[it] = m_inputs[it].second;
                m_inputs[it].second += m_gradient * m_inputs[it].first->getOutput() *
                                               m_coef + 0.4 * (m_inputs[it].second - momentum);
            }
            m_gradient = 0;
        }
    }
}