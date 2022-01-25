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

void importDataFromFile(string name_score,vector<string> &name,vector<int> &score,vector<char> &grade){
    ifstream Mem;
    Mem.open(name_score);
    string textl;
    while(getline(Mem,textl)){
        int a = textl.find(':');
        string w;   
        w = (textl.substr(0,a));
        name.push_back(w);

        textl = textl.erase(0,a+2);
        int x,y,z,sum=0;
        char *chartext = const_cast<char*>(textl.c_str()); 
        sscanf(chartext,"%d %d %d",&x,&y,&z);
        sum = x+y+z;
        score.push_back(sum);
    
        char grades = score2grade(sum);
        grade.push_back(grades);   
    }
    Mem.close();
}

void getCommand(string &command,string &key){
    string Search;
    cout << "Please input your command: ";
    getline(cin,Search);
    int a = Search.find(' ') , b = Search.size();
    command = (Search.substr(0,a));
    key = (Search.substr(a+1,b));
}

void searchName(vector<string> name,vector<int> score,vector<char> grade,string key){
    int j=name.size(),count =0;
    cout<<"---------------------------------\n";
    for(int i=0;i<j;i++){
        if(key == toUpperStr(name[i])){
            cout<<name[i]<<"'s score = "<<score[i]<<endl;
            cout<<name[i]<<"'s grade = "<<grade[i]<<endl;
            count++;
        }
    }
    if(count == 0){
        cout<<"Cannot found.\n";
    }
    cout<<"---------------------------------\n";
}

void searchGrade(vector<string> name,vector<int> score,vector<char> grade,string key){
    int j=name.size(),count=0;
    cout<<"---------------------------------\n";
    for(int i=0;i<j;i++){
        if(key[0] == grade[i]){
            cout<<name[i]<<" (" <<score[i]<<')'<<endl;
            count++;
        }
    }
    if(count == 0){
        cout<<"Cannot found.\n";
    }
    cout<<"---------------------------------\n";
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