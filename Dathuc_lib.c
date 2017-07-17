#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Dathuc_lib.h"


//Kiem tra chuoi nhap vao co dung format khong
int kiemtrachuoi(char chuoi[]){
	int sbool=1, i, j;
	char test[]=" 0123456789+-^xX";
	//Kiem tra tung ky tu trong chuoi
	for (i=0;i<strlen(chuoi);i++){
		int ssbool=0;
		//Kiem tra ky tu thu i co dung format khong?
		for (j=0;j<16;j++){
			if (chuoi[i]==test[j]){
				ssbool=1;
				break;
			}		
		}
		if (!ssbool){
			return 0;
		}
	}
	return sbool;
}

void xoakhoangtrang(char chuoi[]){
	int i, j;
	for (i=0;i<strlen(chuoi);i++){
		if (chuoi[i]==' ') {
			for (j=i;j<strlen(chuoi);j++){
				chuoi[j]=chuoi[j+1];
			}
			i--;
		}
	}
}

void format(char chuoi[]){
	if (chuoi[0]=='+'){
		return;
	}
	if (chuoi[0]!='-'){
		int i, n=strlen(chuoi);
		for (i=n;i>=0;i--){
			chuoi[i+1]=chuoi[i];
		}
		chuoi[0]='+';
	}
}

void themkhoangtrang(char chuoi[]){
	int i, j;
	for (i=1;i<strlen(chuoi);i++){
		if (chuoi[i]=='+'||chuoi[i]=='-'){
			int n=strlen(chuoi);
			for (j=n;j>=i;j--){
				chuoi[j+1]=chuoi[j];
			}
			chuoi[i]=' ';
			i++;
		}
	}
}

void tachchuoi(char chuoi[],struct SOHANG SOHANGX[]){
    char *ch;
    int i=0;
    ch=strtok(chuoi," ");
    while (ch != NULL)
    {
    	strcpy(SOHANGX[i].text,ch);
    	i++;
    	ch=strtok(NULL," ");
    }
}

int demsohang(struct SOHANG SOHANGX[]){
	int i,dem=0;
	for (i=0;i<100;i++){
		if (SOHANGX[i].sign=='+'||SOHANGX[i].sign=='-'){
			dem+=1;
		}
	}
	return dem;
}

void phantichsohang(struct SOHANG SOHANGX[]){
	int i, n=100, dem=0;
	
	//Them thanh phan sign
	for (i=0;i<n;i++){
		if (SOHANGX[i].text[0]=='-'||SOHANGX[i].text[0]=='+'){
			SOHANGX[i].sign = SOHANGX[i].text[0];
			dem++;
		}else{
			break;
		}
	}
	
	//Them thanh phan coe
	for (i=0;i<dem;i++){
		if (SOHANGX[i].text[1]=='x' && SOHANGX[i].text[0]=='+'){
			SOHANGX[i].coe=1;
		}else{
			if (SOHANGX[i].text[1]=='x' && SOHANGX[i].text[0]=='-'){
				SOHANGX[i].coe=-1;
			}else{
				SOHANGX[i].coe=atoi(SOHANGX[i].text);
			}	
		}
	}
	
	//Them thanh phan exp
	for (i=0;i<dem;i++){
		int len=strlen(SOHANGX[i].text);
    	char *foundx = memchr((SOHANGX[i].text),'x',len);
    	char *found = memchr((SOHANGX[i].text),'^',len);
    	if(foundx && found){
    		int m=len-(found-SOHANGX[i].text)-1;
    		char text[15],exp[5];
    		strcpy(text,SOHANGX[i].text);
    		strrev(text);
            memcpy(exp,text,m);
            exp[m]='\0';
            strrev(exp);
            SOHANGX[i].exp=atoi(exp);
//			char text[15], eexp[5];
//			int exp;
//			strcpy(text,SOHANGX[i].text);
//			strrev(text);
//			exp=atoi(text);
//			itoa(exp,eexp,10);
//			strrev(eexp);
//			SOHANGX[i].exp=atoi(eexp);
	    }else{
	    	if(foundx && !found){
	    		SOHANGX[i].exp=1;
			}else{
				SOHANGX[i].exp=0;
			}
	    }
	}
}

void rutgondathuc(struct SOHANG SOHANGX[]){
	struct SOHANG RONG;
	struct SOHANG SOHANGY[100];
	int i, j, k=0, n=demsohang(SOHANGX);
	
	RONG.sign='\0';
	RONG.coe=0;
	RONG.exp=0;

	for (i=0;i<100;i++){
		SOHANGY[i]=RONG;
	}
	
	for (i=0;i<n;i++){
		if (SOHANGX[i].sign=='-' || SOHANGX[i].sign=='+'){
			SOHANGY[k]=SOHANGX[i];
			for (j=i+1;j<n;j++){
				if (SOHANGX[j].sign=='-' || SOHANGX[j].sign=='+'){
					if (SOHANGY[k].exp==SOHANGX[j].exp){
						SOHANGY[k].coe+=SOHANGX[j].coe;
						SOHANGX[j].sign='\0';
					}			
				}
			}
			k++;
		}
	}
	
	for (i=0;i<n;i++){
		SOHANGX[i]=RONG;
	}
	int m=demsohang(SOHANGY);
	for (i=0;i<m;i++){
		SOHANGX[i]=SOHANGY[i];
	}
	sapxepdathuc(SOHANGX);
}

void sapxepdathuc(struct SOHANG SOHANGX[]){
	struct 	SOHANG SOHANGK;
	int i, j, n=demsohang(SOHANGX);
	
	//Xoa nhung don thuc co heso=0
	for (i=0;i<n;i++){
		if (SOHANGX[i].coe==0){
			SOHANGX[i].sign='\0';
			SOHANGX[i].exp=0;	//exp=0 de thuan tien cho sap xep o duoi
		}
	}
	
	//Xoa don thuc rong trong da thuc, giong nhu xoa khoang trang trong 1 chuoi
	for (i=0;i<n;i++){
		if (SOHANGX[i].sign=='-' || SOHANGX[i].sign=='+'){
			continue;
		}else{
			for (j=i;j<=n;j++){
				SOHANGX[j]=SOHANGX[j+1];	
			}
		}
		i--;
		n--;
	}
	
	//Sap xep da thuc giam dan theo exp
	for (j=1;j<n;j++){
		for (i=0;i<n-1;i++){
			if (SOHANGX[i].sign=='-' || SOHANGX[i].sign=='+'){
				if (SOHANGX[i].exp<SOHANGX[i+1].exp){
					SOHANGK=SOHANGX[i];
					SOHANGX[i]=SOHANGX[i+1];
					SOHANGX[i+1]=SOHANGK;
				}	
			}
		}
	}
	
	if (!(SOHANGX[0].sign=='-'||SOHANGX[0].sign=='+')){
		SOHANGX[0].sign='+';
		SOHANGX[0].coe=0;
		SOHANGX[0].exp=0;
	}
}

void xuatdathuc(struct SOHANG SOHANGX[]){
	int i, n=demsohang(SOHANGX);
	
	if (SOHANGX[0].coe==0){
		printf("0");
		return;
	}
	
	for (i=0;i<n;i++){
		if (SOHANGX[i].sign=='-' || SOHANGX[i].sign=='+'){
			if (SOHANGX[i].coe<0){
				printf("-");
			}else{
				if (i!=0){
					printf("+");
				}
			}
			float tam=fabs(SOHANGX[i].coe);
			if (tam!=1){
				float z=floor(tam);
				if (tam-z==0){
					printf("%.f",tam);
				}else{
					printf("%.2f",tam);
				}
			}
			if (SOHANGX[i].exp==0){
				if (tam==1){
					printf("%.f",tam);
				}
			}else{
				if (SOHANGX[i].exp==1){
					printf("x");
					continue;
				}else{
					printf("x^%d",SOHANGX[i].exp);
				}
			}
		}
	}
}


void congdathuc(struct SOHANG SOHANGX[], struct SOHANG SOHANGY[], struct SOHANG SOHANGT[]){
	int i, lenx=demsohang(SOHANGX), leny=demsohang(SOHANGY);
	for (i=0;i<lenx;i++){
		SOHANGT[i]=SOHANGX[i];
	}
	for (i=0;i<leny;i++){
		SOHANGT[i+lenx]=SOHANGY[i];
	}
	rutgondathuc(SOHANGT);
}

void hieudathuc(struct SOHANG SOHANGX[], struct SOHANG SOHANGY[], struct SOHANG SOHANGH[]){
	struct SOHANG SOHANGK[100];
	int i, lenx=demsohang(SOHANGX), leny=demsohang(SOHANGY);
	for (i=0;i<lenx;i++){
		SOHANGH[i]=SOHANGX[i];
	}
	for (i=0;i<leny;i++){
		SOHANGK[i]=SOHANGY[i];
	}
	for (i=0;i<leny;i++){
		if (SOHANGY[i].sign='-'){
			SOHANGK[i].sign='+';
		}else{
			SOHANGK[i].sign='-';
		}
		if (SOHANGY[i].coe>0){
			SOHANGK[i].coe=(-1)*SOHANGY[i].coe;
		}else{
			SOHANGK[i].coe=fabs(SOHANGY[i].coe);
		}
	}
	for (i=0;i<leny;i++){
		SOHANGH[i+lenx]=SOHANGK[i];
	}
	rutgondathuc(SOHANGH);
}


void nhandonthuc(struct SOHANG SOHANGX, struct SOHANG SOHANGY, struct SOHANG *SOHANGT){
	struct SOHANG SOHANGK;
	SOHANGK=SOHANGX;
	SOHANGK.coe=SOHANGX.coe*SOHANGY.coe;
	SOHANGK.exp=SOHANGX.exp+SOHANGY.exp;
	if (SOHANGX.coe*SOHANGY.coe<0){
		SOHANGK.sign='-';
	}else{
		SOHANGK.sign='+';
	}
	*SOHANGT=SOHANGK;
}

void tichdonthuc(struct SOHANG SOHANGX[], struct SOHANG SOHANGY, struct SOHANG SOHANGT[]){
	int i, n=demsohang(SOHANGX);
	for (i=0;i<n;i++){
		nhandonthuc(SOHANGX[i],SOHANGY,&SOHANGT[i]);
	}
	rutgondathuc(SOHANGT);
}

void tichdathuc(struct SOHANG SOHANGX[], struct SOHANG SOHANGY[], struct SOHANG SOHANGT[]){
	int i, j, k=0, m=demsohang(SOHANGX), n=demsohang(SOHANGY);
	for (i=0;i<m;i++){
		for (j=0;j<n;j++){
			nhandonthuc(SOHANGX[i],SOHANGY[j],&SOHANGT[k]);
			k++;
		}
	}
	rutgondathuc(SOHANGT);
}

void chiadonthuc(struct SOHANG SOHANGX, struct SOHANG SOHANGY, struct SOHANG *SOHANGT){
	struct SOHANG SOHANGK;
	if (SOHANGX.exp>=SOHANGY.exp){
		SOHANGK=SOHANGX;
		SOHANGK.coe=SOHANGX.coe/SOHANGY.coe;
		SOHANGK.exp=SOHANGX.exp-SOHANGY.exp;
		*SOHANGT=SOHANGK;
	}else{
		SOHANGK=SOHANGX;
		SOHANGK.coe=0;
		SOHANGK.exp=0;
		*SOHANGT=SOHANGK;
	}
}

void chiadathuc(struct SOHANG SOHANGX[], struct SOHANG SOHANGY[], struct SOHANG SOHANGT[], struct SOHANG SOHANGTH[]){
	struct SOHANG THUONG[100], DU[100], TAM[50][100],  DATHUC[50][100];
	int k, m=demsohang(SOHANGX), n=demsohang(SOHANGY);
	int x=SOHANGX[0].exp, y=SOHANGY[0].exp;
	
	if (x<y){
		gandathuc(SOHANGTH,SOHANGX);
	}else{
		gandathuc(DATHUC[0],SOHANGX);
		chiadonthuc(SOHANGX[0],SOHANGY[0],&THUONG[0]);
		for (k=1;k<=x-y+1;k++){
			tichdonthuc(SOHANGY,THUONG[k-1],TAM[k-1]);
			hieudathuc(DATHUC[k-1],TAM[k-1],DATHUC[k]);
			chiadonthuc(DATHUC[k][0],SOHANGY[0],&THUONG[k]);
		}
		gandathuc(SOHANGT,THUONG);
		gandathuc(SOHANGTH,DATHUC[x-y+1]);
	}
	rutgondathuc(SOHANGT);
	rutgondathuc(SOHANGTH);
}


void gandathuc(struct SOHANG DATHUCA[], struct SOHANG DATHUCB[]){
	int i=0, m=demsohang(DATHUCB);
	while (i<m){
		DATHUCA[i]=DATHUCB[i];
		i++;
	}
}
