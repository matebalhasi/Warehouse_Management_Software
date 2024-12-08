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
	
	void beolvas() {
		std::ifstream input("complaints.txt");
		string s;
		if (input.is_open() == false) {
			cout << "Nem sikerult megnyitni az allomanyt" << endl;
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
		cout << "beolvasas meg van" << endl;
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
		 cout << "Mi a panasza?" << endl;
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


