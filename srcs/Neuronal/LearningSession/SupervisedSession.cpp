//
// Created by sebastien on 8/20/16.
//

#include <fstream>
#include <chanel.hpp>
#include <Neuronal/LearningSession/SupervisedSession.hpp>
#include <Neuronal/Network/Perceptron.hpp>

namespace   Skynet {
    namespace   Neuronal {

        void    SupervisedSession::setStop(double stop) {
            m_stop = stop;
        }

        void SupervisedSession::exec() {
            double      error = m_stop * 2;
            std::ofstream       eqm("eqm.txt");
            std::ofstream       coef("coef.txt");

            while (error > m_stop) {
                error = 0;
                for (unsigned int it = 0; it < m_experiences.size(); it++) {
                    m_experiences[it]->apply(*m_network, true);
                    error += m_experiences[it]->getEqm();
                }
                m_network->update(error);
                eqm << error << std::endl;
                coef << dynamic_cast<Perceptron*>(m_network)->getCoef() << std::endl;
            }
        }

        void SupervisedSession::load(json11::Json const& json) {
            loadExperiences(json["experiences"], m_experiences);
            loadExperiences(json["tests"], m_tests);
            m_stop = json["stop"].number_value();
        }

        void        SupervisedSession::loadExperiences(json11::Json const& json, std::vector<Experience*> &dir) {
            Experience              *exp;
            std::vector<double>     values;

            for (unsigned int it = 0; it < json.array_items().size(); it++) {
                exp = new Experience();
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
                dir.push_back(exp);
            }
        }

        double    SupervisedSession::evaluate() {
            double      error = 0;

            for (unsigned int it = 0; it < m_tests.size(); it++) {
                m_tests[it]->apply(*m_network);
                error += m_tests[it]->getEqm();
            }
            if (m_tests.size())
                error /= m_tests.size();
            return (error);
        }
    }
}