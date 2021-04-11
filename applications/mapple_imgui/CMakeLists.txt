get_filename_component(APP_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})
add_subdirectory(state)
add_subdirectory(view)
add_subdirectory(app)