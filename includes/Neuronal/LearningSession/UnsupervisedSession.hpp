//
// Created by sebastien on 10/13/16.
//

#ifndef SKYNET_UNSUPERVISEDSESSION_HPP
#define SKYNET_UNSUPERVISEDSESSION_HPP

#include    "Data/Extract.hpp"
#include    "Neuronal/LearningSession.hpp"

namespace Skynet {
    namespace Neuronal {
        class UnsupervisedSession : public LearningSession {
        public:
            void                load(json11::Json const&);
            void                setInputs(std::vector<Data::Extract::Values*> const&);

            void                exec();
            double              evaluate();

        private:
            unsigned int                        m_iterations;
            std::vector<Data::Extract::Values*> m_inputs;
        };
    }
}

#endif //SKYNET_UNSUPERVISEDSESSION_HPP
