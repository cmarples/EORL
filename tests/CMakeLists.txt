include(Catch)

set(TEST_MAIN "unit_tests.exe")
set(TEST_SOURCES 
    "test_ellipsoid.cpp"
    "test_ellipse.cpp"
)

set(TEST_INCLUDES "./")

add_executable(${TEST_MAIN} ${TEST_SOURCES})
target_include_directories(${TEST_MAIN} PUBLIC ${TEST_INCLUDES})
target_link_libraries(${TEST_MAIN} PUBLIC ${LIBRARY_NAME} Ellipse Catch2::Catch2WithMain)

catch_discover_tests(${TEST_MAIN})
