set(LIBRARY_SOURCES
    "ellipsoid_closest_surface_point.cpp"
    )
set(LIBRARY_HEADERS
    )
set(LIBRARY_INCLUDES "./")

set(SUB_LIBRARY_NAME "Distances")

add_library(${SUB_LIBRARY_NAME} STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS})
target_include_directories(${SUB_LIBRARY_NAME} PUBLIC
    ${LIBRARY_INCLUDES}
    "../ellipsoid")
target_link_libraries(${SUB_LIBRARY_NAME} PUBLIC Eigen3::Eigen)