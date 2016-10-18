//
// Created by sebastien on 8/12/16.
//

#include        "Neuronal/Excitable.hpp"

namespace           Skynet {
    namespace           Neuronal {

        Excitable::Excitable() {
            m_output = 0;
        }

        void                Excitable::exec() { }

        void                Excitable::learn() { }

        void                Excitable::setOutput(double out) {
            m_output = out;
        }

        double              Excitable::getOutput() const {
            return (m_output);
        }

    }
}