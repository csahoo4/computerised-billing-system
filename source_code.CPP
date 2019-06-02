#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<ctype.h>
#include<conio.h>
#include<process.h>
void products_enter();
void members_enter();
void readp();
void readm();
void billing();
void sales();
void modifyp();
void modifym();
void instructions();
class welcomescreen
{private:
int e;
public:
void wscreen();}wsc;
void welcomescreen::wscreen()
{for (int z=1;z<=80;z++)
{gotoxy(z,4);
cout<<"*";
}
gotoxy(36,5);
cout<<"WELCOME";
for (z=1;z<=80;z++)
{gotoxy(z,6);
cout<<"*";
}
gotoxy(33,10);
cout<<"COMPUTERISED";
gotoxy(32,11); cout<<"**************";
gotoxy(36,13);
cout<<"BILLING";
gotoxy(35,14); cout<<"*********";
gotoxy(36,16);
cout<<"SYSTEM";
gotoxy(35,17); cout<<"********";
gotoxy(24,20);
cout<<"Press 1 to go to MAIN MENU......\n";
gotoxy(24,21); cout<<"Press any key to EXIT..........."; cin>>e;
if(e!=1)
exit(0);
clrscr(); }
class products_record
{public:
float rate;
int stock;
int no;
char name[20];
};
products_record ob1,ob2;
fstream pro1,pro2;
class members_record
{public:
int no;
char name[20];
char add[50];
long int tel;
long int card;
float amt ;
};
members_record m1,m2;
fstream mem1,mem2;
class tables
{public:
int no;
int qty;
char name[20];
float rate;
float total;
};
tables n1,n2;
int i=0;
float discount=0.0;
void main()
{clrscr();
wsc.wscreen();
remove("sale.dat");
int n;
char l='y';
do
{clrscr();
gotoxy(30,5);
cout<<"MAIN MENU";
for (int z=29;z<=40;z++)
{gotoxy(z,6);
cout<<"-";
}
gotoxy(20,7);
cout<<"1:ADD NEW PRODUCTS";
gotoxy(20,8);
cout<<"2:ADD NEW MEMBERS";
gotoxy(20,9);
cout<<"3:VIEW AN EXISTING PRODUCT RECORD ";
gotoxy(20,10);
cout<<"4:VIEW AN EXISTING MEMBER'S RECORD ";
gotoxy(20,11);
cout<<"5:BILLING ";
gotoxy(20,12);
cout<<"6:TODAY'S SALES ";
gotoxy(20,13);
cout<<"7:MODIFY PRODUCT RECORD ";
gotoxy(20,14);
cout<<"8:MODIFY MEMBER'S RECORD ";
gotoxy(20,15);
cout<<"9:INSTRUCTIONS ";
gotoxy(20,16);
cout<<"0:EXIT";
gotoxy(20,19);
cout<<"Enter your choice:";
cin>>n;
switch(n)
{case 1: products_enter();
		  break;
case 2:	members_enter();
		  break;
case 3:	readp();
		   break;
case 4:	readm();
		 break;
case 5:	billing();
		 break;
case 6:	sales();
		break;
case 7:	modifyp();
		 break;
case 8:	modifym();
		break;
case 9:	instructions();
		break;
case 0:	l='n';
		}
	} while (l=='y');
	clrscr();
}
void products_enter()
{   int q=0;
	char l='y';
	pro1.open("products.dat",ios::in);
	pro1.seekg(0,ios::end);
	q=pro1.tellg()/sizeof(products_record);
	q+=1255;
	pro1.close();
	pro1.open("products.dat" ,ios::app);
do
	{clrscr();
		gotoxy(28,2);
		cout<<"ENTERING PRODUCT RECORDS ";
		gotoxy(15,6);
		cout<<"Name :";
		gets(ob1.name);
		if (!ob1.name[0])
			return;
		gotoxy(15,7);
		cout<<"Stock :";
		cin>>ob1.stock;
		gotoxy(15,8);
		cout<<"Rate (Rs.):";
		cin>>ob1.rate;
		ob1.no = q++;
		gotoxy(15,9);
		cout<<"Number :";
		cout<<ob1.no;
		pro1.write((char*)&ob1,sizeof(products_record));
		gotoxy(10,15);
		cout<<"Do you want to enter more (Y/N) ";
		cin>>l;
	} while (l=='y'||l=='Y');
	pro1.close();
}
products_record products_search(int no)
{fstream pro1;
	pro1.open("products.dat" ,ios::in||ios::nocreate);
	while(pro1)
	{pro1.read((char*)&ob1,sizeof(products_record));
		if (ob1.no==no)
			return ob1;
	}
	pro1.close();
	ob1.no=0;
	return ob1;
}
void products_modify(int no)
{ob2.no=0;
	pro1.open("products.dat",ios::in);
	pro2.open("product1.dat",ios::app);
	pro1.seekg(0,ios::beg);
	pro1.read((char*)&ob1,sizeof(products_record));
	while (!pro1.eof() )
	{if (ob1.no!=no )
			pro2.write((char*)&ob1,sizeof(products_record));
		else
			ob2=ob1;
		pro1.read((char*)&ob1,sizeof(products_record));
	}
	if (ob2.no)
	{gotoxy(13,7);
		cout<<"CURRENT RECORDS ARE ";
		gotoxy(15,8);
		cout<<"NAME :";
		puts(ob2.name);
		gotoxy(15,9);
		cout<<"RATE :(Rs.)";
		cout<<ob2.rate;
		gotoxy(15,10);
		cout<<"STOCK :";
		cout<<ob2.stock;
		gotoxy(13,12);
		cout<<"ENTER NEW PRODUCT RECORDS";
		gotoxy(15,13);
		cout<<"NAME :";
		ob1.no=ob2.no;
		gets(ob1.name);
		if (!isalnum(ob1.name[0]))
			strcpy(ob1.name,ob2.name);
		gotoxy(15,14);
		cout<<"RATE :(Rs.)";
		cin>>ob1.rate;
		if (!ob1.rate)
			 ob1.rate=ob2.rate;
		gotoxy(15,15);
		cout<<"STOCK :";
		cin>>ob1.stock;
		if (!ob1.stock)
			ob1.stock=ob2.stock;
		pro2.write((char*)&ob1,sizeof(products_record));
	}
	else
	{gotoxy(20,9);
		cout<<"NO ENTRY\a";
	}
	pro1.close();
	pro2.close();
	remove ("products.dat");
	rename ("product1.dat","products.dat");
}
void members_enter()
{int m;
	char l='y';
	mem1.open("members.dat",ios::in);
	mem1.seekg(0,ios::end);
	m=mem1.tellg()/sizeof(members_record);
	mem1.close();
	m+=10;
	clrscr();
	mem1.open("members.dat",ios::app);
	do
	{clrscr();
		gotoxy(28,2);
		cout<<"ENTERING MEMBER RECORDS ";
		gotoxy(15,6);
		cout<<"Name :";
		gets(m1.name);
		if (!m1.name[0])
			return;
		gotoxy(15,7);
		cout<<"Card number :";
		cin>>m1.card;
		gotoxy(15,8);
		cout<<"Address :";
		gets(m1.add);
		gotoxy(15,9);
		cout<<"Tel. :";
		cin>>m1.tel;
		gotoxy(15,10);
		cout<<"Amount Deposited (Rs.):";
		cin>>m1.amt;
		if (m1.amt<=100)
		{gotoxy(15,11);
			cout<<"Amount less\a";
			gotoxy(15,12);
			cout<<"Try Again";
			goto end;
		}
		m1.no = m++;
		gotoxy(15,11);
		cout<<"Membership number :";
		cout<<m1.no;
		mem1.write((char*)&m1,sizeof(members_record));
		end:
		gotoxy(10,15);
		cout<<"Do you want to enter more (Y/N) ";
		cin>>l;
	} while (l=='y'||l=='Y');
	mem1.close();
}
members_record members_search(int no)
{fstream mem2;
	mem2.open("members.dat",ios::in);
	while (mem2)
	{mem2.read((char*)&m1,sizeof(members_record));
		if (m1.no==no)
			return m1;
	}
	mem2.close();
	m1.no=0;
	return m1;
}
void members_modify(int no)
{m2.no=0;
	mem1.open("members.dat",ios::in);
	mem2.open("member1.dat",ios::app);
	mem1.seekg(0,ios::beg);
	mem1.read((char*)&m1,sizeof(members_record));
	while (!mem1.eof())
	{if (m1.no!=no)
			mem2.write((char*)&m1,sizeof(members_record));
		else
			m2=m1;
		mem1.read((char*)&m1,sizeof(members_record));
	}
	if (m2.no)
	{gotoxy(13,7);
		cout<<"CURRENT RECORDS ARE ";
		gotoxy(15,8);
		cout<<"NAME :";
		puts(m2.name);
		gotoxy(15,9);
		cout<<"CARD NUMBER :";
		cout<<m2.card;
		gotoxy(15,10);
		cout<<"ADDRESS :";
		puts(m2.add);
		gotoxy(15,11);
		cout<<"TELEPHONE :";
		cout<<m2.tel;
		gotoxy(15,12);
		cout<<"AMOUNT :(Rs.)";
		cout<<m2.amt;
		gotoxy(13,14);
		cout<<"ENTER NEW RECORDS";
		gotoxy(15,15);
		cout<<"NAME :";
		m1.no=m2.no;
		gets(m1.name);
		if (!m1.name[0])
			strcpy(m1.name,m2.name);
		gotoxy(15,16);
		cout<<"ADDRESS :";
		gets(m1.add);
		if (!m1.add[0])
			strcpy(m1.add,m2.add);
		gotoxy(15,17);
		cout<<"CARD NUMBER :";
		cin>>m1.card;
		if (!m1.card)
			m1.card=m2.card;
		gotoxy(15,18);
		cout<<"TELEPHONE :";
		cin>>m1.tel;
		if (!m1.tel)
			m1.tel=m2.tel;
		gotoxy(15,19);
		cout<<"AMOUNT ADDED :(Rs.)";
		cin>>m1.amt;
		m1.amt+=m2.amt;
		mem2.write((char*)&m1,sizeof(members_record));
	}
	else
	{gotoxy(20,10);
		cout<<"NO ENTRY\a";
	}
	mem1.close();
	mem2.close();
	remove ("members.dat");
	rename ("member1.dat","members.dat");
}
void readp()
{char l='y';
	do
	{clrscr();
		gotoxy(28,2);
		cout<<"VIEWING PRODUCT RECORDS ";
		gotoxy(15,6);
		cout<<"Enter product number:";
		int no;
		cin>>no;
		ob1=products_search(no);
		if (ob1.no)
		{gotoxy(18,9);
			cout<<"The record is";
			gotoxy(20,10);
			cout<<" Number :";
			cout<<ob1.no;
			gotoxy(20,11);
			cout<<" Stock :";
			cout<<ob1.stock;
			gotoxy(20,12);
			cout<<" Name : ";
			puts(ob1.name);
			gotoxy(20,13);
			cout<<" Rate :(Rs.)";
			cout<<ob1.rate;
		}
		else
		{gotoxy(20,10);
			cout<<"NO ENTRY \a";
		}
		gotoxy(15,16);
		cout<<"Any more records desired (Y/N)";
		cin>>l;
	} while (l=='y'||l=='Y');
}
void modifyp()
{char l='y';
	do
	{clrscr();
		gotoxy(25,2);
		cout<<"MODIFYING A PRODUCT RECORD";
		gotoxy(15,5);
		cout<<"Enter the product number:";
		int no;
		cin>>no;
		products_modify(no);
		gotoxy(13,20);
		cout<<"Any more modifications desired(Y/N)";
		cin>>l;
	} while (l=='y'||l=='Y');
}
void readm()
{char l='y';
	do
	{clrscr();
		gotoxy(25,2);
		cout<<"VIEWING A MEMBER'S RECORD ";
		gotoxy(15,6);
		cout<<"Enter membership number:";
		int no;
		cin>>no;
		m1=members_search(no);
		if (m1.no)
		{gotoxy(18,9);
			cout<<"The record is";
			gotoxy(20,10);
			cout<<"Number :";
			cout<<m1.no;
			gotoxy(20,11);
			cout<<"Name :";
			puts(m1.name);
			gotoxy(20,12);
			cout<<"Card number :";
			cout<<m1.card;
			gotoxy(20,13);
			cout<<"Address :";
			puts(m1.add);
			gotoxy(20,14);
			cout<<"Telephone :";
			cout<<m1.tel;
			gotoxy(20,15);
			cout<<"Amount :(Rs.)"<<m1.amt;
		}
		else
		{gotoxy(17,12);
			cout<<"NO ENTRY\a ";
		}
		gotoxy(15,18);
		cout<<"Any more records desired (Y/N)";
		cin>>l;
	} while (l=='y'||l=='Y');
}
void modifym()
{char l='y';
	do
	{clrscr();
		gotoxy(25,2);
		cout<<"MODIFYING MEMBER'S RECORDS ";
		gotoxy(15,5);
		cout<<"Enter the membership number:";
		int no;
		cin>>no;
		members_modify(no);
		gotoxy(13,22);
		cout<<"Any more modifications desired(Y/N)";
		cin>>l;
	} while (l=='y'||l=='Y');
}
void billing()
{clrscr();
	fstream b1;
	b1.open("sale.dat",ios::app);
	gotoxy(30,2);
	cout<<"BILLING ";
	gotoxy(15,7);
	cout<<"Are you a member(Y/N):";
	float less=1.0;
	char m;
	int no;
	long card;
	cin>>m;
	if (m=='y'||m=='Y')
	{gotoxy(18,9);
		cout<<"Enter membership number:";
		cin>>no;
		gotoxy(18,10);
		cout<<"Enter card number:";
		cin>>card;
		m1=members_search(no);
		if (card!=m1.card)
		{gotoxy(20,12);
			cout<<"Incorrect \a";
			getch();
			return;
		}
		else
		if (m1.amt>100)
		{less=0.95;
			m1.amt-=5;
		}
		else
		{gotoxy(20,12);
			cout<<"Amount Less\a";
			gotoxy(15,15);
			cout<<"Continue with normal billing(Y/N)";
			cin>>m;
			if (m=='n'||m=='n')
				return;
		}
		fstream t3,t4;
		t3.open("members.dat",ios::in);
		t4.open("member1.dat",ios::app);
		t3.seekg(0,ios::beg);
		t3.read((char*)&m2,sizeof(members_record));
		while (!t3.eof())
		{if (m2.no!=m1.no)
				t4.write((char*)&m2,sizeof(members_record));
			else
				t4.write((char*)&m1,sizeof(members_record));
			t3.read((char*)&m2,sizeof(members_record));
		}
		t3.close();
		t4.close();
		remove("members.dat");
		rename("member1.dat","members.dat");
	}
	clrscr();
	float total=0.0;
	gotoxy(60,1);
	cout<<"p.no.= 0:Exit Billing";
	gotoxy(30,1);
	cout<<"BILLING";
	i=0;
	void table1();
	beg:
	table1();
	gotoxy(4,6+i);
	cin>>n1.no;
	ob1=products_search(n1.no);
	gotoxy(56,6+i);
	float output1(products_record);
	if (n1.no>0)
	{if(ob1.no>0)
		{cin>>n1.qty;
			strcpy(n1.name,ob1.name);
			n1.rate=ob1.rate;
			n1.total=output1(ob1);
			total+=n1.total;
			fstream t3,t4;
			t3.open("sale.dat",ios::in);
			t4.open("sale1.dat",ios::app);
			t3.seekg(0,ios::beg);
			int qty=n1.qty;
			n1.qty=n1.total/n1.rate;
			char test='y';
			t3.read((char*)&n2,sizeof(tables));
			while (!t3.eof())
			{if (n1.no==n2.no)
				{n2.qty+=n1.qty;
					n2.total+=n1.total;
					test='n';
				}
				t4.write((char*)&n2,sizeof(tables));
				t3.read((char*)&n2,sizeof(tables));
			}
			if (test=='y')
			{t4.seekg(0,ios::end);
				t4.write((char*)&n1,sizeof(tables));
			}
			t3.close();
			t4.close();
			remove("sale.dat");
			rename("sale1.dat","sale.dat");
			n1.qty=qty;
			if (n1.total)
			{fstream temp3,temp4;
				temp3.open("products.dat",ios::in);
				temp4.open("product1.dat",ios::app);
				temp3.seekg(0,ios::beg);
				temp3.read((char*)&ob1,sizeof(products_record));
				while (!temp3.eof())
				{if (ob1.no==n1.no)
				ob1.stock-=n1.qty;
				temp4.write((char*)&ob1,sizeof(products_record));
				temp3.read((char*)&ob1,sizeof(products_record));
				}
				temp3.close();
				temp4.close();
				remove("products.dat");
				rename("product1.dat","products.dat");
			}
			i++;
			goto beg;
		}
		else
			if (ob1.no==0)
			{gotoxy(10,6+i);
				cout<<"No entry\a";
				i++;
				goto beg;
			}
	}
	else
		if (n1.no==0)
		{for (int j=0;j<81;j++)
			{gotoxy(j,6+i);
				cout<<"-";
			}
		}
		gotoxy(5,9+i);
		cout<<"Number of items = ";
		cout<<i;
		gotoxy(5,10+i);
		cout<<"Grand total = Rs.";
		cout<<total;
		if (less!=1)
		{discount+=0.05*total;
			gotoxy(5,12+i);
			cout<<"Discount = Rs.";
			cout<<0.05*total;
			gotoxy(5,13+i);
			cout<<"Net total = Rs.";
			cout<<less*total;
		}
		b1.close();
		getch();
}
float output1(products_record ob1)
{if (ob1.no==0)
	return 0;
	float stotal;
	stotal=ob1.rate*n1.qty;
	gotoxy(4,6+i);
	cout<<ob1.no;
	gotoxy(10,6+i);
	puts(ob1.name);
	gotoxy(38,6+i);
	cout<<ob1.rate;
	gotoxy(43,6+i);
	cout<<"     ";
	gotoxy(56,6+i);
	if (n1.qty>ob1.stock)
	{gotoxy(50,6+i);
		cout<<"Out of stock\a";
		return 0;
	}
	cout<<n1.qty;
	gotoxy(68,6+i);
	cout<<stotal;
	gotoxy(74,6+i);
	cout<<"      ";
	return stotal;
}
void table1()
{for (int a=1;a<=80;a++)
	{gotoxy(a,2);
		cout<<"_";
		gotoxy(a,5);
		cout<<"-";
	}
	for (a=3;a<=5;a++)
	{gotoxy(1,a);
		cout<<"|";
		gotoxy(9,a);
		cout<<"|";
		gotoxy(31,a);
		cout<<"|";
		gotoxy(49,a);
		cout<<"|";
		gotoxy(64,a);
		cout<<"|";
		gotoxy(80,a);
		cout<<"|";
	}
	gotoxy(1,6+i);
	cout<<"|";
	gotoxy(9,6+i);
	cout<<"|";
	gotoxy(31,6+i);
	cout<<"|";
	gotoxy(49,6+i);
	cout<<"|";
	gotoxy(64,6+i);
	cout<<"|";
	gotoxy(80,6+i);
	cout<<"|";
	gotoxy(2,3);
	cout<<"Product";
	gotoxy(14,3);
	cout<<"Product name ";
	gotoxy(35,3);
	cout<<"Rate (Rs.)";
	gotoxy(53,3);
	cout<<"Quantity";
	gotoxy(67,3);
	cout<<"Total (Rs.)";
	gotoxy(2,4);
	cout<<"number";
	gotoxy(53,4);
	cout<<"(Kgs/pcs)";
}
void sales()
{clrscr();
	gotoxy(28,1);
	cout<<"TODAY'S SALES";
	float sales=0.0;
	fstream sal1;
	sal1.open("sale.dat",ios::in);
	i=0;
	sal1.read((char*)&n1,sizeof(n1));
	while(!sal1.eof() && n2.no!=n1.no)
	{table1();
		gotoxy(4,6+i);
		cout<<n1.no;
		gotoxy(10,6+i);
		puts(n1.name);
		gotoxy(38,6+i);
		cout<<n1.rate;
		gotoxy(43,6+i);
		cout<<"     ";
		gotoxy(56,6+i);
		cout<<n1.qty;
		gotoxy(68,6+i);
		cout<<n1.total;
		sales+=n1.total;
		gotoxy(74,6+i);
		cout<<"     ";
		i++;
		n2.no=n1.no;
		sal1.read((char*)&n1,sizeof(n1));
	}
	gotoxy(1,6+i);
	for(int n=1;n<=80;n++)
		cout<<"-";
	gotoxy(5,8+i);
	cout<<"Grand total = Rs.";
	cout<<sales;
	gotoxy(5,10+i);
	cout<<"Discount = Rs.";
	cout<<discount;
	gotoxy(5,11+i);
	cout<<"Net total = Rs.";
	cout<<(sales-discount);
	getch();
}
void enter()
{clrscr();
	gotoxy(5,1);
	cout<<"Entering Records";
	gotoxy(5,6);
	cout<<"For Products";
	gotoxy(5,8);
	cout<<"This part of the program helps the store management to ";
	cout<<"add more";
	gotoxy(5,9);
	cout<<"products to their store. The existing product records are";
	cout<<" not ";
	gotoxy(5,10);
	cout<<"affected by this option. The new record(s) are appended at";
	cout<<" the end";
	gotoxy(5,11);
	cout<<"of the file containing such records namely ";
	cout<<"'products.dat'";
	cout<<". This";
	gotoxy(5,12);
cout<<"option automatically assigns a product number to the ";   cout<<"product";
	cout<<" which";
	gotoxy(5,13);
	cout<<"must be remembered for any product reference.";
	gotoxy(5,15);
	cout<<"For members";
	gotoxy(5,17);
cout<<"This option works just like its counterpart for products."; cout<<"It";
	cout<<" stores";
	gotoxy(5,18);
	cout<<"records in the file ";
	cout<<"'members.dat'";
	cout<<" and assigns a membership number ";
	gotoxy(5,19);
cout<<"for every new entry. For further details see the help"; cout<<" section";
	cout<<" on ";
	gotoxy(5,20);
	cout<<"'Membership Rules'.";
	getch();
}
void view()
{clrscr();
	gotoxy(30,5);
	cout<<"Viewing Records";
	gotoxy(10,7);
cout<<"This option enables the user to view the latest records";  cout<<" of ";
	gotoxy(10,8);
	cout<<"either products or members. It helps in operations like ";
	gotoxy(10,9);
	cout<<"stock checking and member verification. The viewing is";
	gotoxy(10,10);
	cout<<"only possible with the product/membership numbers.";
	getch();
}
void modify()
{clrscr();
	gotoxy(30,5);
	cout<<"Modifying Records";
	gotoxy(10,7);
	cout<<"This option helps in altering the records in the files.";
	gotoxy(10,8);
	cout<<"It can be used for deleting the entries as well. In ";
	gotoxy(10,9);
	cout<<"case of products either the record could be changed to";
	gotoxy(10,10);
cout<<"some new entry or its stock could be made zero. For";                        cout<<" members";
	gotoxy(10,11);
	cout<<"deletion is only possible by overwriting with a new entry.";
	getch();
}
void procedure()
{clrscr();
	gotoxy(30,5);
	cout<<"Billing Procedure";
	gotoxy(10,7);
	cout<<"The actual billing procedure consists of two sections.";
	gotoxy(10,8);
	cout<<"One checks if the buyer is a member or not and accordingly";
	gotoxy(10,9);
cout<<"performs the necessary tasks. The other section consists"; cout<<" of";
	gotoxy(10,10);
cout<<"billing. The user is asked to enter the product number ";  cout<<"and the ";
	gotoxy(10,11);
cout<<"quantity bought. The computer calculates the total itself "; cout<<"and ";
	gotoxy(10,12);
cout<<"also the discount if necessary. In order to exit the"; cout<<" procedure";
	gotoxy(10,13);
cout<<"and view the final total, the user should enter the"; cout<<" product number";
	gotoxy(10,14);
	cout<<"as '0'.";
	getch();
}
void rules()
{clrscr();
	gotoxy(30,5);
	cout<<"Membership Rules";
	gotoxy(5,7);
	cout<<"The program lets its subscribers (stores) maintain a";
	cout<<" member's list";
	gotoxy(5,8);
	cout<<"in order to help them in increasing their sales for a";
	cout<<" marginal cut";
	gotoxy(5,9);
	cout<<"in their profits. The program sets minimum membership ";
	cout<<"amount as Rs.100";
	gotoxy(5,10);
	cout<<"which must be paid at the time of registration. The member";
	cout<<" will be ";
	gotoxy(5,11);
	cout<<"given a membership number and a membership card (to be ";
	cout<<"collected ";
	gotoxy(5,12);
	cout<<"after a week by reference to the membership number and ";
	cout<<"other";
	gotoxy(5,13);
	cout<<" particulars). In case a member loses the membership card ";
	cout<<", he/she ";
	gotoxy(5,14);
	cout<<"must register a complaint with the store by submitting a";
	cout<<" written";
	gotoxy(5,15);
	cout<<"application with all the particulars. He/She can collect ";
	cout<<"his/her ";
	gotoxy(5,16);
	cout<<"remaining money by showing proofs of the particulars.";
	gotoxy(5,17);
	cout<<"The membership allows a person to avail a special discount";
	cout<<" of 5%";
	gotoxy(5,18);
	cout<<"over every purchase. Rs.5 will be subtracted from the ";
	cout<<"member's account";
	gotoxy(5,19);
	cout<<"over every purchase. The account will be rendered ";
	cout<<"inaccessible if the ";
	gotoxy(5,20);
	cout<<"amount will be less than Rs.100 and the member would be";
	cout<<" expected to ";
	gotoxy(5,21);
cout<<"deposit more money for continuing the membership. The"; cout<<" store";
	cout<<" will also";
	gotoxy(5,22);
cout<<"give away attractive gifts to a lucky member once every"; cout<<" year.";
	getch();
}
void today()
{
	clrscr();
	gotoxy(30,5);
	cout<<"Today's sales";
	gotoxy(10,7);
cout<<"This option shows the total sales in terms of both"; cout<<" quantity";
	gotoxy(10,8);
	cout<<"and amount per item. This is stored in a file namely ";
	gotoxy(10,9);
	cout<<"'sale.dat' which is modified after every buying during the";
	gotoxy(10,10);
	cout<<"billing process.";
	getch();
}
void instructions()
{clrscr();
	int n;
	char l='y';
	do
	{clrscr();
		gotoxy(30,5);
		cout<<"HELP INDEX";
		for (int z=29;z<=39;z++)
		{gotoxy(z,6);
			cout<<"-";
		}
		gotoxy(20,7);
		cout<<"1:ADD RECORDS";
		gotoxy(20,8);
		cout<<"2:VIEWING RECORDS ";
		gotoxy(20,9);
		cout<<"3:MODIFYING RECORDS";
		gotoxy(20,10);
		cout<<"4:BILLING PROCEDURE";
		gotoxy(20,11);
		cout<<"5:TODAY'S SALES ";
		gotoxy(20,12);
		cout<<"6:MEMBERSHIP DETAILS";
		gotoxy(20,13);
		cout<<"0:BACK TO MAIN MENU";
		gotoxy(21,16);
		cout<<"Enter your choice:";
		cin>>n;
		switch(n)
		{       case 1:	enter();
				break;
			case 2:	view();
				break;
			case 3:	modify();
				break;
			case 4:	procedure();
				break;
			case 5:	today();
				break;
			case 6:	rules();
				break;
			case 0:	l='n';
		}}while(l=='y');}