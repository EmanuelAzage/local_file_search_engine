#include <iostream>
#include "multiwin.h"
#include <QApplication>
#include <string>


int main(int argc, char* argv[]){

	if(argc < 2){
    	std::cout << "usage: ./search config_file...Please provide an configuration file" << std::endl;
    	return 1;
  	}
	
	QApplication app(argc, argv);

	std::string config_file = argv[1];

	Multiwin* multiwin = new Multiwin(config_file);

	multiwin->show();

	return app.exec();
}
