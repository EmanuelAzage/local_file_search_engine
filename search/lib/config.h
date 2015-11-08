#include <fstream>
#include <string>

using namespace std;


void get_config_inputs(string config_file_str, map<string, string>& config_inputs){
	ifstream config_file(config_file_str.c_str() );

	if(config_file.fail()){
		cout << endl<< "ERROR: Couldn't open configuration file." << endl << endl;
	}

	string line;
	string param;
	string val;
	unsigned int i = 0;
	while(!config_file.eof() && !config_file.fail() ){
		getline(config_file, line);

		if(config_file.fail()){ break;} // just finished last line of file

		if(line.empty()){ continue;} // go to next line if empty
		
		if(line[0] == '#'){ continue;} // skip line if comment #
		

		i = 0;
		// get parameter
		while( line[i] != ' ' && line[i] != '='){// not a space and or =
			param += line[i];
			i++;
		}
		
		while(line[i] == ' ' || line[i] == '='){// skip all the spaces and = before value
			i++;
		}

		//get val
		while( line[i] != ' ' && line[i] != '#' && i < line.size() ){
			val += line[i];
			i++;
		}

		config_inputs.insert(make_pair(param, val));
		param.clear();
		val.clear();

	}
} 