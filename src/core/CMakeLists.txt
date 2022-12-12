set(NAME "core")

#include(${PROJECT_SOURCE_DIR}/cmake/StaticAnalyzers.cmake)

add_library(${NAME} STATIC
        Application.cpp
        Application.hpp
        Window.cpp
        Window.hpp)

target_include_directories(${NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${NAME} PRIVATE cxx_std_20)
target_link_libraries(${NAME}
#  PRIVATE project_warnings
  # Added SDL2::SDL2 and imgui here.
#  PUBLIC fmt spdlog SDL2::SDL2 imgui)
  PUBLIC SDL2::SDL2 imgui)
