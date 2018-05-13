cmake_minimum_required( VERSION 3.0 )
project( f2pmul )
enable_testing()

# Version
set( F2PMUL_VERSION_MAJOR 0 )
set( F2PMUL_VERSION_MINOR 0 )
set( F2PMUL_VERSION_PATCH 0 )
set( F2PMUL_VERSION "${F2PMUL_VERSION_MAJOR}.${F2PMUL_VERSION_MINOR}.${F2PMUL_VERSION_PATCH}" )

# Subdirs
add_subdirectory( test )
