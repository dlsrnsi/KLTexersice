

#include <iostream>
#include <ctype.h>
#include "..\header\ham-kma.h"
using namespace std;
extern "C" int get_sent_or_line(	/* read a sentence from input file */
	FILE *fp,
	unsigned char *sent,
	unsigned char inputmode);
extern "C" void hamout_HAM(	/* output test for HAM internal str. */
	FILE *fp,	/* output file */
	HAM_PMORES p,	/* HAM result for input sentence */
	HAM_PRUNMODE mode);

HAM_MORES2	HamOut2;


int main(
	int argc,
	char *argv[]) 
{
	char toklist[999];
	int flag;	/* temporary variable */
	FILE *fpin;
	fopen_s(&fpin, "다크나이트.txt", "r, ccs=UTF-8");

	char *optstr = NULL;	/* option string: e.g. "1aC2", "pVc" */
	HAM_RUNMODE mode;	/* HAM running mode: 'header/runmode.h' */

	unsigned char sent[SENTSIZE];	/* input sentence */
	HAM_PMORES	hamout1;	/* frame-based morph. analysis output */

	flag = open_HAM(&mode, optstr, "./hdic/KLT2000.ini");
	while (get_sent_or_line(fpin, sent, mode.inputmode)) {
			hamout1 = morph_anal(sent, NULL, &mode);
			hamout_HAM(fpin, hamout1, &mode);
	}
	close_HAM();
}
