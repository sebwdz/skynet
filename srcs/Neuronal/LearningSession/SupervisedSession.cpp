//
// Created by sebastien on 8/20/16.
//

#include <fstream>
#include "Neuronal/LearningSession/SupervisedSession.hpp"

namespace   Skynet {
    namespace   Neuronal {

        void SupervisedSession::exec() {
            double      error = m_stop * 2;

            m_network->reset(0);
            while (error > m_stop) {
                error = 0;
                for (unsigned int it = 0; it < m_experiences.size(); it++) {
                    m_experiences[it]->apply(*m_network, true);
                    error += m_experiences[it]->getEqm();
                }
                m_network->update(error);
            }
        }

        void SupervisedSession::load(json11::Json const& json) {
            m_stop = json["session"]["stop"].number_value();
        }

        void        SupervisedSession::loadExperiences(json11::Json const& json) {
            SupervisedExperience    *exp;
            std::vector<double>     values;

            m_experiences.clear();
            for (unsigned int it = 0; it < json.array_items().size(); it++) {
                exp = new SupervisedExperience();
                values.clear();
                json11::Json const& input = json[it]["inputs"];
                for (unsigned int x = 0; x < input.array_items().size(); x++)
                    values.push_back(input[x].number_value());
                exp->setInputs(values);
                values.clear();
                json11::Json const& output = json[it]["outputs"];
                for (unsigned int x = 0; x < output.array_items().size(); x++)
                    values.push_back(output[x].number_value());
                exp->setExpected(values);
                m_experiences.push_back(exp);
            }
        }

        double    SupervisedSession::evaluate() {
            double      error = 0;

            for (unsigned int it = 0; it < m_experiences.size(); it++) {
                m_experiences[it]->apply(*m_network);
                error += m_experiences[it]->getEqm();
            }
            if (m_experiences.size())
                error /= m_experiences.size();
            return (error);
        }
    }
}