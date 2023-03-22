# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BookStoreProgram_autogen"
  "CMakeFiles\\BookStoreProgram_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BookStoreProgram_autogen.dir\\ParseCache.txt"
  )
endif()
