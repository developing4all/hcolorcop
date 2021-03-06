
#include <QTimer>

#include "hscreenwidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QScreen>

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
#ifdef Q_OS_WIN
	if(!screenTimer->isActive())
	{
		QWidget *scr = QApplication::desktop();
		WId w = scr->winId();
		QPixmap pm = QPixmap::grabWindow(w,0,0,scr->width(), scr->height());
		screenShot = pm.toImage();
	}
#else
    if(!screenTimer->isActive())
    {
#if QT_VERSION >= 0x050000
        QScreen *currentScreen = QApplication::screens().at(QApplication::desktop()->screenNumber(pos));
        screenShot = currentScreen->grabWindow((QApplication::desktop()->screen( QApplication::desktop()->screenNumber(pos)))->winId()).toImage();
#else
        screenShot = QPixmap::grabWindow( QApplication::desktop()->screen( QApplication::desktop()->screenNumber(pos) )->winId() ).toImage();
#endif
    }
#endif
	
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
#ifdef Q_OS_WIN
	QWidget *scr = QApplication::desktop();
	WId w = scr->winId();
	QPixmap pm = QPixmap::grabWindow(w,0,0,scr->width(), scr->height());
	screenShot = pm.toImage();
#else
    #if QT_VERSION >= 0x050000
    QScreen *currentScreen = QApplication::primaryScreen();
    screenShot = currentScreen->grabWindow(QApplication::desktop()->winId()).toImage();
    #else
    screenShot = QPixmap::grabWindow( QApplication::desktop()->winId() ).toImage();
    #endif
#endif
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

void HScreenWidget::enterEvent( QEvent * )
{
	grabMouse( QCursor( QPixmap(":images/picker_cursor.gif")) );
}

void HScreenWidget::leaveEvent( QEvent * )
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


void HScreenWidget::paintEvent( QPaintEvent * )
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
