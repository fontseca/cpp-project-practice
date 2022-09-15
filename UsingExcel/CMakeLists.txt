cmake_minimum_required(VERSION 3.24)

project(UsandoExcel
  LANGUAGES C CXX
  VERSION 1.0.0.0
  DESCRIPTION "Using Excel Files"
  HOMEPAGE_URL "https://github.com/PeterLag1/cpp-project-practice/UsandoJson"
)

find_package(libxlsxwriter CONFIG REQUIRED)

add_executable(
  ${PROJECT_NAME}
    Main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
    PRIVATE
      libxlsxwriter
)