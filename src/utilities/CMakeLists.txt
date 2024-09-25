set(INPUT_SOURCES
    "newton_raphson.cpp")
set(INPUT_HEADERS
    "newton_raphson.hpp")

add_library(Input STATIC
    ${INPUT_SOURCES}
    ${INPUT_HEADERS})
target_include_directories(Input PUBLIC "./")