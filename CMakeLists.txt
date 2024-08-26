cmake_minimum_required(VERSION 3.22.1)
project(Coretech)

set(CMAKE_CXX_STANDARD 14)

# Find libpcap
find_package(PkgConfig REQUIRED)
pkg_check_modules(PCAP REQUIRED libpcap)

include_directories(${PCAP_INCLUDE_DIRS})
link_directories(${PCAP_LIBRARY_DIRS})

add_executable(Coretech
        PcapReader.cpp
        Main.cpp
        Menu.cpp
        PcapReader.h
        Menu.h)

# Link libpcap with your executable
target_link_libraries(Coretech ${PCAP_LIBRARIES})