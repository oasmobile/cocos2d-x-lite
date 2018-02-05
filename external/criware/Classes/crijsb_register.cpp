#include "crijsb_register.h"
#include "crijsb_atom.h"

void criJsb_Register(JSContext* cx, JS::HandleObject global) {
	criJsbAtom_Register(cx, global);
}