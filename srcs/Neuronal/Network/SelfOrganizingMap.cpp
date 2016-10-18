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
            m_outputs.clear();
            if (m_winner) {
                m_outputs.push_back(m_winner->getPos().first);
                m_outputs.push_back(m_winner->getPos().second);
            }
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
            return (m_outputs);
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
                                        {"outputs", json11::Json::array {(int)m_size.first, (int)m_size.second}}};
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
        }

    }
}