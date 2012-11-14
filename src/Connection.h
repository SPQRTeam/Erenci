/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QString>

class Connection : public QObject
{
    Q_OBJECT
public:
	enum ResultsCode{
		RESULT_SUCCEEDED = 0,
		RESULT_FAILED = 1,
		RESULT_PARTIALLY_FAILED = 2
	};
	/** communucation port with NaoConsoleDemon */
	static const quint16 port = 30000;

    explicit Connection(QObject *parent = 0);
	~Connection();

signals:
	void		disconnected();

public slots:
	bool		connectToNao(QString name);
	void		disconnect();
	QString		getError();
	QString		getIP();


	QString		query(QString query);

private:
	QTcpSocket * socket;
	void		write(QString content);
	QString		read();
	QString		ip;

};

#endif // CONNECTION_H
