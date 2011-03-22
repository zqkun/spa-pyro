#include"TokenList.h"
     int index;
	// vector<string> TokenList::fullVector;
	 TokenList::TokenList()
	 {
		 index=-1;
	 }
	 TokenList::TokenList(string s)
	 {
		 index=-1;
		 tokenList(s);
	 }

int TokenList::tokenList(string s)
{   
	
	vector<string> temp1,temp2;
	temp1=tokenBy(s," ");
	
	mergeVector(temp1);
	temp1=fullVector;
	
	fullVector.clear();

    string a[]={";",",","(",")",".","=","<",">"};
	for(int j=0;j<8;j++)
	{
		for(int i=0;i<(int)temp1.size();i++)
		{
			temp2=tokenBy(temp1[i],a[j]);
	        mergeVector(temp2);
		}
		temp1=fullVector;
	    fullVector.clear();
		
	}
	fullVector=temp1;
	return 0;
}
vector<string> TokenList::tokenBy(string s,string deliminator)
{
	//cout<<"the string is "<<s<<endl;
	vector<string> temp;
	bool indicatorH=false,indicatorT=false;
	string pch;
	tokenizer.set(s,deliminator);
	pch=tokenizer.next();
	if(deliminator==" "||s.substr(s.size()-1,1)==deliminator)
		indicatorT=true;
	if(deliminator!=" "&&s.substr(0,1)==deliminator)
		indicatorH=true;
	if(indicatorH)
		temp.push_back(deliminator);

	while(pch!="")
	{
	  temp.push_back(pch);
	if(deliminator!=" ")
      temp.push_back(deliminator);
	
       pch=tokenizer.next();
	}

	if(!indicatorT)
		temp.pop_back();

	int length=TokenListLength(temp);
	//cout<<"after token "<<length<<"compare with "<<s.length()<<endl;
	if(length<(int)s.length()&&deliminator!=" ")
	{   // cout<<"duplicate"<<deliminator<<endl;
		throw new string("duplicate "+deliminator+"are not valide \n");
	}
	else if(length>(int)s.length())
	{
		//cout<<"error tokenize with"<<deliminator<<endl;
		throw new string("error tokenize with"+deliminator);
	}
	return temp;
}
int TokenList::TokenListLength(vector<string> s)
{
	int length=0;
	for(int i=0;i<(int)s.size();i++)
		length+=s[i].length();
	return length;
}
void TokenList::mergeVector(vector<string>vector)
{
	
	fullVector.reserve(fullVector.size() + vector.size()); // Optional, tiny performance improvement

    fullVector.insert(fullVector.end(), vector.begin(), vector.end()); //insert the first vector
   // fullVector.insert(fullVector.end(), vector2.begin(), vector2.end()); //insert the second
}
void TokenList::showTokenList()
{
	int size=fullVector.size();
	for(int i=0;i<size;i++)
	{
		cout<<fullVector[i]<<endl;
	}
}
 string TokenList::getNextToken()
 {

	 index++;
	 if(index<(int)fullVector.size())
	     return fullVector[index];
	 else
	 {  
		 return "NULL";
	 }
		 //throw new string("out of bond");
 }
 vector<string> TokenList::getTokenList()
 {
	 return fullVector;
 }
 int TokenList::getSize()
 {
	 return fullVector.size();
 }
 void destruc()
 {

 }