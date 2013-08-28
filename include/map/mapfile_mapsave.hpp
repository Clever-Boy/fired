#ifndef __MAPFILE_MAPSAVE
#define __MAPFILE_MAPSAVE


void mapSaveMeta(fired::Map *map, FILE *fp);
void mapSaveTiles(fired::Map *map, FILE *fp);
void mapSaveDecors(fired::Map *map, FILE *fp);
void mapSaveCollectorItems(fired::MapObjectCollector *obj, FILE *fp);
void mapSaveObject(fired::MapObject obj, FILE *fp);
void mapSaveObjects(fired::Map *map, FILE *fp);

#endif