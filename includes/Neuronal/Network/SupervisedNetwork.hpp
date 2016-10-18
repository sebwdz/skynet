//
// Created by sebastien on 8/20/16.
//

#ifndef SKYNET_SUPERVISEDNETWORK_HPP
#define SKYNET_SUPERVISEDNETWORK_HPP

#include            <vector>
#include            "Neuronal/Network.hpp"

namespace Skynet {
    namespace Neuronal {
        class                   SupervisedNetwork : public Network {
        public:

            virtual void                        setExpected(std::vector<double> const&) = 0;
            std::vector<double> const           &getOutputs() const;

        protected:
            std::vector<double>                 m_outputs;
        };
    }
}

#endif //SKYNET_SUPERVISEDNETWORK_HPP
