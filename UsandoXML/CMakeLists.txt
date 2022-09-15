cmake_minimum_required(VERSION 3.24)

project(UsandoXml
  LANGUAGES C CXX
  VERSION 1.0.0.0
  DESCRIPTION "Using XML Files"
  HOMEPAGE_URL "https://github.com/fontseca/cpp-project-practice"
)

find_package(bitserializer CONFIG REQUIRED)

add_executable(
  ${PROJECT_NAME}
    Main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
    PRIVATE
      BitSerializer::core
)