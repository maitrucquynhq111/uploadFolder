#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Dathuc_lib.h"

void main(){
	
	char DATHUCA[255], DATHUCB[255];
	struct SOHANG SOHANGA[100], SOHANGB[100], SOHANGT[100], SOHANGH[100], SOHANGN[100], SOHANGC[100], SOHANGTH[100], KIEMTRA[100];
	
	//Nhap da thuc 1
	do{
		printf("Nhap da thuc A: ");
		fflush(stdin);
		fgets(DATHUCA,255,stdin);
		int n=strlen(DATHUCA);
		DATHUCA[n-1]='\0';
		strlwr(DATHUCA);
	}
	while(!kiemtrachuoi(DATHUCA));
	
	//Nhap da thuc 2
	do{
		printf("Nhap da thuc B: ");
		fflush(stdin);
		fgets(DATHUCB,255,stdin);
		int n=strlen(DATHUCB);
		DATHUCB[n-1]='\0';
		strlwr(DATHUCB);
	}
	while(!kiemtrachuoi(DATHUCB));
	
	//Xoa khoang trang 2 chuoi
	xoakhoangtrang(DATHUCA);
	xoakhoangtrang(DATHUCB);
	
	//Them dau + cho ky tu dau tien trong chuoi
	format(DATHUCA);
	format(DATHUCB);
	
	//Them khoang trang ngan cach giua cac so hang
	themkhoangtrang(DATHUCA);
	themkhoangtrang(DATHUCB);
	
	//Tach tung so hang trong chuoi vao STRUCT
	tachchuoi(DATHUCA,SOHANGA);
	tachchuoi(DATHUCB,SOHANGB);
	
	//Them coe, sign, exp cho tung so hang
	phantichsohang(SOHANGA);
	phantichsohang(SOHANGB);

	//Rut gon da thuc
	rutgondathuc(SOHANGA);
	rutgondathuc(SOHANGB);
	
	printf("\nDa thuc A: ");
	xuatdathuc(SOHANGA);
	printf("\nDa thuc B: ");
	xuatdathuc(SOHANGB);
	
	//Cong da thuc
	congdathuc(SOHANGA,SOHANGB,SOHANGT);
	printf("\n\nTong: ");
	xuatdathuc(SOHANGT);
	
	//Tru da thuc
	hieudathuc(SOHANGA,SOHANGB,SOHANGH);
	printf("\nHieu: ");
	xuatdathuc(SOHANGH);
	
	//Nhan da thuc
	tichdathuc(SOHANGA,SOHANGB,SOHANGN);
	printf("\nTich: ");
	xuatdathuc(SOHANGN);
	
	//Chia da thuc
	if (SOHANGB[0].coe==0){
		printf("\nKhong chia duoc.");
	}else{
		chiadathuc(SOHANGA,SOHANGB,SOHANGC,SOHANGTH);
		printf("\nThuong: ");
		xuatdathuc(SOHANGC);
		if (SOHANGTH[0].coe!=0){
			printf("\nDu: ");
			xuatdathuc(SOHANGTH);
		}
	}
}
