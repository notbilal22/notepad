#pragma once
#pragma once
#pragma once
#include<iostream>
#include<fstream>
using namespace std;
int co = 0;
string st[100];
class trietree
{
	ifstream in;
	ofstream out;
	struct node
	{
		node* next[26];//26 letters pointers
		char data;//store character at index
		string data1;//getting word after tree
		bool valid;//bool flag for completion of word
		node()
		{
			data1 = "";
			valid = false;
			data = '-';
			for (int i = 0; i < 26; i++)
			{
				next[i] = NULL;
			}
		}
	};
	node* start;
	node* temp = start;
	int calc_height()
	{
		int h = 0;

		height(start, 0, h);
		return h;
	}
	void height(node* n, int c, int& h)
	{


		if (n != NULL)
		{
			if (c > h)
			{
				h = c;

			}
			for (int i = 0; i < 26; i++)
			{
				height(n->next[i], c + 1, h);
			}

		}
	}
	void store_tree()
	{
		out.open("di.txt");
		int c = calc_height();
		out << c << endl;
		node* n = start;
		for (int i = 1; i <= c; i++)
		{
			level(n, 0, i);
		}

		out.close();
	}
	void level(node* n, int c, int h)
	{


		if (n != NULL)
		{
			if (c == h)
			{

				out << n->data << " " << n->valid << " " << endl;

			}
			for (int i = 0; i < 26; i++)
			{
				level(n->next[i], c + 1, h);
			}

		}
		else if (n == NULL && c == h)
		{

			out << 0 << " " << 0 << endl;
		}
	}
	void traverse(node* n)
	{
		if (n != NULL)
		{

			if (co <= 10)
			{
				for (int i = 0; i < 26; i++)
				{

					traverse(n->next[i]);
				}
				if (n->valid == 1)
				{

					st[co] = n->data1;
					co++;
				}
			}


		}
	}
public:
	trietree()
	{
		start = new node;
	}
	void retrieve_tree(string str, string str1[])
	{
		node* n = start;
		int temp;
		for (int i = 0; i < str.length(); i++)
		{
			if (!(str[i] >= 65 && str[i] <= 90))
			{
				temp = str[i] - 97;
			}
			else
			{
				temp = -1;
				return;
			}
			if (n == NULL || n->next[temp] == NULL)
			{
				return;
			}
			n = n->next[temp];

		}
		traverse(n);
		co = 0;
		for (int i = 0; i < 10; i++)
		{
			str1[i] = st[i];
		}
	}
	bool search_for(string str)
	{
		node* n = start;
		int temp;
		for (int i = 0; i < str.length(); i++)
		{
			temp = str[i] - 97;
			if (n == NULL || n->next[temp] == NULL)
			{
				return 0;
			}
			n = n->next[temp];

		}
		for (int i = 0; i < 100; i++)
		{
			st[i] = "";
		}
		traverse(n);
		if (st[0] == "")
		{
			return 0;
		}
		else {
			return 1;
		}
		co = 0;
	}
	void convert_to_trietree()
	{
		int temp_convert;//store index
		string str;//get word from file
		in.open("dictionary.txt");

		while (!in.eof())
		{
			node* curr = start;
			in >> str;
			for (int i = 0; i < str.length(); i++)
			{

				temp_convert = str[i];

				temp_convert = temp_convert - 97;
				if (curr->next[temp_convert] != NULL)
				{
					if (i == str.length() - 1)
					{
						curr->next[temp_convert]->valid = true;
						curr->next[temp_convert]->data1 = str;
						break;
					}
					curr = curr->next[temp_convert];
				}
				else
				{

					curr->next[temp_convert] = new node;
					curr->next[temp_convert]->data = str[i];
					if (i == str.length() - 1)
					{
						curr->next[temp_convert]->valid = true;
						curr->next[temp_convert]->data1 = str;
						break;
					}
					curr = curr->next[temp_convert];
				}


			}
		}
		in.close();
	}
};
