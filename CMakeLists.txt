cmake_minimum_required(VERSION 3.00)

project(bit)

set(DEBUG TRUE) 
if (DEBUG) 
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fsanitize=address") 
else ()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2") 
endif ()

aux_source_directory(src SRC)
aux_source_directory(test TEST)
add_library(bit STATIC ${SRC})

target_include_directories(bit PUBLIC /home/void/Projects/fse/bit/include)

enable_testing()

add_executable(test1 test/test1.c)
target_include_directories(test1 PRIVATE include)
target_link_libraries(test1 bit)
add_test(TEST_GREET test1)

add_executable(test2 test/test2.c) 
target_include_directories(test2 PRIVATE include)
target_link_libraries(test2 bit)
add_test(TEST_SINGLE_BIT test2)

add_executable(test3 test/test3.c) 
target_include_directories(test3 PRIVATE include)
target_link_libraries(test3 bit)
add_test(TEST_MULTI_BITS test3)

add_executable(test4 test/test4.c) 
target_include_directories(test4 PRIVATE include)
target_link_libraries(test4 bit)
add_test(TEST_MIX_ACCESS test4)

add_executable(test5 test/test5.c) 
target_include_directories(test5 PRIVATE include)
target_link_libraries(test5 bit)
add_test(TEST_EOF_BUFFER test5)

add_executable(test6 test/test6.c) 
target_include_directories(test6 PRIVATE include)
target_link_libraries(test6 bit)
add_test(TEST_OTHER test6)
