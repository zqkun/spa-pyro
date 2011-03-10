#include "SymbolTable.h"
using namespace std;


void ProcTable::insertProc(string s)
{
	this->insertSymbol(s);
}// end InsertProc

string ProcTable::getProcName(int index)
{
	if(isProcIndexExist(index)) return this->getSymbolName(index);
	else return "";
}// end GetProcName

int ProcTable::getProcIndex(string s)
{
	if(isProcNameExist(s)) return this->getSymbolIndex(s);
	else return -1;
}// end GetProcIndex

int ProcTable::getSize()
{
	return this->getSymbolMapSize();
}// end getProcTableSize

bool ProcTable::isProcNameExist(string procName)
{
	return this->isNameExist(procName);
}// end ContainsProc

bool ProcTable::isProcIndexExist(int procIndex)
{
	return this->isIndexExist(procIndex);
}// end ContainsProc

set<string> ProcTable::getAllProc()
{
	return this->getAllSymbol();
}// end GetAllProc


/**
 * For call tables
 */

/* procIndex1 calls procIndex2 */
void ProcTable::addCall(int procIndex1, int procIndex2) {
	set<int> tmp;

	/* check if the procIndex1 has already existed in callTable */
	if(callTable.find(procIndex1) != callTable.end())	//procIndex1 exists
	{
		tmp = callTable[procIndex1];
		tmp.insert(procIndex2);
		callTable[procIndex1] = tmp;
	}
	else	//procIndex1 does not exist
	{
		tmp.insert(procIndex2);
		callTable.insert(pair<int, set<int>>(procIndex1, tmp));
	}

	addCalled(procIndex2, procIndex1);
}//end addCall(int procIndex1, int procIndex2)


/* procIndex1 calls procList */
void ProcTable::addCall(int procIndex1, vector<int> procList){
	set<int> tmp;
	int indexTmp;

	/* check if the procIndex1 has already existed in callTable */
	if(callTable.find(procIndex1) != callTable.end())	//procIndex1 exists
	{
		tmp = callTable[procIndex1];
		for(indexTmp = 0; indexTmp < (int)procList.size(); indexTmp++)
			tmp.insert(procList[indexTmp]);
		callTable[procIndex1] = tmp;
	}
	else	//procIndex1 does not exist
	{
		/* copy element from list<int> to set<int> */
		for(indexTmp = 0; indexTmp < (int)procList.size(); indexTmp++)
			tmp.insert(procList[indexTmp]);
		callTable.insert(pair<int, set<int>>(procIndex1, tmp));
	}
}//end addCall(int procIndex1, vector<int> procList)


/* procIndex1 was called by procIndex2 */
void ProcTable::addCalled(int procIndex1, int procIndex2){
	set<int> tmp;

	/* check if the procIndex1 has already existed in calledTable */
	if(calledTable.find(procIndex1) != calledTable.end())	//procIndex1 exists
	{
		tmp = calledTable[procIndex1];
		tmp.insert(procIndex2);
		calledTable[procIndex1] = tmp;
	}
	else	//procIndex1 does not exist
	{
		tmp.insert(procIndex2);
		calledTable.insert(pair<int, set<int>>(procIndex1, tmp));
	}
}

/* procIndex1 was called procList */
void ProcTable::addCalled(int procIndex1, vector<int> procList){
	set<int> tmp;
	int indexTmp;

	/* check if the procIndex1 has already existed in calledTable */
	if(calledTable.find(procIndex1) != calledTable.end())	//procIndex1 exists
	{
		tmp = calledTable[procIndex1];
		for(indexTmp = 0; indexTmp < (int)procList.size(); indexTmp++)
			tmp.insert(procList[indexTmp]);
		calledTable[procIndex1] = tmp;
	}
	else	//procIndex1 does not exist
	{
		/* copy element from list<int> to set<int> */
		for(indexTmp = 0; indexTmp < (int)procList.size(); indexTmp++)
			tmp.insert(procList[indexTmp]);
		calledTable.insert(pair<int, set<int>>(procIndex1, tmp));
	}
}//end addCalled(int procIndex1, vector<int> procList)

/* get all procedures called by procIndex */
vector<int> ProcTable::getCall(int procIndex){
	vector<int> tmpVec;
	set<int>	tmpSet;

	/* verify procIndex */
	if(procIndex < 0 || !isProcIndexExist(procIndex)){
		tmpVec.push_back(-1);
		return tmpVec;
	}

	/* Check if procIndex exists in exists */
	if(callTable.find(procIndex) != callTable.end())	//procIndex exists
	{
		tmpSet = callTable[procIndex];
		/* In case procIndex calls no procdure */
		if(tmpSet.size() <= 0){
			tmpVec.push_back(-1);
			return tmpVec;
		}

		/* copy element from set<int> to list<int> */
		for(set<int>::iterator it = tmpSet.begin(); it != tmpSet.end(); it++)
			tmpVec.push_back(*it);
	}
	else	//procIndex does not exist
	{
		tmpVec.push_back(-1);
	}

	return tmpVec;
}//end getCall


/* get all procedures who call procIndex */
vector<int> ProcTable::getCalled(int procIndex){
	vector<int> tmpVec;
	set<int>	tmpSet;

	/* verify procIndex */
	if(procIndex < 0 || !isProcIndexExist(procIndex)){
		tmpVec.push_back(-1);
		return tmpVec;
	}

	/* Check if procIndex exists in exists */
	if(calledTable.find(procIndex) != calledTable.end())	//procIndex exists
	{
		tmpSet = calledTable[procIndex];
		/* In case procIndex was called by no procdure */
		if(tmpSet.size() <= 0){
			tmpVec.push_back(-1);
			return tmpVec;
		}

		/* copy element from set<int> to list<int> */
		for(set<int>::iterator it = tmpSet.begin(); it != tmpSet.end(); it++)
			tmpVec.push_back(*it);
	}
	else	//procIndex does not exist
	{
		tmpVec.push_back(-1);
	}

	return tmpVec;
}//end getCalled

/* get all procedures called recursively by procIndex */
vector<int> ProcTable::getCall_(int procIndex){
	
	if (call_Table.find(procIndex) != call_Table.end())
		return call_Table[procIndex];

	if (!isIndexExist(procIndex)) {
		vector<int> result;
		result.push_back(-1);
		return result;
	}

	set<int> visited;
	queue<int> curr_queue;

	//minimum spanning tree
	vector<int> next_queue = getCall(procIndex);
	for (unsigned int i = 0; i < next_queue.size(); i++)
		curr_queue.push(next_queue[i]);

	while (!curr_queue.empty())
	{
		int curr_proc = curr_queue.front();
		curr_queue.pop();

		if (visited.find(curr_proc) == visited.end())
		{
			visited.insert(curr_proc);
			vector<int> next_queue = getCall(curr_proc);
			for (unsigned int i = 0; i < next_queue.size(); i++)
				curr_queue.push(next_queue[i]);
		}
	}

	vector<int> result(visited.begin(), visited.end());
	call_Table[procIndex] = result;

	return result;
}

/* get all procedures called recursively by procIndex */
vector<int> ProcTable::getCalled_(int procIndex){
	
	if (called_Table.find(procIndex) != called_Table.end())
		return called_Table[procIndex];

	if (!isIndexExist(procIndex)) {
		vector<int> result;
		result.push_back(-1);
		return result;
	}

	set<int> visited;
	queue<int> curr_queue;

	//minimum spanning tree
	vector<int> next_queue = getCalled(procIndex);
	for (unsigned int i = 0; i < next_queue.size(); i++)
		curr_queue.push(next_queue[i]);

	while (!curr_queue.empty())
	{
		int curr_proc = curr_queue.front();
		curr_queue.pop();

		if (visited.find(curr_proc) == visited.end())
		{
			visited.insert(curr_proc);
			vector<int> next_queue = getCalled(curr_proc);
			for (unsigned int i = 0; i < next_queue.size(); i++)
				curr_queue.push(next_queue[i]);
		}
	}

	vector<int> result(visited.begin(), visited.end());
	called_Table[procIndex] = result;

	return result;
}

//For Debugging
void ProcTable::printProcTable()
{
	this->printSymbolTable("Procedure");
}

void ProcTable::printCallTable(){
	if(callTable.size() == 0) 
		cout<<"CallTable table is empty!"<<endl;
	else{
		set<int> proc2Set;
		for(map<int, set<int>>::iterator itProc1 = callTable.begin(); itProc1 != callTable.end(); itProc1++)
		{
			cout<<"Procedure "<<this->getProcName(itProc1->first)<<" calls procedure: ";
			proc2Set = itProc1->second;
			for(set<int>::iterator itProc2 = proc2Set.begin(); itProc2 != proc2Set.end(); itProc2++)
				cout<<this->getProcName(*itProc2)<<", ";
			cout<<endl;
		}
	}
}//end printCallTable

void ProcTable::printCalledTable(){
	if(calledTable.size() == 0) 
		cout<<"CalledTable table is empty!"<<endl;
	else{
		set<int> proc2Set;
		for(map<int, set<int>>::iterator itProc1 = calledTable.begin(); itProc1 != calledTable.end(); itProc1++)
		{
			cout<<"Procedure "<<this->getProcName(itProc1->first)<<" is called by procedure: ";
			proc2Set = itProc1->second;
			for(set<int>::iterator itProc2 = proc2Set.begin(); itProc2 != proc2Set.end(); itProc2++)
				cout<<this->getProcName(*itProc2)<<", ";
			cout<<endl;
		}
	}
}//end printCalledTable

void ProcTable::printCall_Table(){
	if(call_Table.size() == 0) 
		cout<<"Call*Table table is empty!"<<endl;
	else{
		vector<int> proc2Vec;
		for(map<int, vector<int>>::iterator itProc1 = call_Table.begin(); itProc1 != call_Table.end(); itProc1++)
		{
			cout<<"Procedure "<<this->getProcName(itProc1->first)<<" recursively calls procedure(s): ";
			proc2Vec = itProc1->second;
			for(unsigned int i = 0; i < proc2Vec.size(); i++)
				cout<<this->getProcName(proc2Vec[i])<<", ";
			cout<<endl;
		}
	}
}//end printCall_Table

void ProcTable::printCalled_Table(){
	if(called_Table.size() == 0) 
		cout<<"Call*Table table is empty!"<<endl;
	else{
		vector<int> proc2Vec;
		for(map<int, vector<int>>::iterator itProc1 = called_Table.begin(); itProc1 != called_Table.end(); itProc1++)
		{
			cout<<"Procedure "<<this->getProcName(itProc1->first)<<" is called recursively by procedure(s): ";
			proc2Vec = itProc1->second;
			for(unsigned int i = 0; i < proc2Vec.size(); i++)
				cout<<this->getProcName(proc2Vec[i])<<", ";
			cout<<endl;
		}
	}
}//end printCall_Table