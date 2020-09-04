file(GLOB_RECURSE XTL_SRC_LIST
        *.cpp
        string/*.cpp
        string/impl/*.cpp)

include_directories(${PROJECT_SOURCE_DIR})

add_library(xtl STATIC ${XTL_SRC_LIST})

target_link_libraries(${PROJECT_NAME} pthread)
