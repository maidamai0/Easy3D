file(GLOB srcs *.cpp)
if(WIN32)
    add_executable(${APP_NAME} WIN32 ${srcs})
else()
    add_executable(${APP_NAME} ${srcs})
endif(WIN32)

# target_include_directories(${PROJECT_NAME} PRIVATE ${EASY3D_THIRD_PARTY}/imgui)
target_link_libraries(${APP_NAME} ${APP_NAME}.view ${APP_NAME}.state easy3d::core easy3d::renderer easy3d::viewer easy3d::util)