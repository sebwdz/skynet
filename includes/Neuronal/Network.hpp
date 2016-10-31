//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_NETWORK_HPP
#define SKYNET_NETWORK_HPP

#include        <vector>
#include        <json11/json11.hpp>

namespace       Skynet {
    namespace       Neuronal {
        class           Network {
        public:
            virtual void                        reset(unsigned int) = 0;
            virtual void                        exec() = 0;
            virtual void                        learn() = 0;
            virtual void                        update(double = 0) = 0;
            virtual void                        generate(json11::Json const&) = 0;
            virtual void                        load(json11::Json const&) {}
            virtual void                        save(json11::Json &) = 0;

            virtual void                        setInputs(std::vector<double> const&) = 0;
            virtual std::vector<double> const   &getOutputs() const = 0;
        };
    }
}

#endif //SKYNET_NETWORK_HPP
