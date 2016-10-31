//
// Created by sebastien on 10/2/16.
//

#include        <iostream>
#include        "Tools/Math/Function.hpp"
#include        "Neuronal/Network/SelfOrganizingMap.hpp"

namespace       Skynet {
    namespace       Neuronal {

        void SelfOrganizingMap::setInputs(std::vector<double> const &inputs) {
            for (unsigned int it = 0; it < m_inputs.size(); it++) {
                m_inputs[it]->setOutput(inputs[it]);
            }
        }

        void SelfOrganizingMap::reset(unsigned int it) {
            m_iteration = it;
            m_current = 0;
            m_step = 1;
            m_initialRay = m_size.first > m_size.second ? m_size.second : m_size.first;
        }

        void        SelfOrganizingMap::exec() {
            m_winner = getWinner();
        }

        void SelfOrganizingMap::update(double) {
            m_current++;
            m_step = std::exp(-1 * ((double)m_current / (double)m_iteration));
        }

        SelfOrganizingMapNeuron* SelfOrganizingMap::getWinner() {
            SelfOrganizingMapNeuron     *neuron;

            neuron = NULL;
            for (unsigned int it = 0; it < m_map.size(); it++) {
                m_map[it]->exec();
                if (!neuron || m_map[it]->getOutput() < neuron->getOutput())
                    neuron = m_map[it];
            }
            return (neuron);
        }

        void        SelfOrganizingMap::learn() {
            double                      ray = Tools::Functions::sigma(m_initialRay, m_current, m_iteration);
            double                      dist;
            double                      factor;

            for (unsigned int it = 0; it < m_map.size(); it++) {
                if ((dist = Tools::Functions::getDistance(m_map[it]->getPos(), m_winner->getPos())) <= ray) {
                    factor = Tools::Functions::gauss(dist / ray * m_initialRay, m_initialRay, m_current, m_iteration);
                    m_map[it]->learn(factor * m_step);
                }
            }
        }

        std::vector<double> const& SelfOrganizingMap::getOutputs() const {
            return (m_outputs[m_winner->getPos().second * m_size.first + m_winner->getPos().first]);
        }

        void SelfOrganizingMap::generate(json11::Json const &json) {
            SelfOrganizingMapNeuron         *neuron;
            unsigned int    inputsSize;

            inputsSize = (unsigned int)json["inputs"].int_value();
            for (unsigned int it = 0; it < inputsSize; it++)
                m_inputs.push_back(new Excitable());
            m_size.first = (unsigned int)json["outputs"][0].int_value();
            m_size.second = (unsigned int)json["outputs"][1].int_value();
            for (unsigned int xp = 0; xp < m_size.first; xp++) {
                for (unsigned int it = 0; it < m_size.second; it++) {
                    neuron = new SelfOrganizingMapNeuron();
                    neuron->setPos(std::make_pair(xp, it));
                    for (unsigned x = 0; x < m_inputs.size(); x++)
                        neuron->addInput(m_inputs[x], (rand() % 1000) / 2000.0);
                    m_map.push_back(neuron);
                }
            }
            m_outputs.resize(m_size.first * m_size.second, std::vector<double>());
            m_outtype = json["outputs_type"].string_value();
        }

        void SelfOrganizingMap::save(json11::Json &out) {
            json11::Json::array         arr;

            for (unsigned int it = 0; it < m_map.size(); it++) {
                json11::Json::array         input;

                for (unsigned int x = 0; x < m_map[it]->getInputNb(); x++)
                    input.push_back(m_map[it]->getInput(x).second);
                json11::Json::object n {{"pos", json11::Json::array {m_map[it]->getPos().first, m_map[it]->getPos().second}}, {"inputs", input}};
                arr.push_back(n);
            }
            out = json11::Json::object {{"inputs", (int)m_inputs.size()},
                                        {"map", arr},
                                        {"outputs", json11::Json::array {(int)m_size.first, (int)m_size.second}},
                                        {"outputs_map", m_outputs},
                                        {"network", json11::Json::object {{"settings", json11::Json::object {{"type", "SelfOrganizingMap"}}}}}};
        }

        void SelfOrganizingMap::load(json11::Json const &json) {
            SelfOrganizingMapNeuron     *neuron;

            m_size.first = (unsigned int)json["outputs"][0].int_value();
            m_size.second = (unsigned int)json["outputs"][1].int_value();
            for (unsigned int it = 0; it < json["inputs"].int_value(); it++)
                m_inputs.push_back(new Excitable());
            for (unsigned int it = 0; it < json["map"].array_items().size(); it++) {
                neuron = new SelfOrganizingMapNeuron();
                neuron->setPos(std::make_pair(json["map"][it]["pos"][0].int_value(), json["map"][it]["pos"][1].int_value()));
                for (unsigned int input = 0; input < m_inputs.size(); input++)
                    neuron->addInput(m_inputs[input], json["map"][it]["inputs"][input].number_value());
                m_map.push_back(neuron);
            }
            m_outputs.resize(m_size.first * m_size.second, std::vector<double>());
            for (unsigned int it = 0; it < m_outputs.size(); it++) {
                for (unsigned int x = 0; x < json["outputs_map"][it].array_items().size(); x++)
                    m_outputs[it].push_back(json["outputs_map"][it][x].number_value());
            }
        }

        void SelfOrganizingMap::apply(UnsupervisedExperience *exp) {
            unsigned int        it = (unsigned int)(m_winner->getPos().second * m_size.first + m_winner->getPos().first);

            exp->apply(*this, false);
            if (m_outtype != "sum" || !m_outputs[it].size())
                m_outputs[it].push_back(exp->getExpected()[0]);
            else
                m_outputs[it][0] += exp->getExpected()[0];
        }

        void SelfOrganizingMap::makeOutputs() {
            double sum;

            if (m_outtype != "average")
                return ;
            for (unsigned int it = 0; it < m_outputs.size(); it++) {
                sum = 0;
                for (unsigned int x = 0; x < m_outputs[it].size(); x++)
                    sum += m_outputs[it][x];
                if (m_outputs[it].size())
                    m_outputs[it] = std::vector<double>(1, (sum / (double)m_outputs[it].size()));
            }
        }
    }
}