set(LIBRARY_SOURCES
    "ellipse.cpp"
	"ellipse_closest_boundary_point.cpp")
set(LIBRARY_HEADERS
    "ellipse.hpp")
set(LIBRARY_INCLUDES "./")

add_library(Ellipse STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS})
target_include_directories(Ellipse PUBLIC
    ${LIBRARY_INCLUDES})
target_link_libraries(Ellipse PUBLIC Eigen3::Eigen)
target_include_directories(Ellipse PUBLIC ${LIBRARY_INCLUDES})
