set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(REQUIRED_SOURCES)

include(CheckFunctionExists)
set(CMAKE_REQUIRED_LIBRARIES Threads::Threads)
check_function_exists(pthread_barrier_init HAVE_PTHREAD_BARRIER)
if(HAVE_PTHREAD_BARRIER)
    ADD_DEFINITIONS(-DHAVE_PTHREAD_BARRIER=1)   
else()
    list(APPEND REQUIRED_SOURCES "pthread_barrier.c")
    ADD_DEFINITIONS(-DHAVE_PTHREAD_BARRIER=0)
endif()

set(TEST_LIBRARIES fiber Threads::Threads dl)

# Build tests
file(GLOB testFiles test_*.c)
foreach(testFile ${testFiles})
    file(RELATIVE_PATH test_file ${CMAKE_CURRENT_SOURCE_DIR} ${testFile})
    string(REGEX REPLACE "^(test_[0-9a-zA-Z_\\-]+)\.c.*$" "\\1" test
                         "${test_file}")
    add_executable(${test} ${test_file} ${REQUIRED_SOURCES})
    target_link_libraries(${test} PRIVATE ${TEST_LIBRARIES})
    add_test(NAME ${test}
             COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test})
endforeach(testFile)
