#include <stdio.h>
#include<locale.h>
#include <stdbool.h>
#include <stdlib.h>

//baz� modeller internet �zerinden search edilerek en iyi sonu�lar� alma ad�na �zelle�tirmeleri yap�lm��t�r.

typedef struct
{ 
	int number; 
	char *name; 
	int grade; 
}student; 

student *hash_table;
int i=0; //neredeyse t�m fonklarda kullan�lacak de�erler global tan�mlanm��t�r.

int calculate_1(int x,int size)
{
	//klasik ilk ogretilen hashleme metodudur. keyden hash table boyutuna modu al�n�r.
	return x%size;
}

unsigned int calculate_2(unsigned char *str,int size)
{           
     //bir�ok kayna�a g�re string �zerinde hashleme metodu yap�lacaksa e�er d2jb modeli kullan�lmaktad�r. Bizde di�erleri gibi kendi sahip oldu�umuz modele g�re �zelle�tirme yapar�k bu modeli kulland�k.
        unsigned int calculate_2 = 5381;
        int c;
        while (c = *str++)
            calculate_2 = ((calculate_2 << 5) + calculate_2) + tolower(c); 
        return calculate_2%size;
}

unsigned long calculate_3(unsigned char *str,int size)
{  
   // hash=hash+c yani loselose hashing modeli. 
	unsigned int calculate_3 = 0;
	int c;
	while (c = *str++)
	    calculate_3 += c;  
	return calculate_3%size;
}

int calculate_4(int x,int size)
{  
//h(k)- [v*((a/w)*k)mod1 16 bit] knuth modelinden biraz daha iyi sonu� vermektedir.
	return (x*2654435761>> 16 ) % size;
} 

int calculate_5(int x,int size)
{   
   // bu hesab�n amac� gelen keyin her bir 3(son 4) basama��n� toplay�p 3 l� basamaklara ay�r�p toplad�ktan sonra modunu almakt�r. �rn: 2017556029
    int y=0,z=0,c=0;
    c+=x%10;
    c+=x%100;
    c+=x%1000;
    z+=x%10000-c;
    z+=x%100000-c;
    z+=x%1000000-c;
    z=z%1000;
    y+=x%10000000-z;
    y+=x%100000000-z;
    y+=x%10000000000-z;
    y=y%1000000;
    return (y+z+c)%size;
}

int basic_hash(student *v, int h_size, int s_size)
{    
     int collision=0;
     hash_table= (student*) malloc(h_size*sizeof(student));
      //collision 0 lanm��, hash tablolar� farkl� boyutlarda ramde yer ayr�lm�� ve primary keyleri olan number -1 e e�itlendi.
     for(i=0;i<h_size;i++)
	 {   
	      hash_table[i].number=-1;
	 }
	if(s_size>h_size)
	  s_size=h_size;
	   //ekleme i�lemi i�in d�ng� normal �artlarda sahip oldu�umuz arrayin boyutuna g�re ekleme yap�lmal�. Ancak hash tablomuz daha k���k bir alana sahipse
    //yer olmayaca��ndan kaynakl� boyut de�i�tirilmesi gerekmektedir.
	for(i=0; i<s_size;i++)
	{  
  	  if(hash_table[calculate_1(v[i].number,h_size)].number == -1)
	  {   
  	    hash_table[calculate_1(v[i].number,h_size)]=v[i];//yap�lan hesaplama sonras� e�er bulunan yer bo� ise de�er alana eklenmi�tir
	  }
     else
	 {
	 	//ancak hesaplama sonucu bulunan alan bo� de�il ise lineer search y�ntemi ile bulunan alandan sonraas� i�in ilk bo� alan bulunmas� gerekmektedir.
	  	int indis = calculate_1(v[i].number,h_size);
	  	bool backing = false;
	  	back:
	  	while(hash_table[indis].number != -1 && indis<h_size)
	  	{
		  indis++; 
		  collision++;
		}
		if(indis != h_size)
		hash_table[indis]=v[i];
		else if(!backing)
		{
			 //e�erki bulunan alan sonras� bo� yer yoksa d�ng� ba�a d�nmeli ve alandan �ncesi i�inde search i�lemide yap�lmal�d�r.
		 indis=0;
		 backing=true;
		 goto back;
		}
	 }
    }
    free(hash_table);
    return collision;
}

int djb2_hash(student *v, int h_size, int s_size)
{   
     int collision=0;
     hash_table= (student*) malloc(h_size*sizeof(student));
        //collision 0 lanm��, hash tablolar� farkl� boyutlarda ramde yer ayr�lm�� ve primary keyleri olan number -1 e e�itlendi.
	 for(i=0;i<h_size;i++)
	 {   
	      hash_table[i].number=-1;
	 }
	if(s_size>h_size)
	  s_size=h_size;
	  	  //ekleme i�lemi i�in d�ng� normal �artlarda sahip oldu�umuz arrayin boyutuna g�re ekleme yap�lmal�. Ancak hash tablomuz daha k���k bir alana sahipse
    //yer olmayaca��ndan kaynakl� boyut de�i�tirilmesi gerekmektedir.
	for(i=0; i<s_size;i++)
	{  
  	  if(hash_table[calculate_2(v[i].name,h_size)].number == -1)
	  {   
  	    hash_table[calculate_2(v[i].name,h_size)]=v[i];//yap�lan hesaplama sonras� e�er bulunan yer bo� ise de�er alana eklenmi�tir
	  }
	  else
	  {  
	  
	  	//ancak hesaplama sonucu bulunan alan bo� de�il ise lineer search y�ntemi ile bulunan alandan sonraas� i�in ilk bo� alan bulunmas� gerekmektedir.
	  	int indis = calculate_2(v[i].name,h_size);
	  	bool backing = false;
	  	back:
	  	while(hash_table[indis].number != -1 && indis<h_size)
	  	{
		  indis++; 
		  collision++;
		}
		if(indis != h_size)
		hash_table[indis]=v[i];
		else if(!backing)
		{
			 //e�erki bulunan alan sonras� bo� yer yoksa d�ng� ba�a d�nmeli ve alandan �ncesi i�inde search i�lemide yap�lmal�d�r.
		 indis=0;
		 backing=true;
		 goto back;
		}
	  }
	  	
    }
    free(hash_table);
    return collision;  
}

int loseLose_hash(student *v, int h_size, int s_size)
{
 int collision=0;
     hash_table= (student*) malloc(h_size*sizeof(student));
       //collision 0 lanm��, hash tablolar� farkl� boyutlarda ramde yer ayr�lm�� ve primary keyleri olan number -1 e e�itlendi.
	 for(i=0;i<h_size;i++)
	 {   
	      hash_table[i].number=-1;
	 }
	if(s_size>h_size)
	  s_size=h_size;
	  //ekleme i�lemi i�in d�ng� normal �artlarda sahip oldu�umuz arrayin boyutuna g�re ekleme yap�lmal�. Ancak hash tablomuz daha k���k bir alana sahipse
    //yer olmayaca��ndan kaynakl� boyut de�i�tirilmesi gerekmektedir.
	for(i=0; i<s_size;i++)
	{  
	
  	  if(hash_table[calculate_3(v[i].name,h_size)].number == -1)
	  {   
  	    hash_table[calculate_3(v[i].name,h_size)]=v[i]; //yap�lan hesaplama sonras� e�er bulunan yer bo� ise de�er alana eklenmi�tir
	  }
	  else
	  {
	  	//ancak hesaplama sonucu bulunan alan bo� de�il ise lineer search y�ntemi ile bulunan alandan sonraas� i�in ilk bo� alan bulunmas� gerekmektedir.
	  	int indis = calculate_3(v[i].name,h_size);
	  	bool backing = false;
	  	back:
	  	while(hash_table[indis].number != -1 && indis<h_size)
	  	{
		  indis++; 
		  collision++;
		}
		if(indis != h_size)
		hash_table[indis]=v[i];
		else if(!backing)
		{
			 //e�erki bulunan alan sonras� bo� yer yoksa d�ng� ba�a d�nmeli ve alandan �ncesi i�inde search i�lemide yap�lmal�d�r.
		 indis=0;
		 backing=true;
		 goto back;
		}
	  }
	  	
    }
    free(hash_table);
    return collision;  
}

int Knuths_hash(student *v, int h_size, int s_size)
{
	int collision=0;
     hash_table= (student*) malloc(h_size*sizeof(student));
     //collision 0 lanm��, hash tablolar� farkl� boyutlarda ramde yer ayr�lm�� ve primary keyleri olan number -1 e e�itlendi.
     for(i=0;i<h_size;i++)
	 {   
	      hash_table[i].number=-1;
	 }
	if(s_size>h_size)
	  s_size=h_size;
	//ekleme i�lemi i�in d�ng� normal �artlarda sahip oldu�umuz arrayin boyutuna g�re ekleme yap�lmal�. Ancak hash tablomuz daha k���k bir alana sahipse
    //yer olmayaca��ndan kaynakl� boyut de�i�tirilmesi gerekmektedir.
	for(i=0; i<s_size;i++)
	{  
  	  if(hash_table[calculate_4(v[i].number,h_size)].number == -1)
	  {   
	  
  	    hash_table[calculate_4(v[i].number,h_size)]=v[i]; //yap�lan hesaplama sonras� e�er bulunan yer bo� ise de�er alana eklenmi�tir
	  }
      else
	  {
	 	//ancak hesaplama sonucu bulunan alan bo� de�il ise lineer search y�ntemi ile bulunan alandan sonraas� i�in ilk bo� alan bulunmas� gerekmektedir.
	  	int indis = calculate_4(v[i].number,h_size);
	  	bool backing = false;
	  	back:
	  	while(hash_table[indis].number != -1 && indis<h_size)
	  	{ 
		  indis++; 
		  collision++;
		}
		if(indis != h_size)
		hash_table[indis]=v[i];
		else if(!backing)
		{
			 //e�erki bulunan alan sonras� bo� yer yoksa d�ng� ba�a d�nmeli ve alandan �ncesi i�inde search i�lemide yap�lmal�d�r.
		 indis=0;
		 backing=true;
		 goto back;
		}
	   }
    }
    free(hash_table);
    return collision;
}

int digitFolding_hash(student *v, int h_size, int s_size)
{
	 int collision=0;
     hash_table= (student*) malloc(h_size*sizeof(student));
     for(i=0;i<h_size;i++)
	 {   
	      hash_table[i].number=-1;
	 }
	 //collision 0 lanm��, hash tablolar� farkl� boyutlarda ramde yer ayr�lm�� ve primary keyleri olan number -1 e e�itlendi.
	if(s_size>h_size)
	  s_size=h_size;
    //ekleme i�lemi i�in d�ng� normal �artlarda sahip oldu�umuz arrayin boyutuna g�re ekleme yap�lmal�. Ancak hash tablomuz daha k���k bir alana sahipse
    //yer olmayaca��ndan kaynakl� boyut de�i�tirilmesi gerekmektedir.
	for(i=0; i<s_size;i++)
	{  
  	  if(hash_table[calculate_5(v[i].number,h_size)].number == -1)
	  {   
  	    hash_table[calculate_5(v[i].number,h_size)]=v[i]; //yap�lan hesaplama sonras� e�er bulunan yer bo� ise de�er alana eklenmi�tir
	  }
     else
	 {
	 	//ancak hesaplama sonucu bulunan alan bo� de�il ise lineer search y�ntemi ile bulunan alandan sonraas� i�in ilk bo� alan bulunmas� gerekmektedir.
	  	int indis = calculate_5(v[i].number,h_size);
	  	bool backing = false;
	  	back:
	  	while(hash_table[indis].number != -1 && indis<h_size)
	  	{
		  indis++; 
		  collision++;
		}
		if(indis != h_size)
		hash_table[indis]=v[i];
		else if(!backing)
		{
		  //e�erki bulunan alan sonras� bo� yer yoksa d�ng� ba�a d�nmeli ve alandan �ncesi i�inde search i�lemide yap�lmal�d�r.
		 indis=0;
		 backing=true;
		 goto back;
		}
	   }
    }
    free(hash_table);
    return collision;
}

void hashingOperations(student *stu,int counter)
{
	int CollisionXS=0,CollisionS=0,CollisionM=0,CollisionL=0,CollisionXL=0;
	//Her bir hash fonksiyonu collision d�nd�rerek �a��r�lm��t�r.
    CollisionXS = basic_hash(stu,70,counter);
    CollisionS=basic_hash(stu,150,counter);
    CollisionM=basic_hash(stu,273,counter);
    CollisionL=basic_hash(stu,325,counter);
    CollisionXL=basic_hash(stu,400,counter);
    //performans hesab� her bir collision de�erinin boyuta g�re % kac oldu�unu bulup toplam % lerin ortalamas� al�nmaktad�r.
    printf("\n         Collision Values Table For Every Hash Table and Hashing Function \n\n      Hash Table Size:   XS   S    M     L     XL  Performance(sigma(average percentage))\n\n\nHashing Methods \n\nMod Hashing:      \t %d %d %d %d %d          %d\n",CollisionXS,CollisionS,CollisionM,CollisionL,CollisionXL,(((100*CollisionXS)/70)+((100*CollisionS)/150)+((100*CollisionM)/273)+((100*CollisionL)/325)+((100*CollisionXL)/400))/5);
    
    CollisionXS = djb2_hash(stu,70,counter);
    CollisionS=djb2_hash(stu,150,counter);
    CollisionM=djb2_hash(stu,273,counter);
    CollisionL=djb2_hash(stu,325,counter);
    CollisionXL=djb2_hash(stu,400,counter);
    printf("djb2 Hashing:     \t %d %d  %d  %d   %d           %d\n",CollisionXS,CollisionS,CollisionM,CollisionL,CollisionXL,(((100*CollisionXS)/70)+((100*CollisionS)/150)+((100*CollisionM)/273)+((100*CollisionL)/325)+((100*CollisionXL)/400))/5);

    CollisionXS =loseLose_hash(stu,70,counter);
    CollisionS=loseLose_hash(stu,150,counter);
    CollisionM=loseLose_hash(stu,273,counter);
    CollisionL=loseLose_hash(stu,325,counter);
    CollisionXL=loseLose_hash(stu,400,counter);
    printf("Lose Lose Hanging:\t %d %d  %d  %d   %d           %d\n",CollisionXS,CollisionS,CollisionM,CollisionL,CollisionXL,(((100*CollisionXS)/70)+((100*CollisionS)/150)+((100*CollisionM)/273)+((100*CollisionL)/325)+((100*CollisionXL)/400))/5);

    CollisionXS =Knuths_hash(stu,70,counter);
    CollisionS=Knuths_hash(stu,150,counter);
    CollisionM=Knuths_hash(stu,273,counter);
    CollisionL=Knuths_hash(stu,325,counter);
    CollisionXL=Knuths_hash(stu,400,counter);
    printf("Knuths Method Hasging:\t %d %d  %d  %d   %d           %d \n",CollisionXS,CollisionS,CollisionM,CollisionL,CollisionXL,(((100*CollisionXS)/70)+((100*CollisionS)/150)+((100*CollisionM)/273)+((100*CollisionL)/325)+((100*CollisionXL)/400))/5);
    
    CollisionXS =digitFolding_hash(stu,70,counter);
    CollisionS=digitFolding_hash(stu,150,counter);
    CollisionM=digitFolding_hash(stu,273,counter);
    CollisionL=digitFolding_hash(stu,325,counter);
    CollisionXL=digitFolding_hash(stu,400,counter);
    printf("Digit Folding Hashing:\t %d %d %d  %d   %d           %d\n",CollisionXS,CollisionS,CollisionM,CollisionL,CollisionXL,(((100*CollisionXS)/70)+((100*CollisionS)/150)+((100*CollisionM)/273)+((100*CollisionL)/325)+((100*CollisionXL)/400))/5);
    printf("\nCONCLUSION: as you can see; Mod Hashing has the worst performance of all.\nFor minimum size hash table, Digggit Folding hashing has the lowest collision.\nwhen Hash table size and our array size is same, djb2 Method has the best performance.\nOn the other hand, in hash tables of different sizes knuths string hashing method shows the best performance\nThe most effective hashing model is djb2 model. \nBut don't forget we use it with string key, so using integer keys may not be as good as.\nThe knuth model is good for hashing with integer ");
}

void fileOperations()
{
	int counter;
     FILE *fp; 
	 fp=fopen("data.txt","r+"); //data dosyam�z a��l�yor
	 char *temp=(char*)malloc(1 * sizeof(char)); //ge�ici bellek tan�mlan�p alan ay�r�l�yor.
	 while((fscanf(fp, "%c", &temp[i])) != EOF)
	 { //data.txt dosyas�nda bulunan t�m veriler char by char �ekiliyor.
		 if(temp[i]==',') //data dosyas�ndan virg�lleri kald�rmay� hedefliyoruz.
		 {
		   temp[i]=' '; 
		 }
		 else if(temp[i]==' ')//ayn� �ekilde isim girdisi tek bir string olsun diye bulunan bo�luklar yerine _ koyuyoruz
		 {
		 	temp[i]='_';
		 }
		temp = realloc(temp, (i+1) * sizeof(int)); //her bir char girdisi i�in ramdeki alan�m�z� b�y�t�yoruz.
		i++;//temp dizisini ilerliyor
	 }
	 fclose(fp);
	 //dosyadan t�m verileri temp dizisine istedi�imiz �ekilde aktard�k ve kapatt�k.
	 
	 fp=fopen("data_temp.txt","w+");
	 fwrite(temp, sizeof(char), i, fp); //data_temp.txt diye olu�turulan text dosyas�na temp dizimizi yerle�tirdik. b�ylece ana data bozulmam�� oldu.
	 fclose(fp); //dosya kapand�.
	 
	 i=0;
     fp = fopen("data_temp.txt","r+" ); //�imdi ise verilerimizi struct arrayde tutmak i�in ge�ici dosyam�z� tekrardan okuma modunda a��yoruz.
     fscanf(fp,"%d",&counter); //text dosyas�nda bulunan ��renci say�s� bilgisi okunuyor
     student stu[counter]; //struct dizimiz ��renci say�s�na g�re a��l�yor
     while(!feof(fp)) 
     {  
	    stu[i].name=(char*)malloc(33 * sizeof(char)); //struct dizisinde bulunan isim dizisi i�in bellekte yer a��l�yor.
        fscanf(fp,"%d %s %d \n",&stu[i].number,stu[i].name,&stu[i].grade); //text dosyas� numara isim not format�nda oldu�u i�in okuma i�lemi istedi�imiz gibi oluyor
        int j=0;
        for(j=0;j<33;j++) 
		{ //�ncesinde yerle�tirdi�imiz _ leri kald�rmak i�in yaz�lan algoritma
        	if(stu[i].name[j]=='_')
			{
        		stu[i].name[j]=' ';
			}
		}
        i++; //struct dizimizde ilerlemeye devam ediyoruz.
	 }
	 hashingOperations(stu,counter); //hashleme islemleri basladi.
}

int main()
{    
     setlocale(LC_ALL, "Turkish"); //tr karakterler tan�mland�
     fileOperations();
	 return 0;
}
