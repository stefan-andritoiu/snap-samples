cmake_minimum_required(VERSION 2.8.9)
project (MRAA)

file(GLOB SOURCES "src/*.cpp")
#For the shared library:

find_package (PkgConfig REQUIRED)

# Force a libmraa search and minimum required version every time a config is generated
unset(MRAA_FOUND CACHE)
set(MRAA_MINIMUM 1.7.0)
pkg_check_modules (MRAA REQUIRED mraa>=${MRAA_MINIMUM})

if (MRAA_FOUND)
  message(STATUS "mraa include path:    "  ${MRAA_INCLUDE_DIRS})
  include_directories(${MRAA_INCLUDE_DIRS})
endif (MRAA_FOUND)

set ( PROJECT_LINK_LIBS libmraa.so )

add_executable(blink ${SOURCES})
target_link_libraries(blink ${PROJECT_LINK_LIBS} )
install(TARGETS blink DESTINATION /bin)
