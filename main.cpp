#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

int a[20][20],v[20],d[20],ans[20],n,color=1,radius = 150; 
double angle,x_1,x_2,y_1,y_2;
int Introduce();
int Fileread();

void Degree();
void Sort();
void Paint();
void Delete();
void Check();
void Out();

void Graphics();
void draw_line(double x11, double y11, double x22, double y22);
void draw_vertex();
// -----------------------------------------------------------------Console 1
int main(){
	if (Introduce()!=1) return 0;
    if (Fileread()!=1) return 0;
    char sign;
    printf("Day la do thi ma ban muon to mau?\n");
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=n;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	printf("Nhap y de tiep tuc, nhap n de dung chuong trinh.\n");
	while (sign!='y' && sign!='n') {
		sign = getchar();
	}	
	if (sign=='n') return 0;
	Degree();
    Sort();
    Paint();
    Graphics();
    return 0;
}

int Introduce(){
	FILE *in;
	in=fopen("Introduce.txt","r");
	char c;
   	if(in==NULL){
           printf("KHONG THE MO FILE!\n");
           return 0;}
    else{
        do{
        	c=fgetc(in);
        	printf("%c",c);
		}
		while(c!=EOF);
        fclose(in);	
    }	
    getchar();
    return 1;
}
int Fileread(){ //lay du lieu tu file de tao mang a[][]
    FILE *in;
    in=fopen("dothi.txt","r");
    if(in==NULL){
           printf("KHONG THE MO FILE!\n");
           return 0;}
    else{
        fscanf(in,"%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) fscanf(in,"%d",&a[i][j]);
        }
        fclose(in);
    }
    return 1;
}
void Degree(){
    for(int i=1;i<=n;i++){ //xet ma tran a[][] neu hang i co "count" so 1 -> bac cua dinh i la "count"
        int count=0;
        for(int j=1;j<=n;j++){
            if(a[i][j]==1) count++;
        }
        d[i]=count;
    }
}
void Sort(){ //sap xep mang dinh v[] theo thu tu giam dan ve bac
    for(int i=1;i<=n;i++){ //tao mang dinh
        v[i]=i;
    }
    for(int i=1;i<=n-1;i++){
        int max=i;
        for(int j=i+1;j<=n;j++){
            if(d[v[max]]<d[v[j]]) max=j;
        }
        int temp=v[i];
        v[i]=v[max];
        v[max]=temp;
    }
}
void Paint(){
    int m=2;
    ans[v[1]]=color;
    while(v[m]){
        if(a[v[1]][v[m]]==0){ //neu khong ke dinh thi to mau
            ans[v[m]]=color;
        }
        m++;
    }
    Check();
}
void Check(){
	bool stop;
    for(int i=1;i<=n;i++){
    	if(ans[i]==0){
			stop=1;
			break;
		}
    }
    if(stop==1) Delete();
    else Out();	
}
void Delete(){
	for(int i=1;i<=n;i++){
		if(ans[v[i]]==color){
			for(int j=i;j<=n;j++){
				v[j]=v[j+1];
			}
		}
	}
    color++;
    Paint();
}
void Out(){
	printf("Do thi da su dung %d mau de to:\n",color);
	for(int i=1;i<=n;i++){
            printf(" + Dinh %d: mau %d\n",i,ans[i]);
        }
}
// -------------------------------------------------------- Console 2
void Graphics(){
	int i,j;
    initwindow(600,500);
    angle = 6.283185/n;
    for(i=1;i<=n;i++){
    	for(j=1;j<=n;j++){
    		if (a[i][j]==1 && j>i){
				draw_line(280+cos(angle*(i-1))*radius, 200-sin(angle*(i-1))*radius,280+cos(angle*(j-1))*radius, 200-sin(angle*(j-1))*radius);
				line(x_1,y_1,x_2,y_2);
			}
			
		}
	}
	draw_vertex();
	getch();
}
void draw_line(double x11, double y11, double x22, double y22){
	double angel, vector_x, vector_y;
	vector_x=x22-x11;
	vector_y=y22-y11;
	if (vector_x<0) angel = 3.141593+atan(vector_y/vector_x);
	else angel = atan(vector_y/vector_x);
	x_1=x11+cos(angel)*19;
	y_1=y11+sin(angel)*19;
	x_2=x22-cos(angel)*19;
	y_2=y22-sin(angel)*19;
}
void draw_vertex(){
    for(int i=1;i<=n;i++){
    	setfillstyle(USER_FILL, ans[i]);//fill color
		circle(280+cos(angle*(i-1))*radius, 200-sin(angle*(i-1))*radius, 20);//ve hinh tron
		floodfill(280+cos(angle*(i-1))*radius+1, 200-sin(angle*(i-1))*radius+1,15);//enclosed area, vi mac dinh circle ve ra la mau trang nen chon 15
		settextstyle(3,0,1);
		char vertexnum[10];
		sprintf(vertexnum,"Dinh %d",i);//noi chuoi
		outtextxy(280+cos(angle*(i-1))*radius-26, 200-sin(angle*(i-1))*radius+20,vertexnum); 
	}
}
