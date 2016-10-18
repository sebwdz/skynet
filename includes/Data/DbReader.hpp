//
// Created by sebastien on 10/12/16.
//

#ifndef SKYNET_DBREADER_HPP
#define SKYNET_DBREADER_HPP

#include "DbObject.hpp"

namespace Skynet {
    namespace Data {

        class           DbReader {
        public:
            void        setDb(DbObject*);
            void        setVariables(json11::Json const&);

            void        list(std::string &, json11::Json const&);
            void        condition(std::string &, json11::Json const&);
            void        execute(json11::Json const&);
        private:
            DbObject        *m_db;
            json11::Json    m_vars;
        };
    }
}

#endif //SKYNET_DBREADER_HPP
