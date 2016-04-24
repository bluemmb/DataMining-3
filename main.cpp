
#include <bits/stdc++.h>
typedef long long int lli;
#define mp make_pair
using namespace std;

string Path = "input.csv";
vector< pair<int , set<string> > > Itemsets;

int main()
{
	freopen(Path.c_str() , "r" , stdin);
	
	bool first = true;
	while ( cin.eof() == false )
	{
		// get whole line
		string s; int sl;
		getline(cin , s);
		sl = s.length();
		
		// ignore empty line
		if ( s=="" ) continue;
		
		// ignore first row
		if ( first ) { first = false; continue; }
		
		
		// get ID and make new Itemset
		int i = 0;
		int id = 0;
		while ( s[i]>='0' && s[i]<='9' ) 
		{ 
			id = id*10 + (s[i]-'0'); 
			i++;
		}
		Itemsets.push_back( mp( id , set<string>() ) );
		
		// jump to Itemset members
		while ( s[i]<'A' || s[i]>'Z' ) i++;
		
		// Get Itemset members
		string t = "";
		while ( i <= sl )
		{
			if ( (i==sl) || (s[i]<'A' || s[i]>'Z') )
			{
				if ( t != "" )
				{
					Itemsets.rbegin()->second.insert( t );
					t = "";
				}
				if ( i==sl ) break;
			}
			else
			{
				t.push_back( s[i] );
			}
			i++;
		}
	}
	
	/*
	// Print data for test
	
	for ( int i=0 ; i<Itemsets.size() ; i++ )
	{
		cout<<Itemsets[i].first<<" "<<Itemsets[i].second.size()<<" : ";
		for ( set<string>::iterator j = Itemsets[i].second.begin() ; j!=Itemsets[i].second.end() ; j++ )
			cout<<"|"<<*j<<"|";
		cout<<"\n";
	}
	*/
	
	return 0;
}
