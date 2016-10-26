//
// Created by sebastien on 10/21/16.
//

#ifndef SKYNET_UNSUPERVISEDEXPERIENCE_HPP_HPP
#define SKYNET_UNSUPERVISEDEXPERIENCE_HPP_HPP

#include        "Neuronal/Experience.hpp"

namespace       Skynet {
    namespace       Neuronal {

        class           UnsupervisedExperience : public Experience {
        public:
            virtual void    apply(Network &, bool = false);
        private:
        };

    }
}

#endif //SKYNET_UNSUPERVISEDEXPERIENCE_HPP_HPP
