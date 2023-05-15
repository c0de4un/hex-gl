# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# OpenGL API Version
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( NOT DEFINED HEX_GL_MAJOR )
    message( STATUS "${CMAKE_PROJECT_NAME} - <HEX_GL_MAJOR> and/or <HEX_GL_MINOR> not set. Default value is set to 3.0" )
    set( HEX_GL_MAJOR 3 )
    set( HEX_GL_MINOR 0 )
endif ( NOT DEFINED HEX_GL_MAJOR )

message( STATUS "${CMAKE_PROJECT_NAME} - OpenGL API version is: ${HEX_GL_MAJOR}.${HEX_GL_MINOR}" )
add_definitions( -DHEX_GL_MAJOR=${HEX_GL_MAJOR} )
add_definitions( -DHEX_GL_MINOR=${HEX_GL_MINOR} )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
