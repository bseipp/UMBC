// File: Sally.cpp
//
// CMSC 341 Spring 2017 Project 2
//
// Implementation of member functions of Sally Forth interpreter
//

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <stdexcept>
#include <cstdlib>
using namespace std;

#include "Sally.h"


// Basic Token constructor. Just assigns values.
//
Token::Token(TokenKind kind, int val, string txt) {
	m_kind = kind;
	m_value = val;
	m_text = txt;
}


// Basic SymTabEntry constructor. Just assigns values.
//
SymTabEntry::SymTabEntry(TokenKind kind, int val, operation_t fptr) {
	m_kind = kind;
	m_value = val;
	m_dothis = fptr;
}


// Constructor for Sally Forth interpreter.
// Adds built-in functions to the symbol table.
//
Sally::Sally(istream& input_stream) :
	istrm(input_stream)  // use member initializer to bind reference
{

	symtab["DUMP"] = SymTabEntry(KEYWORD, 0, &doDUMP);

	symtab["+"] = SymTabEntry(KEYWORD, 0, &doPlus);
	symtab["-"] = SymTabEntry(KEYWORD, 0, &doMinus);
	symtab["*"] = SymTabEntry(KEYWORD, 0, &doTimes);
	symtab["/"] = SymTabEntry(KEYWORD, 0, &doDivide);
	symtab["%"] = SymTabEntry(KEYWORD, 0, &doMod);
	symtab["NEG"] = SymTabEntry(KEYWORD, 0, &doNEG);

	symtab["DUP"] = SymTabEntry(KEYWORD, 0, &doDup);
	symtab["DROP"] = SymTabEntry(KEYWORD, 0, &doDrop);
	symtab["SWAP"] = SymTabEntry(KEYWORD, 0, &doSwap);
	symtab["ROT"] = SymTabEntry(KEYWORD, 0, &doRot);
	symtab["@"] = SymTabEntry(KEYWORD, 0, &doFetch);
	symtab["SET"] = SymTabEntry(KEYWORD, 0, &doSet);
	symtab["!"] = SymTabEntry(KEYWORD, 0, &doAssign);

	symtab[">"] = SymTabEntry(KEYWORD, 0, &doGreater);
	symtab[">="] = SymTabEntry(KEYWORD, 0, &doGreaterEqual);
	symtab["=="] = SymTabEntry(KEYWORD, 0, &doEqual);
	symtab["!="] = SymTabEntry(KEYWORD, 0, &doNotEqual);
	symtab["<="] = SymTabEntry(KEYWORD, 0, &doLessEqual);
	symtab["<"] = SymTabEntry(KEYWORD, 0, &doLess);

	symtab["AND"] = SymTabEntry(KEYWORD, 0, &doAnd);
	symtab["OR"] = SymTabEntry(KEYWORD, 0, &doOr);
	symtab["NOT"] = SymTabEntry(KEYWORD, 0, &doNot);

	symtab["IFTHEN"] = SymTabEntry(KEYWORD, 0, &doIfThen);
	symtab["ELSE"] = SymTabEntry(KEYWORD, 0, &doElse);
	symtab["ENDIF"] = SymTabEntry(KEYWORD, 0, &doEndIf);

	symtab["DO"] = SymTabEntry(KEYWORD, 0, &doDo);
	symtab["UNTIL"] = SymTabEntry(KEYWORD, 0, &doUntil);

	symtab["."] = SymTabEntry(KEYWORD, 0, &doDot);
	symtab["SP"] = SymTabEntry(KEYWORD, 0, &doSP);
	symtab["CR"] = SymTabEntry(KEYWORD, 0, &doCR);
}


// This function should be called when tkBuffer is empty.
// It adds tokens to tkBuffer.
//
// This function returns when an empty line was entered 
// or if the end-of-file has been reached.
//
// This function returns false when the end-of-file was encountered.
// 
// Processing done by fillBuffer()
//   - detects and ignores comments.
//   - detects string literals and combines as 1 token
//   - detetcs base 10 numbers
// 
//
bool Sally::fillBuffer() {
	string line;     // single line of input
	int pos;         // current position in the line
	int len;         // # of char in current token
	long int n;      // int value of token
	char *endPtr;    // used with strtol()


	while (true) {    // keep reading until empty line read or eof

					  // get one line from standard in
					  //
		getline(istrm, line);

		// if "normal" empty line encountered, return to mainLoop
		//
		if (line.empty() && !istrm.eof()) {
			return true;
		}

		// if eof encountered, return to mainLoop, but say no more
		// input available
		//
		if (istrm.eof()) {
			return false;
		}


		// Process line read

		pos = 0;                      // start from the beginning

									  // skip over initial spaces & tabs
									  //
		while (line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t')) {
			pos++;
		}

		// Keep going until end of line
		//
		while (line[pos] != '\0') {

			// is it a comment?? skip rest of line.
			//
			if (line[pos] == '/' && line[pos + 1] == '/') break;

			// is it a string literal? 
			//
			if (line[pos] == '.' && line[pos + 1] == '"') {

				pos += 2;  // skip over the ."
				len = 0;   // track length of literal

						   // look for matching quote or end of line
						   //
				while (line[pos + len] != '\0' && line[pos + len] != '"') {
					len++;
				}

				// make new string with characters from
				// line[pos] to line[pos+len-1]
				string literal(line, pos, len);  // copy from pos for len chars

												 // Add to token list
												 //
				tkBuffer.push_back(Token(STRING, 0, literal));

				// Different update if end reached or " found
				//
				if (line[pos + len] == '\0') {
					pos = pos + len;
				}
				else {
					pos = pos + len + 1;
				}

			}
			else {  // otherwise "normal" token

				len = 0;  // track length of token

						  // line[pos] should be an non-white space character
						  // look for end of line or space or tab
						  //
				while (line[pos + len] != '\0' && line[pos + len] != ' ' && line[pos + len] != '\t') {
					len++;
				}

				string literal(line, pos, len);   // copy form pos for len chars
				pos = pos + len;

				// Try to convert to a number
				//
				n = strtol(literal.c_str(), &endPtr, 10);

				if (*endPtr == '\0') {
					tkBuffer.push_back(Token(INTEGER, n, literal));
				}
				else {
					tkBuffer.push_back(Token(UNKNOWN, 0, literal));
				}
			}

			// skip over trailing spaces & tabs
			//
			while (line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t')) {
				pos++;
			}

		}
	}
}



// Return next token from tkBuffer.
// Call fillBuffer() if needed.
// Checks for end-of-file and throws exception 
//
Token Sally::nextToken() {
	Token tk;
	bool more = true;

	while (more && tkBuffer.empty()) {
		more = fillBuffer();
	}

	if (!more && tkBuffer.empty()) {
		throw EOProgram("End of Program");
	}

	tk = tkBuffer.front();
	tkBuffer.pop_front();
	return tk;
}


// The main interpreter loop of the Sally Forth interpreter.
// It gets a token and either push the token onto the parameter
// stack or looks for it in the symbol table.
//
//
void Sally::mainLoop() {

	Token tk;
	map<string, SymTabEntry>::iterator it;

	try {
		while (1) {
			tk = nextToken();

			if (tk.m_kind == INTEGER || tk.m_kind == STRING) {

				// if INTEGER or STRING just push onto stack
				params.push(tk);

			}
			else {
				it = symtab.find(tk.m_text);

				if (it == symtab.end()) {   // not in symtab

					params.push(tk);

				}
				else if (it->second.m_kind == KEYWORD) {

					// invoke the function for this operation
					//
					it->second.m_dothis(this);

				}
				else if (it->second.m_kind == VARIABLE) {

					// variables are pushed as tokens
					//
					tk.m_kind = VARIABLE;
					params.push(tk);

				}
				else {

					// default action
					//
					params.push(tk);

				}
			}
		}

	}
	catch (EOProgram& e) {

		cerr << "End of Program\n";
		if (params.size() == 0) {
			cerr << "Parameter stack empty.\n";
		}
		else {
			cerr << "Parameter stack has " << params.size() << " token(s).\n";
		}

	}
	catch (out_of_range& e) {

		cerr << "Parameter stack underflow??\n";

	}
	catch (...) {

		cerr << "Unexpected exception caught\n";

	}
}

// -------------------------------------------------------
void Sally::evaluateTkList(list<Token> tkList, Sally *Sptr) {
	list<Token>::const_iterator iterator;
	Token tk;
	map<string, SymTabEntry>::iterator it;

	//cycle through list of tokens without destroying it
	for (iterator = tkList.begin(); iterator != tkList.end(); ++iterator) {
		tk = *iterator;
		if (tk.m_kind == INTEGER || tk.m_kind == STRING) {

			// if INTEGER or STRING just push onto stack
			Sptr->params.push(tk);
		}
		else {
			it = Sptr->symtab.find(tk.m_text);

			if (it == Sptr->symtab.end()) {   // not in symtab

				Sptr->params.push(tk);

			}
			else if (it->second.m_kind == KEYWORD) {

				// invoke the function for this operation
				//
				it->second.m_dothis(Sptr);

			}
			else if (it->second.m_kind == VARIABLE) {

				// variables are pushed as tokens
				//
				tk.m_kind = VARIABLE;
				Sptr->params.push(tk);

			}
			else {

				// default action
				//
				Sptr->params.push(tk);

			}
		}
	}
}

void Sally::doDo(Sally *Sptr) {
	//evaluate until we hit until
	//when we hit until, check the boolean, is it true or false, if false, call do again with list
	list<Token> tkList;
	Token tk;
	
	tk = Sptr->nextToken();

	while (tk.m_text != "UNTIL") {
		tkList.push_back(tk);
		tk = Sptr->nextToken();
	}
	int i = 0;
	//evaluate it once
	evaluateTkList(tkList, Sptr);

	Token p1;

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need a parameter for DO");
	}
	//grab the top of the parameter stack, to check if its positive or negative
	p1 = Sptr->params.top();
	Sptr->params.pop();

	//as long as the value is false, keep evaluating
	while (p1.m_value == 0) {
		evaluateTkList(tkList, Sptr);
		p1 = Sptr->params.top();
		Sptr->params.pop();
	}
}

void Sally::doUntil(Sally *Sptr) {

}

void Sally::doIfThen(Sally *Sptr) {
	Token p1;

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need a parameter for IFTHEN");
	}
	p1 = Sptr->params.top();

	if (p1.m_value == 0) {
		bool skip = true;
		int ifCounter = 0;
		while (skip) {
			Token tk = Sptr->tkBuffer.front();
			if (tk.m_text == "IFTHEN") {
				ifCounter++;
				Sptr->nextToken();
			}
			else if (tk.m_text == "ELSE") {
				if (ifCounter <= 0)
					skip = false;
				else {
					ifCounter--;
					Sptr->nextToken();
				}
			}
			else {
				Sptr->nextToken();
			}
		}
	}
}

void Sally::doElse(Sally *Sptr) {
	Token p1;

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need a parameter for ELSE");
	}
	p1 = Sptr->params.top();

	if (p1.m_value == 1) {
		bool skip = true;
		int ifCounter = 0;
		while (skip) {
			Token tk = Sptr->tkBuffer.front();
			if (tk.m_text == "IFTHEN") {
				ifCounter++;
				Sptr->nextToken();
			}
			else if (tk.m_text == "ENDIF") {
				if (ifCounter <= 0)
					skip = false;
				else {
					ifCounter--;
					Sptr->nextToken();
				}
			}
			else {
				Sptr->nextToken();
			}
		}
	}
}

void Sally::doEndIf(Sally *Sptr) {
	if (Sptr->params.size() < 1) {
		throw out_of_range("Need a parameter for ENDIF");
	}
	Sptr->params.pop();
}

void Sally::doLess(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for <");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	if (p2.m_value - p1.m_value < 0)
		Sptr->params.push(Token(INTEGER, 1, ""));
	else
		Sptr->params.push(Token(INTEGER, 0, ""));
}

void Sally::doLessEqual(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for <=");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	if (p2.m_value - p1.m_value <= 0)
		Sptr->params.push(Token(INTEGER, 1, ""));
	else
		Sptr->params.push(Token(INTEGER, 0, ""));
}

void Sally::doNotEqual(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for !=");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	if (p2.m_value - p1.m_value != 0)
		Sptr->params.push(Token(INTEGER, 1, ""));
	else
		Sptr->params.push(Token(INTEGER, 0, ""));
}

void Sally::doEqual(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for ==");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	if (p2.m_value - p1.m_value == 0)
		Sptr->params.push(Token(INTEGER, 1, ""));
	else
		Sptr->params.push(Token(INTEGER, 0, ""));
}

void Sally::doGreaterEqual(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for >=");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	if (p2.m_value - p1.m_value >= 0)
		Sptr->params.push(Token(INTEGER, 1, ""));
	else
		Sptr->params.push(Token(INTEGER, 0, ""));
}

void Sally::doGreater(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for >");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	if (p2.m_value - p1.m_value > 0)
		Sptr->params.push(Token(INTEGER, 1, ""));
	else
		Sptr->params.push(Token(INTEGER, 0, ""));
}

void Sally::doAnd(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for AND");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	if (p2.m_value == 0 || p1.m_value == 0)
		Sptr->params.push(Token(INTEGER, 0, ""));
	else
		Sptr->params.push(Token(INTEGER, 1, ""));
}

void Sally::doOr(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for OR");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	if (p2.m_value == 0 && p1.m_value == 0)
		Sptr->params.push(Token(INTEGER, 0, ""));
	else
		Sptr->params.push(Token(INTEGER, 1, ""));
}

void Sally::doNot(Sally *Sptr) {
	Token p1;

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need one parameter for NOT");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();

	if (p1.m_value == 0)
		Sptr->params.push(Token(INTEGER, 1, ""));
	else
		Sptr->params.push(Token(INTEGER, 0, ""));
}

void Sally::doSet(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for SET");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	string variableName = p1.m_text;
	int value = p2.m_value;

	Sptr->symtab[variableName] = SymTabEntry(VARIABLE, value, NULL);
}

void Sally::doFetch(Sally *Sptr) {
	Token p1;

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need one parameter for @");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();

	int value = Sptr->symtab[p1.m_text].m_value;

	Sptr->params.push(Token(INTEGER, value, ""));
}

void Sally::doAssign(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for !");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	int newValue = p2.m_value;
	Sptr->symtab[p1.m_text] = SymTabEntry(VARIABLE, newValue, NULL);
}

void Sally::doDup(Sally *Sptr) {
	Token p1;

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need one parameter for DUP");
	}
	p1 = Sptr->params.top();
	Sptr->params.push(p1);
}

void Sally::doDrop(Sally *Sptr) {
	if (Sptr->params.size() < 1) {
		throw out_of_range("Need one parameter for DROP");
	}

	Sptr->params.pop();
}

void Sally::doSwap(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for SWAP");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	Sptr->params.push(p1);
	Sptr->params.push(p2);
}

void Sally::doRot(Sally *Sptr) {
	Token p1, p2, p3;

	if (Sptr->params.size() < 3) {
		throw out_of_range("Need three parameters for ROT");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	p3 = Sptr->params.top();
	Sptr->params.pop();

	Sptr->params.push(p2);
	Sptr->params.push(p1);
	Sptr->params.push(p3);
}

void Sally::doPlus(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for +.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	int answer = p2.m_value + p1.m_value;
	Sptr->params.push(Token(INTEGER, answer, ""));
}

void Sally::doMinus(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for -.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	int answer = p2.m_value - p1.m_value;
	Sptr->params.push(Token(INTEGER, answer, ""));
}

void Sally::doTimes(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for *.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	int answer = p2.m_value * p1.m_value;
	Sptr->params.push(Token(INTEGER, answer, ""));
}

void Sally::doDivide(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for /.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	int answer = p2.m_value / p1.m_value;
	Sptr->params.push(Token(INTEGER, answer, ""));
}

void Sally::doMod(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for %.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	int answer = p2.m_value % p1.m_value;
	Sptr->params.push(Token(INTEGER, answer, ""));
}

void Sally::doNEG(Sally *Sptr) {
	Token p;

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need one parameter for NEG.");
	}
	p = Sptr->params.top();
	Sptr->params.pop();
	Sptr->params.push(Token(INTEGER, -p.m_value, ""));
}

void Sally::doDot(Sally *Sptr) {

	Token p;
	if (Sptr->params.size() < 1) {
		throw out_of_range("Need one parameter for .");
	}

	p = Sptr->params.top();
	Sptr->params.pop();

	if (p.m_kind == INTEGER) {
		cout << p.m_value;
	}
	else {
		cout << p.m_text;
	}
}

void Sally::doSP(Sally *Sptr) {
	cout << " ";
}

void Sally::doCR(Sally *Sptr) {
	cout << endl;
}

void Sally::doDUMP(Sally *Sptr) {
	cout << Sptr->tkBuffer.front().m_value << endl;
}
