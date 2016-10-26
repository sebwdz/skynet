//
// Created by sebastien on 10/21/16.
//

#include "Neuronal/Loader/SessionLoader.hpp"
#include "Neuronal/LearningSession/UnsupervisedSession.hpp"
#include "Neuronal/LearningSession/SupervisedSession.hpp"

namespace       Skynet {
    namespace       Neuronal {

        LearningSession* SessionLoader::getSession(std::string const &str) {
            LearningSession     *session;

            if (str == "SelfOrganizingMap")
                session = new UnsupervisedSession();
            else
                session = new SupervisedSession();
            return (session);
        }

        SessionLoader& SessionLoader::getInstance() {
            static SessionLoader       instance;
            return (instance);
        }

    }
}