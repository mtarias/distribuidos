

struct data{
    int nDict;
    string text<200>;
    int sizeT;
};

 
program DICCIONARIO {
  version DICCIONARIO_VERSION {
    int init(int)=1;
    int addword(data)=2;
    int verify(data)=3;
    string suggestword(data)=4;
    string readtext(data)=5;
    string show(data) =6;
  } = 1;
} = 0x123456AB;
