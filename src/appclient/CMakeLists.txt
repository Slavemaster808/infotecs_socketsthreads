set(target_name appcl)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
  ${target_name}
  PRIVATE
    appclient/mainclient.cpp
)

target_link_libraries(
  ${target_name}
  PRIVATE
    clnt
)