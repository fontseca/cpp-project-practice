cmake_minimum_required(VERSION 3.24)

project(CppProjectPractice
  LANGUAGES C CXX
  VERSION 1.0.0.0
  DESCRIPTION "Practice C++ libraries"
  HOMEPAGE_URL "https://github.com/PeterLag1/cpp-project-practice"
)

add_subdirectory(UsandoJson)
add_subdirectory(UsandoXML)
add_subdirectory(UsandoYML)

