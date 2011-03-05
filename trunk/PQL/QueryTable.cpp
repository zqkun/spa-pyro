#include <iostream>
#include "QueryTable.h"


//////////////////////// add Clause --- Start ///////////////////////////////
//QueryTable::QueryTable()
//{}
void QueryTable::addClause(int type, vector<int> content){

	if(type == 1) // select
	{
		if(selectVector.empty() == true)
		{
			selectVector.push_back(1);
		}

		if(content.front() == 60) // content is boolean
		{
			Select selectTemp;
			selectTemp.tuple = content;
			selectClause.push_back(selectTemp);
			selectVector.push_back(content.front());
		}
		else  //content is tuple
		{   

			vector<int>::iterator it;
			for (it = content.begin(); it < content.end(); it++)
			{
				Select selectTemp;
				if(selectVector.size()>1)
				{
					selectVector.push_back(-1);
				}
				selectTemp.tuple.push_back(*it);
				selectVector.push_back(*it);
				it = it+1;
				selectTemp.tuple.push_back(*it);
				selectVector.push_back(*it);

				selectClause.push_back(selectTemp);
			}		
		}
		
	}
	else if(type == 2) // such that, no length parameter
	{
		SuchThat SuchThatTemp;
		SuchThat validTemp;

		SuchThatTemp.relCond = content;
		SuchThatTemp.argumentNoCorrect = false;
		if(SuchThatTemp.relCond.size() == 5)
		{
			SuchThatTemp.argumentNoCorrect = true;
		}
		else if(SuchThatTemp.relCond.size() == 4)
		{
			
			if((SuchThatTemp.relCond[1] == 157 && SuchThatTemp.relCond[2]!=157) || (SuchThatTemp.relCond[1] != 157 && SuchThatTemp.relCond[3] ==157))
			{
				SuchThatTemp.argumentNoCorrect = true;
			}
		}
		else if(SuchThatTemp.relCond.size() == 3)
		{
			if(SuchThatTemp.relCond[1] == 157 && SuchThatTemp.relCond[2]==157)
			{
				SuchThatTemp.argumentNoCorrect = true;
			}
		}
		suchThatClause.push_back(SuchThatTemp);

		//add data for validation
		for(int i = 0; i<content.size();i++)
		{

			//cout<<content[i]<<" ///////////////BEFORE CHANGE"<<endl;
			if(content[i] == 8) // make "follow*" to be "follow"
			{
				validTemp.relCond.push_back(7);
			}
			else if(content[i] == 6) // make "parent*" to be "parent"
			{
				validTemp.relCond.push_back(5);
			}
			else if(content[i] == 12) // make "calls*" to be "calls"
			{
				validTemp.relCond.push_back(11);
			}
			else if(content[i] == 53 || content[i] == 54 || content[i] == 55) // make "assign", "while", "if" to be "stmt" 
			{
				//cout<<" I am inside this 53 54 55!"<<endl;
				validTemp.relCond.push_back(51);
			}
			else
			{
				validTemp.relCond.push_back(content[i]);
			}
			//cout<<validTemp.relCond[i]<<" ###########AFTER CHANGE"<<endl;
			
		}
		suchThatClauseValid.push_back(validTemp);


		/*
		cout<<SuchThatTemp.relCond[0]<<" ";
		cout<<SuchThatTemp.relCond[1]<<" ";
		cout<<SuchThatTemp.relCond[2]<<" ";
		cout<<SuchThatTemp.relCond[3]<<" ";
		cout<<SuchThatTemp.relCond[4]<<" ";
		*/
		//cout<<SuchThatTemp.argumentNoCorrect<<" ";
		//cout<<endl;
		

		//add the content to the suchThatVector
		if(suchThatVector.empty() == true)
		{
			suchThatVector.push_back(2);
		}
		else 
		{
			suchThatVector.push_back(-1);
		}
		vector<int>::iterator it;
		for (it = content.begin(); it < content.end(); it++)
		{
			suchThatVector.push_back(*it);
		}
		
	}
	else if(type == 3) // with
	{
		With withTemp;
		With validTemp;
		if(content.size() == 7 || content.size() == 9)
		{
			withTemp.argumentNoCorrect = true;
		}
		else
		{
			withTemp.argumentNoCorrect = false;
		}
		withTemp.attrCond = content;
		withClause.push_back(withTemp);

		//add data for validation
		for(int i = 0; i<content.size();i++)
		{

			//cout<<content[i]<<" ///////////////BEFORE CHANGE"<<endl;
			if(content[i] == 53 || content[i] == 54 || content[i] == 55) // make "assign", "while", "if" to be "stmt" 
			{
				//cout<<" I am inside this 53 54 55!"<<endl;
				validTemp.attrCond.push_back(51);
			}
			else
			{
				validTemp.attrCond.push_back(content[i]);
			}
			//cout<<validTemp.attrCond[i]<<" ###########AFTER CHANGE"<<endl;
			
		}
		withClauseValid.push_back(validTemp);
		
		//add the content to the withVector
		if(withVector.empty() == true)
		{
			withVector.push_back(3);
		}
		else 
		{
			withVector.push_back(-1);
		}
		vector<int>::iterator it;
		for (it = content.begin(); it < content.end(); it++)
		{
			withVector.push_back(*it);
		}
		
	
	}
	else // other value
	{
		cout<<"Wrong type of content!"<<endl;
		exit(1);
	}


}
//////////////////////// add Clause --- End ///////////////////////////////

//////////////////////// getQuery --- Start ///////////////////////////////
vector<int> QueryTable::getQuery(){
	vector <int> queryHolder;
	//insert select part
	if(selectVector.empty() == false)
	{
		queryHolder.insert(queryHolder.end(), selectVector.begin(), selectVector.end()); 
		queryHolder.push_back(-2); // add a tail to select part	
	}

	//insert such that part
	if(suchThatVector.empty() == false)
	{
		queryHolder.insert(queryHolder.end(), suchThatVector.begin(), suchThatVector.end());
		queryHolder.push_back(-2); // add a tail to such that part
	}

	//insert with part
	if(withVector.empty() == false)
	{
		queryHolder.insert(queryHolder.end(), withVector.begin(), withVector.end());
		queryHolder.push_back(-2); // add a tail to with part
	}
	return queryHolder;

}
//////////////////////// getQuery --- End ///////////////////////////////


//////////////////////// getSize  --- Start ///////////////////////////////
int QueryTable::getSize()
{
	cout<< "QueryTable::getSize(): " << selectClause.size() << endl;
	return selectClause.size();
}
//////////////////////// getSize  --- End ///////////////////////////////

//////////////////////// Clause Size  --- Start ///////////////////////////////
int QueryTable::selectSize(){
		
	return selectClause.size();
}

int QueryTable::suchThatSize(){

	return suchThatClause.size();
}
int QueryTable::withSize(){

	return withClause.size();
}
//////////////////////// Clause Size  --- End ///////////////////////////////

//////////////////////// selectAt  --- Start ///////////////////////////////
vector<int> QueryTable::selectAt(int index){
	
	vector<int> tupleTemp;
	//check whether index is out of range (need to throw exception, make it as function)
	if(index > selectClause.size())
	{
		throw new string("select index out of range!");
	}
	else
	{
		tupleTemp = selectClause.at(index).tuple;
	}

	return tupleTemp;
}

vector<int> QueryTable::suchThatAt(int index)
{
	vector<int> relCondTemp;

	if(index>suchThatClause.size())
	{
		cout<<"index out of range!"<<endl;
	}
	else
	{
		relCondTemp = suchThatClause.at(index).relCond;
	}

	return relCondTemp;

}

vector<int> QueryTable::withAt(int index){

	vector<int> attrCondTemp;
	if(index>withClause.size())
	{
		cout<<"index out of range!"<<endl;
	}
	else
	{
		attrCondTemp = withClause.at(index).attrCond;
	}

	return attrCondTemp;

}
//////////////////////// selectAt  --- End ///////////////////////////////


/////////////////////////Get Clause --- Start ///////////////////////////
vector < Select > QueryTable::getSelectClause(){
	return selectClause;
}

vector < SuchThat >  QueryTable::getSuchThatClauseV(){

	return suchThatClauseValid;
}

vector < With >  QueryTable::getWithClauseV(){
	return withClauseValid;
}

/////////////////////////Get Clause --- End ///////////////////////////

void QueryTable::showTable()
{

	vector<int> temHolder = getQuery();
	for(int i=0;i<temHolder.size();i++)
	{
		cout<<temHolder[i]<<" ";
	}
	cout<<endl;

}