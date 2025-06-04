#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <set>


using namespace std;

// MAP - BST cu indexare
// SET - BST
// MULTISET - BST, permite duplicate
// PRIORITY_QUEUE - heap (max sau min)
// UNORDERED_MAP - hash map

// FOLOSESTE greater<> PENTRU PRIORITY_QUEUE SI SET PENTRU A AVEA SORTARE DESCRESCATOARE
// CA sa separi cuvintele dintr-un text foloseste sstream, stringstream

// 1. REGATUL NUMERELOR 
// PRIORITY_QUEUE

// int main ()
// {
//     priority_queue<int, vector<int>, greater<int>> pq;
//     int comori;
//     cin >> comori;

//     int limitaK;
//     cin >> limitaK;

//     for (int i = 1; i <= comori; i++) {
//         int valoare;
//         cin >> valoare;

//         if (i > limitaK){
//             if (valoare > pq.top())
//             {
//                 pq.pop();
//                 pq.push(valoare);
//             }
//         }
//         else {
//             pq.push(valoare);
//         }
//     }
//     // heap with the K largest values
//     vector<int> kLargest;
//     while (!pq.empty())
//     {
//         kLargest.push_back(pq.top());
//         pq.pop();
//     }

//     for (int i = kLargest.size() - 1; i >= 0; i--) {
//         fout << kLargest[i] << " ";
//     }

//     return 0;
// }



// 2. TARAMUL CODRILOR VRAJITIT
// BST


vector<string> getWords(string& text)
{
    vector<string> words;
    
    stringstream ss(text);

    string word;

    while(ss >> word)
    {
        words.push_back(word);
    }

    return words;
}

int main ()
{
    ofstream fout("output.txt");

    set<int> gradina;
    // set<int, greater<>> gradina;
    int copaci;
    cin >> copaci;

    string aux;
    getline(cin, aux); // get endl

    for (int i = 1;i <= copaci; i++)
    {
        string text;
        getline(cin, text);

        vector<string> words = getWords(text);

        string instructiune = words[0];

        if (instructiune == "Adauga")
        {
            string insusire = words[1];
            gradina.insert(stoi(insusire));
        }
        else if (instructiune == "Cauta")
        {
            string insusire = words[1];
            if (gradina.find(stoi(insusire)) != gradina.end())
            {
                fout << "DA" << endl;
            }
            else
            {
                fout << "NU" << endl;
            }
        }
        else if (instructiune == "Arata")
        {
            for (auto& g : gradina)
            {
                fout << g << " "; 
            }
            fout << endl;
        }

    }


    return 0;
}




// 3 ARHIVA SECRETA A REGATULUI STRUCTURIA 
// ?? HASHMAPS

// vector<string> getWords(string& text)
// {
//     vector<string> words;
//     stringstream ss(text);

//     string word;

//     while (ss >> word)
//     {
//         words.push_back(word);
//     }

//     return words;
// }

// int main()
// {
//     ofstream fout("output.txt");

//     unordered_map<string, string> arhiva; // titlu, categorie
//     unordered_map<string, int> cantitati; // titlu, cantitate

//     int comenzi;
//     cin >> comenzi;

//     string aux;
//     getline(cin, aux); // get endl

//     for (int i = 1; i <= comenzi; i++)
//     {
//         string text;
//         getline(cin, text);
//         vector<string> words = getWords(text);

//         string instructiune = words[0];

//         if (instructiune == "ADD")
//         {
//             string titlu = words[1], categorie = words[2], cantitate = words[3];
//             int cantitateInt = stoi(cantitate);

//             if (arhiva.find(titlu) == arhiva.end())
//             {
//                 // daca nu exista titlul 
//                 arhiva.insert({titlu, categorie});
//                 cantitati.insert({titlu, cantitateInt});
//             }
//             else
//             {
//                 if (arhiva[titlu] == categorie)
//                 {
//                     // daca exista titlul si categoria este aceeasi
//                     cantitati[titlu] += cantitateInt;
//                 }
//                 else
//                 {
//                     fout << "INVALID" << endl;
//                 }
//             }
//         }
//         else if (instructiune == "REMOVE")
//         {
//             string titlu = words[1], cantitate = words[2];
//             int cantitateInt = stoi(cantitate);

//             cantitati[titlu] -= cantitateInt;
//             if (cantitati[titlu] <= 0)
//             {
//                 // daca cantitatea devine 0 sau mai mica, se sterge
//                 cantitati.erase(titlu);
//                 arhiva.erase(titlu);
//             }
//         }
//         else if (instructiune == "CHECK")
//         {
//             string titlu = words[1];

//             if (arhiva.find(titlu) != arhiva.end())
//             {
//                 fout << arhiva[titlu] << endl;
//             }
//             else
//             {
//                 fout << "NU" << endl;
//             }
//         }
//         else if (instructiune == "COUNT")
//         {
//             string categorie = words[1];

//             int count = 0;

//             for (auto& a : arhiva)
//             {
//                 if (a.second == categorie)
//                 {
//                     count += cantitati[a.first];
//                 }
//             }

//             fout << count << endl;
//         }
//     }

//     return 0;
// }