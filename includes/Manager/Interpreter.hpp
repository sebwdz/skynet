//
// Created by sebastien on 10/22/16.
//

#ifndef SKYNET_INTERPRETER_HPP
#define SKYNET_INTERPRETER_HPP

#include <Data/Extract.hpp>
#include "AManager.hpp"

namespace   Skynet {
    namespace   Manager {
        class       Interpreter : public AManager {
        public:
            Interpreter(json11::Json const&);

            void            execute(json11::Json const&, json11::Json const&);
        private:
            Data::Extract   m_extracter;
        };
    }
}

#endif //SKYNET_INTERPRETER_HPP
