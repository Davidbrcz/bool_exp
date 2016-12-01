cmake_minimum_required (VERSION 2.8)
project(gram)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Wextra -Wno-overloaded-virtual")  

find_package(Java REQUIRED)
if (NOT ANTLR_JAR_LOCATION)
    message(FATAL_ERROR "Missing antlr4.jar location. You can specify it's path using: -DANTLR_JAR_LOCATION=<path>")
  else()
    get_filename_component(ANTLR_NAME ${ANTLR_JAR_LOCATION} NAME_WE)
    if(NOT EXISTS "${ANTLR_JAR_LOCATION}")
      message(FATAL_ERROR "Unable to find ${ANTLR_NAME} in ${ANTLR_JAR_LOCATION}")
    else()
      message(STATUS "Found ${ANTLR_NAME}: ${ANTLR_JAR_LOCATION}")
    endif()
endif()
  
add_custom_target(GenerateParser
   COMMAND
   ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/generated
   COMMAND
   "${Java_JAVA_EXECUTABLE}" -jar ${ANTLR_JAR_LOCATION} -Dlanguage=Cpp -listener -visitor -o ${PROJECT_SOURCE_DIR}/generated/ -package gram ${PROJECT_SOURCE_DIR}/gram.g4
   WORKING_DIRECTORY
   "${CMAKE_BINARY_DIR}")


include_directories(generated)
include_directories(/usr/local/include)

link_directories(/usr/local/lib/)
add_executable(bool_expr main.cpp listener.cpp expr.cpp rewriter.cpp
  ${PROJECT_SOURCE_DIR}/generated/gramLexer.cpp
  ${PROJECT_SOURCE_DIR}/generated/gramParser.cpp
  ${PROJECT_SOURCE_DIR}/generated/gramBaseListener.cpp
  ${PROJECT_SOURCE_DIR}/generated/gramBaseVisitor.cpp
  ${PROJECT_SOURCE_DIR}/generated/gramListener.cpp
  ${PROJECT_SOURCE_DIR}/generated/gramVisitor.cpp
  )

add_dependencies(bool_expr GenerateParser)
target_link_libraries(bool_expr antlr4-runtime)
