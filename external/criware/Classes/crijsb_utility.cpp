#include "crijsb_utility.h"

void criJsbUtil_SetObjectInstance(se::Object *seobj, void *instance)
{
	seobj->setPrivateData(instance);
}

void criJsbUtil_RemoveObjectInstance(se::Object *seobj)
{
	seobj->clearPrivateData();
}

void *criJsbUtil_GetObjectInstance(se::Object *seobj)
{	
	return seobj->getPrivateData();
}

se::Object *criJsbUtil_GetInstanceObject(void *instance) {
	return se::Object::getObjectWithPtr(instance);
}