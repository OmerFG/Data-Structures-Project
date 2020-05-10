#include<iostream>
#include<stdlib.h>
using namespace std;
class node
{
public:
    node* next;
    char x;
};
node *root=NULL;
node *iter=NULL; //linked list ve onun gerekli elemanlar�n� tan�mlad�k classlarla tan�mlad�k.
class Node
{
public:
    Node* next;
    char y;
}; //kuyruk yap�s� i�in class tan�mlad�k.
typedef Node queue;
queue *front=NULL;
queue *back=NULL;
queue *temp=NULL; //queue ve onun i�in gerekli elemanlar� tan�mlad�k.
void add(){
	string aorb;
	int i=0;
	cout<<"Enter string which includes a or b. You can exit with entering different value."<<endl;
	cin>>aorb; //kullan�Ac�dan a ya da b giri�i yapaca�� de�i�keni tan�mlad�k ve ald�k.
	int count_ab=0; 
	while(aorb[i]=='a' || aorb[i]=='b'){ //eleman a veya b ise devam et.
	if(aorb[i]=='a'){
		if(front==NULL){ //kuyru�umuz bo� ise ilk eleman� buraya ekle.
				front=(queue*)malloc(sizeof(queue));  //alan a�
				front->y=aorb[i];      //a��lan alana aorb yi ekle
				front->next=NULL;   //sonraki eleman null e�itlemesi yapt�k.
				back=front;    //ilk eleman oldu�undan �n ve arkas� ayn� yer oldu.
		}
		else if(front !=NULL){   //ilk eleman�m�z var ise
				back->next=(queue*)malloc(sizeof(queue));    //kuyru�un gerisine yer a�
				back->next->y=aorb[i];        //elemana e�itle
				back=back->next;   //yeni eleman�m�z kuyru�un arkas� olur (fifo)
				back->next=NULL;   //arkay� NULL a e�itledik.
	}
	}
		else if(aorb[i]=='b'){  //e�er eleman�m�z kuyruktakilere e�it de�ilse.
         	if(root==NULL){  //listemizde eleman yok ise
				root=(node*)malloc(sizeof(node));  //listede ilk eleman� yani k�k� olu�turuyoruz.
				root->x=aorb[i];   //kok girilen elemana e�it oluyor.
				root->next=NULL;  //kok�n nexti null oldu.
			}
			else if(root!=NULL){  //Listemizin k�k� var ise
				iter=root;  //hareket ettirece�imiz eleman� k�ke e�itliyoruz.
				while(iter->next!=NULL){ //iterimiz son elemana ula�ana dek hareket ediyoruz.
				iter=iter->next; }
				 iter->next=(node*)malloc(sizeof(node));  //son elemandan sonras�na yeni node a��yoruz.
				 iter->next->x=aorb[i];   //a��lan node girilen elemana e�it oldu.
				 iter->next->next=NULL;		  //yeni eleman�n sonu null oldu.	
			}
		}i++;
		}
}
void show(){
	   iter=root; 
		temp=front;
			while(iter!=NULL){
			cout<<iter->x;
			iter=iter->next;
		}
			while(temp!=NULL){
			cout<<temp->y;
			temp=temp->next;
		}
		cout<<endl; 
}
void deleting(int a_coefficent,	int b_coefficent){
	cout<<"First regular situation: ";
	show();
	 bool control=true; //her bir a silinmesinde katsay� kadar b eleman silindi�ini kontrol edece�imiz de�i�ken
      int counta;
      int countb;
   while(front!=NULL && root!=NULL){  //iki listenin herhangi biri bo�alana kadar devam edece�iz.
    temp=front;
    iter=root;
    counta=0;
    countb=0;
	while(temp!=NULL){
    temp=temp->next;
    counta++;
	}
    while(iter!=NULL){
    iter=iter->next;
    countb++;
	}  //listede kalan elemanlar� hesaplad�k.
    iter=root;
    temp=front;
    if(counta>=a_coefficent && countb>=b_coefficent){  	 //listemizde girilen katsay�lardan daha az eleman var ise silme i�lemi yapamay�z.
   	   if(control=true){  //ilk b nin kat say�s� kadar b silecez.
		   for(int i=0;i<b_coefficent;i++){
   	    	iter=root;  //ge�ici eleman k�ke e�itlendi
   	    	root=root->next;  //k�k�m�z nexte e�it oldu
   	    	free(iter); //eski k�k�m�z� sildik.
   	    	control=false; //b katsay�s� kadar eleman sildik b den.
		   }
		   }
		   if(control==false){  //�imdi ise b kaysay�s� kadar b sildiysek a katsay�s� kadar a silece�iz.
		   	for(int i=0;i<a_coefficent;i++){
		   		temp=front;   //ge�icimiz �n elemana e�itlendi
		   		front=front->next;  //yeni �n eleman atand�.
		   		free(temp);  //eski �n eleman�m�z silindi
		   		control=true;  //controlumuzu d�zelttik.
			   }
		   }
		  
	    cout<<"Deleting a amount of "<<a_coefficent<<" and deleting b amount of "<<b_coefficent<<" the rest of them :"<<endl;
	show(); //kalan elemanlar her silme i�leminde tekrardan ekrana yaz�ld�.
   } 
   else if(counta<a_coefficent || countb<b_coefficent) { //listede katsay�lardan daha az eleman varsa d�ng� bitirildi.
   	break;
   }}
}
void getCoefficent(){
		int a_coefficent;
	int b_coefficent;
	 cout<<"Please enter coefficent of a"<<endl; //a n�n katsay�s� al�nd�
	 cin>>a_coefficent;
	  cout<<"Please enter coefficent of b"<<endl; // b nin katsay�s� al�nd�.
	 cin>>b_coefficent;
	 system("CLS"); //ekran temizlendi.
	deleting(a_coefficent,b_coefficent); //katsay�lara g�re silme i�lmeleri yapacak fonksiyon �a��r�ld�.
}
void check(){
	 if(root==NULL&&front==NULL){  //e�er listelerde eleman kalmad�ysa 
   	cout<<"This situation is organized"<<endl;  //bu mesaj verilecek
   }
   else{  //listelerin birinde bile eleman kald�ysa
   		cout<<"This situation is not organized"<<endl; //bu mesaj gelecek.
   }
}
int main(){
	int operate;
	do{
		back:
	cout<<"Choose operate"<<endl;
	cout<<"1. Add"<<endl<<"2. Control and listing step by step"<<endl<<"3. show"<<endl<<"4. Exit"<<endl; //se�enekler
	cin>>operate;
	switch(operate){
		case 1: add(); break;
		case 2:	if(root==NULL || front==NULL){
			cout<<"You need input element at the list"<<endl; //olurda liste bo�sa �nce eleman ekletmeyi yapt�ral�m kullan�c�ya.
			goto back;
		}
		show(); //katsay�lar� almadan �nce listede eleman varsa yazd�rd�k.
		getCoefficent(); 
        check();  break;
        case 3: show();
	}	}while(operate!=4);
	return 0;
}
