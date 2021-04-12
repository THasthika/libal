cmake_minimum_required(VERSION 3.12)

# set(PROJECT_NAME )

project(LibAl VERSION 0.1)

configure_file(libal_config.h.in libal_config.h)

set(LIBAL_INCLUDE_DIR      include/)
set(LIBAL_SRC_DIR     src/)

set(SRC_FILES
    ./src/bst.c
    ./src/common.c
    ./src/dynamic.c
    ./src/hash_table.c
    ./src/list.c
    ./src/queue.c
    ./src/rbt.c
    ./src/sort.c
    ./src/stack.c
)

set(INCLUDE_FILES
    ./include/bst.h
    ./include/common.h
    ./include/dynamic.h
    ./include/hash_table.h
    ./include/list.h
    ./include/queue.h
    ./include/rbt.h
    ./include/sort.h
    ./include/stack.h
)

add_library(${PROJECT_NAME} SHARED ${INCLUDE_FILES} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC "${LIBAL_INCLUDE_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIBAL_SRC_DIR}")

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    PUBLIC_HEADER "${INCLUDE_FILES}"
)

install(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include)

## TESTS
enable_testing()

set(TestTargets
    TestBST
    TestDynamic
    TestHashTable
    TestList
    TestQueue
    TestRBT
    TestSort
    TestStack
)
set(TestSources
    ./test/check_bst.c
    ./test/check_dynamic.c
    ./test/check_hash_table.c
    ./test/check_list.c
    ./test/check_queue.c
    ./test/check_rbt.c
    ./test/check_sort.c
    ./test/check_stack.c
)

foreach (tname tsource IN ZIP_LISTS TestTargets TestSources)
    add_executable(${tname} ${tsource})
    target_link_libraries(${tname} ${PROJECT_NAME})
    target_include_directories(${tname} PUBLIC ${LIBAL_INCLUDE_DIR})
    add_test(NAME ${tname} COMMAND ${tname})
endforeach()

