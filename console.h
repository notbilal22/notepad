#pragma once
#pragma once
#pragma once
#include<iostream>
#include<fstream>
#include <windows.h>
#include<conio.h>
#include<iomanip>
#include"trietree.h"
#include"huffman.h"
using namespace std;
class console
{
private:
	string storing_suggestions[10];
	string temp_word;//for temporary word storing
	string sentence;//for main sentence
	TREE huffman;
	trietree trie_tree;
	char character_ret()
	{
		int x = temp_word.length() - 1;
		return temp_word[x];

	}
	void display_sentence()
	{
		system("cls");
		cout << sentence;
	}
	void input_from_user()
	{
		int count = 0;
		char temp;
		bool flag = true;
		do {

			temp = _getch();
			temp_word += temp;
			char check_if_letter = character_ret();

			if (check_if_letter >= 97 && check_if_letter <= 122 || check_if_letter >= 65 && check_if_letter <= 90)
			{
				count = 0;
				if (!(check_if_letter >= 65 && check_if_letter <= 90))
					trie_tree.retrieve_tree(temp_word, storing_suggestions);
				display_sentence();
				cout << " " << temp_word;
				cout << endl << storing_suggestions[count];
				count++;

			}
			else if (check_if_letter == '/')
			{
				string erase_backslash;
				if (count < 10)
				{
					display_sentence();
					cout << " ";
					for (int i = 0; i < temp_word.length() - 1; i++)
					{
						cout << temp_word[i];
					}

					cout << endl << storing_suggestions[count];
					count++;
				}
				else
				{
					cout << "all suggestions are already showed" << endl;
				}
				temp_word.pop_back();

			}
			else if (check_if_letter == ';')
			{
				count--;
				sentence += storing_suggestions[count];
				display_sentence();
				count = 0;
				temp_word = "";
			}
			else if (check_if_letter == ' ')
			{
				Word_Correction(temp_word);
				flag = iscapital(temp_word[0]);
				if (temp_word != " ") {
					if (flag == true) {
						sentence += temp_word;
					}
					else {
						if (trie_tree.search_for(temp_word) == true)
						{
							sentence += temp_word;
						}
					}
				}
				else {
					sentence += temp_word;
				}
				display_sentence();
				temp_word = "";
				count = 0;
			}
			else if (check_if_letter == '=')
			{
				huffman.store(sentence);
				break;
			}
			else if (check_if_letter == '-')
			{
				temp_word.pop_back();
				if (temp_word != "") {
					temp_word.pop_back();
					display_sentence();
					cout << " " << temp_word;
					cout << endl << storing_suggestions[count];
				}

			}
			else
			{
				temp_word.pop_back();
			}
		} while (true);

	}
	bool iscapital(char check)
	{
		if (check >= 65 && check <= 90)
		{
			return true;
		}
		return false;
	}
	void Word_Correction(string& cap)
	{
		for (int i = 1; i < cap.length(); i++)
		{
			if (cap[i] >= 65 && cap[i] <= 90) {
				cap[i] += 32;
			}
			if (!(cap[i] >= 65 && cap[i] <= 90 || cap[i] >= 97 && cap[i] <= 122))
			{
				cap.erase(i);
			}
		}

	}
public:
	console()
	{
		for (int i = 0; i < 10; i++)
		{
			storing_suggestions[i] = "";
		}
		temp_word = sentence = "";


	}
	void shopher()
	{
		huffman.load(sentence);
		sentence += " ";
		trie_tree.convert_to_trietree();
		display_sentence();
		input_from_user();
		display_sentence();
	}
};

