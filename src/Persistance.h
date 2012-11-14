/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#ifndef PERSISTANCE_H
#define PERSISTANCE_H

#include <map>
#include <vector>
#include <QWidget>
#include <QString>
#include "MotionMaker.h"

typedef std::vector< QString > DatJointsOrder; //joints name in dats
typedef std::map< QString, QString > DatJoints; //joint name in dat, joint value

class Erenci;

class Persistance : public QWidget
{
    Q_OBJECT
public:

	DatJointsOrder datJointsOrder;

	explicit Persistance(QWidget *parent = 0);
	~Persistance();

	void setModel(MotionMaker * model); /** do not own 'model' memory management*/

signals:
	void fileSaved(bool saved);

public slots:

	void open();
	void close();
	void save();
	void saveACopy();

	void exportToDat();
	void importDat();
	//TODO: importKme();

	void editingPerformed();

private:
	static const QString SETTING_NAME_ID_FILE_PATH;
	static const QString SETTING_NAME_ID_DAT_PATH;

	MotionMaker * model;

	QString		filePath;
	bool		fileOpened;
	bool		modelEdited;

	Erenci *	getController();
	void		writeFile(QString path);

	DatJoints	datJointsTemp;
	void		tempMapReset();
	int			findIndexInJointOrder(QString key);
	void		showMessage(QString text);
};

#endif // PERSISTANCE_H
