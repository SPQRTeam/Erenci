/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#include "DoublePicker.h"
#include "ui_DoublePicker.h"
#include <math.h>
#include <QDebug>

const double DoublePicker::EPSILON = 0.0001;

DoublePicker::DoublePicker(QWidget *parent) :
									QWidget(parent),
									ui(new Ui::DoublePicker){
	ui->setupUi(this);
	this->oldValue = ui->spin->value();

	connect(ui->spin, SIGNAL(valueChanged(double)), this, SLOT(updateBySpin(double)));
	connect(ui->slider, SIGNAL(valueChanged(int)), this, SLOT(updateBySlider(int)));
	connect(ui->checkActivated, SIGNAL(toggled(bool)), this, SLOT(updateByActivationCheck(bool)));

}

DoublePicker::~DoublePicker(){
    delete ui;
}

QString DoublePicker::getTextValue() const{
	return QString::number(this->getValue(),'f',2);
}

double DoublePicker::getValue() const{
	return ui->spin->value();
}

double DoublePicker::getMinValue() const{
	return ui->spin->minimum();
}

double DoublePicker::getMaxValue() const{
	return ui->spin->maximum();
}

void DoublePicker::setValue(double val){
	bool oldState = this->blockSignals(true);
		ui->spin->setValue(val);
		emit valueChanged(val);
	this->blockSignals(oldState);
}

void DoublePicker::setLimits(double min, double max){
	ui->lblMin->setText(QString::number(min,'f',2));
	ui->lblMax->setText(QString::number(max,'f',2));
	ui->spin->setMinimum(min);
	ui->spin->setMaximum(max);

	ui->spin->setValue(min);
}

void DoublePicker::setActivated(bool activate){
	ui->checkActivated->setChecked(activate);
}


void DoublePicker::showActivationCheck(bool show){
	if(show){
		ui->checkActivated->show();
	}else{
		ui->checkActivated->hide();
	}
}

bool DoublePicker::isActivated(){
	return ui->checkActivated->isChecked();
}

void DoublePicker::updateBySlider(int val){
	if(!isAlmostSame(oldValue, val)){
		ui->spin->setValue(sliToSpin(val));
		this->oldValue = ui->spin->value();
	}
}

void DoublePicker::updateBySpin(double val){
	if(!isAlmostSame(oldValue, val)){
		this->oldValue = val;
		ui->slider->setValue(spinToSli(val));
		emit valueChanged(val);
	}
}

void DoublePicker::updateByActivationCheck(bool checked){
	emit activationChanged(checked);
}

double DoublePicker::sliToSpin(int val) const{
	return ( ( ( val * (ui->spin->maximum() - ui->spin->minimum()) ) / ui->slider->maximum()) + ui->spin->minimum());
}

int	DoublePicker::spinToSli(double val) const{
	double r =  ((val - ui->spin->minimum()) * ui->slider->maximum()) / (ui->spin->maximum() - ui->spin->minimum());
	return floor(r + 0.5);
}

bool DoublePicker::isAlmostSame(double a, double b) const{
		return ( fabs(a - b) < DoublePicker::EPSILON );
}
