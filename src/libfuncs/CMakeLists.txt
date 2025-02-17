set(target_name helpfuncs)

add_library(${target_name} STATIC
  libfuncs/funcs.cpp
  libfuncs/funcs.hpp)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)