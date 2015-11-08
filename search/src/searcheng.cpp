#include "../lib/searcheng.h"
#include <fstream>
#include <iostream>




SearchEng::SearchEng(){}

//delete all the webpages we have created
SearchEng::~SearchEng(){
	std::map<std::string, WebPage*>::iterator it;
	for(it = map_all_webpages.begin(); it != map_all_webpages.end(); ++it){
		delete it->second;
	}
}

void SearchEng::add_parse_from_index_file(std::string index_file, PageParser* parser){
	std::ifstream index(index_file.c_str());
	std::string web_file;

	while(!index.eof()){
		getline(index, web_file);

		if(!web_file.empty()){//skip blank lines
			add_parse_page(web_file, parser);
		}
	}
 
}


void SearchEng::add_parse_page(std::string filename, PageParser* parser){
	MySet<std::string> temp_all_words;
	MySet<std::string> temp_all_links;

	parser->parse(filename, temp_all_words, temp_all_links);
	

	if(!map_all_webpages.count(filename) ){//this filename isn't in the map
		//create a new webpage and store a pointer to it in our map
		WebPage* wp = new WebPage(filename);
		map_all_webpages.insert ( std::pair<std::string, WebPage*>(filename, wp) );

		map_all_webpages[filename]->all_words(temp_all_words);//same as wp->all_words(temp_all_words)

		std::set<std::string>::iterator it;
		for(it = temp_all_links.begin(); it != temp_all_links.end(); ++it){
			std::ifstream checkExistence( (*it).c_str() );
			if(!checkExistence.fail() ){
				if(!map_all_webpages.count(*it) ){//add the link to our map if its not in there
					WebPage* wp2 = new WebPage(*it);
					map_all_webpages.insert ( std::pair<std::string, WebPage*>(*it, wp2) );
				}
				wp->add_outgoing_link(map_all_webpages[*it]);
				map_all_webpages[*it]->add_incoming_link(wp);
			}
			if(checkExistence.is_open() ){
				checkExistence.close();
			}
		}


		//fill second map
		std::set<std::string>::iterator it2;
		for(it2 = temp_all_words.begin(); it2 != temp_all_words.end(); ++it2){
			std::string tmp = *it2;
			str_to_lower(tmp);
			if(!word_to_setofwps.count(tmp) ){// curr word not inside map
				
				MySet<WebPage*> set_wp;
				set_wp.insert(wp);
				word_to_setofwps.insert( std::make_pair(tmp, set_wp) );
			}
			else{// curr word is inside map
				word_to_setofwps[tmp].insert(wp);
			}
		}

	}else{//webpage is in the map but hasnt had its member set filled in
		WebPage* wp = map_all_webpages[filename];

		wp->all_words(temp_all_words);

		//populate filename's 
		std::set<std::string>::iterator it;
		for(it = temp_all_links.begin(); it != temp_all_links.end(); ++it){
			std::ifstream checkExistence( (*it).c_str() );
			if(!checkExistence.fail() ){
				if(!map_all_webpages.count(*it) ){//add the link to our map if its not in there
					WebPage* wp2 = new WebPage(*it);
					map_all_webpages.insert ( std::pair<std::string, WebPage*>(*it, wp2) );
				}
				wp->add_outgoing_link(map_all_webpages[*it]);
				map_all_webpages[*it]->add_incoming_link(wp);
			}
			if(checkExistence.is_open() ){
				checkExistence.close();
			}
		}


		//fill second map
		std::set<std::string>::iterator it2;
		for(it2 = temp_all_words.begin(); it2 != temp_all_words.end(); ++it2){
			std::string tmp = *it2;
			str_to_lower(tmp);
			if(!word_to_setofwps.count(tmp) ){// curr word not inside map
				
				MySet<WebPage*> set_wp;
				set_wp.insert(wp);
				word_to_setofwps.insert( std::make_pair(tmp, set_wp) );
			}
			else{// curr word is inside map
				word_to_setofwps[tmp].insert(wp);
			}
		}
	}

	
}

MySet<WebPage*> SearchEng::OR_command(std::vector<std::string> words_to_search){
	MySet<WebPage*> cand_search_result;

	MySet<WebPage*> match_search;
	for(unsigned int i = 0; i< words_to_search.size(); i++){
		if(word_to_setofwps.count(words_to_search[i] ) ){// word in search exists in our map
			match_search = match_search.set_union( word_to_setofwps[words_to_search[i] ] );
		}
	}

	//go through all the wps that match and add their outgoing and incoming links into the new set
	MySet<WebPage*>::iterator it;
	for(it = match_search.begin(); it != match_search.end(); ++it){
		cand_search_result.insert(*it);

		MySet<WebPage*> outgoingSet = (*it)->outgoing_links();
		MySet<WebPage*>::iterator itOut;
		for(itOut = outgoingSet.begin(); itOut != outgoingSet.end(); ++itOut){
			cand_search_result.insert(*itOut);
		}

		MySet<WebPage*> incomingSet = (*it)->incoming_links();
		MySet<WebPage*>::iterator itIn;
		for(itIn = incomingSet.begin(); itIn != incomingSet.end(); ++itIn){
			cand_search_result.insert(*itIn);
		}
	}

	return cand_search_result;
} 

MySet<WebPage*> SearchEng::AND_command(std::vector<std::string> words_to_search){
	MySet<WebPage*> cand_search_result;

	MySet<WebPage*> match_search;
	if(word_to_setofwps.count(words_to_search[0] ) ){
		match_search = word_to_setofwps[words_to_search[0] ];
	}
	if(words_to_search.size() > 1){//search has more than one word
		for(unsigned int i = 1; i< words_to_search.size(); ++i){
			if(word_to_setofwps.count(words_to_search[i] ) ){// word in search exists in our map
				match_search = match_search.set_intersection( word_to_setofwps[words_to_search[i] ] );
			}else{//word is not in our map, return empty set
				match_search.clear();
				return match_search;
			}
		}
	}

	//go through all the wps that match and add their outgoing and incoming links into the new set
	MySet<WebPage*>::iterator it;
	for(it = match_search.begin(); it != match_search.end(); ++it){
		cand_search_result.insert(*it);

		MySet<WebPage*> outgoingSet = (*it)->outgoing_links();
		MySet<WebPage*>::iterator itOut;
		for(itOut = outgoingSet.begin(); itOut != outgoingSet.end(); ++itOut){
			cand_search_result.insert(*itOut);
		}

		MySet<WebPage*> incomingSet = (*it)->incoming_links();
		MySet<WebPage*>::iterator itIn;
		for(itIn = incomingSet.begin(); itIn != incomingSet.end(); ++itIn){
			cand_search_result.insert(*itIn);
		}
	}


	return cand_search_result;
	
}

MySet<WebPage*> SearchEng::one_word_search(std::string word){//word is lowercase
	MySet<WebPage*> cand_search_result;

	MySet<WebPage*> match_search = word_to_setofwps[word];

	//go through all the wps that match and add their outgoing and incoming links into the new set
	MySet<WebPage*>::iterator it;
	for(it = match_search.begin(); it != match_search.end(); ++it){
		cand_search_result.insert(*it);

		MySet<WebPage*> outgoingSet = (*it)->outgoing_links();
		MySet<WebPage*>::iterator itOut;
		for(itOut = outgoingSet.begin(); itOut != outgoingSet.end(); ++itOut){
			cand_search_result.insert(*itOut);
		}

		MySet<WebPage*> incomingSet = (*it)->incoming_links();
		MySet<WebPage*>::iterator itIn;
		for(itIn = incomingSet.begin(); itIn != incomingSet.end(); ++itIn){
			cand_search_result.insert(*itIn);
		}
	}

	return cand_search_result;
}	

bool SearchEng::is_in_map(std::string fn){
	return map_all_webpages.count(fn);
}


void SearchEng::str_to_lower(std::string& word){
  for(unsigned int i = 0; i < word.size(); i++){
    if(isalpha(word[i])){
      word[i] = char_to_lower(word[i]);
    }
  }
}

char SearchEng::char_to_lower(char c){
	if(c < 'a'){
	    c += 32;
	}
	return c;
}

void SearchEng::print_words(){

	std::cout << "printing second map: " << std::endl;
	std::map<std::string, MySet<WebPage*> >::iterator it;
	for(it = word_to_setofwps.begin(); it != word_to_setofwps.end(); ++it){
		std::cout << it->first << ", " << std::endl;
	}
}

void SearchEng::print_map(){

	std::cout << "printing internal map 1: " << std::endl;
	std::map<std::string, WebPage*>::iterator it;
	for(it = map_all_webpages.begin(); it != map_all_webpages.end(); ++it){
		std::cout << it->first << ", " << it->second->filename() << std::endl;
	}
}

const std::map<std::string, WebPage*>& SearchEng::get_map_all_webpages(){
	return map_all_webpages;
}

WebPage* SearchEng::get_webpage_at(std::string filename){
	return map_all_webpages[filename];
}