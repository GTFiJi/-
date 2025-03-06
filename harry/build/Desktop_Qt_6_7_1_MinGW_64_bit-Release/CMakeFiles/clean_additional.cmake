# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\hdjkshdjsad_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\hdjkshdjsad_autogen.dir\\ParseCache.txt"
  "hdjkshdjsad_autogen"
  )
endif()
