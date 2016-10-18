//
// Created by sebastien on 8/20/16.
//

#ifndef SKYNET_SUPERVISEDSESSION_HPP
#define SKYNET_SUPERVISEDSESSION_HPP

#include <json11/json11.hpp>
#include        "Neuronal/LearningSession.hpp"

namespace   Skynet {
    namespace       Neuronal {
        class           SupervisedSession : public LearningSession{
        public:
            void                setStop(double);

            virtual void        exec();
            void                load(json11::Json const&);
            void                loadExperiences(json11::Json const&, std::vector<Experience*>&);
            double              evaluate();

        protected:
            double      m_stop;
        };
    }
}

#endif //SKYNET_SUPERVISEDSESSION_HPP
