set(SRCS	BPFunctions.cpp
			BPMemory.cpp
			BPStructs.cpp
			CPMemory.cpp
			CommandProcessor.cpp
			Debugger.cpp
			DriverDetails.cpp
			Fifo.cpp
			FPSCounter.cpp
			FramebufferManagerBase.cpp
			HiresTextures.cpp
			ImageWrite.cpp
			IndexGenerator.cpp
			MainBase.cpp
			OnScreenDisplay.cpp
			OpcodeDecoding.cpp
			PerfQueryBase.cpp
			PixelEngine.cpp
			PixelShaderGen.cpp
			PixelShaderManager.cpp
			RenderBase.cpp
			Statistics.cpp
			TextureCacheBase.cpp
			TextureConversionShader.cpp
			VertexLoader.cpp
			VertexLoaderManager.cpp
			VertexLoader_Color.cpp
			VertexLoader_Normal.cpp
			VertexLoader_Position.cpp
			VertexLoader_TextCoord.cpp
			VertexManagerBase.cpp
			VertexShaderGen.cpp
			VertexShaderManager.cpp
			VideoBackendBase.cpp
			VideoConfig.cpp
			VideoState.cpp
			XFMemory.cpp
			XFStructs.cpp
			memcpy_amd.cpp)
set(LIBS core png)

if(NOT _M_GENERIC)
	set(SRCS ${SRCS}	TextureDecoder_x64.cpp
						DLCache_x64.cpp)
else()
	set(SRCS ${SRCS}	TextureDecoder_Generic.cpp
						DLCache_Generic.cpp)
endif()
if(NOT ${CL} STREQUAL CL-NOTFOUND)
	list(APPEND LIBS ${CL})
endif()

if(wxWidgets_FOUND AND WIN32)
	set(SRCS ${SRCS} EmuWindow.cpp)
endif()

if(LIBAV_FOUND OR WIN32)
	set(SRCS ${SRCS} AVIDump.cpp)
endif()

add_dolphin_library(videocommon "${SRCS}" "${LIBS}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	if(LIBAV_FOUND)
		target_link_libraries(videocommon ${LIBS} ${LIBAV_LIBRARIES})
		add_definitions(-D__STDC_CONSTANT_MACROS)
	endif()
endif()
