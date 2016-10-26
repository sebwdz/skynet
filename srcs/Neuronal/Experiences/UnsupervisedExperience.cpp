//
// Created by sebastien on 10/21/16.
//

#include <iostream>
#include <Neuronal/Experiences/UnsupervisedExperience.hpp>

namespace       Skynet {
    namespace       Neuronal {

        void UnsupervisedExperience::apply(Network &network, bool learn) {
            network.setInputs(m_inputs);
            network.exec();
            if (learn)
                network.learn();
        }
    }
}