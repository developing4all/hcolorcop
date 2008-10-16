#include "hscreenwidget.h"
#include "hcolorcop.h"

#include <QMouseEvent>
#include <QColorDialog>

HColorCop::HColorCop()
         : QDialog()
{
	ui.setupUi(this);
	grabbing = false;
	
	multiply = 2;
	/*
	QLabel *oldss = ui.screenShot;
	screenLabel = new HScreenWidget(this);
	ui.screenShot = screenLabel;
	ui.hboxLayout5->addWidget(ui.screenShot);
	delete oldss;
	*/
	screenLabel = ui.screenShot;
	
	connect( ui.pickerBtn, SIGNAL( pressed() ), this, SLOT(pickerClick()));
	connect( ui.plusBtn, SIGNAL( clicked(bool) ), this, SLOT(plusClicked(bool)));
	connect( ui.minBtn, SIGNAL( clicked(bool) ), this, SLOT(minClicked(bool)));
	
	connect( screenLabel, SIGNAL(rgbChanged( QRgb )), this, SLOT(setColor( QRgb ) ));
	connect( screenLabel, SIGNAL(imageChanged( QImage )), ui.screenColors, SLOT(setImage( QImage ) ));
	//imageChanged( Image );
	//setImage
	
	connect( ui.hueSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setHsv( int ) ));
	connect( ui.saturationSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setHsv( int ) ));
	connect( ui.valueSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setHsv( int ) ));
	
	connect( ui.redSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setRgb( int ) ));
	connect( ui.greenSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setRgb( int ) ));
	connect( ui.blueSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setRgb( int ) ));
	
	connect( ui.colorLabel, SIGNAL( pressed() ), this, SLOT(colorClick()));
	
	
	screenLabel->grabScreen( QCursor::pos(), multiply );
	screenLabel->stopTimers();
}

void HColorCop::plusClicked(bool)
{
	if(multiply < 10)
		multiply += 1;
	screenLabel->setMultiply(multiply);
	
	ui.multiplyText->setText( QString::number(multiply * 100 ) + "%");
}

void HColorCop::minClicked(bool)
{
	if(multiply > 1)
		multiply -= 1;
	screenLabel->setMultiply(multiply);
	
	ui.multiplyText->setText( QString::number(multiply * 100 ) + "%");
}

void HColorCop::setHsv(int)
{
	QColor color;
	color.setHsv(ui.hueSpin->value(), ui.saturationSpin->value(), ui.valueSpin->value() );
	setColor( color.rgb() );
}

void HColorCop::setRgb(int)
{
	QColor color( ui.redSpin->value(), ui.greenSpin->value(), ui.blueSpin->value());
	setColor( color.rgb() );
}

void HColorCop::colorClick()
{
	//bool * ok = 0;
	QRgb rgb = QColorDialog::getRgba ( currentColor/*, ok, this*/);
	setColor( rgb );
}

void HColorCop::pickerClick()
{
    if ( !grabbing ) {          // prepare to grab...
        grabbing = TRUE;
        grabMouse( QCursor( QPixmap(":images/picker_cursor.gif")) );
		ui.pickerBtn->animateClick();
    }
}

void HColorCop::mouseMoveEvent ( QMouseEvent * event )
{
    if ( grabbing )
		screenLabel->grabScreen( mapToGlobal(event->pos()), multiply );
	else
	{
		if(qApp->widgetAt(mapToGlobal(event->pos())) != ui.screenShot)
			mouseGrabber()->releaseMouse();
	}
}

void HColorCop::mousePressEvent ( QMouseEvent * event )
{
    QDialog::mousePressEvent(event);
    /*
    if ( !grabbing ) {          // prepare to grab...
        grabbing = TRUE;
        grabMouse( QCursor( QPixmap(":/picker.gif")) );
    }
    */
}

void HColorCop::mouseReleaseEvent ( QMouseEvent * event )
{
    if ( grabbing )
	{
		releaseMouse();
		grabbing = false;
		screenLabel->grabScreen( mapToGlobal(event->pos()), multiply );
		screenLabel->stopTimers();
	}
}

void HColorCop::setColor( QRgb rgb )
{
	currentColor = rgb;
	QPalette p(ui.colorLabel->palette());
	p.setColor(ui.colorLabel->backgroundRole(), QColor(rgb));
	ui.colorLabel->setPalette(p);
	
	
	disconnect( ui.hueSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setHsv( int ) ));
	disconnect( ui.saturationSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setHsv( int ) ));
	disconnect( ui.valueSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setHsv( int ) ));
	
	disconnect( ui.redSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setRgb( int ) ));
	disconnect( ui.greenSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setRgb( int ) ));
	disconnect( ui.blueSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setRgb( int ) ));
	
	//rgbval << rgb;
	QColor color(rgb);
	ui.colorName->setText( color.name().toUpper() );
	
	ui.hueSpin->setValue(color.hue());
	ui.saturationSpin->setValue(color.saturation());
	ui.valueSpin->setValue(color.value());

	ui.redSpin->setValue(color.red());
	ui.greenSpin->setValue(color.green());
	ui.blueSpin->setValue(color.blue());
	
	connect( ui.hueSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setHsv( int ) ));
	connect( ui.saturationSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setHsv( int ) ));
	connect( ui.valueSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setHsv( int ) ));
	
	connect( ui.redSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setRgb( int ) ));
	connect( ui.greenSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setRgb( int ) ));
	connect( ui.blueSpin, SIGNAL( valueChanged( int ) ), this, SLOT( setRgb( int ) ));
}

