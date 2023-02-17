#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades ){
    ifstream source(filename.c_str());
    string textline ;
    while(getline(source, textline)){
        char format[] = "%[^:]: %d %d %d" ;
        char name_eq[100] ;
        int a,b,c ;
        sscanf(textline.c_str(), format, name_eq, &a, &b, &c);
        int score_eq = a+b+c ;
        char grade_eq = score2grade(score_eq) ;
        names.push_back(name_eq) ;
        scores.push_back(score_eq) ;
        grades.push_back(grade_eq) ;

    }
}

void getCommand(string &command, string &key){
string input ;
char c[1000] ;
char k[1000] ;
cout << "Please input your command: " ;
getline(cin, input);
char format[] = "%s %[^\n]";
sscanf(input.c_str(), format,c ,k );
command = c;
key = k ;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool notfound = true ;
    cout << "---------------------------------\n" ;
    for(unsigned int i = 0; i < names.size(); i++){
        if(key.compare(toUpperStr(names[i]))== 0) {
            notfound = false ;
            cout << names[i] << "'s" << " " << "score = " << scores[i] << endl;
            cout << names[i] << "'s" << " " << "grade = " << grades[i] << endl;
        }
    }
    if(notfound) cout << "Cannot found.\n";
    cout << "---------------------------------\n" ;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool notfound = true ;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(key[0] == grades[i]){
            notfound = false ;
            cout << names[i] << " " << "(" << scores[i] << ")" << endl ;
        }
    }
    if(notfound) cout << "Cannot found.\n";
    cout << "---------------------------------\n" ;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
