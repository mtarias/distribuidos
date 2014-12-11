#include<fstream>
#include<iostream>
#include <string.h>
#include <sstream>
#include "diccionario.h"
using namespace std;

int main(int argc, char** argv) {

  if(argc != 2) {
    cerr << "Uso: " << argv[0] << " server_address" << endl;
    return 1;
  }

  char *serverAddress = argv[1];

  CLIENT *client = clnt_create(serverAddress, DICCIONARIO, DICCIONARIO_VERSION, "tcp");
  if(client == NULL) {
    cerr << "ERROR creando el cliente." << endl;
    clnt_pcreateerror(serverAddress);
    return 1;
  }
  
  data ins;
  int na = 0;
  int *load= init_1(&na,client);
  if(load==NULL){
    cout << "No se cargaron los diccionarios apropiadamente" << endl;
  }
  bool c = TRUE;
  
  while (c){
    cout << "Bienvenido al DICCIONARIO de Marco Arias\nAnote lo que desea hacer\n" << endl;
    int op = 0;
    cout << "1.- Verificar palabra" << endl;
    cout << "2.- Agregar palabra" << endl;
    cout << "3.- Sugerir palabra" << endl;
    cout << "4.- Agregar palabras por Archivo" << endl;
    cout << "5.- Mostrar todas las palabras de un diccionario" << endl;
    cout << "6.- Salir" << endl;
    cin >> op;
    string input;
    int nDict = 0;
    
    if(op==1){
	cout << "Ingrese una palabra que desea verificar" << endl;
	cin >> input;
	cout << "Ingrese el diccionario que desea verificar" << endl;
	cin >> nDict;
	char* cstr = new char[input.length() + 1];
        strcpy(cstr, input.c_str());
	ins.text = cstr;
	ins.nDict = nDict;
	ins.sizeT = sizeof(input);
	int* i = NULL;
	i = verify_1(&ins, client);
	if(i!=NULL){
	  if(*i==1){
	    cout << "\nLa palabra SI esta en el diccionario\n" << endl;
	    op = 0;
	  }
	  else{
	    cout << "\nLa palabra NO esta en el diccionario\n" << endl;
	  }
	}
	else{
	  cout << "\nHubo un problema al verificar la palabra\n" << endl;
	  clnt_perror(client, serverAddress);
	}
    }
    else if(op==2){
        cout << "Ingrese la palabra que desea agregar al diccionario" << endl;
        cin >> input;
	cout << "Ingrese el diccionario" << endl;
	cin >> nDict;
	char* cstr = new char[input.length() + 1];
        strcpy(cstr, input.c_str());
	ins.text = cstr;
	ins.nDict = nDict;
	ins.sizeT = sizeof(input);
	int *i = NULL;
	i = addword_1(&ins, client);
	if(i!=NULL){
	  if(*i==1){
	    cout << "\nLa palabra se agrego al diccionario\n" << endl;
	  }
	}
	else{
	  cout << "\nHubo un problema al agregar la palabra\n" << endl;
	  clnt_perror(client, serverAddress);
	}
    }
    else if (op==3){
	cout << "Ingrese una palabra que desea sugerir" << endl;
	cin >> input;
	char* cstr = new char[input.length() + 1];
        strcpy(cstr, input.c_str());
	ins.text = cstr;
	char** res = suggestword_1(&ins,client);
	
	if(res!=NULL){
	    cout << "\nLa palabra sugerida es " << *res << "\n" << endl;
	    res = NULL;
	}
	else{
	  cout << "\nHubo un problema al buscar sugerencias\n" << endl;
	  clnt_perror(client, serverAddress);
	}
    }
    else if(op==4){
      string fName;
      char* data;
      ifstream *myfile;
      char fileText[5000];
      
      cout << "Ingrese el nombre del archivo con las palabras (con el .txt)" << endl;
      cin >> fName;
      cout << "Ingrese el diccionario que quiere revisar" << endl;
      cin >> nDict;
      char* cstr = new char[fName.length() + 1];
      strcpy(cstr, fName.c_str());
      
      int i = 0;
       
      myfile = new ifstream(cstr);
      if (myfile->is_open()){
	myfile->read(fileText, 5000);
	myfile->close();
      }
 
      ins.text = fileText;
      ins.nDict = nDict;
      
      char** res = readtext_1(&ins,client);
      
      for(int i=0;i<5000;i++){
	fileText[i] = '\0';
      }
      
      if(res!=NULL){
	data = strtok (*res, " ");
        cout << "\nPalabras detectadas: " << data << endl;
        data = strtok (NULL, " ");
        cout << "Nuevas palabras agregadas al diccionario: "<< data << endl;
        data = strtok (NULL, " ");
        cout << "Palabras ya existentes: " << data << "\n" << endl;
      }
      else{
	cout << "\nHubo un problema al analizar el archivo\n" << endl;
	clnt_perror(client, serverAddress);
      }
      
    }
    else if(op==5){
      cout << "Elija un diccionario" << endl;
      cin >> nDict;
      string s("Hola");
      char* cstr = new char[s.length() + 1];
      strcpy(cstr, s.c_str());
      ins.text = cstr;
      ins.nDict = nDict;
      char** res = show_1(&ins, client); 
      string buf;
      string str(*res);
      if(res!=NULL){
	stringstream ss(str);
        while (ss >> buf){
	  cout << buf << endl;
	}
	cout << endl;
      }
      else{
	cout << "Hubo un problema al ver las palabras"<<endl;
      }
      
    }
    else if(op==6){
      c=FALSE;
      cout << "\nEsta abandonando el diccionario" << endl;
      cout << "ADIOS =)" <<endl;
    }
    else{
      cout << "\nDigite una opción válida\n" << endl;
    }
  }
  return 0;
}
