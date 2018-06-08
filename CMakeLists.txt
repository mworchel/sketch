cmake_minimum_required(VERSION 3.9)

project(sketch LANGUAGES CXX)

set(APP_NAME sketch-app)

# Collect source files
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/application.cpp")
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/application.hpp")
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/ball.cpp")
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/ball.hpp")
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/force.cpp")
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/force_provider.hpp")
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/force_providers.hpp")
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/main.cpp")
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/vector_helper.hpp")
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/world.cpp")
list(APPEND APP_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/world.hpp")

add_executable(${APP_NAME} ${APP_SOURCE_FILES})

target_compile_features(${APP_NAME} PUBLIC cxx_std_11)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${APP_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
