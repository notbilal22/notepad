#pragma once
#pragma once
#pragma once
#include<iostream>
#include<fstream>
using namespace std;
struct listNODE
{
	int frequency;
	char data;
	listNODE* next, * left, * right;

	listNODE()
	{
		frequency = 0; data = '-'; next = left = right = NULL;
	}
};
class Linkedlist
{
private:
	listNODE* head;
public:
	Linkedlist()
	{
		head = NULL;
	}
	bool isempty()
	{
		if (head == NULL) {
			return true;
		}
		return false;
	}
	void insert(int frequency, char data)
	{
		listNODE* newnode = new listNODE;
		newnode->data = data;
		newnode->frequency = frequency;
		if (head == NULL)
		{
			head = newnode;
		}
		else {
			listNODE* current = head;
			if (current->frequency > newnode->frequency)
			{
				newnode->next = current;
				head = newnode;
				return;
			}
			else {
				while (current->next != NULL)
				{
					if (current->next->frequency > newnode->frequency)
					{
						newnode->next = current->next;
						current->next = newnode;
						return;
					}
					current = current->next;
				}
				current->next = newnode;
			}

		}
	}
	listNODE* del()
	{
		listNODE* curr = head;
		head = head->next;
		return curr;
	}
	void insertarray(int* arr, int mode)
	{
		for (int i = 0; i < 27; i++)
		{
			if (arr[i] != 0)
			{
				if (mode == 0)
				{
					if (i == 26) {
						insert(arr[i], 32);
					}
					else {
						insert(arr[i], i + 97);
					}
				}
				else if (mode == 1)
				{
					insert(arr[i], i + 65);

				}
			}
		}
	}
	void insertfromBST(listNODE* newnode)
	{
		listNODE* current = head;
		if (head == NULL)
		{
			head = newnode;
		}
		else {
			if (current->frequency > newnode->frequency)
			{
				newnode->next = current;
				head = newnode;
				return;
			}
			else {
				while (current->next != NULL)
				{
					if (current->next->frequency > newnode->frequency)
					{
						newnode->next = current->next;
						current->next = newnode;
						return;
					}
					current = current->next;
				}
				current->next = newnode;
			}
		}

	}
	listNODE* gethead()
	{
		return head;
	}
	void makeheadNULL()
	{
		head = NULL;
	}
	void insertfromfile(int freq, char data)
	{
		listNODE* newnode = new listNODE;
		newnode->data = data;
		newnode->frequency = freq;
		listNODE* current = head;
		if (head == NULL)
		{
			head = newnode;
		}
		else {
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = newnode;
		}
	}
};
class TREE {
	Linkedlist obj;
	listNODE* headofsortedlist;
	int small[27], capital[27];
	string sm[27], cap[27], str, encrypted = "";
	void frequency(string x)
	{
		int length = x.length();
		for (int i = 0; i < length; i++)
		{
			if (x[i] >= 65 && x[i] <= 90)
			{
				int index = x[i] - 65;
				capital[index]++;
			}
			else if (x[i] >= 97 && x[i] <= 122)
			{
				int index = x[i] - 97;
				small[index]++;
			}
			else if (x[i] == 32)
			{
				small[26]++;
			}
		}
	}
	void insertion(string x)
	{
		frequency(x);
		obj.insertarray(small, 0);
		obj.insertarray(capital, 1);
		headofsortedlist = obj.gethead();
	}
	void encrypt(listNODE* ptr, char dest, int index, string binary)
	{
		if (ptr != NULL)
		{
			if (ptr->data == dest)
			{
				if (ptr->data >= 65 && ptr->data <= 90)
				{
					cap[index] = binary;
				}
				else {
					sm[index] = binary;
				}
				binary = "";
			}
			else {
				binary += "0";
				encrypt(ptr->left, dest, index, binary);
				binary.pop_back();
				binary += "1";
				encrypt(ptr->right, dest, index, binary);
			}
		}
	}
	void binary()
	{
		encrypted = "";
		int x = str.length();
		int index = 0;
		for (int i = 0; i < x; i++)
		{
			if (str[i] >= 65 && str[i] <= 90)
			{
				index = str[i] - 65;
				encrypted += cap[index];
			}
			else if (str[i] >= 97 && str[i] <= 122)
			{
				index = str[i] - 97;
				encrypted += sm[index];
			}
			else if (str[i] == 32)
			{
				encrypted += sm[26];
			}
		}
	}
	void makeBSt(string s)
	{
		obj.makeheadNULL();
		str = s;
		insertion(s);
		listNODE* left, * right;
		listNODE* current = obj.gethead();
		while (current != NULL)
		{

			left = obj.del();
			right = obj.del();
			current = obj.gethead();
			listNODE* newnode = new listNODE;
			int x = left->frequency + right->frequency;
			newnode->frequency = x;
			newnode->left = left;
			newnode->right = right;
			obj.insertfromBST(newnode);

		}
	}
	void encryption()
	{
		listNODE* ptr = obj.gethead();
		string str = "";
		for (int i = 0; i < 27; i++)
		{
			if (small[i] != 0) {
				if (i == 26)
				{
					encrypt(ptr, 32, i, str);
				}
				else {
					encrypt(ptr, i + 97, i, str);
				}
			}
		}
		for (int i = 0; i < 27; i++)
		{

			if (capital[i] != 0)
			{
				encrypt(ptr, i + 65, i, str);
			}
		}
		binary();
	}
	void decrypt(string& sent)
	{
		int x = encrypted.length();
		char j = 0;
		for (int i = 0; i < x; i++)
		{
			listNODE* current = obj.gethead();
			string temp = str;
			while (current != NULL && current->data == '-' && encrypted[i] != NULL)
			{
				j = encrypted[i];
				if (j == '1')
				{
					current = current->right;
				}
				else if (j == '0')
				{
					current = current->left;
				}
				i++;
			}
			if (current != NULL && current->data != '-') {
				sent += current->data;
				i--;
			}
		}
	}
	void readbinary()
	{
		ifstream read;
		read.open("encrypted.txt");
		char encrypt = ' ';
		encrypted = "";
		while (!(read.eof()))
		{
			read >> encrypt;
			encrypted += encrypt;
		}
		read.close();
	}
	void readTRee()
	{
		ifstream read;
		char data;
		int freq;
		obj.makeheadNULL();
		read.open("huffman.txt");
		while (!read.eof())
		{
			read >> freq;
			read >> data >> data;
			if (data != '@') {
				if (data == 42)
				{
					data = 32;
				}
				if (data != -52) {
					obj.insertfromfile(freq, data);
				}
			}
			else {
				break;
			}
		}
	}
	void writetree()
	{
		ofstream write;
		listNODE* current = headofsortedlist;
		char data;
		write.open("huffman.txt");
		write << write.eof();
		write.close();
		write.open("huffman.txt", ios::app);

		while (current != NULL)
		{
			if (current->data != '-')
			{
				if (current->data == ' ')
				{
					data = 42;
				}
				else {
					data = current->data;
				}
				write << current->frequency << "," << data << endl;
			}
			current = current->next;
		}
		write << "1,@" << endl;
		write.close();
	}
	void writebinary()
	{
		ofstream write;
		write.open("encrypted.txt");
		write << encrypted;
		write.close();
	}
	void maketreefromfile()
	{
		listNODE* left, * right;
		listNODE* current = obj.gethead();
		while (current != NULL)
		{

			left = obj.del();
			right = obj.del();
			current = obj.gethead();
			listNODE* newnode = new listNODE;
			int x = left->frequency + right->frequency;
			newnode->frequency = x;
			newnode->left = left;
			newnode->right = right;
			obj.insertfromBST(newnode);

		}
	}
public:
	TREE() {
		for (int i = 0; i < 26; i++)
		{
			small[i] = capital[i] = 0;
			sm[i] = cap[i] = "0";
		}
	}
	void load(string& sent)
	{
		readbinary();
		readTRee();
		maketreefromfile();
		decrypt(sent);
		cout << endl;
	}
	void store(string var)
	{
		makeBSt(var);
		encryption();
		writebinary();
		writetree();
	}
};
