cmake_minimum_required(VERSION 3.24)

project(UsandoJson
  LANGUAGES C CXX
  VERSION 1.0.0.0
  DESCRIPTION "Using json Files"
  HOMEPAGE_URL "https://github.com/PeterLag1/cpp-project-practice/UsandoJson"
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

# this is heuristically generated, and may not be correct
# find_package(cpprestsdk CONFIG REQUIRED)

# # note: 1 additional targets are not displayed.
# target_link_libraries(
#   ${PROJECT_NAME}
#     PRIVATE
#       cpprestsdk::cpprest
#       cpprestsdk::cpprestsdk_zlib_internal
#       cpprestsdk::cpprestsdk_boost_internal
#       cpprestsdk::cpprestsdk_openssl_internal
# )