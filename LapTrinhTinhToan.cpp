#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#define esp 1e-3
#define max 10

// Khai bao cau truc  Node
struct Node {
    float data;
    Node *next;
};
typedef struct Node *stack;

// Tao Node
struct Node *createNode(int data) {
	Node *p=(Node *) malloc(sizeof(Node));
    if (p == NULL) {
        return NULL;
    }
    p->data = data;
    p->next = NULL;
    return p;
}

// Khoi tao Stack rong
void setEmpty(stack s){ 
    s = NULL; 
}

// Kiem tra Stack rong
int  isEmpty(stack s) {
    return (s == NULL);
}

// Dua mot phan tu vao dinh cua Stack
void push(stack &s, int data) {
    Node *ptr = createNode(data);
    if (isEmpty(s)) {
        s = ptr;
    }
    else {
        ptr->next = s;
        s = ptr;
    }
}

// Lay mot phan tu ra khoi dinh cua Stack
int pop(stack &s) {
    if (!isEmpty(s)) {
        int data = s->data;
        s = s->next;
        return data;
    }
    else {
        printf("Stack rong\n");
    }
}

// Ham khoi tao Node head
stack InitHead(){
    stack head;
    head = NULL;
    return head;
}
stack Inputfile(int n,int i,FILE *fptr){
    stack head = InitHead();
    float x;
    	for(int j = 1;j <= n+1;j++){
            fscanf(fptr,"%f", &x);
            printf("%8.3f",x);
        	push(head, x);
        }
    return head;
}
void Output(stack head){
	stack p;
    for( p = head; p != NULL; p = p->next){
        printf("%8.3f", p->data);
    }
}
// Doc danh sach lien ket tu file
void Read_file(stack s[max],FILE *fptr,int *n1){
	int i,j,n;
	float x;
	fptr=fopen("DAYSO.IN","r");
	if(fptr == NULL)
	{
      printf("Error! Khong the mo File");   
      exit(1);             
   	}
    fscanf(fptr,"%d", &n);
    *n1=n;
    printf("\nCau a) Doc du lieu tu file'DAYSO.IN'");
    printf("\n------------------------------------");
    printf("\n\n\tN = %d\n",n);
    for(int i=1;i<=n;i++){
        printf("- Danh sach lien ket ngan xep thu %d:\t",i);	
	    s[i] = Inputfile(n,i,fptr);
	    printf("\n");
	}
	printf("\n Xuat danh sach lien ket:\n\n");
	for(i=1;i<=n;i++){
		printf("\t|");
		Output(s[i]);
		printf(" |\n");
	}
}
stack Input(int n,int i){
    stack head = InitHead();
    float x;
    	for(int j = 1;j <= n+1;j++){
            scanf("%f", &x);
        	push(head, x);
        }
    return head;
}
void EnterMatrix(stack s[],int *n1){
	int i,j,n;
	float x;
	printf("\n Mo rong! Nhap danh sach lien ket tu ban phim");
	printf("\n--------------------------------------------\n");
	printf("\n\tNhap N danh sach: ");
    scanf("%d", &n);
    *n1=n;
    for(int i=1;i<=n;i++){
    	printf("- Danh sach lien ket ngan xep thu %d:\t",i);	
           s[i] = Input(n,i); 
        }
	printf("\n Xuat danh sach lien ket:\n\n");
	for(i=1;i<=n;i++){
		printf("\t|");
		Output(s[i]);
		printf(" |\n");
	}
}
// Xoa phan tu khoi danh sach
void Delete(stack s[max],int n,int a)
{
	int i;
	printf("\n\t\tMa tran A\n\n");
	for(i=1;i<=n;i++)
	{
		if(a==1){
		    pop(s[i]);
		}    
		else{
			int b=2;
			stack p=s[i];
			while(b!=a){
				p=p->next;
				b++;
			}
			p->next=p->next->next;
		}
		printf("\t|");
		Output(s[i]);
		printf(" |\n");
	}
}
// Xuat danh sach sau khi xoa
void Output_file(stack head,FILE *fp)
{
	stack p;
    for( p = head; p != NULL; p = p->next)
	{
        fprintf(fp,"%8.3f", p->data);
    }
    fprintf(fp,"\n");
}
// Tim nghiem X cua he phuong trinh AX=B
void Enter(float *a, int n)
{ 
	int i;
	for (i=1; i<=n; i++) scanf("%f", a+i);
}
void Show(FILE *fptr,float a[], int n)
{
	fptr=fopen("RESULT2.OUT","w");
	int i;
	for (i=1; i<=n; i++) {
		printf("%10.3f\t", a[i]);
		fprintf(fptr,"%f\t",a[i]);
	}
	fclose(fptr);
}

int KtraHoitu(float a[][max],int n){
	float sum;
	int i,j;
	for(i=1;i<=n;i++){
		sum=0;
		for(j=1;j<=n;j++){
			if(j!=i) sum+=a[i][j];
		}
		if(fabs(a[i][i])<=sum) return 0;
	}
	return 1;
}
void  KtraKq(float a[][max],float b[],float x[],int n){
	float B[max],d;
	int i,j;
	printf("\n\n\tKiem tra lai ket qua :\n\n");
	for(i=1;i<=n;i++)
	{	
		for(j=1;j<=n;j++){
			B[i]=a[i][j]*x[j] + B[i];
			printf("(%f x %f)",a[i][j],x[j]);
			if(j<n) printf(" + ");
		}
		d=b[i]-B[i];
		printf(" - (%f) = %f\n\n",b[i],d);
	}
}
void Gauss_Seidel(FILE *fptr,stack s[],int n){
	float a[max][max],b[max],x[max],y[max],temp;
	int  i, j, lap, dem;
	printf("\nCau c) Tim nghiem X cua he phuong trinh AX=B bang phuong phap Gauss_Seidel");
	printf("\n---------------------------------------------------------------------------\n");
	for(i=1;i<=n;i++)
	{
		stack p = s[i];
		{
			for(j=1;j<=n;j++)
			{
				if(p!=NULL)
				{
					a[i][j]=p->data;
					p=p->next;
				}
			}
		}
	}
	printf("\n\tNhap ma tran B:\n");
	for(i=1;i<=n;i++)
	{
		printf(" b[%d] = ",i);
		scanf("%f",&b[i]);
	}
	printf("\n\tMa tran B vua nhap:\n\n");
	for(i=1;i<=n;i++)
	{
		printf("\t%8.3f\n",b[i]);
	}
	printf("\n");	
	printf("\tTa co he phuong trinh AX = B\n\n");
	for(i=1;i<=n;i++){
		printf("\t|");
		for(j=1;j<=n;j++){
			printf("%8.3f ",a[i][j]);
		}
		printf("|\t");
		printf("|x[%d]|\t",i);
		printf("|%8.3f |\n",b[i]);
	}
	if(KtraHoitu(a,n)==0)
	{
		printf("\n\tHe phuong trinh khong hoi tu!");
		return ;
	}	
	printf("\n\tNhap nghiem ban dau : ");
	Enter(x, n);
	dem = 0;
	do
	{	
		lap=0;dem++;
		printf("\n\n\t\t-Lan lap thu %2d:",dem);
		for(i=1; i<=n; i++)
		{
			float s=0;
			for (j=1; j<=n; j++)
			{
				if (j!=i) s+=a[i][j]*x[j];
			}	
			temp = (b[i] - s)/a[i][i];
			if (fabs(x[i]-temp)>esp && dem<30) lap=1;
			x[i] = temp;
			printf("\tx[%d]=%f",i,x[i]);
			}
	}
	while (lap);
	if (dem<30)
		{	
			printf("\n\n\tNghiem cua he phuong trinh : X = ( ");
			Show(fptr,x,n);
			printf(" )");
			KtraKq(a,b,x,n);
		}
	else printf("\n\n\tHe phuong trinh khong giai duoc bang phuong phap Gauss_Seidel");
}
int main()
{
	FILE *fptr, *fp;
 	stack s[max];
 	int i, n, c;
	char a;
	printf("\n==================================================================================================================\n");
	printf("||DO AN 321: SU DUNG CAC THAO TAC LAM VIEC VOI DANH SACH LIEN KET KIEU STACK VA FILE DE GIAI  TRIDIAGONAL MATRIX||");
	printf("\n==================================================================================================================\n");
 	while(a!='k'&&a!='f'){
 		printf("\n\t==========================================================\n");
 		printf("\t|| Nhan phim 'k' de nhap danh sach lien ket tu ban phim ||");
 		printf("\n\t|| Nhan phim 'f' de lay danh sach lien ket tu file\t||");
 		printf("\n\t==========================================================\n");
 		a=getch();
	}
 	if(a=='k') EnterMatrix(s,&n);
  	if (a=='f')Read_file(s,fptr,&n);
	printf("\nCau b) Xoa bot moi danh sach mot phan tu:");
	printf("\n-----------------------------------------\n");
	do {
		printf("\n Nhap cot muon xoa (cot <= %d): ",n+1); 
		scanf("%d",&c);
	}
	while (c>n+1);
	Delete(s,n,c);
	fp=fopen("RESULT1.OUT","w");
	for(i=1;i<=n;i++)
	{
		Output_file(s[i],fp);
	}		
	fclose(fp);
	Gauss_Seidel(fptr,s,n);
	return 0;
}
