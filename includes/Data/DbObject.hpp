//
// Created by sebastien on 10/12/16.
//

#ifndef SKYNET_DBOBJECT_HPP
#define SKYNET_DBOBJECT_HPP

#include    <pqxx/pqxx>
#include    "json11/json11.hpp"

namespace Skynet {
    namespace Data {

        class               DbObject {
        public:
            void            connect(std::string const&);
            void            execute(std::string const&);

            void            commit();

            json11::Json const  &getResult();

        private:
            pqxx::connection        *m_connection;
            pqxx::work              *m_work;
            json11::Json            m_result;
        };
    }
}

#endif //SKYNET_DBOBJECT_HPP
