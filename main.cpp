
#include <bits/stdc++.h>
typedef long long int lli;
#define mp make_pair
using namespace std;

// Important Variables
string Path = "input.csv";
vector< pair<int , set<string> > > Itemsets;
map< set<string> , int > Table;

// Print All Itemsets
void PrintItemsets()
{
	for ( int i=0 ; i<Itemsets.size() ; i++ )
	{
		cout<<Itemsets[i].first<<" "<<Itemsets[i].second.size()<<" : ";
		for ( set<string>::iterator j = Itemsets[i].second.begin() ; j!=Itemsets[i].second.end() ; j++ )
			cout<<"|"<<*j<<"|";
		cout<<"\n";
	}
}

int main()
{
	freopen(Path.c_str() , "r" , stdin);
	
	bool first = true;
	map<string , int> m;
	
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
					m[t]++;
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
	
	// Create Initial Table
	for ( map<string , int>::iterator i = m.begin() ; i != m.end() ; i++ )
	{
		set<string> s;
		s.insert( i->first );
		Table[ s ] = i->second;
	}
	
	// --------------------------------------------------------------------
	
	
	
	return 0;
}
