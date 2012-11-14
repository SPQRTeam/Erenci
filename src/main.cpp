/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#include <QtGui/QApplication>
#include "Erenci.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    Erenci erenci;
    erenci.show();

    return a.exec();
}
