

set(WIREDTIGER_WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/wiredtiger")

include(FindPkgConfig)

list(APPEND CMAKE_PREFIX_PATH "${WIREDTIGER_WORKING_DIRECTORY}/installDir")
pkg_check_modules(WIREDTIGER IMPORTED_TARGET GLOBAL wiredtiger)

if (${WIREDTIGER_FOUND})
  return()
endif()

execute_process(
  COMMAND mkdir -p installDir
  WORKING_DIRECTORY ${WIREDTIGER_WORKING_DIRECTORY}
)

execute_process(
  COMMAND cmake -B build -G Ninja
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=installDir
  WORKING_DIRECTORY ${WIREDTIGER_WORKING_DIRECTORY}
)

execute_process(
  COMMAND cmake --build build -j4
  WORKING_DIRECTORY ${WIREDTIGER_WORKING_DIRECTORY}
)

execute_process(
  COMMAND cmake --install build
  WORKING_DIRECTORY ${WIREDTIGER_WORKING_DIRECTORY}
)

pkg_check_modules(WIREDTIGER REQUIRED wiredtiger)


