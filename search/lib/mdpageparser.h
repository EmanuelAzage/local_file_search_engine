//this is webpageparser.h, this class is a child class of pageparser abstract class
#ifndef MDPAGEPARSER_H
#define MDPAGEPARSER_H

#include "lib/pageparser.h"
#include "myset.h"
#include <fstream>
#include <iostream>//debugging
#include <string>

class MDPageParser : public PageParser {
 public:
  // Why do we need a destructor?? there isn't a need for private variables 
  ~MDPageParser() { }

  /** 
   * Parses a file and returns all unique words according
   *  to some parser rules and all hyperlinks based 
   *  on the format the parser is designed to implement
   */
  virtual void parse(std::string filename, MySet<std::string>& allWords, MySet<std::string>& allLinks);

 private:
 	// will I need some member variables?

};

#endif