
#include <bits/stdc++.h>
typedef long long int lli;
#define mp make_pair
using namespace std;

// #define DEBUG

// Important Variables
string Path = "input.csv";
vector< pair<int , set<string> > > Itemsets;
map< set<string> , int > Table;
map< set<string> , int > Help;
map< set<string> , int > Answer;
const int MinSupport = 2;

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

// p = p Union q
void Union( set<string> &p , const set<string> &q )
{
	set<string>::iterator i = q.begin();
	while ( i != q.end() )
	{
		p.insert( *i );
		i++;
	}
}

// Count number of Itemsets that contain p
int Count( const set<string> &p )
{
	int ret = 0;
	for (int k=0 ; k<Itemsets.size() ; k++)
	{
		set<string> &q = Itemsets[k].second;
		
		set<string>::iterator i = p.begin() , j = q.begin();
		while ( i!=p.end() && j!=q.end() )
		{
			if ( *i == *j ) i++;
			else if ( *j > *i ) break;
			j++;
		}
		
		ret += ( i == p.end() );
	}
	
	return ret;
}

// Print Like Set
void PrintSet( const set<string> &p )
{
	set<string>::iterator i = p.begin();
	bool first = true;
	
	cout<<"{";
	while ( i != p.end() )
	{
		if ( first ) first = false; else cout<<",";
		cout<<*i;
		i++;
	}
	cout<<"}";
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
		if ( i->second >= MinSupport )
			Table[ s ] = i->second;
	}
	
	// --------------------------------------------------------------------
	
	// GOOOOOOO
	
	while ( Table.size() != 0 )
	{
		// Union Sets and check their frequency then save them in Help variable
		for ( map< set<string> , int>::iterator i = Table.begin(),j ; i != Table.end() ; i++ )
		{
			j = i; j++;
			for ( ; j != Table.end() ; j++ )
			{
				set<string> neu;
				Union( neu , i->first );
				Union( neu , j->first );
				
				int cnt = Count(neu);
				
				#ifdef DEBUG
				// Print FirstSet + SecondSet = UnionOfThem -> Count
				PrintSet(i->first); cout<<" + "; PrintSet(j->first); cout<<" = "; PrintSet(neu); cout<<" -> "; cout<<cnt<<"\n";
				#endif
				
				if ( cnt >= MinSupport )
				{
					Help[neu] = cnt;
				}
			}
		}
		Table.clear();
		
		// Copy from Help -> Paste in Table , Answer
		for ( map< set<string> , int >::iterator i = Help.begin() ; i != Help.end() ; i++ )
		{
			Table[i->first] = i->second;
			Answer[i->first] = i->second;
		}
		
		Help.clear();
		
		#ifdef DEBUG
		cout<<"\n--------------------------------------------------------------------------------------\n";
		#endif
	}
	
	
	cout<<"Answer : \n";
	for ( map< set<string> , int >::iterator i = Answer.begin() ; i != Answer.end() ; i++  )
	{
		PrintSet( i->first );
		cout<<" -> ";
		cout<<i->second<<"\n";
	}
	
	return 0;
}
