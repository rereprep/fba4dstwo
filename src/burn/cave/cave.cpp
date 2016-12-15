#include "cave.h"

int nCaveXSize = 0, nCaveYSize = 0;
int nCaveXOffset = 0, nCaveYOffset = 0;
int nCaveExtraXOffset = 0, nCaveExtraYOffset = 0;
int nCaveRowModeOffset = 0;
const bool bCaveRotateScreen = true;

int CaveScanGraphics()
{
	SCAN_VAR(nCaveXOffset);
	SCAN_VAR(nCaveYOffset);

	SCAN_VAR(nCaveTileBank);

	SCAN_VAR(nCaveSpriteBank);
	SCAN_VAR(nCaveSpriteBankDelay);

	for (int i = 0; i < 4; i++) {
		SCAN_VAR(CaveTileReg[i][0]);
		SCAN_VAR(CaveTileReg[i][1]);
		SCAN_VAR(CaveTileReg[i][2]);
	}

	return 0;
}

// This function fills the screen with the background colour
void CaveClearScreen(unsigned int nColour)
{
#ifdef NDS
	clear_gui_texture(((nColour & 0x001f ) << 3) | ((nColour & 0x03e0 ) << 2) | ((nColour & 0x7c00 ) << 7), nCaveXSize, nCaveYSize);
#else

	if (nColour) {
		unsigned int* pClear = (unsigned int*)pBurnDraw;
		nColour = nColour | (nColour << 16);
		for (int i = nCaveXSize * nCaveYSize / 16; i > 0 ; i--) {
			*pClear++ = nColour;
			*pClear++ = nColour;
			*pClear++ = nColour;
			*pClear++ = nColour;
			*pClear++ = nColour;
			*pClear++ = nColour;
			*pClear++ = nColour;
			*pClear++ = nColour;
		}
	} else {
		memset(pBurnDraw, 0, nCaveXSize * nCaveYSize * sizeof(short));
	}

#endif
}

