#include <iostream>
#include "multiwin.h"
#include <QApplication>
#include <string>


int main(int argc, char* argv[]){
	std::string config_file;

	if(argc >= 2){
		config_file = argv[1];
	}
	
	if(argc < 2){
    	//std::cout << "usage: ./search config_file...Please provide an configuration file" << std::endl;
    	config_file = "configsearch.txt";//default
  	}
	
	QApplication app(argc, argv);

	Multiwin* multiwin = new Multiwin(config_file);

	multiwin->show();

	return app.exec();
}
