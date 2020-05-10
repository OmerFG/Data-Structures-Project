#include<iostream>
using namespace std;
float *input_inline(float array[],int size){
	int k;
	for(int i=0; i<size;i++){ //aray elemanlar� kullan�c�dan al�nd� ve araya eklendi.
		cout<<"Enter value of "<<i+1<<". member"<<endl;
		cin>>array[i];
	}      
	for(int j=0;j<size;j++){
    	for(int i=0; i<size;i++){  //k���kten b�y��e s�ralama yap�ld�.
	    	if(array[j]<array[i]){
			k=array[i];
			array[i]=array[j];
			array[j]=k;
		}
	}
	}
	return array; //fonksiyon i�erisinde olu�an array maine g�nderildi.
}
void control(float array1[],float array2[],int size1,int size2){
	int k=0,j=0;
	bool control=false;
	while(array1[k]!=array2[j]){ // 2. dizinin ilk eleman� 1. dizinin hangi eleman�na e�itse oradan sonra kontrol� sa�layaca��z
 k++;
 	}
	for(int i=k;i<size1;i++){ //ilk dizinin e�itli�i oldu�u yerden itibaren kontrol sa�lancak
		if(j!=size2){	//2. dizinin boyutunu a�mad��� s�re boyunca kontrol sa�lanacak.
		if(array1[i]==array2[j]){ //de�erlerin e�it olup olmad���n�n kontrol�n� sa�lad�m.
				 j++;
	             control=true; //e�er de�erler s�ral� bir �ekilde durmadan ayn�ysa control true olacak.
				}
				else if(array1[i]!=array2[j]){ //e�er bir yerde s�ral� e�itlik bozulursa
					control=false; //d�ng� sonlanacak.
					goto none;
				}
		}
		}
	none:
if(control==true){ //sub array ise
cout<<"Array2 is subset of array1";
}
else if(control==false){// de�il ise
	cout<<"Array2 is not subset of array2";
}
}
int main(){
	int i,j;
	float *ptr;
	cout<<"Enter size of first array"<<endl;  
	cin>>i;
	cout<<"Enter size of second array"<<endl;
	cin>>j;
	float array1[i];
	float array2[j];  //main ba�lang�c�ndan buraya kadar dizilerin boyutlar�yla beraber tan�m� yapt�k.
	ptr=&array1[0]; //ptr yi array1 in adresine e�itledik.
   ptr=input_inline(array1,i); //fonksiyona g�nderdi�imiz arrayin i�erisine eleman eklemeleri s�ral� �ekilde yap�p tekrar pointera e�itledik bu �ekilde dizimiz istenen �ekli ald�
   	ptr=&array2[0]; //array1 i�in yap�lan i�lemleri array2 i�inde yapt�k. ptr art�k array1 in adresini tutmas� gerekmiyor.
   ptr=input_inline(array2,j); //ptr array1 in adresindeki de�i�iklikleri yapt� �uan s�ra array2 de.
   if(i>=j ){ //b�y�k olan dizinin alt eleman�n� kontrol edece�imizden control fonkuna b�y�k eleman� ilk g�ndermeliyiz.
   control (array1,array2,i,j);
   }
   else if(j>i){
   	 control (array2,array1,j,i);
   }
	return 0;
}
