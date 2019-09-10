/*
 * assignment1.cpp
 *
 * <add comments to describe the purpose of this application>
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>

using namespace std;

enum direction {LEFT_RIGHT,RIGHT_LEFT,DOWN,UP,RIGHT_DOWN,RIGHT_UP,LEFT_DOWN,LEFT_UP};

const int MAX = 50;

struct wordGame
{
	int version=2;
	int numberRows;
	int numberColumns;
	char puzzle[MAX][MAX];
}wordgame;

struct wordFind
{
	string word;
	bool found;
	int row;
	int column;
	direction where;
}wordfind;

// outputs in cout the direction of the found word
string direct(direction where)
{
	switch(where)
	{
	case LEFT_RIGHT : return "right";
	case RIGHT_LEFT : return "left";
	case DOWN : return "down";
	case UP : return "up";
	case RIGHT_DOWN : return "right/down";
	case RIGHT_UP : return "right/up";
	case LEFT_DOWN : return "left/down";
	case LEFT_UP : return "left/up";
	};
	return "";
}

// read the puzzle from the input file
bool readPuzzle(wordGame &game, string inputFileName)
{
	ifstream infile(inputFileName);
	if(infile.fail())
	{
		return false;
	}else{
		int r;
		int col;

		// reads the two ints to identify the size of the puzzle
		infile>>r;
		infile>>col;
		if(r>0 && r<=MAX)
		{
			game.numberRows=r;
		}else return false;
		if(col>0 && col<=MAX)
		{
			game.numberColumns=col;
		}else return false;

		// counts the rows and columns to make sure that
		// the input puzzle provides the correct amount of lines of data
		int countRow=0, countCol=0;
		string temp;
		getline(infile,temp);
		while(!infile.eof())
		{
			infile>>temp;
			countRow++;
		};
		countCol=(int)temp.length();
		if(countRow!=game.numberRows || countCol!=game.numberColumns)
		{
			return false;
		};
		infile.close();
		infile.open(inputFileName);
		infile>>r;
		infile>>col;

		// builds the 2d puzzle array
		char c;
		infile.get(c);
		for(int i=0;i<game.numberRows;i++)
		{
			for(int j=0;j<game.numberColumns;j++)
			{
				infile.get(c);
				game.puzzle[i][j]=c;
			};
			infile.get(c);
		};
		infile.close();
	};
	return true;
}

// displays the puzzle from the input file
void displayPuzzle(wordGame &game)
{
	// prints all the chars from game.puzzle[][]
	for(int i=0;i<game.numberRows;i++)
	{
		for(int j=0;j<game.numberColumns;j++)
		{
			cout<<game.puzzle[i][j];
		};
		cout<<endl;
	};
}

// finds a specific word in the puzzle from the input files
void findWord(wordGame &game, wordFind &theFind)
{
	theFind.found=0;
	size_t foundB;
	theFind.row=0;
	theFind.column=0;
	string test="";

	// ALL OF THE FOLLOWING DIRECTIONAL CASES FOLLOW A SIMILAR FORMAT, EXCEPT FOR THE LOOPS AND INDICES
	// left to right direction
	for(int i=0;i<game.numberRows;i++)
	{
		test="";
		// makes a test string to compare with the word that is currently being searched for
		for(int j=0;j<game.numberColumns;j++)
		{
			// converts to upper case letters
			test+=(char)toupper(game.puzzle[i][j]);
		};
		// looks for the word in the test string
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			// if found, sets all the values in wordFind to be output in the cout in main()
			theFind.found=1;
			theFind.row=i+1;
			theFind.column=(int)foundB+1;
			theFind.where=LEFT_RIGHT;
		};
	};

	// right to left direction
	for(int i=0;i<game.numberRows;i++)
	{
		test="";
		for(int j=game.numberColumns-1;j>=0;j--)
		{
			test+=(char)toupper(game.puzzle[i][j]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=i+1;
			theFind.column=game.numberColumns-(int)foundB;
			theFind.where=RIGHT_LEFT;
		};
	};

	// downwards direction
	for(int j=0;j<game.numberColumns;j++)
	{
		test="";
		for(int i=0;i<game.numberRows;i++)
		{
			test+=(char)toupper(game.puzzle[i][j]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=(int)foundB+1;
			theFind.column=j+1;
			theFind.where=DOWN;
		};
	};
		// upwards direction
	for(int j=0;j<game.numberColumns;j++)
	{
		test="";
		for(int i=game.numberRows-1;i>=0;i--)
		{
			test+=(char)toupper(game.puzzle[i][j]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=game.numberRows-(int)foundB;
			theFind.column=j+1;
			theFind.where=UP;
		};
	};

	// right/down direction
	for(int j=0;j<game.numberColumns;j++)
	{
		test="";
		for(int i=0;i<game.numberRows;i++)
		{
			test+=(char)toupper(game.puzzle[i][i+j]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=(int)foundB+1;
			theFind.column=(int)foundB+j+1;
			theFind.where=RIGHT_DOWN;
		};
	};
	for(int i=0;i<game.numberRows;i++)
	{
		test="";
		for(int j=0;j<game.numberColumns;j++)
		{
			test+=(char)toupper(game.puzzle[i+j][j]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=(int)foundB+i+1;
			theFind.column=(int)foundB+1;
			theFind.where=RIGHT_DOWN;
		};
	};

	// right/up direction
	for(int j=0;j<game.numberColumns;j++)
	{
		test="";
		for(int i=game.numberRows-1;i>=0;i--)
		{
			test+=(char)toupper(game.puzzle[i][game.numberRows-1-i+j]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=game.numberRows-(int)foundB;
			theFind.column=(int)foundB+j+1;
			theFind.where=RIGHT_UP;
		};
	};
	for(int i=0;i<game.numberRows;i++)
	{
		test="";
		for(int j=0;j<game.numberColumns;j++)
		{
			test+=(char)toupper(game.puzzle[i-j][j]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=i+1-(int)foundB;
			theFind.column=(int)foundB+1;
			theFind.where=RIGHT_UP;
		};
	};

	// left/down direction
	for(int j=0;j<game.numberColumns;j++)
	{
		test="";
		for(int i=0;i<game.numberRows;i++)
		{
			test+=(char)toupper(game.puzzle[i][j-i]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=(int)foundB+1;
			theFind.column=j+1-(int)foundB;
			theFind.where=LEFT_DOWN;
		};
	};
	for(int i=0;i<game.numberRows;i++)
	{
		test="";
		for(int j=0;j<game.numberColumns;j++)
		{
			test+=(char)toupper(game.puzzle[i+j][game.numberColumns-j-1]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=i+1+(int)foundB;
			theFind.column=game.numberColumns-(int)foundB;
			theFind.where=LEFT_DOWN;
		};
	};

	// left/up direction
	for(int j=0;j<game.numberColumns;j++)
	{
		test="";
		for(int i=0;i<game.numberRows;i++)
		{
			test+=(char)toupper(game.puzzle[game.numberRows-i-1][game.numberColumns-j-i-1]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=game.numberRows-(int)foundB;
			theFind.column=game.numberColumns-(int)foundB-j;
			theFind.where=LEFT_UP;
		};
	};
	for(int i=0;i<game.numberRows;i++)
	{
		test="";
		for(int j=0;j<game.numberColumns;j++)
		{
			test+=(char)toupper(game.puzzle[i-j][game.numberColumns-j-1]);
		};
		foundB=test.find(theFind.word);
		if(foundB!=string::npos)
		{
			theFind.found=1;
			theFind.row=i-(int)foundB+1;
			theFind.column=game.numberColumns-(int)foundB;
			theFind.where=LEFT_UP;
		};
	};
}

// main function
int main()
{
	// UNCOMMENT TO HAVE USER INPUT FILES
	string puzzleFile, wordFile;
	cin>>puzzleFile;
	cin>>wordFile;

	/*string puzzleFile = "puzzle1.txt";
	string wordFile = "words1.txt";*/
	if(!readPuzzle(wordgame,puzzleFile))
	{
		cout<<"The puzzle file \""<<puzzleFile<<"\" could not be opened or is invalid"<<endl;
		return 0;
	};
	cout<<"The file \""<<puzzleFile<<"\""<<endl;
	displayPuzzle(wordgame);
	ifstream infile(wordFile);
	if(!infile.is_open())
	{
		cout<<"The puzzle file \""<<wordFile<<"\" could not be opened or is invalid"<<endl;
		return 0;
	};
	string word,copy;
	while(!infile.eof())
	{
		infile>>word;
		if(copy==word)return 0;
		wordfind.word=word;
		findWord(wordgame,wordfind);
		if(!wordfind.found)
		{
			cout<<"The word "<<wordfind.word<<" was not found"<<endl;
		}else{
			cout<<"The word "<<wordfind.word<<" was found at ("<<wordfind.row<<", "<<wordfind.column<<") - "<<direct(wordfind.where)<<endl;
		};
		copy=word;
	};
	return 0;
}
