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

        void Experience::apply(Network &network, bool learn) {
            SupervisedNetwork      *supervisedNetwork = dynamic_cast<SupervisedNetwork*>(&network);
            std::vector<double> const   &outputs = network.getOutputs();
            network.setInputs(m_inputs);
            network.exec();
            m_errors.resize(m_expected.size(), 0);
            for (unsigned int it = 0; it < outputs.size(); it++)
                m_errors[it] = m_expected[it] - outputs[it];
            calEqm();
            if (learn) {
                if (supervisedNetwork)
                    supervisedNetwork->setExpected(m_expected);
                network.learn();
            }
        }

        void                            Experience::calEqm() {
            m_eqm = 0;
            for (unsigned int it = 0; it < m_errors.size(); it++)
                m_eqm += m_errors[it] * m_errors[it];
            m_eqm *= 0.5;
        }

        std::vector<double> const       &Experience::getErrors() const {
            return (m_errors);
        }

        double                          Experience::getEqm() const {
            return (m_eqm);
        }
    }
}