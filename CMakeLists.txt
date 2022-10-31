cmake_minimum_required(VERSION 3.16)

project(logical_expression_evaluation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("CXX_FLAGS " ${CMAKE_CXX_STANDARD})
enable_testing()

if (BUILD_TESTING)
# lc   include(CTest)
#    find_package(GTest REQUIRED)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    #add_executable(${PROJECT_NAME} tests/run_all_tests.cpp main.cpp)
    #add_subdirectory(tests)
#else()
#    add_executable(${PROJECT_NAME} main.cpp)
endif()

add_subdirectory(tokenizer)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} logical_expression_tokenizer)
