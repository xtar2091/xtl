include_directories(${PROJECT_SOURCE_DIR})

add_executable(ThreadPool ThreadPool.cpp)

link_directories(${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME})
target_link_libraries(ThreadPool ${PROJECT_NAME} pthread)