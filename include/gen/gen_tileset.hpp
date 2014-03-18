/***********************************************************************
     * File       : gen_tileset.hpp
     * Created    : Mar 18, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN_TILESET
#define __GEN_TILESET


namespace fired {
	struct GenTileset {
		int  ID;
		char name[64];

		GenTileset(int _ID, const char *_name);
	};
}

#endif
