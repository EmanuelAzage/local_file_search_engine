//this is webpageparser.cpp, implementatation of WebPageParser class

#include "../lib/mdpageparser.h"


/** 
* Parses a file and returns all unique words according
*  to some parser rules and all hyperlinks based 
*  on the format the parser is designed to implement
*/
void MDPageParser::parse(std::string filename, MySet<std::string>& allWords, MySet<std::string>& allLinks){

	std::ifstream input_file(filename.c_str());// ifstream constructor takes char* NOT strings
	std::string link;
	std::string word;	
	std::string contents;
	char ch;

	//copy over enter file into a string
	while(!input_file.eof()){
		input_file.get(ch);
		if(!input_file.fail()){
			contents += ch;
		}
	}


	for(unsigned int i = 0; i<contents.size(); i++){
		if( isalpha(contents[i]) || isdigit(contents[i]) ){ //a letter or number
			while( isalpha(contents[i]) || isdigit(contents[i]) ){ //add char to word as long as it is a letter/num
				word += contents[i];
				i++;
			}
			i--; //we went 1 to far in the above while loop
			allWords.insert(word);
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
				allWords.insert(word);
				word.clear();
				if(contents[i] != ']'){
					i++;
				}
			}
			i++;
			if(word != "") {
				allWords.insert(word);
			}
			word.clear();

			if( contents[i] == '(' ){ // [] is followed by '('
				i++; // skip '('
				while( contents[i] != ')' ){
					link += contents[i];
					i++;
				}
				allLinks.insert(link);
				link.clear();
			}
		}
	}

}