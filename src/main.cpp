#include <iostream>
#include <vector>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../include/commands.hpp"

using namespace std;

string localpath;
	
int main(){

	// Initial path
	char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
	localpath = "";
	localpath += cwd;
	localpath += "/";

	// Start command line programm and wait for get a command
	cout << ">> ";
	string input;

	while(getline(cin, input)){

		// Tokenize
		vector<string> out;
		tokenize(input,out);

		// Detect command
		if(out.at(0) == "cp"){
			// Command cp
			// Check number of arguments
			if(out.size() != 3){
				cout << "\033[1;41mInvalid Arguments!" << endl;
				cerr << "Usage: cp <origin directory> <destination directory>\033[0m" << endl;
			} else {

				cp_command(localpath + out.at(1), localpath + out.at(2));

			}

		} else if (out.at(0) == "mv"){
			// Command mv
			// Check number of arguments
			if(out.size() != 3){
				cout << "\033[1;41mInvalid Arguments!" << endl;
				cerr << "Usage: mv <origin directory> <destination directory>\033[0m" << endl;
			} else {
				mv_command(localpath + out.at(1), localpath + out.at(2));
			}
		}  else if (out.at(0) == "touch"){
			// Command touch
			// Check number of arguments
			if(out.size() != 2){
				cout << "\033[1;41mInvalid Arguments!" << endl;
				cerr << "Usage: touch <directory>\033[0m" << endl;
			} else {
				touch_command(localpath + out.at(1));
			}
		}  else if (out.at(0) == "mkdir"){
			// Command mkdir
			// Check number of arguments
			if(out.size() != 2){
				cout << "\033[1;41mInvalid Arguments!" << endl;
				cerr << "Usage: mkdir <directory>\033[0m" << endl;
			} else {
				mkdir_command(localpath + out.at(1));
			}

		}  else if (out.at(0) == "ls"){
			// Command ls

			string path = localpath + ".";
			if(out.size() == 2){
				path = localpath + out.at(1);
			} else if(out.size() > 2){
				cerr << "\033[1;41mInvalid Arguments!" << endl;
				cerr << "Usage: ls [path]\033[0m" << endl;
			}
			ls_command(path);

		} else if (out.at(0) == "cd"){
			// Command cd

			string tmppath = localpath + out.at(1);
			if(out.at(1).at(out.at(1).size() - 1) != '/'){
				tmppath += "/";
			}

			struct stat info;
			if( stat( tmppath.c_str(), &info ) != 0 ){
				cout << "\033[1;41mCannot access " <<  tmppath << "\033[0m" << endl;

			} else if( info.st_mode & S_IFDIR ){  // S_ISDIR() doesn't exist
				cout << "\033[1;32m" <<  tmppath << " is a directory\033[0m" << endl;
				localpath = tmppath;
			} else{
				cout << "\033[1;41m" << tmppath << " is no directory" << endl;
			}
			

		} else if (out.at(0) == "pwd"){
			// Command pwd
			cout << localpath << endl;

		}  else if (out.at(0) == "help"){
			// Help
			help();

		}  else if (out.at(0) == "exit"){
			// Exit
			cout << "CU later🫶🏻👋"<< endl;
			return 0;

		} else {
			// Another commands
			cout << "\033[1;41mInvalid command!\033[0m" << endl;
			help();
		}

		cout << "\n>> ";
	}
	return 0;
}
