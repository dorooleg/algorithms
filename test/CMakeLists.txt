include_directories("${PROJECT_SOURCE_DIR}")

add_executable(stack_test stack_test.cpp)
target_link_libraries(stack_test gtest)
add_test(NAME stack_test COMMAND stack_test)

add_executable(hashed_array_tree hashed_array_tree_test.cpp)
target_link_libraries(hashed_array_tree gtest)
add_test(NAME hashed_array_tree COMMAND hashed_array_tree)
