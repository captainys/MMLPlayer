set(TARGET_NAME mozart_piano_sonata)
add_executable(${TARGET_NAME} MACOSX_BUNDLE main.cpp)

target_link_libraries(${TARGET_NAME} fssimplewindow mmlplayer yssimplesound yssimplesound_platform)
