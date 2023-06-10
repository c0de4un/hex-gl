# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# CONFIG
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

include( "${CMAKE_CURRENT_SOURCE_DIR}/gl/config.cmake" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# CONSTANTS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( HEX_GL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gl" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# HEADERS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( HEX_GL_PUBLIC "${HEX_GL_DIR}/public/hex/gl/" )
set( HEX_GL_HEADERS
    # CFG
    "${HEX_GL_PUBLIC}cfg/hex_gl.hpp"
    # RENDER
    "${HEX_GL_PUBLIC}render/GLState.hpp"
    "${HEX_GL_PUBLIC}render/GLRenderer.hpp"
    # ASSETS
    "${HEX_GL_PUBLIC}assets/GLProgram.hpp"
    "${HEX_GL_PUBLIC}assets/GLShader.hpp"
)

# Append to Exportable Headers
set( HEX_EXPORT_HEADERS ${HEX_GL_HEADERS} ${HEX_EXPORT_HEADERS} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# SOURCES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( HEX_GL_PRIVATE "${HEX_GL_DIR}/private/hex/gl/" )
set( HEX_GL_SOURCES
    # RENDER
    "${HEX_GL_PRIVATE}render/GLState.cpp"
    "${HEX_GL_PRIVATE}render/GLRenderer.cpp"
    # ASSETS
    "${HEX_GL_PRIVATE}assets/GLProgram.cpp"
    "${HEX_GL_PRIVATE}assets/GLShader.cpp"
)

# Append to Exportable Sources
set( HEX_EXPORT_SOURCES ${HEX_GL_SOURCES} ${HEX_EXPORT_SOURCES} )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
