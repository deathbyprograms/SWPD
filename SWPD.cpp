//Imports for standard functions.
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

//returns a vector of entry names.. Close to the equivalent of an Arraylist in Java.
std::vector<std::string> ls(const char* target) {

	//Makes a vector for our list of files.
	std::vector<std::string> list;

	//Makes a pointer that will point to our directory
	DIR *dir;

	//Makes a pointer that will point to a file as we are reading it.
	struct dirent *ent;

	//A null pointer is returned if we couldn't open the directory, which means it didn't exist. Goes to the else statement.
	if ((dir = opendir(target)) != NULL) {

		//Stops when the directory is out of files to read.
		while ((ent = readdir(dir)) != NULL) {

			//Doesn't add "." or ".." to the list, which represent the current directory and the parent directory respectively.
			if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0){

				//Doesn't finish this loop, but continues to the next iteration.
				continue;

			}

			//Makes the full path of the file
			char* path=(char*)calloc(strlen(target)+strlen(ent->d_name)+2, 1);
			strcat(path, target);
			strcat(path, "/");
			strcat(path, ent->d_name);

			//Checks if the current file is a directory
			DIR* subdir = opendir(path);
			if (subdir != NULL) {

				//Recurse through the directory if it is one.
				std::vector<std::string> sublist = ls(path);

				//Add the results to the end of our current list.
				for(std::string str: sublist){
					list.push_back(str);
				}

			}else{

				//Adds the current file name to the vector we made earlier if it is not a directory.
				std::string librarypath = std::string(path);
				list.push_back(librarypath);

			}

		}

		//Makes sure to close the directory when we are done with it.
		closedir(dir);

		//Returns the vector.
		return list;

	} else {

		//Fails if the directory doesn't exist. The puts statement provides an error message.
		puts("Directory doesn't exist.");
		exit(EXIT_FAILURE);
	}
}

//A method to handle the beef of all the calculation.
const char* run(const char* dir){

    //As a placeholder, constructs a string just as a list of files.
    std::string answer("");
    std::vector<std::string> list = ls(dir);
    for(std::string str:list){
        answer+=str+="\n";
    }

    //Turns the library string into a C-style string, because .c_str() was throwing random bits for the first 8 bytes for some reason.
    char *realAnswer= (char*)calloc(answer.length()+1 ,1);
    for(unsigned int i=0; i<answer.length(); i++){
        realAnswer[i]=answer[i];
    }

    //Returns the constructed string, which is what will be displayed as the result.
    return realAnswer;
}
