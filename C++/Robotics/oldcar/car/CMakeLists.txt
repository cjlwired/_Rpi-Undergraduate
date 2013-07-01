## Define application name and sources
set(APP_NAME car)
set(APP_SOURCES Main.cpp App.cpp GripControl.cpp App.h GripControl.h)

## List geometry files
set(GEOMETRY_FILES hw2_part.pdat hw2_ground.pdat hw2_grip3.pdat hw2_grip5.pdat hw2_grip10.pdat hw2_grip20.pdat)


## Configure the xml file and copy to data directory
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/car.xml.in" "${DVC_DATA_DIR}/car.xml" )


## Build and link application
add_executable (${APP_NAME} ${APP_SOURCES})
target_link_libraries (${APP_NAME} ${DVC_LIBRARIES})



## This is an unsafe hack for Visual Studio :-)
if (MSVC)
	set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:msvcrt.lib")
endif(MSVC)


## Copy geometry files to data directory as a post build step
foreach(file ${GEOMETRY_FILES})
  add_custom_command(
    TARGET ${APP_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${file}" "${DVC_DATA_DIR}/Geometry/${file}")  
endforeach(file ${GEOMETRY_FILES}})

