CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )
PROJECT ( fired )

set( VERSION_MAJOR "0" )
set( VERSION_MINOR "9" )
set( VERSION_PATCH "9" )

INCLUDE_DIRECTORIES ("include" "include/meta" )
FILE ( GLOB SRC "src/*/*.cpp" )


if ( WIN32 )

        SET ( CMAKE_RESOURCE   "docs/fired.o" )
        SET ( CMAKE_CXX_FLAGS  "-DSFML_STATIC" )
        SET ( CMAKE_EXE_LINKER_FLAGS  "-mwindows -static-libgcc -static-libstdc++ -static -Wl,-Bstatic" )
        SET ( LINK_LIBS sfml-audio-s sfml-graphics-s sfml-window-s sfml-system-s winmm opengl32 gdi32 freetype glew jpeg opengl32 openal32 sndfile m sqlite3 )
        ADD_CUSTOM_COMMAND( OUTPUT docs/fired.o COMMAND windres.exe -Idocs -idocs/fired.rc -o docs/fired.o )

elseif ( UNIX )

        SET ( CMAKE_RESOURCE  "" )
        SET ( LINK_LIBS sfml-system sfml-window sfml-graphics sfml-audio m sqlite3 stdc++ )

endif ( )


ADD_EXECUTABLE ( fired ${SRC} ${CMAKE_RESOURCE} )
TARGET_LINK_LIBRARIES ( fired  ${LINK_LIBS} )
