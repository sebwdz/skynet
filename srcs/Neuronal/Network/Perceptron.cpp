//
// Created by sebastien on 8/12/16.
//

#include            <iostream>
#include            <chanel.hpp>
#include            "Neuronal/Network/Perceptron.hpp"

namespace           Skynet {
    namespace           Neuronal {

        Perceptron::Perceptron() {
            m_prevEqm = -1;
            m_coef = 0.05;
        }

        void            Perceptron::exec() {
            PerceptronLayer     *layer;

            for (unsigned int it = 1; it < m_layers.size(); it++)
                m_layers[it]->exec();
            layer = m_layers.back();
            m_outputs.resize(layer->getCellsNb(), 0);
            for (unsigned int it = 0; it < layer->getCellsNb(); it++)
                m_outputs[it] = layer->getCell(it)->getOutput();
        }

        void            Perceptron::learn() {
            for (unsigned int it = m_layers.size() - 1; it > 0; it--) {
                m_layers[it]->learn();
            }
        }

        void            Perceptron::update(double cur) {
            double      err;

            if (m_prevEqm != -1) {
                err = m_prevEqm - cur;
                m_coef += err * 0.02;
                m_coef = m_coef > 0.5 ? 0.5 : (m_coef < 0.0005 ? 0.0005 : m_coef);
                //if ((err < 0 ? -err : err) < 0.001) {
                    m_coef += ((rand() % 1000) - 500) / 1000000.0;
                //}
            }
            m_prevEqm = cur;
            for (unsigned int it = 1; it < m_layers.size(); it++)
                m_layers[it]->setCoef(m_coef);
        }

        void            Perceptron::generate(json11::Json const& json) {
            PerceptronLayer     *layer = new PerceptronLayer();
            const unsigned int  nb = (unsigned int)json["inputs"].int_value();

            for (unsigned int it = 0; it < nb; it++) {
                layer->addCell(new Excitable());
            }
            addLayer(layer);
        }

        void            Perceptron::setInputs(std::vector<double> const &inputs) {
            PerceptronLayer     *layer;

            layer = m_layers.at(0);
            for (unsigned int it = 0; it < inputs.size(); it++) {
                layer->getCell(it)->setOutput(inputs[it]);
            }
        }

        void            Perceptron::addLayer(PerceptronLayer *layer) {
            m_layers.push_back(layer);
        }

        PerceptronLayer                     *Perceptron::getLayer(unsigned int key) const {
            return (m_layers.at(key));
        }

        unsigned int                        Perceptron::getLayerNb() const {
            return (m_layers.size());
        }

        double                              Perceptron::getCoef() const {
            return (m_coef);
        }
    }
}
