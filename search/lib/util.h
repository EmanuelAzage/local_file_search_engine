#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <fstream>
#include <iostream>

std::string convToLower(std::string src);

void get_config_inputs(std::string config_file_str, std::map<std::string, std::string>& config_inputs);

#endif
