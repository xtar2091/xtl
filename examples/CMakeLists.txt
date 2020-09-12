include_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME})

add_executable(ThreadPool ThreadPool.cpp)
target_link_libraries(ThreadPool ${PROJECT_NAME} pthread)

add_executable(StringStream StringStream.cpp)
target_link_libraries(StringStream ${PROJECT_NAME})

add_executable(Log Log.cpp)
target_link_libraries(Log ${PROJECT_NAME} pthread)
