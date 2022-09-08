#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>

#define rad2deg(a) (((a)/3.1415926) * 180.0) 
#define deg2rad(a) (((a)/180.0) * 3.1415926) 


double sqrt(double x);
double cos(double x);


int main()
{
	char StrLine[256];           //存取字串
	char text[] = "<gx:coord>";  //比較之字串
	char xcoord[10] = { '\0' };     //存取座標
	char ycoord[10] = {'\0' };
	int term1 = 0;             
	int term2 = 0;
	int conf = 0;
	


	char StrLine2[256];
	char xxcoord[10] = { '\0' };
	char yycoord[10] = {'\0' };

	int nsample;
	printf("輸入座標數（約為所輸入數字之1/2,範圍100-1300) :");
	scanf("%d", &nsample);
	
	int textdistance;
	printf("輸入重合所定義之距離(正整數）:");
	scanf("%d", &textdistance);
	
	printf("\nyour route(x,y)            text route(x,y)          distance\n \n");

	FILE* pFile;
	FILE* qFile;


	pFile = fopen("myroute.kml", "r");  //開檔
	qFile = fopen("textroute.kml", "r");

	if (pFile == NULL || qFile == NULL)
		printf("開讀檔失敗!");

	else
	{


		for (int i = 0; i < nsample; i++)    //讀取kml檔案
		{
			fgets(StrLine, 128, pFile);  //讀取一行
			char* edf = strstr(StrLine, text); //是否為座標

			fgets(StrLine2, 128, qFile);  //讀取一行
			char* cdf = strstr(StrLine2, text); //是否為座標


			if (edf == NULL || cdf == NULL)  //非座標則回到for繼續讀檔
				continue;

			else
			{

				char x[10] = { 0 };    //暫時存字串，跳到上層for迴圈就會重新存取
				char y[10] = { 0 };
				char xx[10] = { 0 };
				char yy[10] = { 0 };



				for (int j = 0; j < 10; j++)   //取x值(經度)
				{
					x[j] = StrLine[14 + j];   //由kml得知x是從第14列開始往後約10位數
					xx[j] = StrLine2[14 + j];
				}


				for (int h = 0; h < 10; h++)  //存到外面陣列 for裡的會被洗掉
				{
					xcoord[h] = x[h];
					xxcoord[h] = xx[h]; 

				}



				for (int p = 0; p < 20; p++)  //找y開頭（1）y開頭前為空白一格
				{
					if (StrLine[14 + p] == ' ')
					{
						term1 = 15 + p;   //空白下一個(14+1+p)1是空白
						break;
					}
					else
						continue;
				}

				for (int q = 0; q < 20; q++)  //找y開頭（2）
				{
					if (StrLine2[14 + q] == ' ')
					{
						term2 = 15 + q;   //空白下一個
						break;
					}
					else
						continue;
				}



				for (int k = 0; k < 10; k++)  //取y值(緯度)
				{
					y[k] = StrLine[term1 + k];  //term1.term2為y的起始位置，由此往後取10位數
					yy[k] = StrLine2[term2 + k];

				}



				for (int m = 0; m < 10; m++)  //存到for外面
				{
					ycoord[m] = y[m];
					yycoord[m] = yy[m];
				}



			}

			//xcoord[9] = '\0';  //最後一個字元清掉避免亂碼
			//ycoord[9] = '\0';
			//xxcoord[9] = '\0';
			//yycoord[9] = '\0';
			
			

			double d1 = atof(xcoord);  //轉成double
			double d2 = atof(ycoord);
			double d3 = atof(xxcoord);
			double d4 = atof(yycoord);

			double earth_r = 6378.137;  //計算距離
			double laRe, loRe, NSD, EWD, distance;
			laRe = deg2rad(d4 - d2);
			loRe = deg2rad(d3 - d1);
			NSD = earth_r * laRe;
			EWD = cos(deg2rad(d2)) * earth_r * loRe;
			distance = sqrt(NSD*NSD + EWD*EWD);

			


			if (distance * 1000 < textdistance)
			{
                 printf("%s   %s      %s   %s    %lfm\n", xcoord, ycoord,xxcoord,yycoord,distance*1000);	
				conf += 1;  //確認是否有重疊
			}
			else
				continue;
				

		}

	}

	fclose(pFile);
	fclose(qFile);

  
       printf("\n\n");

       if(conf==0)
          printf("路線無重合\n");
       else
     
          printf("顯示之座標路線有重合\n");
          


	printf("\n\n");
	
	return 0;

}
