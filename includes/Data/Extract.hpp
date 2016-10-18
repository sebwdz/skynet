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
            struct      Values {
                std::vector<double>     _values;
            };

            void    extract(json11::Json const&, json11::Json const&);
            std::vector<Values*> const  &getValues() const;

        private:
            std::vector<Values*>     m_values;

        };
    }
}

#endif //SKYNET_DATAEXTRACT_HPP