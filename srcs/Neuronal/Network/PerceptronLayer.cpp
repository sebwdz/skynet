//
// Created by sebastien on 8/12/16.
//

#include            "Neuronal/Neuron/Simple.hpp"
#include            "Neuronal/Network/PerceptronLayer.hpp"

namespace       Skynet {
    namespace       Neuronal {
        void            PerceptronLayer::addCell(Excitable *cell) {
            m_cells.push_back(cell);
        }

        void            PerceptronLayer::exec() {
            for (unsigned int it = 0; it < m_cells.size(); it++) {
                m_cells[it]->exec();
            }
        }

        void            PerceptronLayer::learn() {
            for (unsigned int it = 0; it < m_cells.size(); it++) {
                m_cells[it]->learn();
            }
        }

        void            PerceptronLayer::setCoef(double coef) {
            SimpleNeuron        *neuron;
            for (unsigned int it = 0; it < m_cells.size(); it++) {
                if ((neuron = dynamic_cast<SimpleNeuron*>(m_cells[it]))) {
                    neuron->setCoef(coef);
                }
            }
        }

        Excitable       *PerceptronLayer::getCell(unsigned int it) const {
            return (m_cells.at(it));
        }

        unsigned int    PerceptronLayer::getCellsNb() const {
            return (m_cells.size());
        }
    }
}
