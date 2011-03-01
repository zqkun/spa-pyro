#include"PqlParser.h"
 
 //int prefix(string token);
/*
void main()
{
	QueryTable table=PqlParser::parser();
	Validator validate;
	validate.populateTable();
	cout<<"suchthat "<<validate.checkSuchThat(table)<<endl;
	cout<<"with "<<validate.checkWith(table)<<endl;
	table.showTable();
}
*/
QueryTable PqlParser::parser(string query) {
  QueryTable table;
  string line;
  string pch;//token elements
  Tokenizer token;
  Tokenizer withToken;
  int p;//swither
  int temp;//temp store the information
  int prefix;//get the prefix of the user defined var
  string withclause;//all the merged withclause.
  string operand1,operand11,operand12, operand2,operand21,operand22;
  int suchthatclause;
  int u=PqlParser::USERDEFINED;
  int g=PqlParser::GRAMMERDEFINED;
  enum KEYWORD
  {
	AND=0,
	SELECT=1,
	SUCH_THAT=2,
	WITH=3,
	PATTERN=4,
	VALUE=101,
  };
  Convertor::update();
  int type;
  vector<int> content;
  //ifstream myfile ("query.txt");
  //if (myfile.is_open())
  //{
   // while ( myfile.good() )
    //{
     // getline (myfile,line);
	  //query=query.append(line);
//	}
	  token.set(query," ,;()");
	  pch=token.next();
	  while (pch !="")
		{
			//printf ("%s\n",pch);
			if(Convertor::isDeclar(pch))
			{
				string temp=pch;
				pch=token.next();
				while(pch!=""&&!(Convertor::isDeclar(pch))&&Convertor::getIndex(pch)==-1)
				{
					Convertor::insertShortcut(pch,temp);
				    Convertor::insertIndex(u++,pch);
					pch=token.next();
				}
			}
			else 
			{
				
			 p=Convertor::getIndex(pch);
			// cout<<p;
			 switch(p)
			 {
				case SELECT:
					

				type=SELECT;
				 do
				 {
					pch=token.next();
					
					temp=Convertor::getIndex(pch);
					prefix=PqlParser::prefix(pch);
				
					if (temp>=USERDEFINED||prefix==VALUE)
					{   
						//prefix=PqlParser::prefix(pch);
						//cout<<"prefix"<<PqlParser::prefix(pch);
						if(prefix!=0)
						content.push_back(prefix);
						
						content.push_back(temp);

						table.addClause(SELECT,content);
						content.clear();
					}
					else if(temp=-1)
					{
						
						break;
					}
					else
					{
						break;
					}
					
				  }while(pch!=""&&temp>u);

				  //table.addClause(SELECT,content);
				  
				  break;
					
				case SUCH_THAT:
				//cout<<type<<"shuaigevs lianghongge";
					
				type=SUCH_THAT;
				//content.clear();
				pch=token.next();
				//cout<<pch<<endl;
				do{// this do loop is for the and clause inside the suchthat;

				pch=token.next();
				suchthatclause=Convertor::getIndex(pch);
					   //cout<<"---------"<<suchthatclause;
						 content.push_back(suchthatclause);
						 pch=token.next();
						 //cout<<pch;
						 temp=Convertor::getIndex(pch);
						 prefix=PqlParser::prefix(pch);
						 cout<<"temp:"<<temp<<"prefix"<<prefix;
						  
						  while (temp>=USERDEFINED||prefix==VALUE||temp==157)
                        {   
					     //cout<<"temp:"<<temp<<"prefix"<<prefix;
							 if(prefix!=0)
							 content.push_back(prefix);
						   	 content.push_back(temp);
							 pch=token.next();
							 //cout<<pch;
							 temp=Convertor::getIndex(pch);
							 prefix=PqlParser::prefix(pch);
							
						}

						table.addClause(type,content);
						content.clear();
					//	table.showQuery();
				}while(temp==0);
				        break;
			  case WITH:

					 
					 int i;
				     type=WITH;
                     do
					 {
				     pch=token.next();
					 i=Convertor::getIndex(pch);
					 while(i!=AND&&i!=SELECT&&i!=SUCH_THAT&&i!=WITH&&i!=PATTERN&&pch!="")
					 {
						 withclause=withclause.append(pch);
						 pch=token.next();
						 i=Convertor::getIndex(pch);
					 }
					 //cout<<"______this is withclause_________"<<withclause;
					 withToken.set(withclause,"=");
					 operand1=withToken.next();
					 operand2=withToken.next();
					 
					 if (operand1!="")
                     {
						 withToken.set(operand1,".");
						 operand11=withToken.next();
					     operand12=withToken.next();
						 prefix=PqlParser::prefix(operand11);
						 if(prefix!=0)
						 content.push_back(prefix);
						 content.push_back(Convertor::getIndex(operand11));
						  
						 //content.push_back(PqlParser::prefix("."));
						 content.push_back(Convertor::getIndex("."));
						  prefix=PqlParser::prefix(operand12);
						 if(prefix!=0)
						 content.push_back(prefix);
						 content.push_back(Convertor::getIndex(operand12));
						 //content.push_back(PqlParser::prefix("="));
						 content.push_back(Convertor::getIndex("="));
					 }
					 else
					 {
						 cout<<"error in with clause";
					 }
					  if (operand2!="")
                     {
						 withToken.set(operand2,".");
						 operand21=withToken.next();
					     operand22=withToken.next();
						 if(operand22=="")
						 {
                         //temp=Convertor::getIndex(operand21);
							 prefix=PqlParser::prefix(operand21);
							 if (prefix!=0)
						 content.push_back(prefix);

						 content.push_back(Convertor::getIndex(operand21));
						 }
						 else
						 {
						 prefix=PqlParser::prefix(operand21);
							 if(prefix!=0)
					     content.push_back(prefix);
					     content.push_back(Convertor::getIndex(operand21));
						 //content.push_back(PqlParser::prefix("."));
						 content.push_back(Convertor::getIndex("."));
						 prefix=PqlParser::prefix(operand22);
							 if(prefix!=0)
					     content.push_back(prefix);
						  // content.push_back(PqlParser::prefix(operand22));
						 content.push_back(Convertor::getIndex(operand22));
						 } 
				     }
					 else
					 {
						 cout<<"error in with clause";
					 }
	 
                 
					 table.addClause(type,content);
					 content.clear(); 
					 withclause.clear();
					}while(i==0);
		 
		         //  table.showQuery();
				break;

		    case PATTERN:
				type=PATTERN;
				break;



			default:
		     pch=token.next();
				break;
	  }
		//pch = strtok (NULL, " ,;()");
   }
			
			
			

	}
	//table.showTable();
  //  myfile.close();
  
//}
 // else cout << "Unable to open file"; 

  return table;
}

int PqlParser:: prefix(string token)
{
	int index,prefix;
	//vector<int> content;
	index=Convertor::getIndex(token);
	//cout<<"========================="<<index;
	if(index>=PqlParser::USERDEFINED&&atoi(token.c_str())==0)
		{
			prefix=Convertor::getIndex(Convertor::getContent(token));
			//content.push_back(prefix);
			//content.push_back(index);
	    }
	else 
	   {
		   if(atoi(token.c_str())!=0)
              prefix=101;
		   else
			   prefix=0;
		   //content.push_back(index);
	   }

	return prefix;
}
