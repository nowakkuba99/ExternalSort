include(FetchContent)

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

add_test(hello_gtests test_module)