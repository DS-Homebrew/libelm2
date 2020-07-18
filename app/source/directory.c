#include <nds.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include <elf.h>

//---------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	//---------------------------------------------------------------------------------

	// Initialise the console, required for printf
	consoleDemoInit();

	if (ELM_Mount())
	{

		DIR *pdir;
		struct dirent *pent;

		pdir = opendir("/");

		if (pdir)
		{

			while ((pent = readdir(pdir)) != NULL)
			{
				if (strcmp(".", pent->d_name) == 0 || strcmp("..", pent->d_name) == 0)
					continue;
				if (pent->d_type == DT_DIR)
					iprintf("[%s]\n", pent->d_name);
				else
					iprintf("%s\n", pent->d_name);
			}
			closedir(pdir);
		}
		else
		{
			iprintf("opendir() failure; terminating\n");
		}
	}
	else
	{
		iprintf("fatInitDefault failure: terminating\n");
	}

	while (1)
	{
		swiWaitForVBlank();
		scanKeys();
		if (keysDown() & KEY_START)
			break;
	}

	return 0;
}
