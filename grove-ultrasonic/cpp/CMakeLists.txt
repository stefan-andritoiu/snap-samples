cmake_minimum_required(VERSION 2.8.9)
project (UPM)

file(GLOB SOURCES "src/*.cxx")

find_package (PkgConfig REQUIRED)

# Force a libmraa search and minimum required version every time a config is generated
unset(MRAA_FOUND CACHE)
set(MRAA_MINIMUM 1.7.0)
pkg_check_modules (MRAA REQUIRED mraa>=${MRAA_MINIMUM})

if (MRAA_FOUND)
  message(STATUS "mraa include path:    "  ${MRAA_INCLUDE_DIRS})
  include_directories(${MRAA_INCLUDE_DIRS})
endif (MRAA_FOUND)


unset(UPM_FOUND CACHE)
set(UPM_MINIMUM 1.3.0)
pkg_check_modules (UPM REQUIRED upm-grovespeaker>=${UPM_MINIMUM})

if (UPM_FOUND)
  message(STATUS "UPM include path:    "  ${UPM_INCLUDE_DIRS})
  include_directories(${UPM_INCLUDE_DIRS})
endif (UPM_FOUND)


#For the shared library:
set ( PROJECT_LINK_LIBS libmraa.so libupm-groveultrasonic.so )

add_executable(ultrasonic ${SOURCES})
target_compile_options(ultrasonic PUBLIC -std=c++11)
target_link_libraries(ultrasonic ${PROJECT_LINK_LIBS} )
install(TARGETS ultrasonic DESTINATION /bin)
