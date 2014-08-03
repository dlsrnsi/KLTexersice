

#include <iostream>
#include <ctype.h>
#include "..\header\ham-kma.h"
#include <QtWidgets\qapplication.h>
#include "ui_TextAnalyzer.h"
#include <QtWidgets\qmainwindow.h>
using namespace std;

extern  int get_sent_or_line(	/* read a sentence from input file */
	FILE *fp,
	unsigned char *sent,
	unsigned char inputmode);
extern void hamout_HAM(	/* output test for HAM internal str. */
	FILE *fp,	/* output file */
	HAM_PMORES p,	/* HAM result for input sentence */
	HAM_PRUNMODE mode);

HAM_MORES2	HamOut2;


int main(int argc, char *argv[]) 
{
	QApplication app(argc, argv);
	Ui::TextAnalyzer ui;
	QMainWindow *mainwindow = new QMainWindow;
	ui.setupUi(mainwindow);
	mainwindow->show();

	


	int flag;	/* temporary variable */
	FILE *fpin;
	FILE *fpout = stdout;
	fopen_s(&fpin, "다크나이트.txt", "r");

	char *optstr = NULL;	/* option string: e.g. "1aC2", "pVc" */
	HAM_RUNMODE mode;	/* HAM running mode: 'header/runmode.h' */

	unsigned char sent[SENTSIZE];	/* input sentence */
	HAM_PMORES	hamout1;	/* frame-based morph. analysis output */

	flag = open_HAM(&mode, optstr, "./hdic/KLT2000.ini");
	while (get_sent_or_line(fpin, sent, mode.inputmode)) {
		cout << sent << "\n";
		hamout1 = morph_anal(sent, NULL, &mode);
		hamout_HAM(fpout, hamout1, &mode);
	}
	close_HAM();

	app.exec();
}
