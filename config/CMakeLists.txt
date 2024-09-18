# Specify the path for config file
set(CONFIG_IN ${CMAKE_SOURCE_DIR}/config/config.hpp.in)
set(CONFIG_OUT ${CMAKE_BINARY_DIR}/configured_files/include/config.hpp)

# Use CMake's configure_file to replace variables in config file
configure_file(${CONFIG_IN} ${CONFIG_OUT} @ONLY)



# Specify the path for Doxygen config file
set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/config/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_SOURCE_DIR}/docs/Doxyfile)

# Use CMake's configure_file to replace variables in Doxygen config
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)