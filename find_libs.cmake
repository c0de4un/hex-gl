# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# GLAD
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( NOT DEFINED GLAD_INCLUDE_DIR )
    message( FATAL_ERROR "hexEngine.GL - <GLAD_INCLUDE_DIR>"  not defined)
endif ( NOT DEFINED GLAD_INCLUDE_DIR )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# GLFW
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( NOT DEFINED GLFW_INCLUDE_DIR )
    message( FATAL_ERROR "hexEngine.GL - <GLFW_INCLUDE_DIR> not defined" )
endif ( NOT DEFINED GLFW_INCLUDE_DIR )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
