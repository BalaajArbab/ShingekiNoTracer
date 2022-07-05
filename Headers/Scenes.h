#ifndef SCENES_H
#define SCENES_H

#include <Renderer/HittableList.h>

void RandomScene(HittableList& worldObjects);
void RandomSceneLights(HittableList& worldObjects);
void Zebra(HittableList& worldObjects);
void Cornell(HittableList& worldObjects);
void Aesthetic(HittableList& worldObjects);
void Sasageyo(HittableList& worldObjects);
void KekWorld(HittableList& worldObjects);
void DragonCurve(HittableList& worldObjects);
void CornellSmoke(HittableList& worldObjects);
void CornellInvisWalls(HittableList& worldObjects);

#endif