# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# hexEngine.GL
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( HEX_GL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gl/public" )
if ( NOT EXISTS "${HEX_GL_INCLUDE_DIR}/hex/gl/cfg/hex_gl.hpp" )
    message( FATAL_ERROR "hexEngine.GL - hex_gl.hpp not found" )
endif ( NOT EXISTS "${HEX_GL_INCLUDE_DIR}/hex/gl/cfg/hex_gl.hpp" )

target_include_directories( hex PRIVATE ${HEX_GL_INCLUDE_DIR} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# GLAD
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

target_include_directories ( hex PUBLIC ${GLAD_INCLUDE_DIR} )
target_sources ( hex PUBLIC "${GLAD_DIR}/src/gl.c" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# GLFW
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( NOT GLFW3_FOUND )
    # Link GLFW3
    target_link_libraries ( hex glfw )

    # Include GLFW3 Headers
    target_include_directories ( hex PRIVATE ${GLFW_INCLUDE_DIR} )
else ( NOT GLFW3_FOUND )
    # Link GLFW3
    target_link_libraries ( hex ${GLFW3_LIBRARIES} )

    # Include GLFW3 Headers
    target_include_directories ( hex PRIVATE ${GLFW_INCLUDE_DIR} )
endif ( NOT GLFW3_FOUND )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
