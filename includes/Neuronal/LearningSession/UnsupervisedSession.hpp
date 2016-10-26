//
// Created by sebastien on 10/13/16.
//

#ifndef SKYNET_UNSUPERVISEDSESSION_HPP
#define SKYNET_UNSUPERVISEDSESSION_HPP

#include    "Data/Extract.hpp"
#include    "Neuronal/LearningSession.hpp"
#include    "Neuronal/Experiences/UnsupervisedExperience.hpp"

namespace Skynet {
    namespace Neuronal {
        class       UnsupervisedSession : public LearningSession {
        public:
            void                load(json11::Json const&);
            void                loadExperiences(json11::Json const&);

            void                exec();
            double              evaluate();

        private:
            std::vector<UnsupervisedExperience*>    m_experiences;
            unsigned int                            m_iterations;
        };
    }
}

#endif //SKYNET_UNSUPERVISEDSESSION_HPP
