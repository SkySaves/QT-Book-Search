# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BookSearch_autogen"
  "CMakeFiles\\BookSearch_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BookSearch_autogen.dir\\ParseCache.txt"
  )
endif()
