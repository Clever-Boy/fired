CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )
PROJECT ( fired )

INCLUDE_DIRECTORIES ("include" "include/meta" )
FILE ( GLOB SRC "src/*/*.cpp" )
ADD_EXECUTABLE ( fired ${SRC} )


if ( WIN32 )

	SET ( CMAKE_CXX_FLAGS  "-DSFML_STATIC" )
	SET ( CMAKE_EXE_LINKER_FLAGS  "-mwindows -static-libgcc -static-libstdc++ -static" )
	TARGET_LINK_LIBRARIES ( fired sfml-audio-s sfml-graphics-s sfml-window-s sfml-system-s winmm opengl32 gdi32 freetype glew jpeg opengl32 openal32 sndfile m sqlite3 )

elseif ( UNIX )

	TARGET_LINK_LIBRARIES ( fired sfml-system sfml-window sfml-graphics sfml-audio m sqlite3 stdc++ )

endif ( )
