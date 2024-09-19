set(EXE_SOURCES
    "main.cpp")
set(EXE_INCLUDES
    "./"
	"${CMAKE_BINARY_DIR}/configured_files/include")

add_executable(${EXECUTABLE_NAME} ${EXE_SOURCES})
target_include_directories(${EXECUTABLE_NAME} PUBLIC
    ${EXE_INCLUDES})
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${LIBRARY_NAME} 
    Eigen3::Eigen)
