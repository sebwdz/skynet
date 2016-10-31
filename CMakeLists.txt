cmake_minimum_required(VERSION 3.5)
project(skynet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

include_directories(includes libs)

set(SOURCE_FILES
        includes/Data/DbObject.hpp
        includes/Data/DbReader.hpp
        includes/Data/Exporter.hpp
        includes/Data/Extract.hpp
        includes/Manager/AManager.hpp
        includes/Manager/MainManager.hpp
        includes/Manager/Request.hpp
        includes/Neuronal/LearningSession/SupervisedSession.hpp
        includes/Neuronal/LearningSession/UnsupervisedSession.hpp
        includes/Neuronal/Loader/Loader.hpp
        includes/Neuronal/Network/MLPerceptron.hpp
        includes/Neuronal/Network/Perceptron.hpp
        includes/Neuronal/Network/PerceptronLayer.hpp
        includes/Neuronal/Network/SelfOrganizingMap.hpp
        includes/Neuronal/Network/SimplePerceptron.hpp
        includes/Neuronal/Network/SupervisedNetwork.hpp
        includes/Neuronal/Neuron/MLP.hpp
        includes/Neuronal/Neuron/Perceptron.hpp
        includes/Neuronal/Neuron/SelfOrganizingMapNeuron.hpp
        includes/Neuronal/Neuron/Simple.hpp
        includes/Neuronal/Excitable.hpp
        includes/Neuronal/Experience.hpp
        includes/Neuronal/LearningSession.hpp
        includes/Neuronal/Network.hpp
        includes/Neuronal/Neuron.hpp
        includes/Tools/Math/Function.hpp
        includes/Tools/Utils.hpp
        includes/chanel.hpp
        srcs/Data/DbObject.cpp
        srcs/Data/DbReader.cpp
        srcs/Data/Exporter.cpp
        srcs/Data/Extract.cpp
        srcs/Manager/AManager.cpp
        srcs/Manager/MainManager.cpp
        srcs/Manager/Request.cpp
        srcs/Neuronal/LearningSession/SupervisedSession.cpp
        srcs/Neuronal/LearningSession/UnsupervisedSession.cpp
        srcs/Neuronal/Loader/Loader.cpp
        srcs/Neuronal/Network/MLPerceptron.cpp
        srcs/Neuronal/Network/Perceptron.cpp
        srcs/Neuronal/Network/PerceptronLayer.cpp
        srcs/Neuronal/Network/SelfOrganizingMap.cpp
        srcs/Neuronal/Network/SimplePerceptron.cpp
        srcs/Neuronal/Network/SupervisedNetwork.cpp
        srcs/Neuronal/Neuron/MLP.cpp
        srcs/Neuronal/Neuron/Perceptron.cpp
        srcs/Neuronal/Neuron/SelfOrganizingMapNeuron.cpp
        srcs/Neuronal/Neuron/Simple.cpp
        srcs/Neuronal/Excitable.cpp
        srcs/Neuronal/Experience.cpp
        srcs/Neuronal/LearningSession.cpp
        srcs/Neuronal/Neuron.cpp
        srcs/Tools/Math/Function.cpp
        srcs/Tools/Utils.cpp
        includes/Manager/Network.hpp
        srcs/Manager/Network.cpp
        includes/Neuronal/Experiences/SupervisedExperience.hpp
        includes/Neuronal/Experiences/UnsupervisedExperience.hpp
        srcs/Neuronal/Experiences/SupervisedExperience.cpp
        srcs/Neuronal/Experiences/UnsupervisedExperience.cpp
        includes/Neuronal/Loader/SessionLoader.hpp
        srcs/Neuronal/Loader/SessionLoader.cpp
        includes/Manager/Interpreter.hpp
        srcs/Manager/Interpreter.cpp
        includes/Manager/Exporter.hpp
        srcs/Manager/Exporter.cpp
        srcs/thriftServer.cpp
        thrift/gen-cpp/Network.cpp
        thrift/gen-cpp/network_constants.cpp
        thrift/gen-cpp/network_types.cpp
        thrift/gen-cpp/shared_constants.cpp
        thrift/gen-cpp/shared_types.cpp
        thrift/gen-cpp/SharedService.cpp)

add_executable(skynet ${SOURCE_FILES})

target_link_libraries(skynet json11 pqxx thrift)