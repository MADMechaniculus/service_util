cmake_minimum_required(VERSION 3.0)
project(service_util)

add_definitions(-DUSE_BOOST)

link_libraries(-lboost_system -lboost_thread -lpthread)

add_library(${PROJECT_NAME} STATIC ./service.cpp ./service.h)