include_directories(${QT_INCLUDE})
include_directories(${CMAKE_CURRENT_BINARY_DIR}) # because of generated UI files

set(SRCS Src/Config/ConfigAudio.cpp
        Src/Config/ConfigGeneral.cpp
        Src/Config/ConfigGfx.cpp
        Src/Config/ConfigMain.cpp
        Src/Config/ConfigPad.cpp
        Src/Config/ConfigWiimote.cpp
        Src/GameList/GameTracker.cpp
        Src/GameList/GameTree.cpp
        Src/GameList/GameGrid.cpp
        Src/GameObject.cpp
        Src/Util/Util.cpp
        Src/Util/Resources.cpp
        Src/LogWidgets.cpp
        Src/main.cpp
        Src/MainWindow.cpp
        Src/RenderWidget.cpp
        Src/SystemInfo.cpp)

set(LIBS    core
            ${LZO}
            discio
            bdisasm
            inputcommon
            common
            audiocommon
            z
            sfml-network
            ${OPENGL_LIBRARIES})

if(USE_EGL)
	set(SRCS ${SRCS} ../DolphinWX/GLInterface/Platform.cpp
		../DolphinWX/GLInterface/EGL.cpp)
	if(USE_WAYLAND)
		set(SRCS ${SRCS} ../DolphinWX/GLInterface/Wayland_Util.cpp)
	endif()
	if(USE_X11)
		set(SRCS ${SRCS} ../DolphinWX/GLInterface/X11_Util.cpp)
	endif()
else()
	if(WIN32)
		set(SRCS ${SRCS} ../DolphinWX/GLInterface/WGL.cpp)
	elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(SRCS ${SRCS} ../DolphinWX/GLInterface/AGL.cpp)
	else()
		set(SRCS ${SRCS} ../DolphinWX/GLInterface/GLX.cpp
			../DolphinWX/GLInterface/X11_Util.cpp)
		set(LIBS ${LIBS} rt ${X11_LIBRARIES}
				${XINPUT2_LIBRARIES}
				${XRANDR_LIBRARIES})
	endif()
endif()

if(SDL2_FOUND)
	# Using shared SDL2
	set(LIBS	${LIBS} ${SDL2_LIBRARY})
else(SDL2_FOUND)
	if(SDL_FOUND)
		# Using shared SDL
		set(LIBS	${LIBS} ${SDL_LIBRARY})
	else(SDL_FOUND)
		# Using static SDL from Externals
		set(LIBS	${LIBS} SDL)
	endif()
endif()

set(EXEGUI dolphin-emu-qt)

qt_moc(MOC_SRCS Src/Config/ConfigAudio.h
                Src/Config/ConfigGeneral.h
                Src/Config/ConfigGfx.h
                Src/Config/ConfigMain.h
                Src/Config/ConfigPad.h
                Src/Config/ConfigWiimote.h
                Src/GameList/GameTracker.h
                Src/GameList/GameTree.h
                Src/GameList/GameGrid.h
                Src/Util/Util.h
                Src/LogWidgets.h
                Src/MainWindow.h
                Src/RenderWidget.h
                Src/SystemInfo.h)
qt_ui(UIC_SRCS Src/MainWindow.ui
               Src/LogWindow.ui
               Src/LogSettings.ui
               Src/GameList/GameTree.ui
                Src/GameList/GameGrid.ui
               Src/SystemInfo.ui)
qt_res(QRC_SRCS Resources/Resources.qrc)

add_executable(${EXEGUI} ${SRCS} ${MOC_SRCS} ${UIC_SRCS} ${QRC_SRCS})
target_link_libraries(${EXEGUI} ${LIBS} ${QT_LIBS})
install(TARGETS ${EXEGUI} RUNTIME DESTINATION ${bindir})
