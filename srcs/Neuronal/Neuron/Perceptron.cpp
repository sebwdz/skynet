//
// Created by sebastien on 8/12/16.
//

#include            "Tools/Math/Function.hpp"
#include            "Neuronal/Neuron/Perceptron.hpp"

namespace       Skynet {
    namespace       Neuronal {
        PerceptronNeuron::PerceptronNeuron() {
            setActivate(Skynet::Tools::Functions::sigmoide);
        }

        void           PerceptronNeuron::setError(double error) {
            m_error = error;
        }

        void           PerceptronNeuron::learn() {
            m_biais -= m_error * m_coef;
            for (unsigned int it = 0; it < m_inputs.size(); it++) {
                m_inputs[it].second += m_inputs[it].first->getOutput() * m_error * m_coef;
            }
        }
    }
}