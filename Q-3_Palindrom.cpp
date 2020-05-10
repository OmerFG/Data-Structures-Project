#include<iostream>
#include<stdlib.h>
#include <fstream>
using namespace std;
class list
{
public:
    list *next;
    list *prev;
    char x;
};    //objemiz tan�mland�.
typedef list node;
node *front=NULL;
node *back=NULL;
node *iter=NULL; //gerekli liste elemanlar� olu�turuldu.
node *add(node *root,char y){
	if(root==NULL){ //liste bo� ise
		root=(node*)malloc(sizeof(node)); //belletke yer a��ld�.
		root->x=y;
		root->next=NULL;
		root->prev=NULL;
		back=root; //atamalar yap�ld�. liste queue mant���yla �al��aca��ndan ilk eleman hem back hem front oldu.
		return root;
	}
	iter=root; //Liste bo� de�ilse.
	while(iter->next!=NULL) //listenin son eleman�na kadar gidildi.
	iter=iter->next; 
	iter->next=(node*)malloc(sizeof(node)); //son elemandan sonra yeni yer a��ld�.
	iter->next->x=y; 
	iter->next->prev=iter;
	iter->next->next=NULL;
	back=iter->next; //yeni eklenen eleman listenin sonu olur.
	return root;
}
void print(){
	iter=front;
   while(iter!=NULL){
   	cout<<iter->x;
   	iter=iter->next;
	}
 // iter son elemana gelene dek yazma i�lemi yapar.
cout<<endl;
}
void organize(){
	cout<<front->x<<" is deleted";
	front->x=back->x;
	cout<<" and "<<front->x<<" is placed, new situation: ";
	print();
}
void control(){
while(front!=back){ //ilk ve son eleman birbirine e�it de�ilse yani listede tek bir eleman kalmad�ysa.
if(front->x==back->x ){ //front ve back de�erleri ayn�ysa
	iter=front;
	front=front->next;
    cout<<iter->x<<"'s are deleted, new situtation: ";
	free(iter);
	front->prev=NULL;
	if(front->next==NULL){//e�er front ileriye al�nd���nda backe e�it olduysa direk burada silme i�lemini ger�ekle�tir ve d�ng�den ��k. yani listede son iki eleman kald�ysa.
		free(back);
		goto resume;
	} 
	iter=back;
	back=back->prev;
    free(iter); //ayn� �ekilde back bir ileriye al�n�r ve eski back silinir.
    back->next=NULL; 
    print(); //her silme i�leminde ekrana yazd�rma fonksiyonu �a�r�l�r kullan�c� bilgilendirilir.
}
else if(front->x!=back->x){ //e�er e�itlik durumu yoksa d�zenleme fonku �a�r�l�r.
cout<<"This situation is not panlinormic, so it will fix."<<endl;
	organize();
}
}
   resume:
   cout<<endl<<"Finally, this situation is palindromic"<<endl;
}
int main(){
	char y;
     ifstream readFile("Deneme.txt"); //dosya kontrol� sa�lan�r.
   if(readFile.is_open()){ //e�er dosya mevcut ve a��labiliyorsa
    while (readFile>>y){ //dosyada karakter karakter ald���m�z de�erleri y ye e�itliyoruz.
   front=add(front,y); //listeye ekleme i�lemi yap�l�yor
   }
    readFile.close(); //i�lemler bitti�inde dosya kapat�l�r.
  }
  else{
  	cout<<"File does not exist"<<endl; //dosya mevcut de�ilse.
  }
  print(); //olu�an durum ekrana yaz�l�r.
   control(); //listenin palinormic olup olmad��� kontrol ediliyor.
}
