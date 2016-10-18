//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_EXCITABLE_HPP
#define SKYNET_EXCITABLE_HPP

namespace   Skynet
{
    namespace       Neuronal
    {
        class           Excitable {
        public:
            Excitable();
            virtual             ~Excitable() {}

            virtual void        exec();
            virtual void        learn();

            void                setOutput(double);
            double              getOutput() const;
        protected:
            double      m_output;
        };
    }
}

#endif //SKYNET_EXCITABLE_HPP
