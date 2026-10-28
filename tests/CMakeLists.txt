# TEST 1
add_executable(teststring teststring.cpp)
target_link_libraries(teststring PRIVATE ring_buffer_lib)
target_compile_features(teststring PRIVATE cxx_std_20)

enable_testing()
add_test(NAME UnitTests COMMAND teststring)
add_test(
    NAME StressFileTest 
    COMMAND teststring "${CMAKE_CURRENT_SOURCE_DIR}/data/names.txt"
)


# TEST 2
add_executable(testnumber testnumber.cpp)
target_link_libraries(testnumber PRIVATE ring_buffer_lib)
target_compile_features(testnumber PRIVATE cxx_std_20)
add_test(
    NAME TestNumber 
    COMMAND testnumber "${CMAKE_CURRENT_SOURCE_DIR}/data/numbers.txt"
)

# TEST 3
add_executable(test_typesafety test_typesafety.cpp)
target_link_libraries(test_typesafety PRIVATE ring_buffer_lib)
add_test(NAME TypeSafetyTest COMMAND test_typesafety)
