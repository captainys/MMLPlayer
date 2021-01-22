set(TARGET_NAME mozart_two_pianos)
add_executable(${TARGET_NAME} MACOSX_BUNDLE main.cpp)

target_link_libraries(${TARGET_NAME} fssimplewindow mmlplayer yssimplesound yssimplesound_platform)
