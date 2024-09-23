set(LIBRARY_SOURCES
    "ellipsoid.cpp"
    "ellipse.cpp")
set(LIBRARY_HEADERS
    "ellipsoid.hpp"
    "ellipse.hpp")
set(LIBRARY_INCLUDES "./")

add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC
    ${LIBRARY_INCLUDES})
target_link_libraries(${LIBRARY_NAME} PUBLIC Eigen3::Eigen)
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})
