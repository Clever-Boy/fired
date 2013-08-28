#ifndef __MAPFILE_MAPLOAD
#define __MAPFILE_MAPLOAD


void mapLoadMeta(fired::Map *map, FILE *fp);
void mapLoadTiles(fired::Map *map, FILE *fp);
void mapLoadDecors(fired::Map *map, FILE *fp);
void mapLoadCollectorItems(fired::Map *map, fired::MapObjectCollector *obj, FILE *fp);
void mapLoadObject(fired::Map *map, fired::BaseMapObject obj, FILE *fp);
void mapLoadObjects(fired::Map *map, FILE *fp);

#endif