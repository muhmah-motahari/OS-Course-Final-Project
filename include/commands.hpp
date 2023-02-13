#include <string>
#include <iostream>

// Declear tokenize input instruction 
void tokenize(std::string const &str, std::vector<std::string> &out);

// Build directive path for commands
std::string path(std::string relative);

// Declear prototype of commands 
void cp_command (std::string org, std::string des);
void mv_command (std::string org, std::string des);
void touch_command (std::string des);
void mkdir_command (std::string direction);
void ls_command (std::string path);
void help();
