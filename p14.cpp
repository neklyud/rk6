#include <stdio.h>
#include <math.h>
#define LEFT 1
#define RIGHT 0
// класс точки плоскости  
class Point2 {
  private:
    int x;
    int y;
    int side;
public:
    Point2(int _x, int _y,int _side) : x(_x), y(_y), side(_side) { };  // конструктор точки
    int getx() { return x; }; // доступ к x
    int gety() { return y; }; // доступ к y
    int getside() { return side; };//доступ к стороне отн оу
	friend double distance(Point2*, Point2*); // расстояние между 2-мя точками
 };//Point2 
// дружественная функция вычисления расстояния между двумя точками 
double distance(Point2* r, Point2* q) {
   double d2=(r->x-q->x)*(r->x-q->x)+(r->y-q->y)*(r->y-q->y); 
   return (sqrt(d2));
  }  // distance 
int main(int argc,char *argv[])
	{
	Point2** p; // адрес массива адресов точек набора
	Point2* t;   // адрес текущей точки
	Point2* p1, *p2;
	int x,y,state;
	float max,k;         //    координаты точки
	int i=0;
	int j=0; // номера точек набора 
	if(argc < 2) //анализ числа аргументов командной строки
 		 return(-1); 
	
	p = new Point2*[argc]; // распределить память под массив адресов точек
	while(++i < argc) 
	{ //цикл ввода точек из командной строки 
		sscanf(argv[i], "(%d%*c%d)", &x, &y); // получение координат точки
		if (x<0)
		p[j]=new Point2(x,y,LEFT); // динамическое конструирование точки
		else 
		p[j]=new Point2(x,y,RIGHT); // динамическое конструирование точки			
		j ++;                                                                                                         
	} // while
	p[j]=NULL; // маркировка конца массива адресов точек набора
	state=p[0]->getside();
	max=0;
	printf("(%d,%d,%d)\n",p[0]->getside(),p[0]->getx(),p[0]->gety());
	for (i=0;p[i]!=NULL;i++)
		{
		if (p[i]->getside()!=state)
			continue;
		for(j=0;p[j]!=NULL;j++)
			{
			if ((p[j]->getside()!=state)&&(max<(k=distance(p[i],p[j]))))	
				{
				p1=p[i];
				p2=p[j];
				max=k;
				}		
			}
		}
	printf("points p1(%d;%d) and p2(%d;%d) max=%f\n",p1->getx(),p1->gety(),p2->getx(),p2->gety(),max);
	for(j=0; p[ j ] != NULL; j++)  
	 delete p[ j ];  
 	delete [  ]p;   //  освобождить дин. память массива адресов точек 
 	return 0; //корректное завершение программы
	}
