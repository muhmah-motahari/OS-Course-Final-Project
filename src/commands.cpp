#include "../include/commands.hpp"
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <sys/stat.h>
#include <dirent.h>
using namespace std;

void tokenize(string const &str, vector<string> &out){
	// construct a stream from the string
	stringstream ss(str);

	string s;
	while(getline(ss, s, ' ')){
		out.push_back(s);
	}
}

void cp_command (string org, string des){
	//cout << "\t\t***\tTest => Origin: " << org << "\t Destination: " << des << endl;

	ifstream rf(org, ios::in | ios::binary);

	if(!rf.is_open()){
		cerr << "\033[1;41mInput file is not exist!!\033[0m" << endl;

	} else {

		ofstream wf(des, ios::out | ios::binary);
  	char tmp;
  	while(!rf.eof()){
  		rf.read(&tmp,1);
  		wf.write(&tmp,1);

  		if(rf.eof())
  			break;
  	}

		cout << "\033[1;32mFile successfully copied\033[0m" << endl;
	}
}

void mv_command (string org, string des){

	cp_command(org, des);

	// Remove origin file
	if (remove(org.c_str()) != 0){
      cerr << "\033[1;41mError deleting file\033[0m" << endl;
  } else{
      cout << "\033[1;32mFile successfully deleted\033[0m" << endl;
  }
}

void touch_command (string des){
	ofstream wf(des, ios::out | ios::app);
	if(!wf.is_open()){
		cerr << "\033[1;41mError: unable to create file\033[0m" << endl;
		return;
	}
	wf.close();
}

void mkdir_command (string direction){
  int result = mkdir(direction.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	// S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH, gives read, write, and execute permissions to the owner and group, and read and execute permissions to others. 
  if (result != 0) {
      cerr << "\033[1;41mError: unable to create directory\033[0m" << endl;
  }	
}

void ls_command (string path){
	DIR* dir = opendir(path.c_str());
	if(!dir){
		cerr << "\033[1;41mError: unable to open directory\033[0m" << endl;
		return;
	}

  struct dirent* entry;
  while ((entry = readdir(dir)) != nullptr) {
    std::string entry_path = path + "/" + entry->d_name;
    struct stat entry_stat;
    if (stat(entry_path.c_str(), &entry_stat) == 0) {
		  if (S_ISDIR(entry_stat.st_mode)) {
		   	std::cout << "\033[1;32m" << entry->d_name << "\033[0m/" << std::endl;
		  }
		  else {
         std::cout << entry->d_name << std::endl;
      }
    }
  }

  closedir(dir);
}
void help(){
  cout << "\nFileManager cli - 1.0 (2023 Feb 07)" << endl << endl;
  cout << "Commands:" << endl;
  cout << "  pwd                                      Show current location (path)" << endl;
  cout << "  cd <destination_location>                Go to a special directory" << endl;
  cout << "  ls [destination_location]                Show the files and directories that exists in current path" << endl;
  cout << "  cp <origin_file> <destination_file>      Copy a file to another directory with special name" << endl;
  cout << "  mv <origin_file> <destination_file>      Move a file to another directory with special name" << endl;
  cout << "  touch <file_name>                        Create a file with special name" << endl;
  cout << "  mkdir <directory_name>                   Create a directory with special nane" << endl;
  cout << "  help                                     Show Help" << endl;
  cout << "  exit                                     Exit from program" << endl;
	
}
