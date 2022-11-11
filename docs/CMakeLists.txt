find_package(Doxygen QUIET)

message(VERBOSE "Doxygen settings :")
message(VERBOSE "${PROJECT_NAME}_SOURCE_DIR :  " ${${PROJECT_NAME}_SOURCE_DIR})
message(VERBOSE "${PROJECT_NAME}_BINARY_DIR :  " ${${PROJECT_NAME}_BINARY_DIR})
message(VERBOSE "DOXYGEN_EXECUTABLE :  " ${DOXYGEN_EXECUTABLE})

if(DOXYGEN_FOUND)
  configure_file(${${PROJECT_NAME}_SOURCE_DIR}/docs/Doxyfile-html.cmake ${${PROJECT_NAME}_BINARY_DIR}/docs/Doxyfile-html)
  add_custom_target(html ${DOXYGEN_EXECUTABLE} ${${PROJECT_NAME}_BINARY_DIR}/docs/Doxyfile-html)
endif (DOXYGEN_FOUND)
