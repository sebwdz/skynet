//
// Created by sebastien on 10/21/16.
//

#include    "Neuronal/Experiences/SupervisedExperience.hpp"
#include    "Neuronal/Network/SupervisedNetwork.hpp"

namespace       Skynet {
    namespace       Neuronal {

        void        SupervisedExperience::apply(Network &network, bool learn) {
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

        void        SupervisedExperience::calEqm() {
            m_eqm = 0;
            for (unsigned int it = 0; it < m_errors.size(); it++)
                m_eqm += m_errors[it] * m_errors[it];
            m_eqm *= 0.5;
        }

        double      SupervisedExperience::getEqm() const {
            return (m_eqm);
        }
    }
}