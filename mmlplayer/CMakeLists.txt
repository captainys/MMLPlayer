set(TARGET_NAME mmlplayer)
add_library(${TARGET_NAME} mmlplayer.cpp mmlplayer.h defaultFMB.cpp)
target_link_libraries(${TARGET_NAME} ym2612)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
