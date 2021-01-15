set(TARGET_NAME carmenoverture)
add_executable(${TARGET_NAME} MACOSX_BUNDLE main.cpp)

if(MSVC)
	set(PLATFORM_LIBS
		yssimplesound_dsound
	)
elseif(APPLE)
	set(PLATFORM_LIBS
		yssimplesound_macosx
	)
elseif(UNIX)
	set(PLATFORM_LIBS
		yssimplesound_linux_alsa
	)
endif()

target_link_libraries(${TARGET_NAME} fssimplewindow mmlplayer yssimplesound ${PLATFORM_LIBS})
