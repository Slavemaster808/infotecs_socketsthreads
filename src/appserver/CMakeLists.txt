set(target_name appserv)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
  ${target_name}
  PRIVATE
    appserver/mainserver.cpp
)

target_link_libraries(
  ${target_name}
  PRIVATE
    srvr
)