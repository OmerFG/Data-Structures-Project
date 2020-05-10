#include<iostream>
using namespace std;
class tree
{
public:
    tree* right;
    tree *left;
    int value;
};
tree *root=NULL;
tree *iter=NULL; //tree yap�s� olu�turuldu.
void printPostorder(tree*node) 
{ 
    if (node == NULL) 
        return; 
    printPostorder(node->left); //  en sola recursive 
    printPostorder(node->right); //en sa�a recursive
    cout << node->value << " "; //ve de�eri ekrana yazd�r.
} 
tree *add(tree *root,int x){
	if(root==NULL){//ilk eleman null veya recursive sonucu en sa� veya en soll eleman null ise 
	   root= new tree(); //yeni node a�
	    root->left=NULL; 
	    root->right=NULL; //her iki taraf� nulla e�itle 
	    root->value=x;  //de�erini ata.
	    return root; //ilk de�er ise maine d�nd�r. recursive sonucu girilen de�er ise recursive in ba�lad��� yere de�eri d�nd�r�yoruz.
	}
	if(root->value<x){  //de�erimiz a�a�taki de�erden b�y�k ise fonksiyonu a�ac�n sa��na gidecek �ekilde recursive yap�yoruz.
		root->right=add(root->right,x);
		return root;    //a�ac�n sa��na ekleme i�lemlerini yapt�ktan sonra rootu d�nd�r�yoruz.
	}
	    root->left=add(root->left,x);//yukar�daki iki ifede girmediyse gelen de�er a�a�takinden k���k olacakt�r.
	    //bu y�zden fonksiyonu durmadan recursive yap�yor ve k���k olan de�eri yerine yerle�tiriyoruz.
	    return root; //root geri d�nd�r�yoruz
}
int main(){
	int x;
	cout<<"Enter a value for including tree. You can exist when you enter 0"<<endl;
	cin>>x;
	while(x!=0){ //kullan�c� 0 girene kadar.
		root=add(root,x); //ekleme i�lemi yap�l�yor.
		cin>>x;
	}
	printPostorder(root);
	return 0;
}
