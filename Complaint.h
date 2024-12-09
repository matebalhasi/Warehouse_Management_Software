#include <iostream>
#include <fstream>
#include <list>
#include <string>
//text formátuma: "*1.complaint"
using namespace std;
class Complaint
{
public:
	list<string>lista;
	list<string>::iterator it;
	int sorszam = 0;
	/*
	bool operator<(const Complaint& c) const {
		if (it<c.it)
			return false;
		if (it <c.it)
			return true;
		return it< c.it;
	}
	
	friend std::ostream& operator<<(std::ostream& s, const list<string>lista) {
		for (auto it=lista.begin(); it < lista.end(); it++)
		{
			s << lista.it;
		}
		return s;
	}
	*/

	void beolvas() {
		std::ifstream input("complaints.txt");
		string s;
		if (input.is_open() == false) {
			cout << "Could not open file" << endl;
			exit(1);
		}
		
			
	while (!input.eof())
	{
		getline(input, s);
		if (s[0]=='*')
		{
			lista.push_back(s);
			sorszam++;
		}
		
		
	 	
	}
			
				
		
		input.close();
		cout << "reading is complete " << endl;
	}
	 void kiir() {
		 for (auto v : lista)
			 std::cout << v << "\n";
	 }
	 void add()
	 {
		 string mycomplaint, be;
		 mycomplaint = '*';
		 mycomplaint += to_string(++sorszam);
		 mycomplaint += '.';
		 cout << "What seems to be the issue?" << endl;
		 getline(cin, be);
		 be += '\n';
		 mycomplaint += be;
		 lista.push_back(mycomplaint);
		 ofstream of("complaints.txt");
		 for (auto v : lista)
			 of << v<< "\n";
		 of.close();
	 }
		
	
};


