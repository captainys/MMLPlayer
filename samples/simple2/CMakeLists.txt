set(TARGET_NAME simple2)
add_executable(${TARGET_NAME} MACOSX_BUNDLE simple2.cpp)

target_link_libraries(${TARGET_NAME} fssimplewindow mmlplayer yssimplesound yssimplesound_platform)
