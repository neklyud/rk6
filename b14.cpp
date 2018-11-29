#include <ctype.h>
#include <iostream>
#include <stdio.h>
using namespace std;
class Alpha{//класс множества латинских букв
private:
	unsigned bin; //бинарный код подмножества латинских букв
public:
	Alpha() {bin=0;};
	Alpha(Alpha& y) {bin=y.bin;};
	Alpha(char*);
	Alpha operator +(Alpha&);
	Alpha operator -(Alpha&);	
	operator char*();
	friend ostream& operator << (ostream&,Alpha&);
};// Alpha 
//конструктор множества букв по строке
Alpha::Alpha(char* s){ 
	bin=0;
	while(*s){
		bin|= (1 << (tolower(*s)-'a')); s++;}
}//Alpha
Alpha Alpha::operator-(Alpha& y)
	{
	Alpha z;
	z.bin=bin^y.bin;
	return z;
	}
//оператор объединения подмножеств букв
Alpha Alpha:: operator+(Alpha& y){ 
	Alpha z;
	z.bin=bin | y.bin;
	return(z);}//operator+
//оператор вывода подмножеств букв
ostream& operator << (ostream& out,Alpha& z){ 
	unsigned  bit=33554432;
	int i;
	for(i=0; i<26;i++){
		if((z.bin& bit)>0)
			out<<(char)('z'-i);
		bit=bit>>1;
	}
	return out;}// operator <<
//оператор преобразования множества в строку
Alpha::operator char*(){ 
	static  char s[32];
	unsigned  b=bin;
	int i=0;
	int j=0;
	int w;
	while(w>0){
	if(w & 1)
	s[j++]='a'+i;
	i++;
	w>>1;
	}//while
	s[j]='\0';
	return (s);
}//operator char*()
//основная функция
int main (int argc,char* argv[]){ 
	if(argc<3)
		{
		printf("Usage - need two arguments\n");
		return 0;
		}
	Alpha x(argv[1]); //буквы 1-го аргумента
	Alpha y(argv[2]); //буквы 2-го аргумента
	Alpha z,a,b; //буквы результата
	a=x-y;
	b=y-x;
	z=a+b; // объединение подмножеств букв
	cout<<z<<"\n"; // или cout<<(char*)z;
	return (0);
}//main
