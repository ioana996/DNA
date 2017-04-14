#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct stack
{
	char s[3];//retine numele fiecarei comenzi pe stiva
	struct stack *next;
}Stack;

Stack* initStack(char s[]) 
{
	Stack* nod;
	nod=(Stack*)malloc(sizeof(Stack));
	strcpy(nod->s,s);
	nod->next=NULL;
	return nod;
}

Stack* addStack(Stack* stack,char s[])
{
	if(stack==NULL)
		return initStack(s);
	else
		{
			Stack* nod;
			nod=initStack(s);
			nod->next=stack;
			return nod;
		 }
	
}

Stack* deleteStack(Stack* stack)
{
	if(stack==NULL)
		return stack;
	else
	{
		Stack* nou;
		nou=stack;
		stack=nou->next;
		free(nou);
	}
	return stack;
}

void printStack(Stack* stack,FILE* fp)
{
	while(stack!=NULL && stack->next!=NULL)//printeaza stiva element cu element
	{	
		fprintf(fp,"%s ",stack->s);
		stack=stack->next;
	 }
	if(stack!=NULL && stack->next==NULL)//dupa ultimul element, in fisierul de output se elimina spatiul
	{	
		fprintf(fp,"%s",stack->s);
		stack=stack->next;
	 }
	fputc((int)'\n',fp);//si se adauga new line
}

void exitStack(Stack* stack)//functie de stergere a stivei
{
	Stack* nod=stack;
	while(nod!=NULL)
	{
		stack=stack->next;
		free(nod);
		nod=stack;
	}
}


typedef struct Node//structura pentru nodurile listei
{
	char nume;
	char snod;
	struct Node *next;
}Node;

Node* initList(int nume,char snod)//initializare a unui nod
{
	Node* nod;
	nod=(Node*)malloc(sizeof(Node));
	nod->nume=nume;
	if(snod=='T')
		nod->snod='T';
	else
		nod->snod='F';
	nod->next=NULL;
	return nod;
}

Node* createList(Node* list,int nume,char snod)//crearea listelor din fisierul data.txt
{
	if(list==NULL)
		return initList(nume,snod);
	else 
	{
		Node *nou,*ptr;
		ptr=list;
		nou=initList(nume,snod);
		while(list->next!=NULL)
			list=list->next;
		list->next=nou;
		return ptr;
	}
}


Node* insertElement(Node* list,char nume,char snod,int bucla,int index)
{	int nr=2;
	Node *ptr;
	if(bucla==0)//daca bucla este 0, avem inserare la inceput de lista sau inserare in interiorul listei
	{
		if(index==1)
		{
			ptr=initList(nume,snod);
			ptr->next=list;//primul nod devine cap de lista
		 }
		else
		{
			Node *nod;
			ptr=list;
			while(nr!=index)
			{
				list=list->next;//se inainteaza pe lista pana la nodul indicat de index
				nr++;//arata numarul nodului in bucla 0
			}
			nod=initList(nume,snod);
			nod->next=list->next;
			list->next=nod;
		}
	}
	if(bucla>0)
	{
		Node *nod;
		ptr=list;
		int b=0;
		while(b!=bucla)
		{
			if(list->next->snod=='F')//de cate ori este intalnit un nod suprapus
				list=list->next;
			else
			{
				b++;//creste indicele buclei
	 			list=list->next;
			}	
		}
		int ct=1;
		while(ct!=index)//dupa ce se ajunge pe bucla indicata,se cauta dupa index pozitia pe care trebuie inserat nodul
		{
			list=list->next;
			ct++;
		}
		nod=initList(nume,snod);
		nod->next=list->next;
		list->next=nod;	 
	}
	return ptr;
}

Node* deleteElement(Node *list,int bucla,int index)
{	Node *ptr;
	ptr=list;
	if(list==NULL)
		return list;
	else
	{
		if(bucla==0)
		{
			if(index==1)//stergere la inceput de lista
			{
				if(ptr==list)
				{
					ptr=list->next;//stergerea primului element din lista
					free(list);
				}
			}
			else
			{
				int nr=1;
				Node* nou;
				while(nr!=index)
				{
					nou=list;//se retine predecesorul nodului care trebuie sters pentru a se face legatura cu succesorul sau
					list=list->next;
					nr++;//merge pana la nodul indicat din bucla 0
				}
				nou->next=list->next;
				free(list);
			}
		}
				
		else
		{
			int b=0;
			Node* nou=list;
		 	while(b!=bucla)
			{
				if(list->next->snod=='F')//de cate ori se intalneste un nod suprapus
					list=list->next;
				else
				{
					b++;//se creste indicele buclei
					nou=list;
	 				list=list->next;
				}	
			}
			int ct=0;
			while(ct!=index)//cauta in bucla pozitia nodului care trebuie sters
			{	
				nou=list;//se retine predecesorul nodului care trebuie sters pentru a se face legatura cu succesorul sau
				list=list->next;
				ct++;
			}
			nou->next=list->next;
			free(list);
		}
	}
	return ptr;//returneaza adresa de inceput de lista		
}

Node* editElement(Node* list,char nume,char snod,int bucla,int index)
{
	if(bucla==0)
	{
		if(index==1)//editare la inceput de lista
		{
			list->nume=nume;
			list->snod=snod;
			return list;
		}
		else
		{
			int nr=1;
			Node *ptr=list;
			while(nr!=index)//cauta in lista elementul care trebuie editat
			{
				list=list->next;
				nr++;
			}
			list->nume=nume;
			list->snod=snod;
			return ptr;
		}
	}
	else
	{
		int b=0;
		Node *ptr=list;
		while(b!=bucla)//se cauta bucla in care se afla elementul cautat
		{
			if(list->next->snod=='F')
				list=list->next;
			else
			{
				b++;
	 			list=list->next;
			}	
		}
		int ct=0;
		while(ct!=index)//se cauta nodul dupa index in bucla gasita la pasul anterior
		{
			list=list->next;
			ct++;
		}
		list->nume=nume;
		list->snod=snod;
		return ptr;
	}
}

void printList(Node* list,FILE* fp)
{
	while(list!=NULL && list->next!=NULL)//printarea elementelor din lsita pana la penultimul nod
	{	
		if(list->snod=='F')
			fprintf(fp,"%c ",list->nume);
		else
			fprintf(fp,"%c* ",list->nume);
		list=list->next;
	 }
	if(list!=NULL && list->next==NULL)//printarea ultimului nod si eliminarea spatiului de la sfarsit de linie
	{	
		if(list->snod=='F')
			fprintf(fp,"%c",list->nume);
		else
			fprintf(fp,"%c*",list->nume);
	 }
	fputc((int)'\n',fp);//adaugare de new line
}

void reversedPrint(Node* list,FILE* fp)
{
	if(list==NULL)
	{
	 	return;
	 }
	reversedPrint(list->next,fp);
	if(list->snod=='F')
			fprintf(fp,"%c ",list->nume);
	else
			fprintf(fp,"%c* ",list->nume);
	list=list->next;
}

Node* reverseList(Node* list)
{
	Node *prev=NULL;
	Node *next=list->next;
	while(list!=NULL)
	{
		list->next=prev;
		prev=list;
		list=next;
		if(next!=NULL)
			next=next->next;
	}
	return prev;//se returneaza nou cap de lista adica ultimul nod din lista neinversata
}

void exitList(Node* list)//stergerea listei nod cu nod
{
	Node* nod=list;
	while(nod!=NULL)
	{
		list=list->next;
		free(nod);
		nod=list;
	}
}

typedef struct undo//structura care retine date despre un element care trebuie reinserat sau editat pentru operatia de undo
{
	char name;
	char value;
	int linie;
	int bucla;
	int index;
	struct undo *next;
}Undo;

Undo* initUndo(char name,char value,int linie,int bucla,int index) //initializarea stivei in care se retin datele nodurilor ce au fost editate sau sterse
{
	Undo* nod;
	nod=(Undo*)malloc(sizeof(Undo));
	nod->name=name;
	nod->value=value;
	nod->linie=linie;
	nod->bucla=bucla;
	nod->index=index;
	nod->next=NULL;
	return nod;
}

Undo* addUndo(Undo* undo,char name,char value,int linie,int bucla,int index)
{
	if(undo==NULL)
		return initUndo(name,value,linie,bucla,index);
	else
	{
		Undo* nod;
		nod=initUndo(name,value,linie,bucla,index);
		nod->next=undo;
		return nod;
	}
}

Undo* findUndo(Undo* undo,Node* list,int l,int b,int in)//gasirea unui element in lista pentru a putea fi editat sau reinserat
{
	Node* nod=list;
	int g=0,p=0;
	while(g!=b)//se cauta bucla in care elementul sters sau editat a existat
	{	
		nod=nod->next;
		if(nod->snod=='T')
		g++;
								
	}
	while(p!=in)//se cauta indexul nodului sters sau editat
	{
		if(nod->next->snod!='T')
		p++;
		nod=nod->next;
	}
	undo=addUndo(undo,nod->nume,nod->snod,l,b,in);//se adauga pe stiva pentru a putea fi reinserat sau editat la comanda de undo cu datele anterioare
	return undo;
}

Undo* deleteUndo(Undo* undo)//stergerea unui element din stiva dupa ce operatia de undo pe elementul respectiv a fost efectuata
{
	if(undo==NULL)
		return undo;
	else
	{
		Undo* nou;
		nou=undo;
		undo=nou->next;
		free(nou);
	}
	return undo;
}

void exitUndo(Undo* undo)//stergerea stivei
{
	Undo* nod=undo;
	while(nod!=NULL)
	{
		undo=undo->next;
		free(nod);
		nod=undo;
	}
}

void Validation(Node* list1,Node* list2,FILE* fp)
{
	Node *l1,*l2;
	l1=list1;
	l2=list2;
	while(l1->snod==l2->snod && l1->next!=NULL && l2->next!=NULL)
	{
		l1=l1->next;//de fiecare data cand valoarile de adevar ale nodurilor corespund se inainteaza pe ambele liste
		l2=l2->next;
	}
	if(l1->snod!=l2->snod) 
	{
		fprintf(fp,"false\n");
		return;
	}
	else //daca listele corespund ca numar de bucle si indecsi, se incepe iar compararea listelor nod cu nod 
	{
		Node *d1=list1,*d2=list2;
		while(d1->next!=NULL && d2->next!=NULL)
		{	
			if((d1->nume=='A' && d2->nume=='T') || (d1->nume=='T' && d2->nume=='A') || (d1->nume=='C' && d2->nume=='G') || (d1->nume=='G' && d2->nume=='C'))//se analizeaza cele patru cazuri de combinatii posibile
			{
				d1=d1->next;
				d2=d2->next;
			}
			else //daca niciunul dintre cazuri nu exista inseamna ca ADN-ul nu are legaturi intre elementele corespunzatoare
			{
				fprintf(fp,"false\n");
				 return;//se iese din functie deoarece nu exista potrivire intre cele doua linii
			}
		}
			
		fprintf(fp,"true\n");//se iese din ciclul while numai atunci cand listele corespund, altfel functia se incheie in while cu return 
	}		
}

int main(int argc,char* argv[])
{
	FILE *data,*comm,*out;
	data=fopen(argv[1],"r");
	comm=fopen(argv[2],"r");
	out=fopen(argv[3],"w");

	Undo* undo;//a doua stiva pe care se retin la editare si stergere , datele nodurilor ce au fost modificate
	undo=NULL;
	Node *list1,*list2;
	list1=NULL;
	list2=NULL;
	Stack* stack;
	stack=NULL;
	int i,contor=0;
	char snod,nume;
	char *buffer,*string;
	buffer=(char*)malloc(1000*sizeof(char));
	string=(char*)malloc(15*sizeof(char));
	size_t lung=strlen(buffer);
	char *ch;
	int l,b,in;
	char n,s;
	size_t len=strlen(string);
	ch=(char*)malloc(3*sizeof(char));
	
	while(getline(&buffer,&lung,data)!=-1)//citire din fisierul data.txt
		{
		 	for(i=0;i<strlen(buffer);i++)//citirea unei linii
			{ 
				if(buffer[i]=='\n')//daca se ajunge la sfarsit de linie atunci incepe sa se creeze lista 2
			  		contor++;
			 	if(contor==0)//aflare pe linia 1 deci se creeaza lista 1
			  	{
					if(buffer[i]!=' ' && buffer[i]!='*' && buffer[i]!='\n')//daca buffer[i] este o litera
					{
						nume=buffer[i];//numele nodului ia valoarea sirului in i
			 	 		if(buffer[i+1]=='*')//daca pe pozitia de langa litera se afla '*' atunci avem nod suprapus
							snod='T';
				 		if(buffer[i+1]==' ' || buffer[i+1]=='\n')
							snod='F';
			 	 		list1=createList(list1,nume,snod);
				 	}
				}
			  	if(contor==1)//aflare pe linia 2 deci se creeaza lista 2
				{
					if(buffer[i]!=' ' && buffer[i]!='*' && buffer[i]!='\n')
					{
						nume=buffer[i];//numele nodului ia vealorea sirului in i
			 	 		if(buffer[i+1]=='*')
							snod='T';//daca pe pozitia de langa litera se afla '*' atunci avem nod suprapus
				 		else
							snod='F';
			 	 		list2=createList(list2,nume,snod);
					 }
				}
			}
				
		 }
	 free(buffer);
			
			
			
	while(getline(&string,&len,comm)!=-1)//citire din fisierul cu comenzi
	{	
		sscanf(string,"%s",ch);//se iau numai primele doua litere de pe fiecare linie
		if(strcmp(ch,"ie")==0)//se compara cu comenzile ce trebuie primite
			sscanf(string,"%s %d %d %d %c %c",ch,&l,&b,&in,&n,&s);
		if(strcmp(ch,"de")==0)//astfel incat parsarea liniei din fisierul comenzi se face diferit pentru fiecare comanda deoarece au argumente diferite
			sscanf(string,"%s %d %d %d",ch,&l,&b,&in);
		if(strcmp(ch,"ee")==0)
			sscanf(string,"%s %d %d %d %c %c",ch,&l,&b,&in,&n,&s);
		if(strcmp(ch,"pl")==0)
			sscanf(string,"%s %d",ch,&l);
		if(strcmp(ch,"pl")==0)
			sscanf(string,"%s %d",ch,&l);
		if(strcmp(ch,"pr")==0)
			sscanf(string,"%s %d",ch,&l);
		if(strcmp(ch,"pv")==0)
		{
			Validation(list1,list2,out);
		}
		if(strcmp(ch,"ie")==0)
		{
			if(l==1)
			{
				list1=insertElement(list1,n,s,b,in);//se insereaza un element nou
				undo=addUndo(undo,n,s,l,b,in);//se retine pe stiva undo pozitia elementului introdus pentru ca la comanda undo sa se stie de unde se sterge elementul
			}
			else
			{
				list2=insertElement(list2,n,s,b,in);
				undo=addUndo(undo,n,s,l,b,in);
			}
		}
		if(strcmp(ch,"de")==0)
		{
			if(l==1)
			{
				undo=findUndo(undo,list1,l,b,in);//se cauta elementul de sters in lista pentru a-i retine datele 
				list1=deleteElement(list1,b,in);
			}
			else
			{
				undo=findUndo(undo,list2,l,b,in);
				list2=deleteElement(list2,b,in);
			}
		}
		if(strcmp(ch,"ee")==0)
		{
			if(l==1)
			{
				undo=findUndo(undo,list1,l,b,in);//se cauta elementul de sters in lista pentru a-i retine datele
				list1=editElement(list1,n,s,b,in);
			}
			else
			{
				undo=findUndo(undo,list2,l,b,in);
				list2=editElement(list2,n,s,b,in);
			}
		}	
		if(strcmp(ch,"pl")==0)
		{
			if(l==1)
				printList(list1,out);
			else
				printList(list2,out);
		}
		if(strcmp(ch,"pr")==0)
		{
			if(l==1)
			{
				reversedPrint(list1,out);
				fseek(out,-1,SEEK_CUR);//scoate spatiul de la sfarsitul fiecarei linii
				fputc((int)'\n',out);//adaugare new line
			}
			else
			{
				reversedPrint(list2,out);
				fseek(out,-1,SEEK_CUR);
				fputc((int)'\n',out);
			}
		}
		if(strcmp(ch,"rs")==0)
		{
			list1=reverseList(list1);
			list2=reverseList(list2);
		}
		if(strcmp(ch,"ex")==0)//stergerea tuturor listelor, stivelor, inchiderea fsierelor si golirea memoriei pentru sirurile utilizate
		{
			exitList(list1);
			exitList(list2);
			exitStack(stack);
			exitUndo(undo);
			free(ch);			
			free(string);
			fclose(data);
			fclose(comm);
			fclose(out);
			return 0;
		}
		if(strcmp(ch,"un")==0)
		{	
			if(strcmp(stack->s,"rs")==0)
			{
				list1=reverseList(list1);
				list2=reverseList(list2);
			}
			if(strcmp(stack->s,"ie")==0)//stergerea unui element la comanda undo atunci cand pe stiva este comanda de inserare
			{
				if(undo->linie==1)
				{
					if(undo->value=='F')//daca nodul inserat nu este suprapus
					{
						list1=deleteElement(list1,undo->bucla,undo->index);//stergere pe bucla si indexul de la inserare
						undo=deleteUndo(undo);
					}
					else//altfel numarul buclelor creste cu o unitate si indexul scade cu una
					{
						list1=deleteElement(list1,undo->bucla+1,undo->index-1);
						undo=deleteUndo(undo);
					}
				}
				else//acelasi principiu,dar pentru lista 2
				{
					if(undo->value=='F')
					{
						list2=deleteElement(list2,undo->bucla,undo->index);
						undo=deleteUndo(undo);
					}
					else
					{
						list2=deleteElement(list2,undo->bucla+1,undo->index-1);
						undo=deleteUndo(undo);
					}
				}
			}
			if(strcmp(stack->s,"ee")==0)
			{
				if(undo->linie==1)
				{
					if(undo->value=='F')//daca nodul editat nu este suprapus
					{
						if(s=='F')//si nodul care l-a inlocuit a fost tot nesuprapus
						{
							list1=editElement(list1,undo->name,undo->value,undo->bucla,undo->index);//atunci editarea se face pe acelasi element cu aceeasi pozitie
							undo=deleteUndo(undo);
						}
						else//nodul care l-a inlocuit a fost suprapus inseamna ca se afla intr-o bucla cu o unitate mai mare decat era nodul needitat si pe index 0
						{
							int u=0;
							list1=editElement(list1,undo->name,undo->value,undo->bucla+1,u);
							undo=deleteUndo(undo);
						}
					}
					else
					{	
						list1=editElement(list1,undo->name,undo->value,undo->bucla,undo->index);
						undo=deleteUndo(undo);
					}
				}
				else//acelasi principiu dar pentru lista 2
				{
					if(undo->value=='F')
					{
						if(s=='F')
						{
							list2=editElement(list2,undo->name,undo->value,undo->bucla,undo->index);
							undo=deleteUndo(undo);
						}
						else
						{
							int u=0;
							list2=editElement(list2,undo->name,undo->value,undo->bucla+1,u);
							undo=deleteUndo(undo);
						}
					}
					else
					{
						list2=editElement(list2,undo->name,undo->value,undo->bucla,undo->index);
						undo=deleteUndo(undo);
					}
				}
			}
			if(strcmp(stack->s,"de")==0)
			{
				if(undo->linie==1)
				{
					list1=insertElement(list1,undo->name,undo->value,undo->bucla,undo->index);//reinserarea nodului in lista
					undo=deleteUndo(undo);//stergerea datelor elementului introdus la comanda undo data pentru comanda delete
				}
				else
				{
					list2=insertElement(list2,undo->name,undo->value,undo->bucla,undo->index);
					undo=deleteUndo(undo);
				}
			}
							
			stack=deleteStack(stack);//steregerea comenzii de pe stiva dupa comanda undo
		}
		if(strcmp(ch,"ps")==0)
			printStack(stack,out);
		if(strcmp(ch,"un")!=0 && strcmp(ch,"ps")!=0)
			stack=addStack(stack,ch);
	}
	return 0;
}
