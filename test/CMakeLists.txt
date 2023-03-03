include(FetchContent)
set (CMAKE_CXX_STANDARD 17)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(test_module tests.cc)

target_link_libraries(test_module
 PRIVATE
  GTest::GTest
  readFile
  writeFile
  )

add_test(NAME hello_gtests COMMAND test_module "${CMAKE_CURRENT_LIST_DIR}")

#set_tests_properties(hello_gtests PROPERTIES ENVIRONMENT DATADIR = ${CMAKE_CURRENT_SOURCE_DIR}/tests)