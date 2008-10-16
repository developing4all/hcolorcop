#include <QApplication>
#include <QDialog>

#ifndef HCOLORCOP_H
#define HCOLORCOP_H

#include "ui_hcolorcop.h"   // defines Ui::HColorCop

class HScreenWidget;

class HColorCop : public QDialog
 {
     Q_OBJECT

 public:
     HColorCop();
     
 public slots:
	void pickerClick();
	void colorClick();
	void plusClicked(bool);
	void minClicked(bool);
 	void setColor( QRgb );
	void setHsv(int);
	void setRgb(int);
     
 protected:
     virtual void mouseMoveEvent ( QMouseEvent * event ); 
     virtual void mousePressEvent ( QMouseEvent * event ); 
     virtual void mouseReleaseEvent ( QMouseEvent * event );
	 
 private:
 	QRgb currentColor;
	bool grabbing;
	HScreenWidget *screenLabel;
	Ui::HColorCop ui;
	int multiply;
 };

#endif // HCOLORCOP_H
