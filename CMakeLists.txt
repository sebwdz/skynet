
cmake_minimum_required (VERSION 2.8)
project (Skynet)

include_directories(Skynet ./includes/ ./libs/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -L ./libs/ -g")

set(SOURCES_FILES
        libs/json11/json11.cpp
        srcs/main.cpp
        srcs/Neuronal/Excitable.cpp
        srcs/Neuronal/Neuron.cpp
        srcs/Tools/Utils.cpp
        includes/Neuronal/Neuron.hpp
        includes/Neuronal/Excitable.hpp
        includes/Neuronal/Neuron/Simple.hpp
        srcs/Neuronal/Neuron/Simple.cpp
        includes/Tools/Math/Function.hpp
        srcs/Tools/Math/Function.cpp
        includes/Neuronal/Neuron/Perceptron.hpp
        srcs/Neuronal/Neuron/Perceptron.cpp
        includes/Neuronal/Neuron/MLP.hpp
        srcs/Neuronal/Neuron/MLP.cpp
        includes/Neuronal/Network.hpp
        includes/Neuronal/Network/Perceptron.hpp
        includes/Neuronal/Network/SimplePerceptron.hpp
        includes/Neuronal/Network/PerceptronLayer.hpp
        srcs/Neuronal/Network/PerceptronLayer.cpp
        srcs/Neuronal/Network/Perceptron.cpp
        srcs/Neuronal/Network/SimplePerceptron.cpp
        includes/Neuronal/Experience.hpp
        srcs/Neuronal/Experience.cpp
        includes/Neuronal/Network/MLPerceptron.hpp
        srcs/Neuronal/Network/MLPerceptron.cpp
        includes/Neuronal/Network/SupervisedNetwork.hpp
        includes/Neuronal/LearningSession.hpp
        srcs/Neuronal/LearningSession.cpp
        includes/Neuronal/LearningSession/SupervisedSession.hpp
        srcs/Neuronal/LearningSession/SupervisedSession.cpp
        srcs/Neuronal/Network/SupervisedNetwork.cpp
        includes/Neuronal/Loader/Loader.hpp
        srcs/Neuronal/Loader/Loader.cpp
        includes/Neuronal/Network/SelfOrganizingMap.hpp
        includes/Neuronal/Neuron/SelfOrganizingMapNeuron.hpp
        srcs/Neuronal/Neuron/SelfOrganizingMapNeuron.cpp
        srcs/Neuronal/Network/SelfOrganizingMap.cpp
        srcs/Data/DbObject.cpp
        srcs/Data/DbReader.cpp
        srcs/Data/Extract.cpp
        srcs/Data/Exporter.cpp
        srcs/Neuronal/LearningSession/UnsupervisedSession.cpp
        srcs/Manager/Request.cpp
        srcs/Manager/AManager.cpp
        srcs/Manager/MainManager.cpp)

add_executable(Skynet ${SOURCES_FILES})

target_link_libraries(Skynet X11 GL GLU SDL pqxx)