cmake_minimum_required(VERSION 3.24)

project(UsandoPdf
  LANGUAGES C CXX
  VERSION 1.0.0.0
  DESCRIPTION "Using pdf Files"
  HOMEPAGE_URL "https://github.com/PeterLag1/cpp-project-practice/UsandoJson"
)

# Agregar librería para trabajar con PDF
find_package(unofficial-libharu CONFIG REQUIRED)

add_executable(${PROJECT_NAME} Main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::libharu::haru)
