cmake_minimum_required(VERSION 4.3.3)
project(LockFreeIPC)
add_executable(${PROJECT_NAME} src/main.cpp)
#add_library(circular_buffer SHARED examples/circularBuffer/circularBuffer.cpp)
#target_link_libraries(${PROJECT_NAME} circular_buffer)
add_subdirectory(3rdParty/googletest)
# Test Executable
add_executable(test_circularBuffer tests/TestCircularBuffer.cpp examples/circularBuffer/circularBuffer.cpp)
target_include_directories(test_circularBuffer PRIVATE
    examples/circularBuffer                      # so test can #include "circularBuffer.cpp" or .h
    3rdParty/googletest/googletest/include
)
target_link_libraries(test_circularBuffer
    gtest
    gtest_main
)

enable_testing()
add_test(NAME CircularBufferTests COMMAND test_circularBuffer)