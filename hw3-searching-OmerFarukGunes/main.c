#include<stdio.h>
#include<stdlib.h> 
#include<conio.h>
#include<locale.h>
#include<string.h>

typedef struct
{
	int counter; //��renci say�s�
	int number; //primary
	char *name; //secondary
	int grade; //secondary
}student; //structer olu�turuldu

void sort(int *arr,int n)//Diziler i�in k���kten b�y��e s�ralama algoritmas�
{
	int temp,i,j;
	for(j=1;j<n;j++)
    {
        for (i=0;i<n-1;i++)
        {
           if (arr[i]>arr[i+1])
           {
               temp=arr[i]; //b�y�k eleman tempe
               arr[i]=arr[i+1]; //k���k eleman b�y�k eleman�n yerine
               arr[i+1]=temp; //tempteki b�y�k eleman k���k eleman�n yerine
           }
        }
    }
} 

void sortStructNumber(student *arr,int n)//struct dizileri i�in numaraya g�re s�ralama algoritmas�
{
	student temp;
	int i,j;
	for(j=1;j<n;j++)
    {
        for (i=0;i<n-1;i++)
        {
           if (arr[i].number>arr[i+1].number)
           {
               temp=arr[i];
               arr[i]=arr[i+1];
               arr[i+1]=temp;
           }
        }
   }
}

void sortStructGrade(student *arr,int n)//struct dizileri i�in nota g�re s�ralama algoritmas�
{
	student temp;
	int i,j;
	for(j=1;j<n;j++)
    {
        for (i=0;i<n-1;i++)
        {
           if (arr[i].grade>arr[i+1].grade)
           {
               temp=arr[i];
               arr[i]=arr[i+1];
               arr[i+1]=temp;
           }
        }
    }
}

void sortStructName(student *arr, int n) //struct dizileri i�in isme g�re s�ralama algoritmas�
{ 
    student temp; 
	int i,j;
	for(j=1;j<n;j++)
    {
        for (i=0;i<n-1;i++)
        {
           if (strcmp(arr[i].name, arr[j].name) > 0) //di�erlerinden farkl� olarak kar��la�t�rmak i�in strcmp() fonksiyonu kullan�ld�.
           { 
               temp=arr[i];
               arr[i]=arr[j];
               arr[j]=temp;
           }
        }
    }
} 


void LinSearch(int *arr,int n, int x)//Diziler i�in do�rusal arama
{
	int i;
	for(i=0; i<n; i++)
	{
		if(arr[i]==x) //de�erler e�it ise aranan de�er bulunmu�tur.
		{
			printf("%d de�eri dizinin %d. eleman�nda bulunmaktad�r.\n",x,i+1);
			return ;
		}
	}
	printf("%d de�eri dizide bulunmamaktad�r.\n",x);
}

void LinSearchPrimary(student *stu, int n,int x)//Primary keye g�re do�rusal arama
{
	int i;
	for(i=0; i<n; i++)
	{
		if(stu[i].number==x)
		{
			printf("%d %s %d\n",stu[i].number,stu[i].name,stu[i].grade); //bulunan de�ere ait t�m veriler yaz�ld�
			return ;
		}
	}
	printf("%d degeri dizide bulunmamaktadir.\n",x);
}

void LinSearchSecondary(student *stu, int n,int x)//secondary key olan nota g�re do�rusal arama
{
	int i;
	printf("%d Notu ��in Do�rusal Arama:\n",x);
	for(i=0; i<n; i++)
	{
		if(stu[i].grade==x)
		{
			printf("%d %s %d \n",stu[i].number,stu[i].name,stu[i].grade);//bulunan de�ere ait t�m veriler yaz�ld�
			//ba�ka notlar�n olabilece�i varsay�larak return edilmedi.
		}
	}
}

void LinSearchSecondaryName(student *stu, int n,char *x)//isme g�re do�rusal arama
{
	int i;
	for(i=0; i<n; i++)
	{
		if(strcmp(x,stu[i].name)==0)
		{
			printf("%d %s %d \n",stu[i].number,stu[i].name,stu[i].grade);
		}
	}
	printf("%s ismi dizide bulunmamaktad�r.\n",x);
}

void BinSearch(int *arr,int n, int x)
{
	int low= 0;
	n=n-1; //high de�er olarak n ele al�nd�
	while(low <= n)
	{
		int index = low+(n-low)/2; //dizinin ortas�ndan aramaya ba�lamak i�in i�lem yap�ld�
		if(arr[index] == x) 
		{
			printf("%d de�eri dizinin %d. eleman�nda bulunmaktad�r.\n",x,index+1); 
		    return;
		}
		else if(arr[index] < x)
		{
			low   = index+1; //bulundu�umuz yer x ten k���kse sa�a hareket ediyoruz
		}
		else
		{
			n = index-1; //bulundu�umuz yer x ten b�y�kse sola hareket ediyoruz
		}
	}
	printf("%d de�eri dizide bulunmamaktad�r.\n",x); //bulunamazsa hata mesaj� d�necektir
} //Diziler i�in binary aramas�


void BinSearchPrimary(student *arr,int n, int x)//struct dizileri i�in primary keye g�re binary aramas�
{
	int low= 0;
	n=n-1;
	while(low <= n)
	{
		int index = low+(n-low)/2;
		if(arr[index].number == x)
		{
	     	printf("%d %s %d \n",arr[index].number,arr[index].name,arr[index].grade); //bulunan de�er t�m verileriyle yaz�ld�
		    return; 
		}
		else if(arr[index].number < x)
		{
			low   = index+1;
		}
		else
		{
			n = index-1;
		}
	}
	printf("%d de�eri dizide bulunmamaktad�r.\n",x);
}

void BinSearchSecondary(student *arr,int n, int x)//ikincil de�ere g�re binary arama algoritmas�
{
	int low= 0;
	n=n-1;
	printf("%d Notu ��in �kili Arama:\n",x);
	while(low <= n)
	{
		int index = low+(n-low)/2;
		if(arr[index].grade == x)
		{
	     	printf("%d %s %d \n",arr[index].number,arr[index].name,arr[index].grade);
		    return;
		}
		else if(arr[index].grade < x)
		{
			low   = index+1;
		}
		else
		{
			n = index-1;
		}
	}
	printf("%d notu dizide bulunmamaktad�r.\n",x);
}

void BinSearchSecondaryName(student *arr,int n, char *x) //name e g�re binary arama algoritmas�
{   

	int low= 0;
	n=n-1;
	while(low <= n)
	{
		int index = low+(n-low)/2;
		if(strcmp(x,arr[index].name)==0)
		{
	     	printf("%d %s %d \n",arr[index].number,arr[index].name,arr[index].grade);
		    return;
		}
		else if(strcmp(x,arr[index].name)>0)
		{
			low   = index+1;
		}
		else
		{
			n = index-1;
		}
	}
	printf("%s ismi dizide bulunmamaktad�r.\n",x);
}
void FileOperation()//txt dosyas� �zerindeki i�lemler
{
     int counter; 
     int i=0;
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
	 
	 //-----------------------------------------
	 fp=fopen("data_temp.txt","w+");
	 fwrite(temp, sizeof(char), i, fp); //data_temp.txt diye olu�turulan text dosyas�na temp dizimizi yerle�tirdik. b�ylece ana data bozulmam�� oldu.
	 fclose(fp); //dosya kapand�.
	 //-----------------------------------------
	 
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
     printf("2019556465 Numaras� ��in Do�rusal Arama:\n");
     LinSearchPrimary(stu,counter,2019556465);
     printf("------------------------------------\n\n");
     
     printf("MEHMET �PEK �smi ��in Do�rusal Arama:\n");
     LinSearchSecondaryName(stu,273,"MEHMET �PEK"); //windows-1452 encoder�nda �al��maktad�r ve veriyi bulmaktad�r. kendi derleyicimde maalesef onun ayar�n� yapamad�m.
     printf("------------------------------------\n\n");
     
     printf("SILA BALLI �smi ��in Do�rusal Arama:\n");
     LinSearchSecondaryName(stu,counter,"SILA BALLI");
     printf("------------------------------------\n\n");
     
     LinSearchSecondary(stu,counter,100);
     printf("------------------------------------\n\n");
     
     LinSearchSecondary(stu,counter,0);
     printf("------------------------------------\n\n");
    
     sortStructNumber(stu,counter);
     
     printf("2018556011 Numaras� ��in �kili Arama:\n");
     BinSearchPrimary(stu,counter,2018556011);
     printf("------------------------------------\n\n");
     
     sortStructGrade(stu,counter);
     BinSearchSecondary(stu,counter,73);
     printf("------------------------------------\n\n");
     
     sortStructName(stu,counter);
     printf("DEN�Z U�UR �smi ��in �kili Arama:\n");  
     BinSearchSecondaryName(stu,273,"DEN�Z U�UR"); //windows-1452 encoder�nda �al��makta ve veriyi bulmaktad�r. kendi derleyicimde maalesef onun ayar�n� yapamad�m.
     printf("------------------------------------\n\n");
     
     printf("SILA BALLI �smi ��in �kili Arama:\n");
     BinSearchSecondaryName(stu,counter,"SILA BALLI");
     printf("------------------------------------\n\n");
     
     fclose(fp);
}

int main()
{
	setlocale(LC_ALL, "Turkish"); //tr karakterler tan�mland�
	
	int array1[]={3,44,38,5,47,15,36,26,27,2,46,4,19,50,48};
	int array2[]={3,44,48,5,47,15,36,26,27,2,48,5,19,50,48}; //arrayler olu�turuldu
	
	sort(array1,15);
	sort(array2,15); //arayler s�raland�.
	printf("1.Dizi ��in 3,5,48 De�erleriyle Do�rusal Arama:\n");
	LinSearch(array1,15,3);
	LinSearch(array1,15,5);
	LinSearch(array1,15,48);
	printf("------------------------------------\n\n");
	
	printf("2.Dizi ��in 3,5,48 De�erleriyle Do�rusal Arama:\n");
	LinSearch(array2,15,3);
	LinSearch(array2,15,5);
	LinSearch(array2,15,48);
	printf("------------------------------------\n\n");
	
	printf("1.Dizi ��in 3,5,48 De�erleriyle �kili Arama:\n");
	printf("------------------------------------\n");
	BinSearch(array1,15,3);
	BinSearch(array1,15,5);
	BinSearch(array1,15,48);
	printf("------------------------------------\n\n");
	
	printf("2.Dizi ��in 3,5,48 De�erleriyle �kili Arama:\n");
	BinSearch(array2,15,3);
	BinSearch(array2,15,5);
	BinSearch(array2,15,48);
	printf("------------------------------------\n\n");
	
	FileOperation();
}
