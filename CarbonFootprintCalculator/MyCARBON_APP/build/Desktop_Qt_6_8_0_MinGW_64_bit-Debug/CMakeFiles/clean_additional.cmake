# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CarbonFootprintCalculator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CarbonFootprintCalculator_autogen.dir\\ParseCache.txt"
  "CarbonFootprintCalculator_autogen"
  )
endif()
