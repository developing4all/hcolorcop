
#include <QImage>
#include "hscreencolors.h"
#include <QPainter>
#include <QSize>

#include <iostream>
using std:: cout; using std::endl;using std::cerr;
#include <math.h>


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
}

void HScreenColors::leaveEvent( QEvent * )
{
}

void HScreenColors::mousePressEvent( QMouseEvent * )
{
}

void HScreenColors::paintEvent( QPaintEvent * )
{
	QPainter painter(this);
	
	if( !image.isNull() )
	{
		QVector<QRgb> colortable = image.colorTable();
		
		
		//cout << colortable.size() << endl;
		//cout << image.numColors() << endl;
		//cout << image.size().width() << endl;
		double numRows = sqrt( image.numColors() );
		//cout << numRows << endl;
		
		for (int i = 0; i < colortable.size(); ++i)
		{
			//if (vector.at(i) == "Alfonso")
			//	cout << "Found Alfonso at position " << i << endl;
		}
	}
	
	painter.setPen(Qt::black);
	painter.drawLine(0, 0, width()-1, 0);
	painter.drawLine(0, 0, 0, height()-1);
	painter.drawLine(0, height()-1, width()-1, height()-1);
	painter.drawLine(width()-1, 0, width()-1, height()-1);
	
	painter.end();
}

