if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_library(logical_node node.cpp)

target_include_directories(
        logical_node
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        logical_node
)