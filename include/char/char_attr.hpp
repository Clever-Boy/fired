/***********************************************************************
     * File       : char_attr.hpp
     * Created    : Apr 01, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CHAR_ATTR
#define __CHAR_ATTR


namespace fired {
	struct CharacterAttributes {
		unsigned short strength;
		unsigned short constitution;
		unsigned short dexterity;
		unsigned short intelligence;
		unsigned short wisdom;

		unsigned short points;


		CharacterAttributes();
	};
}

#endif
