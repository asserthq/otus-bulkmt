cmake_minimum_required(VERSION 3.23)

project(bulk-mt)

add_executable(bulk-mt src/main.cpp src/bulk.h src/command_observer.h src/console_logger.h src/file_logger.h)

target_compile_features(bulk-mt PRIVATE cxx_std_20)
set_target_properties(bulk-mt PROPERTIES CXX_STANDARD_REQUIRED ON)