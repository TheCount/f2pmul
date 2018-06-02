include_directories( ${CMAKE_SOURCE_DIR} )

# Test macro
macro( test TESTNAME )
	add_executable( ${TESTNAME}-test ${TESTNAME}.c )
	add_test( ${TESTNAME}-Test ${TESTNAME}-test )
endmacro( test )

test( modmatrix )
test( modtest )
test( multest )
