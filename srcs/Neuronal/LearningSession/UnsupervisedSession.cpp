//
// Created by sebastien on 10/13/16.
//

#include <iostream>
#include "Neuronal/LearningSession/UnsupervisedSession.hpp"

namespace   Skynet {
    namespace   Neuronal {

        void UnsupervisedSession::load(json11::Json const &json) {
            m_iterations = (unsigned int)json["iterations"].int_value();
        }

        void UnsupervisedSession::setInputs(std::vector<Data::Extract::Values *> const &inputs) {
            m_inputs = inputs;
        }

        void UnsupervisedSession::exec() {
            m_network->reset(m_iterations);
            for (unsigned int it = 0; it < m_iterations; it++) {
                for (unsigned int x = 0; x < m_inputs.size(); x++) {
                    m_network->setInputs(m_inputs[x]->_values);
                    m_network->exec();
                    m_network->learn();
                }
                std::cout << "\r" << (it / (double)m_iterations) * 100;
                std::cout.flush();
                m_network->update(0);
            }
        }

        double UnsupervisedSession::evaluate() {
            return (0);
        }
    }
}