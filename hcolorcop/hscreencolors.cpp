
#include <QImage>
#include "hscreencolors.h"
#include <QPainter>
#include <QSize>
#include <QMouseEvent>

#include <iostream>
using std:: cout; using std::endl;using std::cerr;
#include <math.h>
//#include <cmath>

HScreenColors::HScreenColors( QWidget *parent )
	: QLabel(parent)
{
}

void HScreenColors::setImage( QImage img )
{
	image = img;
	image = image.convertToFormat(QImage::Format_Indexed8/*, Qt::ColorOnly | Qt::DiffuseDither | Qt::AvoidDither*/);
	repaint();
}

void HScreenColors::enterEvent( QEvent * )
{
	grabMouse( QCursor( QPixmap(":images/picker_cursor.gif")) );
}

void HScreenColors::leaveEvent( QEvent * )
{
	releaseMouse();
}

void HScreenColors::mousePressEvent( QMouseEvent * event )
{
	releaseMouse();
	//currentPos = event->pos();
	QImage img =  QPixmap::grabWindow( winId() ).toImage();
	QRgb color = img.pixel(event->pos());
	
	emit rgbChanged( color );
	/*
	repaint();
	emit rgbChanged( color );
	emit imageChanged( img );
	*/
}

void HScreenColors::paintEvent( QPaintEvent * )
{
	QPainter painter(this);
	
	if( !image.isNull() )
	{
		QVector<QRgb> colortable = image.colorTable();
		
		/*
		cout << "colortable.size(): " << colortable.size() << endl;
		cout << "image.numColors(): " << image.numColors() << endl;
		cout << "image.size().width(): " << image.size().width() << endl;
		*/
		double numRows = sqrt( image.numColors() );
		//cout << "numRows: " << numRows << endl;
		double rest = fmod(numRows , 1.0);
		//cout << "rest: " << rest << endl;
		if( rest > 0)
			numRows += 1;
		double width = image.size().width() / numRows;
		
		int x = 0;
		int y = 0;
		
		for (int i = 0; i < colortable.size(); ++i)
		{
			if(x >= (numRows*width))
			{
				x = 0;
				y += width;
			}
			
			QColor currentColor( colortable.at(i) );
			painter.fillRect( QRect(x,y, width, width), QBrush(currentColor));
			//if (vector.at(i) == "Alfonso")
			//	cout << "Found Alfonso at position " << i << endl;
			x += width;
		}
	}
	
	painter.setPen(Qt::black);
	painter.drawLine(0, 0, width()-1, 0);
	painter.drawLine(0, 0, 0, height()-1);
	painter.drawLine(0, height()-1, width()-1, height()-1);
	painter.drawLine(width()-1, 0, width()-1, height()-1);
	
	painter.end();
}

