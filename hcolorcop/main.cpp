#include <QApplication>
#include "hcolorcop.h"


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	
	HColorCop w;
	w.show();
	
	return app.exec();
}
