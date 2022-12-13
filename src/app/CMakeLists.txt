set(NAME "App")

file(COPY fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${NAME} main.cpp)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${NAME} PRIVATE cxx_std_20)
target_link_libraries(${NAME} PRIVATE core)