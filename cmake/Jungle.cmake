execute_process(
  COMMAND ./prepare.sh -j8
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Jungle"
)
add_subdirectory(Jungle)