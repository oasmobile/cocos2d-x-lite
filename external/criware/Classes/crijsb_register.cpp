#include "crijsb_register.h"
#include "crijsb_atom.h"

bool criJsb_Register(se::Object* global) {
	criJsbAtom_Register(global);
	return true;
}