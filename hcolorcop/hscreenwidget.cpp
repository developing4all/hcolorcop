
#include <QTimer>

#include "hscreenwidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>


HScreenWidget::HScreenWidget( QWidget *parent )
	:QLabel(parent)
{
    setMinimumSize(QSize(135, 135));
    setMaximumSize(QSize(135, 135));
	
	screenTimer = new QTimer(this);
    connect(screenTimer, SIGNAL(timeout()), this, SLOT(regrabScreen()));
    //timer->start(1000);
	/*
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);
	//setText("TEST");
	*/
}


void HScreenWidget::grabScreen( QPoint pos, int mult )
{
	if(!screenTimer->isActive())
		screenShot = QPixmap::grabWindow( QApplication::desktop()->winId() ).toImage();
	
	color = screenShot.pixel(pos);
	
	multiply = mult;
	mousePos = pos;
	currentPos = QPoint(68, 68 );
	repaint();
	screenTimer->start(200);
	emit rgbChanged( color );
	emit imageChanged( img );
//	return color;
}

void HScreenWidget::regrabScreen()
{
	screenShot = QPixmap::grabWindow( QApplication::desktop()->winId() ).toImage();
	repaint();
	emit rgbChanged( color );
	emit imageChanged( img );
}

void HScreenWidget::stopTimers()
{
	screenTimer->stop();
	emit rgbChanged( color );
	emit imageChanged( img );
}

void HScreenWidget::enterEvent( QEvent * event )
{
	grabMouse( QCursor( QPixmap(":images/picker_cursor.gif")) );
}

void HScreenWidget::leaveEvent( QEvent * event )
{
	releaseMouse();
}

void HScreenWidget::mousePressEvent( QMouseEvent * event )
{
	currentPos = event->pos();
	repaint();
	emit rgbChanged( color );
	emit imageChanged( img );
}


void HScreenWidget::paintEvent( QPaintEvent * event )
{
	
	QPainter painter(this);
	
	//QImage img = screenShot.toImage();
	
	int x = mousePos.x() - 68;
	int y = mousePos.y() - 68;
	
	img = screenShot.copy ( x, y, 135, 135 );
	
	//img = img.scaled(135 * multiply, 135 * multiply, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	img = img.scaled(135 * multiply, 135 * multiply, Qt::IgnoreAspectRatio);
	
	x = (135 * multiply/2) - 68;
	y = (135 * multiply/2) - 68;
	
	img = img.copy ( x, y, 135, 135 );
	
	//color = screenShot.pixel(mousePos);
	//emit rgbChanged( color );
	
	color = img.pixel(currentPos);
	
	x = currentPos.x() -1;
	y = currentPos.y() -1;
	
	painter.drawImage(0, 0, img);
	
	painter.drawLine(x, y, x+3, y);
	painter.drawLine(x, y, x, y+3);
	painter.drawLine(x, y+3, x+3, y+3);
	painter.drawLine(x+3, y, x+3, y+3);
	
	x = currentPos.x() -2;
	y = currentPos.y() -2;
	painter.setPen(Qt::white);
	painter.drawLine(x, y, x+5, y);
	painter.drawLine(x, y, x, y+5);
	painter.drawLine(x, y+5, x+5, y+5);
	painter.drawLine(x+5, y, x+5, y+5);
	
	
	painter.setPen(Qt::black);
	painter.drawLine(0, 0, width()-1, 0);
	painter.drawLine(0, 0, 0, height()-1);
	painter.drawLine(0, height()-1, width()-1, height()-1);
	painter.drawLine(width()-1, 0, width()-1, height()-1);
	
	painter.end();
}
