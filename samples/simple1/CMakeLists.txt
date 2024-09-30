set(TARGET_NAME simple1)
add_executable(${TARGET_NAME} MACOSX_BUNDLE simple1.cpp)

target_link_libraries(${TARGET_NAME} fssimplewindow mmlplayer yssimplesound yssimplesound_platform)
