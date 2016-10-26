//
// Created by sebastien on 10/12/16.
//

#ifndef SKYNET_DATAEXTRACT_HPP
#define SKYNET_DATAEXTRACT_HPP

#include    "json11/json11.hpp"

namespace Skynet {
    namespace Data {

        class       Extract {
        public:

            void    extract(json11::Json const&, json11::Json const&);
            json11::Json const          &getResult() const;

        private:
            json11::Json                m_result;

        };
    }
}

#endif //SKYNET_DATAEXTRACT_HPP
