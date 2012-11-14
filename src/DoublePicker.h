/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#ifndef DOUBLEPICKER_H
#define DOUBLEPICKER_H

#include <QWidget>

namespace Ui {
    class DoublePicker;
}

class DoublePicker : public QWidget
{
    Q_OBJECT

public:
    explicit DoublePicker(QWidget *parent = 0);
	virtual ~DoublePicker();

public slots:
	virtual double	getValue() const;
	virtual QString getTextValue() const;
	virtual double	getMinValue() const;
	virtual double	getMaxValue() const;

	virtual void	setValue(double value);
	virtual void	setLimits(double min, double max);
	virtual void	setActivated(bool activate); ///toggle the checker
	virtual void	showActivationCheck(bool show);

	virtual bool	isActivated();

signals:
	void	valueChanged(double);
	void	activationChanged(bool);

private slots:
	void updateBySlider(int val);
	void updateBySpin(double val);
	void updateByActivationCheck(bool checked);

private:
	static const double EPSILON;
    Ui::DoublePicker *ui;

	double	oldValue;

	double	sliToSpin(int val) const;
	int		spinToSli(double val) const;
	bool	isAlmostSame(double a, double b) const;

};

#endif // DOUBLEPICKER_H
