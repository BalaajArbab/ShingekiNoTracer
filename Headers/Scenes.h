#ifndef SCENES_H
#define SCENES_H

#include <Renderer/HittableList.h>
#include <Materials/Material.h>
#include <Materials/Skybox.h>


void RandomScene(HittableList& worldObjects);
void RandomSceneLights(HittableList& worldObjects);
void Zebra(HittableList& worldObjects);
void Cornell(HittableList& worldObjects);
shared_ptr<Skybox> BadApple(HittableList& worldObjects, shared_ptr<Material> bckground);
void Sasageyo(HittableList& worldObjects);
void KekWorld(HittableList& worldObjects);
void DragonCurve(HittableList& worldObjects);
void CornellSmoke(HittableList& worldObjects);
void CornellInvisWalls(HittableList& worldObjects);

#endif