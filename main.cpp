#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool mysorterfunction(const pair< size_t, size_t > &p1, const pair <size_t, size_t > &p2)
{
	return (p1.second > p2.second);
}

int main(int argc, char const *argv[])
{
    stringstream manuscriptStr;

	ifstream frManusc("manuscrito.txt");

	if(!frManusc.is_open())
    {
        cout << "Error, manuscript file not found" << endl;

        return 1;
    }

	char ch;

	while(frManusc.get(ch))
	{
		manuscriptStr << ch;
	}

	//frequencia de caracteres do manuscrito

    vector < pair< size_t, size_t > > frequencyList;
    vector < pair< size_t, size_t > > frequency2;

    for(size_t i=0; i<256; i++)
    {
        pair< size_t, size_t > p;
        p.first = i;
        p.second = 0;        
        frequencyList.push_back(p);
        frequency2.push_back(p);
    }
    for(size_t i=0; i<manuscriptStr.str().size(); i++)
    {
        char ch = manuscriptStr.str().at(i);
        frequencyList.at(ch).second++;      
        frequency2.at(ch).second++; 
    }

    //sort c++ by element excluding elements with 0 appearences
	stable_sort(frequencyList.begin(), frequencyList.end(), mysorterfunction);
	stable_sort(frequency2.begin(), frequency2.end(), mysorterfunction);
    
    for (size_t i = 0; i < frequencyList.size(); ++i)
    {
    	if (frequencyList.at(i).second == 0)
    	{
    		frequencyList.erase(frequencyList.begin()+i, frequencyList.end());
    		frequency2.erase(frequency2.begin()+i, frequency2.end());
    	}
    }

	int choice = 0;
	int alteration = 0; //resposta certa = -33
	bool trocou=false;

	while(choice != 7)
	{	
		cout << "What do you want to do?" << endl;
		cout << "1. Choose value of manipulation (from -50 to 50)" << endl;
		cout << "2. Show current manuscript" << endl;
		cout << "3. Show list of characters" << endl;
		cout << "4. Save progress in .txt file" << endl;
		cout << "5. Show current characters an their frequency" << endl;
		cout << "6. Convert specific character (does not involve the 16 more frequent characters neither the already changed)" << endl;
		cout << "7. Exit" << endl;
		cout << "Option: ";

		cin >> choice;

		if (choice == 1)
		{
			cout << "Enter a number from -50 to 50 to guess the manipulation value: ";
			cin >> alteration;
			trocou=true;
			if (alteration < -50 or alteration > 50)
			{
				cout << "Invalid value!" << endl;

				return 2;
			}
			frequency2.at(0).first=65+alteration;
		    frequency2.at(1).first=130+alteration;
		    frequency2.at(2).first=134+alteration;
		    frequency2.at(3).first=144+alteration;
		    frequency2.at(4).first=138+alteration;
		    frequency2.at(5).first=148+alteration;
		    frequency2.at(6).first=147+alteration;
		    frequency2.at(7).first=143+alteration;
		    frequency2.at(8).first=149+alteration;
		    frequency2.at(9).first=142+alteration;
		    frequency2.at(10).first=133+alteration;
		    frequency2.at(11).first=132+alteration;
		    frequency2.at(12).first=141+alteration;
		    frequency2.at(13).first=150+alteration;
		    frequency2.at(14).first=136+alteration;
		    frequency2.at(15).first=145+alteration;
		}

		else if (choice == 2)
		{
		    for(size_t i = 0; i < manuscriptStr.str().size(); i++)
		    {
		        char ch = manuscriptStr.str().at(i);

		        for(size_t j = 0; j < frequencyList.size(); j++)
		        {
		            if(ch == frequencyList.at(j).first)
		            {
		                cout << (char) frequency2.at(j).first;
		            }
		        }        
		    }
		    cout << endl;
		}

		else if (choice == 3)
		{
			cout << "Current changes:" << endl;
		    for(size_t i=0; i<frequencyList.size(); i++)
		    {
		        cout << (char) frequencyList.at(i).first << " -> " << (char) frequency2.at(i).first << endl;
		    }
		}

		else if (choice == 4)
		{
			ofstream solved("progress.txt");

			solved << "Manuscript:" << endl;
		    for(size_t i = 0; i < manuscriptStr.str().size(); i++)
		    {
		        char ch = manuscriptStr.str().at(i);

		        for(size_t j = 0; j < frequencyList.size(); j++)
		        {
		            if(ch == frequencyList.at(j).first)
		            {
		                solved << (char) frequency2.at(j).first;
		            }
		        }        
	    	}

	    	if (trocou==true)
	    	{
	    		solved << endl << endl << "Alteration guess: " << alteration << endl;
	    	}
			else
			{
				solved << endl << endl << "No alteration guess made." << endl;
			}

			solved << "Characters changed:" << endl;

			for(size_t i=0; i<frequencyList.size(); i++)
		    {
		        solved << "Changed " << (char) frequencyList.at(i).first << " to " << (char) frequency2.at(i).first << endl;
		    }

    		cout << "Solved text saved as progress.txt." << endl;
		}

		else if (choice == 5)
		{
		    for(size_t i=0; i<frequencyList.size(); i++)
		    {
		        cout << (char) frequency2.at(i).first << " -> " << frequency2.at(i).second << endl;
		    }
		}

		else if (choice == 6)
		{
			char original;
			bool existe=false;

			cout << "Enter a character to change: ";
			cin >> original;

			for (int i = 16; i < frequencyList.size(); i++)
			{
				if (original == frequencyList.at(i).first)
				{
					existe=true;
					char conversion;
					cout << "Enter what to change to: ";
					cin >> conversion;

					frequency2.at(i).first = conversion;
				}
			}
			if (existe == false)
			{
				cout << "Character not found." << endl;
			}
		}

		else if (choice != 7)
		{
			cout << "Invalid choice." << endl;
			return 3;
		}

	}

	return 0;
}
