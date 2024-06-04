cmake_minimum_required(VERSION 3.8)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC Debug Information Format Policy
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Project name
project("monopoly_ai")

add_subdirectory(extern/pybind11)
include_directories(${CMAKE_SOURCE_DIR}/extern/pybind11/include)
add_subdirectory(SFML)
include_directories(${CMAKE_SOURCE_DIR}/SFML/include)
add_subdirectory(monopoly_ai)
add_subdirectory(tests)

target_compile_definitions(monopoly_ai PRIVATE "BASE_PATH=\"${PROJECT_SOURCE_DIR}/\"")

