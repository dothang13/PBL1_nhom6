#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const long long MAX = 100;

FILE *f1, *f2, *f3;
char nf1[100], nf2[100];

void file_matran(char nf[100], FILE **f) // kiem tra ten file hop le hay khong
{
	fgets(nf, MAX, stdin);
    nf[strcspn(nf, "\n")] = '\0';
    *f = fopen(nf, "r");
    if (*f == NULL) {
        printf("Loi mo file !\n");
        exit(1);
    }
}

void mo_file() { // mo file: file ma tran A, ma tran B, va file xuat ket qua
    printf("Nhap ten file ma tran A: ");
    file_matran(nf1,&f1);
    printf("Nhap ten file ma tran B: ");
	file_matran(nf2,&f2);
    f3 = fopen("file3.txt", "w");
}

void nhap(FILE *f, int *n, int *m, float a[][MAX]) {
    if (fscanf(f, "%d %d", n, m) != 2 || *n <= 0 || *m <= 0) {
        printf("Loi dinh dang ma tran!\n");
        exit(0);
    }

    int i, j;
    for (i = 0; i < *n; i++) {
        for (j = 0; j < *m; j++) {
            if (fscanf(f, "%f", &a[i][j]) != 1) {
                printf("Loi dinh dang ma tran!\n");
                exit(0);
            }
        }
    }
    if (fgetc(f) != EOF) {
        printf("Loi dinh dang ma tran!\n");
        exit(0);
    }
}


void xuat(FILE *f, int n,int m, float a[][MAX]) { // xuat file
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            fprintf(f, "%10.2f ", a[i][j]);
        }
        fprintf(f, "\n");
    }
}

void output(int n, int m, float a[][MAX]){ // xuat ra may tinh
	int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%10.2f ", a[i][j]);
        }
        printf("\n");
    }
}

void trong() {
    fprintf(f3, "--------------------------\n");
}

void trongg(){
	printf("--------------------------\n");
}


int check_tong(int n1, int m1, int n2, int m2)
{
	if ((n1 == n2) && (m1 == m2)) return 1;
	else return 0;
}

int check_tich(int m1, int n2)
{
	if ( m1 == n2 ) return 1;
	else return 0;
}

void tinh_tich(int n1, int m1, int n2, int m2, float a[][MAX], float b[][MAX], float tich[][MAX]) {
    int i, j, k;
    for (i = 0; i < n1; i++) {
        for (j = 0; j < m2; j++) {
            for (k = 0; k < m1; k++) {
                tich[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    fprintf(f3, "Tich cua ma tran A va ma tran B la: \n");
    xuat(f3, n1,m2, tich);
    trong();
    printf("Tich cua ma tran A va ma tran B la: \n");
    output(n1,m2,tich);
    trongg();
}

void tinh_tong(int n1, int m1, int n2, int m2, float a[][MAX], float b[][MAX], float tong[][MAX]) {
    int i, j;
    for (i = 0; i < n1; i++) {
        for (j = 0; j < m1; j++) tong[i][j] = a[i][j] + b[i][j];
    }
    fprintf(f3, "Tong cua ma tran A va ma tran B la: \n");
    xuat(f3, n1, m1, tong);
    trong();
    printf("Tong cua ma tran A va ma tran B la: \n");
    output(n1, m1,tong);
    trongg();
}

void swap(int p, int q, float a[][MAX], int n , int m) { // n cua ma tran A, m cua ma tran B
    int tam;
    int i;
    for (i = 0; i < n; i++)
	{
		tam = a[i][p];
		a[i][p] = a[i][q];
		a[i][q] = tam;
	}
    fprintf(f3, "Ma tran tich sau khi hoan doi hai cot %d va %d la: \n", p, q);
    xuat(f3, n, m, a);
    trongg();
    printf("Ma tran tich sau khi hoan doi hai cot %d va %d la: \n", p, q);
    output(n, m, a);
}

void xuli_tong(int n1, int m1, int n2, int m2, float a[][MAX], float b[][MAX], float tong[][MAX])
{
	if (check_tong(n1, m1, n2, m2)) tinh_tong(n1, m1, n2 , m2, a, b, tong);
	else
	{
		printf("Khong the tinh tong vi kich thuoc hai ma tran khong bang nhau!!\n");
		trongg();
		fprintf(f3,"Khong the tinh tong vi kich thuoc hai ma tran khong bang nhau!!\n");
		trong();
	}
	
}

void xuli_tich(int n1, int m1, int n2, int m2, float a[][MAX], float b[][MAX], float tich[][MAX])
{
	if (check_tich(m1,n2)) tinh_tich(n1, m1, n2 , m2, a, b, tich);
	else
	{
		printf("Khong the tinh tich vi so cot cua A khong bang so hang cua B!!\n");
		fprintf(f3,"Khong the tinh tich vi so cot cua A khong bang so hang cua B!!\n");
		fclose(f3);
		exit(2);
	}
}

void doi_cot(int n1, int m2, float tich[][MAX])
{
	int p,q;
	printf("Nhap hai cot cua ma tran tich muon doi cot (chi so bat dau tu 0 va nho hon %d): \n",m2);
    int d = 0; // so lan nhap
    do
    {
	    scanf("%d", &p);
	    scanf("%d", &q);
	    if (p>=m2 || q>=m2 || p<0 || q<0)
		{
			printf("Ban da nhap it nhat mot cot khong ton tai\n");
			d+=1;
			if (d==3)
			{
				fprintf(f3,"Hai cot cua ma tran tich ban muon hoan doi khong ton tai!\n");
				fprintf(f3,"Va ban da nhap sai du lieu 3 lan. Chuong trinh dung lai!!!\n");
				printf("Ban da nhap sai du lieu 3 lan. Chuong trinh dung lai!!!\n");
				break;
			}
		}
	    else swap(p, q, tich, n1, m2);
	} while (p>=m2 || q>=m2 || p<0 || q<0);
}
int main() {

	int n1,m1,n2,m2;
    float a[MAX][MAX], b[MAX][MAX], tich[MAX][MAX], tong[MAX][MAX];
    int i, j, k;

    mo_file();


    nhap(f1, &n1, &m1, a);
    nhap(f2, &n2, &m2, b);
    
    trongg();
	fprintf(f3,"Xuat ma tran A ra file: \n");
	xuat(f3, n1, m1, a);
	trong();
	printf("Xuat ma tran A ra may tinh: \n");	
	output(n1, m1, a);
	trongg();
	
	fprintf(f3,"Xuat ma tran B ra file: \n");
	xuat(f3, n2, m2, b);
	trong();
	printf("Xuat ma tran B ra may tinh: \n");	
	output(n2, m2, b);
	trongg();
	
	// kiem tra hai ma tran co cung kich thuoc khong?
	
	xuli_tong(n1, m1, n2, m2, a, b, tong);
	
	xuli_tich(n1, m1, n2, m2, a, b, tich);
    
	printf("\n");
    
	doi_cot(n1, m2, tich);
    
    fclose(f3);
}

