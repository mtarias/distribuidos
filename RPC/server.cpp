#include <iostream>
#include <string>
#include<fstream>
#include<iostream>
#include <cstring>
#include <map>
#include <sstream>
#include "diccionario.h"

#define MAXDICTIONARY 10
#define MAXWORDS 50

using namespace std;

multimap<int,string> dictionary;

int* init_1_svc(int *n,struct svc_req* request){
  static int result = 1;
  char fileText[5000];
  int i = 0;
  stringstream names;
  names << "Dict_" << i ;
  i++;
  string name = names.str();
  char* cstr = new char[name.length() + 1];
  strcpy(cstr, name.c_str());
  
  ifstream file (cstr);
  
  while(file){
    if (file.is_open()){
      data ins;
      string s;
      while(file >> s){
	char* word = new char[s.length() + 1];
        strcpy(word, s.c_str());
	ins.text = word;
	ins.nDict = i-1;
	addword_1_svc(&ins,request);
      }
      file.close();
    }
    
    names.str("");
    names << "Dict_" << i ;
    name = names.str();
    cstr = new char[name.length() + 1];
    strcpy(cstr, name.c_str());
    file.open(cstr);
    i++;
  }
  
  return &result;
}

int* addword_1_svc(data *ins,struct svc_req* request){
  static int result = 1;
  string word = ins->text;
  int nDict = ins->nDict;
  dictionary.insert(make_pair(nDict,word));
  return &result;
}

int* verify_1_svc(data *ins, struct svc_req* request){
  static int result;
  result = 0;
  string word = ins->text;
  int nDict = ins->nDict;
  pair<multimap<int,string>::iterator,multimap<int,string>::iterator> keyRange = dictionary.equal_range(nDict);
  multimap<int,string>::iterator it;
  for (it = keyRange.first; it != keyRange.second; ++it){
    string s = (*it).second;
    if(word.compare(s)==0){
      result = 1;
    }
  }
  return &result;
}

char** suggestword_1_svc(data *ins, struct svc_req* request){
  static char* res;
  // Buscamos si la palabra esta en el diccionario
  string word = ins->text;
  char first = word[0];
  multimap<int,string>::iterator it;
  
  for (it = dictionary.begin(); it != dictionary.end();  ++it){
    char b = ((*it).second)[0];
    if(word.compare((*it).second)==0){
      cout << "Son iguales"<< endl;
      char *cstr = new char[word.length() + 1];
      strcpy(cstr,word.c_str());
      res = const_cast<char*>(cstr);
      return &res;
    }
    else if(first==b){
      string suggest = (*it).second;
      cout << "Palabra sugerida es " << suggest << endl;
      char *cstr = new char[suggest.length() + 1];
      strcpy(cstr,suggest.c_str());
      res = const_cast<char*>(cstr);
      return &res;
    }
  }
  return &res;
}

char** show_1_svc(data *ins, struct svc_req* request){
  static char* res;
  int nDict = ins->nDict;
  pair<multimap<int,string>::iterator,multimap<int,string>::iterator> keyRange = dictionary.equal_range(nDict);
  multimap<int,string>::iterator it;
  stringstream ss;
  for (it = keyRange.first; it != keyRange.second; ++it){
    string s = (*it).second;
    char* cstr = new char[s.length() + 1];
    strcpy(cstr, s.c_str());
    ss << cstr << " ";
  }
  string r = ss.str();
  res = new char[r.length() + 1];
  strcpy(res, r.c_str());
  
  return &res;
}

char** readtext_1_svc(data *text, struct svc_req* request){
  static char* stats;
  int n = text->nDict;
  cout << text->text << endl;
  stringstream ss(text->text);
  string word;
  data ins;
  ins.nDict=n;
  
  //Enteros de estadisticas
  int dectwords = 0;
  int newwords = 0;
  int totalwords = 0;

  while (ss >> word){
    totalwords++;
    char* cstr = new char[word.length() + 1];
    strcpy(cstr, word.c_str());
    ins.text = cstr;
    
    int *res;
    res = verify_1_svc(&ins,request);
    if(*res==1){
      dectwords++;
    }
    else{
      addword_1_svc(&ins,request);
      newwords++;
    }
  }
  stringstream ss2;
  ss2 << totalwords << " " << newwords << " " << dectwords;
  string st = ss2.str();
  char* cstr = new char[st.length() + 1];
  strcpy(cstr, st.c_str());
  
  stats = const_cast<char*>(cstr);
  
  cout << "Palabras detectadas: " << totalwords << endl;
  cout << "Nuevas palabras agregadas al diccionario: "<< newwords << endl;
  cout << "Palabras ya exixtentes: " << dectwords << endl;
  
  return &stats;
}