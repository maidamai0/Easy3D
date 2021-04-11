get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(LIB_NAME ${APP_NAME}.${PROJECT_NAME})

file(GLOB srcs *.cpp)
add_library(${LIB_NAME} ${srcs})

# target_include_directories(${PROJECT_NAME} PRIVATE ${EASY3D_THIRD_PARTY}/imgui)
# target_link_libraries(${PROJECT_NAME} 3rd_imgui easy3d::core easy3d::renderer easy3d::viewer easy3d::util)