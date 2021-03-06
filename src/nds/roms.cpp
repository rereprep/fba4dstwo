#include "burnint.h"
#include <stdio.h>
#include <string.h>

#include "nds.h"

#define MAX_ROM_COUNT	4096

typedef struct rom_ent {
	char name[14];
	short stat;
} ROM_FILE_ENT;

static ROM_FILE_ENT * pRom_ent = NULL;
static int rom_count = 0;

static int FindDrvInfoByName(char * fn)
{
	char sfn[256];
	strcpy( sfn, fn );
	sfn[strlen(fn)-4] = 0;
	for (nBurnDrvSelect=0; nBurnDrvSelect<nBurnDrvCount; nBurnDrvSelect++) 
		if ( strcasecmp(sfn, BurnDrvGetTextA(DRV_NAME)) == 0 )
			return nBurnDrvSelect;
	return -1;
}

static int isValidFile(dirent * pfd, ROM_FILE_ENT * pre)
{
	struct stat st;
	
	char fullpath[MAX_PATH];
	strcpy(fullpath, ui_current_path);
	strcat(fullpath, "/");
	strcat(fullpath, pfd->d_name);
	
	lstat(fullpath, &st);

	if ( (st.st_mode&S_IFDIR) ) {
		if ( strcmp(".", pfd->d_name) == 0 ) return 0;
		if ( pre ) {
			strncpy( pre->name, pfd->d_name, 15);
			pre->name[15] = '\0';
			pre->stat = -1;
		}
		return 0;
	}
	char * ext = strrchr(pfd->d_name, '.');
	if ( strcasecmp(ext, ".zip") ) return 0;
	
	if ( pre ) {
		strcpy( pre->name, pfd->d_name );
		pre->stat = FindDrvInfoByName( pfd->d_name );
		if ( (unsigned int)pre->stat >= nBurnDrvCount ) {
			pre->stat = -2;
			return 0;
		}
	}
	return 1;
}

static int findloop( ROM_FILE_ENT * pre )
{
	int count = 0;
	
	DIR* dir = opendir(ui_current_path);
	dirent* fi;
	
	if (dir) {
		while ( (fi=readdir(dir))  ) {
			if ( isValidFile(fi, pre) ) {
				count++;
				if (pre) pre++;
			}
		}
		closedir(dir);
	}
	return count;
}

extern "C" int findRomsInDir(int force)
{
#if 0
	if ( force && pRom_ent ) {
		free( pRom_ent );
		pRom_ent = NULL;
	}
	if ( pRom_ent ) return rom_count;
	rom_count = findloop( NULL );	
	if ( rom_count ) {
		pRom_ent = (ROM_FILE_ENT *) malloc ( rom_count * sizeof(ROM_FILE_ENT) );
		if (!pRom_ent) {
			rom_count = 0;
			return 0; // error alloc memory
		}
		rom_count = findloop( pRom_ent );
	}
	return rom_count;
#else
	// alloc enough memory now !!! for nds doesn't have TLB or MMU
	if (!pRom_ent) pRom_ent = (ROM_FILE_ENT *) malloc ( MAX_ROM_COUNT * sizeof(ROM_FILE_ENT) );
	if (force || (rom_count <= 0))
		rom_count = findloop( pRom_ent );
	return rom_count;
#endif
}

char * getRomsFileName(int idx)
{
	if (idx >= rom_count) return NULL;
	return &(pRom_ent[idx].name[0]);
}

int getRomsFileStat(int idx)
{
	if (idx >= rom_count) return -1;
	return pRom_ent[idx].stat;
}
