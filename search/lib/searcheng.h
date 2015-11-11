#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "lib/webpage.h"
#include "lib/myset.h"
#include "lib/pageparser.h"

class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  void add_parse_from_index_file(std::string index_file, 
				 PageParser* parser);
  void add_parse_page(std::string filename, 
		      PageParser* parser);

  /**** Add other desired member functions here *****/
  MySet<WebPage*> AND_command(std::vector<std::string> words_to_search);
  MySet<WebPage*> OR_command(std::vector<std::string> words_to_search);
  MySet<WebPage*> one_word_search(std::string word);
  void set_up_word_map();  
  void print_words();
  void print_map();
  bool is_in_map(std::string fn);
  WebPage* get_webpage_at(std::string filename);
  const std::map<std::string, WebPage*>& get_map_all_webpages();


 private:
  /**** Add other desired data members here *****/
 	//MySetWebPage match_search;//set of webpage* that contain a word from the search  
  std::map<std::string, WebPage*> map_all_webpages;//map of all webpages and their filenames
	std::map<std::string, MySet<WebPage*> > word_to_setofwps;  	

	void str_to_lower(std::string& word);
  char char_to_lower(char c);
};

#endif
