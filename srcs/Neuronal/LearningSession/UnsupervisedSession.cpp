//
// Created by sebastien on 10/13/16.
//

#include <iostream>
#include <Neuronal/Network/SelfOrganizingMap.hpp>
#include "Neuronal/LearningSession/UnsupervisedSession.hpp"

namespace   Skynet {
    namespace   Neuronal {

        void    UnsupervisedSession::load(json11::Json const &json) {
            m_iterations = (unsigned int)json["iterations"].int_value();
        }

        void    UnsupervisedSession::loadExperiences(json11::Json const &exps) {
            UnsupervisedExperience      *exp;
            std::vector<double>         values;

            m_experiences.clear();
            for (unsigned int it = 0; it < exps.array_items().size(); it++) {
                exp = new UnsupervisedExperience();
                values.resize(exps[it]["inputs"].array_items().size(), 0);
                for (unsigned int x = 0; x < exps[it]["inputs"].array_items().size(); x++)
                    values[x] = exps[it]["inputs"][x].number_value();
                exp->setInputs(values);
                values.resize(exps[it]["outputs"].array_items().size(), 0);
                for (unsigned int x = 0; x < exps[it]["outputs"].array_items().size(); x++)
                    values[x] = exps[it]["outputs"][x].number_value();
                exp->setExpected(values);
                m_experiences.push_back(exp);
            }
        }

        void    UnsupervisedSession::exec() {
            SelfOrganizingMap       *map;

            m_network->reset(m_iterations);
            for (unsigned int it = 0; it < m_iterations; it++) {
                for (unsigned int x = 0; x < m_experiences.size(); x++)
                    m_experiences[x]->apply(*m_network, true);
                m_network->update(0);
            }
            if ((map = dynamic_cast<SelfOrganizingMap*>(m_network))) {
                for (unsigned int x = 0; x < m_experiences.size(); x++)
                    map->apply(m_experiences[x]);
                map->makeOutputs();
            }
        }

        double  UnsupervisedSession::evaluate() {
            return (0);
        }
    }
}