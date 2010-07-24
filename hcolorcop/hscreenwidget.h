#ifndef HSCREENWIDGET_H
#define HSCREENWIDGET_H

#include <QLabel>

class QTimer;

class HScreenWidget : public QLabel
 {
     Q_OBJECT

 public:
     HScreenWidget(QWidget *parent = 0);
     void grabScreen( QPoint, int );
	 void setMultiply(int m){ multiply = m; repaint(); emit imageChanged(img);}
	 void stopTimers();
	 QImage getImage(){return img;}
	 
 public slots:
     void regrabScreen();
	 
 signals:
 	void rgbChanged( QRgb );
 	void imageChanged( QImage );
  
 protected:
	 virtual void paintEvent( QPaintEvent * );
	 virtual void enterEvent( QEvent * );
	 virtual void leaveEvent( QEvent * );
	 virtual void mousePressEvent( QMouseEvent * );

 private:
	 QImage screenShot;
	 QImage img;
	 QRgb color;
	 QPoint mousePos;
	 QPoint currentPos;
	 int multiply;
	 QTimer *screenTimer;

};

#endif // HSCREENWIDGET_H
