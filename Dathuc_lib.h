struct SOHANG{
		char text[15];
		char sign;
		float coe;
		int exp;
};

int kiemtrachuoi(char chuoi[]);
void xoakhoangtrang(char chuoi[]);
void format(char chuoi[]);
void themkhoangtrang(char chuoi[]);
void tachchuoi(char chuoi[],struct SOHANG SOHANGX[]);
int demsohang(struct SOHANG SOHANGX[]);
void phantichsohang(struct SOHANG SOHANGX[]);
void rutgondathuc(struct SOHANG SOHANGX[]);
void sapxepdathuc(struct SOHANG SOHANGX[]);
void xuatdathuc(struct SOHANG SOHANGX[]);
void congdathuc(struct SOHANG SOHANGX[], struct SOHANG SOHANGY[], struct SOHANG SOHANGT[]);
void hieudathuc(struct SOHANG SOHANGX[], struct SOHANG SOHANGY[], struct SOHANG SOHANGH[]);
void nhandonthuc(struct SOHANG SOHANGX, struct SOHANG SOHANGY, struct SOHANG *SOHANGT);
void tichdonthuc(struct SOHANG SOHANGX[], struct SOHANG SOHANGY, struct SOHANG SOHANGT[]);
void tichdathuc(struct SOHANG SOHANGX[], struct SOHANG SOHANGY[], struct SOHANG SOHANGT[]);
void chiadonthuc(struct SOHANG SOHANGX, struct SOHANG SOHANGY, struct SOHANG *SOHANGT);
void chiadathuc(struct SOHANG SOHANGX[], struct SOHANG SOHANGY[], struct SOHANG SOHANGT[], struct SOHANG SOHANGTH[]);
void gandathuc(struct SOHANG DATHUCA[], struct SOHANG DATHUCB[]);
