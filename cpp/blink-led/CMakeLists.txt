cmake_minimum_required(VERSION 2.8.9)
project (MRAA)

file(GLOB SOURCES "src/*.cpp")
#For the shared library:
set ( PROJECT_LINK_LIBS libmraa.so )

add_executable(blink ${SOURCES})
target_link_libraries(blink ${PROJECT_LINK_LIBS} )
install(TARGETS blink DESTINATION /bin)