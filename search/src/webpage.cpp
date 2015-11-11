//webpage.cpp
#include "../lib/webpage.h"

// default constructor
WebPage::WebPage() {
	_filename = "";
}

// constructor with initial filename
WebPage::WebPage(std::string filename){
	_filename = filename;
}

// destructor
WebPage::~WebPage(){}

/**
* Sets the filename/URL of this webpage
*/
void WebPage::filename(std::string fname){
	_filename = fname;
}

/**
* Returns the filename/URL of this webpage
*/
std::string WebPage::filename() const{
	return _filename;
}

/**
* Updates the set containing all unique words in the text
*  with the contents of the input parameter words
*/
void WebPage::all_words(const MySet<std::string>& words){
	_all_words = words;
}

/**
* Returns all the unique, tokenized words in this webpage 
*/
MySet<std::string> WebPage::all_words() const{
	return _all_words;
}

/**
* Adds a webpage that links to this page
*/
void WebPage::add_incoming_link(WebPage* wp){
	_incoming_webpages.insert(wp);
}

/**
* Returns all webpages that link to this page
*/
MySet<WebPage*> WebPage::incoming_links() const{
	return _incoming_webpages;
}

/**
* Adds a webpage that this page links to
*/
void WebPage::add_outgoing_link(WebPage* wp){
	_outgoing_webpages.insert(wp);
}

/**
* Returns all webpages this page links to
*/
MySet<WebPage*> WebPage::outgoing_links() const{
	return _outgoing_webpages;
}

/**
* Displays the webpage text to the screen 
*/
std::ostream & operator<< (std::ostream & os, const WebPage & page){
	std::ifstream webpage_file(page._filename.c_str());
	std::string webpage_disp;
	char ch;

	while(!webpage_file.eof()){
		webpage_file.get(ch);

		if( (ch == ']') && (webpage_file.peek() == '(') ){// skip (link_to_file) after ']'
			webpage_disp += ch; // add ']'
			while(ch != ')'){
				webpage_file.get(ch);
			}
			webpage_file.get(ch); // grab ')'
 		}
 		
		webpage_disp += ch;
	}

	os << webpage_disp;

	return os;
}

/**** Add other desired member functions here *****/

void WebPage::print_words(){
	std::set<std::string>::iterator it;
	for(it = _all_words.begin(); it != _all_words.end(); ++it){
		std::cout << *it << std::endl;
	}
}
