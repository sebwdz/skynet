//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_PERCEPTRONLAYER_HPP
#define SKYNET_PERCEPTRONLAYER_HPP

#include            <vector>
#include            "Neuronal/Excitable.hpp"

namespace           Skynet {
    namespace           Neuronal {
        class               PerceptronLayer {
        public:
            void            addCell(Excitable*);
            void            exec();
            void            learn();
            void            setCoef(double);

            Excitable       *getCell(unsigned int) const;
            unsigned int    getCellsNb() const;
        private:
            std::vector<Excitable*>     m_cells;
        };
    }
}

#endif //SKYNET_PERCEPTRONLAYER_HPP
