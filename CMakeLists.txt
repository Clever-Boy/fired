CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )
PROJECT ( fired )

SET ( VERSION_MAJOR "0" )
SET ( VERSION_MINOR "9" )
SET ( VERSION_PATCH "9" )

INCLUDE_DIRECTORIES ("include" "include/meta" )
FILE ( GLOB SRC "src/*/*.cpp" )


IF ( WIN32 )

        SET ( CMAKE_RESOURCE   "docs/fired.o" )
        SET ( CMAKE_CXX_FLAGS  "-DSFML_STATIC" )
        SET ( CMAKE_EXE_LINKER_FLAGS  "-mwindows -static-libgcc -static-libstdc++ -static -Wl,-Bstatic" )
        SET ( CMAKE_LINK_LIBS sfml-audio-s sfml-graphics-s sfml-window-s sfml-system-s winmm opengl32 gdi32 freetype glew jpeg opengl32 openal32 sndfile m sqlite3 )
        ADD_CUSTOM_COMMAND ( OUTPUT docs/fired.o COMMAND windres.exe -Idocs -idocs/fired.rc -o docs/fired.o )

ELSEIF ( UNIX )

        SET ( CMAKE_RESOURCE  "" )
        SET ( CMAKE_LINK_LIBS sfml-system sfml-window sfml-graphics sfml-audio m sqlite3 stdc++ )

ENDIF ( )


ADD_EXECUTABLE ( fired ${SRC} ${CMAKE_RESOURCE} )
TARGET_LINK_LIBRARIES ( fired  ${CMAKE_LINK_LIBS} )
