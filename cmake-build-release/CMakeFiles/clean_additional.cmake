# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/OpenGLTP_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/OpenGLTP_autogen.dir/ParseCache.txt"
  "OpenGLTP_autogen"
  )
endif()
