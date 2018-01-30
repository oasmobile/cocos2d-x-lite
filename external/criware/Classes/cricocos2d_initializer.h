#ifndef CRI_INCL_CRICOCOS2D_INITIALIZER_H
#define CRI_INCL_CRICOCOS2D_INITIALIZER_H

class CRICOCOS2D {
public :
	static void criWare_Initialize();

	static void criWare_Finalize();

	static void criWare_Suspend();

	static void criWare_Resume();

	static bool criWare_IsInitialized();

	static void criWare_EnableAssetsAccess();
};

#endif
