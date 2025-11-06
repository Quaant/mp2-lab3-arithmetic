set(SRC main_arithmetic.cpp)

include_directories(../include)

add_executable(main ${SRC})
target_link_libraries(main arithmetic)