//crawler.cpp
//writes to a txt file, all the files from DFS

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

#include "config.h"

using namespace std;

void dfs_crawl(ofstream& outputFile, std::string filename, set<string>& visited);

int main(int argc, char* argv[]){
	map<string, string> config_inputs;
	string config_file; 
	
	if(argc >= 2){
		config_file = argv[1];
	}else{
		config_file = "config.txt";//default
	}

   	get_config_inputs(config_file, config_inputs);
		
	ifstream seedFile( config_inputs["SEED_FILE"].c_str() );

	if(seedFile.fail()){
		cout << "Failed to open seed file" << endl;
		return 1;
	}

	ofstream outputFile( config_inputs["OUTPUT_FILE"].c_str() );

	if(outputFile.fail()){
		cout << "Failed to open output file" << endl;
		return 1;
	}

	set<string> visited;
		
	string filename;
	while( !seedFile.eof() ){
		getline(seedFile, filename);
		dfs_crawl(outputFile, filename, visited);
	}	

	if(outputFile.is_open() ){
		outputFile.close();
	}

	return 0;
}

void dfs_crawl(ofstream& outputFile, string filename, set<string>& visited){
	//BASECASES FOR RECURSION
	
	ifstream file(filename.c_str() );
	if(file.fail()){//could not open file, so file doesn't exist for filename, basecase
		return;
	}

	if(visited.count(filename) ){ //have already discovered this node/filename before, basecase
		return;
	}

	//***********RECURSIVE CASE******************************************************
	visited.insert(filename);
	outputFile << filename << endl;
	
	//find links and do recursive call on that link

	std::string link;
	std::string word;	
	std::string contents;
	char ch;

	//copy over enter file into a string
	while(!file.eof()){
		file.get(ch);
		if(!file.fail()){
			contents += ch;
		}
	}

	//get the filename links from the string and call dfs_crawl for all filename/links found
	for(unsigned int i = 0; i<contents.size(); i++){
		if( isalpha(contents[i]) || isdigit(contents[i]) ){ //a letter or number
			while( isalpha(contents[i]) || isdigit(contents[i]) ){ //add char to word as long as it is a letter/num
				word += contents[i];
				i++;
			}
			i--; //we went 1 to far in the above while loop
			word.clear();
		}
		else if( contents[i] == '[' ){
			i++; // skip '['
			while( (contents[i] != ']') ){ //add to word as long as we are in the brackets
				while( isalpha(contents[i]) || isdigit(contents[i]) ){
					word += contents[i]; 
					i++;
				}
				//at ']' char
				word.clear();
				if(contents[i] != ']'){
					i++;
				}
			}
			i++;
			if(word != "") {
				// allWords.insert(word);
			}
			word.clear();

			if( contents[i] == '(' ){ // [] is followed by '('
				i++; // skip '('
				while( contents[i] != ')' ){
					link += contents[i];
					i++;
				}
				dfs_crawl(outputFile, link, visited);
				link.clear();
			}
		}
	}
	file.close();
}