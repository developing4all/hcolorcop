#ifndef HSCREENCOLORS_H
#define HSCREENCOLORS_H

#include <QLabel>

class QImage;

class HScreenColors : public QLabel
 {
     Q_OBJECT

 public:
     HScreenColors(QWidget *parent = 0);
	 
 public slots:
     void setImage( QImage );
	 
 signals:
 	void rgbChanged( QRgb );
	
 protected:
    virtual void paintEvent( QPaintEvent * );
    virtual void enterEvent( QEvent * );
    virtual void leaveEvent( QEvent * );
    virtual void mousePressEvent( QMouseEvent * );
	 
 private:
	 QImage image;
};

#endif //HSCREENCOLORS_H
