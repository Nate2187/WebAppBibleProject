// WebAppBibleProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include "cJSON.h"
#include <vector>
#include <sstream>
#include <fstream>

std::string getVerse(std::string userInput);
std::string readFile(const std::string &fileName);
int parse_object(std::string content);

std::string globalBookName;
std::string globalChapter;
std::string globalVerse;

int main()
{
	//while (1) {

	std::string verse;
	std::cout << "Enter a query in book(book must be in all lowercase) chapter:verse format!\n";

	getline(std::cin, verse);

	getVerse(verse);
	std::string jsonContent = readFile(globalBookName + ".json");

	parse_object(jsonContent);
	//}

	system("pause");

}

//2 seperate files
//parse user input use file matching parse chapter, parse verse, return verse
//split user input into array of String
//Check for name of book
//Throw error if book doesn't exist
//check for chapter/verse 
//throw error if book doesn't exist
//else return verse





std::string getVerse(std::string userInput)
{
	std::replace(userInput.begin(), userInput.end(), ':', ' ');

	try {
		std::string result[3];
		int i = 0;
		std::stringstream ssin(userInput);
		while (ssin.good() && i < 3) {
			ssin >> result[i];
			++i;
		}
		if
			(result[0] == "isaiah") {

			globalBookName = "isaiah";

			if (std::stoi(result[1]) > 66) {
				std::cout << "ERROR SELECT A VERSE BETWEEN 1 AND 66 \n";
				return "";
			}

			globalChapter = result[1];
			//for verse we need to construct the CJSON object and then get the chapter length and compare it to index in value[2]

			globalVerse = result[2];
		}
		else if
			(result[0] == "titus") {

			globalBookName = "titus";

			if (std::stoi(result[1]) > 3) {
				std::cout << "ERROR SELECT A VERSE BETWEEN 1 AND 66 \n";
				return "";
			}
			globalChapter = result[1];
			//for verse we need to construct the CJSON object and then get the chapter length and compare it to index in value[2]

			globalVerse = result[2];
		}
		else {
			std::cout << "ERROR : INVALID INPUT PLEASE ENTER EITHER ISAIAH OR TITUS \n";
		}
	}
	catch (const std::exception) {
		std::cout << "EXCEPTION THROWN";
	}
	return "";
}

std::string readFile(const std::string &fileName)
{
	std::string data;
	std::ifstream in(fileName.c_str());
	getline(in, data, std::string::traits_type::to_char_type(std::string::traits_type::eof()));
	return data;
}


//next step 
//Use cJSON to parse through the text and return the verse




int parse_object(std::string content)
{
	cJSON* book = NULL;
	cJSON* chaptersArray = cJSON_CreateArray();
	cJSON* chapter = NULL;
	cJSON* versesArray = cJSON_CreateArray();
	cJSON* verse = NULL;
	cJSON* verseContent = NULL;
	int status = 0;

	//root node
	cJSON *bible_json = cJSON_Parse(content.c_str());

	if (bible_json == NULL) {
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
		status = 0;
		goto end;

	end:
		cJSON_Delete(bible_json);
		return status;

	}


	book = cJSON_GetObjectItem(bible_json, "book");
	if (cJSON_IsString(book) && (book->valuestring != NULL))
	{
		printf("\n", book->valuestring);
	}

	chaptersArray = cJSON_GetObjectItem(bible_json, "chapters");
	
	int chapterIndex = std::stoi(globalChapter) - 1;
	chapter = cJSON_GetArrayItem(chaptersArray, chapterIndex);

	versesArray = cJSON_GetObjectItem(chapter, "verses");

	int verseIndex = std::stoi(globalVerse) - 1;
	verse = cJSON_GetArrayItem(versesArray, verseIndex);

	verseContent = cJSON_GetObjectItem(verse, globalVerse.c_str());
	std::cout << verseContent->valuestring << " \n";

}
