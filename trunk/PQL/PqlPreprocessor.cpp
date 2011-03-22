#include "PqlPreprocessor.h"


PqlPreprocessor::PqlPreprocessor(string query){
	PqlParser::parser(query, &qt);
}

QueryTable PqlPreprocessor::getTable(){
	return qt;
}

int PqlPreprocessor::selectSize(){
	return qt.selectSize();
}

void PqlPreprocessor::selectAt(vector<int> &tupleTemp, int index){
	qt.selectAt(tupleTemp,index);
}

int PqlPreprocessor::suchThatSize(){
	return qt.suchThatSize();
}

void PqlPreprocessor::suchThatAt(vector<int> &relCondTemp, int index){
	qt.suchThatAt(relCondTemp,index);
}

int PqlPreprocessor::withSize(){
	return qt.withSize();
}

void PqlPreprocessor::withAt(vector<int> &attrCondTemp,int index){
	qt.withAt(attrCondTemp,index);
}
int PqlPreprocessor::patternSize(){
	return qt.patternSize();
}

void PqlPreprocessor::patternAt(vector<int> &expression, int index){
	qt.patternAt(expression,index);
}


int PqlPreprocessor::getIndex(std::string key){
	return Convertor::getIndex(key);
}

string PqlPreprocessor::getContent(int indx){
	return Convertor::getKeyword(indx);
}

int PqlPreprocessor::procCode(string key){
	string tmp = "\""+key+ "\"";
	return Convertor::getIndex(tmp);
}

int PqlPreprocessor::varCode(string key){
	string tmp = "\""+key+ "\"";
	return Convertor::getIndex(tmp);
}

string PqlPreprocessor::varDecode(int i){
	string indx = Convertor::getKeyword(i);
	Tokenizer s;
	s.set(indx, "\"");
	return s.next();
}

string PqlPreprocessor::procDecode(int i){
	//cout << i << endl;
	string indx = Convertor::getKeyword(i);
	vector<string> v;
	string tmp = "\"";
	Tokenize(indx, v, tmp);
	//cout << "It should be correct: "<<v.at(0) << endl;
	return v.at(0);
}

void PqlPreprocessor::Tokenize(const string& str,
                      vector<string>& tokens,
                      string& delimiters)
{
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}