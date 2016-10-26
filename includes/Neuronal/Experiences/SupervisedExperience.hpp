//
// Created by sebastien on 10/21/16.
//

#ifndef SKYNET_SUPERVISEDEXPERIENCES_H
#define SKYNET_SUPERVISEDEXPERIENCES_H

#include    "Neuronal/Experience.hpp"

namespace   Skynet {
    namespace   Neuronal {

        class           SupervisedExperience : public Experience {
        public:
            virtual void    apply(Network &, bool = false);
            void            calEqm();

            double          getEqm() const;
        private:
            std::vector<double>                 m_errors;
            double                              m_eqm;
        };

    }
}

#endif //SKYNET_SUPERVISEDEXPERIENCES_H
