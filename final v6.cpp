// FCAI – Programming 1 – 2022 - Assignment 3 - Part 2
// Program Name: task 1 ass3.cpp / creating  image filters
// Program Description: creating a menu for displaying filters and a function for each filters
// Last Modification Date: 22/4/2022
// Author  and ID and Group: Mariam Moutaz Mohamed / id:20210386
// Author  and ID and Group: Ganna Ahmed Abd El-Naby Silem / id:20210102
// Author  and ID and Group: Yassin Yasser Ahmed Abd EL- sadek / id:20210451
// Teaching Assistant: xxxxx xxxxx
// Purpose:creating a photoshop editior



#include <iostream>
#include<fstream>
#include<string.h>
#include<cmath>
#include "bmplib.h"
#include"bmplib.cpp"
using namespace std;
unsigned char btm_image[SIZE][SIZE];
unsigned char zoom [SIZE][SIZE];
unsigned char zoomimage [SIZE][SIZE];
unsigned char image1 [SIZE][SIZE];

unsigned char first_image[SIZE][SIZE];
unsigned char second_image[SIZE][SIZE];
unsigned char finalresult[SIZE][SIZE];






void load_twoimages()
{       //loading the second image and put it to second_image array
        char secimage_name[100];
		cout << "Please enter the second image name to merge with:";
		cin >> secimage_name;

		strcat(secimage_name, ".bmp");
		readGSBMP(secimage_name, second_image);

}


void load_image()
{   //loading the first image and put it to first image array
	char image1_name[100];
	char secimage_name[100];
	cout << "Please enter the first image name :";
		cin >> image1_name;

		strcat(image1_name, ".bmp");
		readGSBMP(image1_name, first_image);
}

void merge_filter()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
		    //getting the average of the corresponding pixels of two images and put them into finalresult
			finalresult[i][j] = int((first_image[i][j] + second_image[i][j]) / 2);

		}

    }

}


void blur_filter()
{
    int row_last,row_begin,col_begin,col_last,sum,counter;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {   // get a four ranges to access all the neighbourhood pixels then creating a nested loops
            row_begin=i-1;
            row_last=i+1;
            col_begin=j-1;
            col_last=j+1;
            if(row_begin==-1)
            {
              row_begin=0;
            }
            if(col_begin==-1)
            {
              col_begin=0;
            }
            if(row_last>SIZE)
            {
               row_last=j;
            }
            if(col_last>SIZE)
            {
               col_last=j;
            }
            counter=0;sum=0;
            //obtain the sum of the elements  and set a counter to count their number
            for(int k=row_begin;k<=row_last;k++)
            {
                for(int y=col_begin;y<=col_last;y++)
                {
                    sum=sum+first_image[k][y];
                    counter++;
                }
            }
            finalresult[i][j]=int(sum/counter);
        }

    }

}



void edge_filter()
{
    int row_last,row_begin,col_begin,col_last,sum,counter,pixdef;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {   // get a four ranges to access all the neighbourhood pixels then creating a nested loops
            row_begin=i-1;
            row_last=i+1;
            col_begin=j-1;
            col_last=j+1;
            if(row_begin==-1)
            {
              row_begin=0;
            }
            if(col_begin==-1)
            {
              col_begin=0;
            }
            if(row_last>SIZE)
            {
               row_last=j;
            }
            if(col_last>SIZE)
            {
               col_last=j;
            }

             for(int k=row_begin;k<=row_last;k++)
            {
                for(int y=col_begin;y<=col_last;y++)
                {
                    pixdef=abs(int(first_image[k][y]-first_image[i][j]));
                   if( pixdef>20)
                   {
                       finalresult[i][j]=0;
                   }
                    else
                    {
                        finalresult[i][j]=255;
                    }
                }
            }
            pixdef=0;
        }

    }

}

void light_image()
{
     //in each iteration subtract the number of coloumn from actual size
     int light_value;

     for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			light_value=(first_image[i][j]+255)/2;
			finalresult[i][j] =  light_value ;

		}

    }

}

void dark_image()
{
     //in each iteration subtract the number of coloumn from actual size
     int dark_value;

     for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			dark_value=first_image[i][j]/2;
			finalresult[i][j] =  dark_value ;

		}

    }

}

void flipimageh()
{
     //in each iteration subtract the number of coloumn from actual size
     for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			finalresult[i][SIZE-j] =  first_image[i][j] ;

		}

    }

}

void flipimagev()
{
    //in each iteration subtract the number of row from the actual size
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			finalresult[SIZE-i][ j] =  first_image[i][j] ;

		}

    }

}



void bwimage()
{

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (first_image[i][j]<=125)
            {


			finalresult[i][j] =  0 ;
            }
            else {
                finalresult[i][j] =  255 ;
            }
		}

    }

}
void invert_image_filter(){

    for(int row=0;row<SIZE;row++){
       for (int colum=0;colum<SIZE;colum++){
            //to make negative image
            finalresult[row][colum]=255-first_image[row][colum];

        }
   }

}
void first_quarimage(){
    //this function for the first quarter image
    //user will use no.quarter which put this quarter
    int no_quar;
    cout<<"enter quarter number which you want q1 : "<<endl;
    cin>>no_quar;
    if(no_quar==1){
          for (int i=0;i<SIZE/2;i++){
             for (int j=0;j<SIZE/2;j++){
                finalresult[i][j]=btm_image[i][j];
             }
          }

    }else if (no_quar==2){

         for (int i=0;i<SIZE/2;i++){
             for (int j=128;j<SIZE;j++){
                finalresult[i][j]=btm_image[i][j-SIZE/2];
             }
          }


    }else if (no_quar==3){
        for (int i=128;i<SIZE;i++){
             for (int j=0;j<SIZE/2;j++){
                finalresult[i][j]=btm_image[i-SIZE/2][j];
             }
          }
    }
    else if (no_quar==4){
        for (int i=128;i<SIZE;i++){
             for (int j=128;j<SIZE;j++){
                finalresult[i][j]=btm_image[i-SIZE/2][j-SIZE/2];
             }
          }
    }
}
void second_quarimage(){
     int no_quar;
    cout<<"enter quarter number which you want q2 : "<<endl;
    cin>>no_quar;
    if(no_quar==1){
          for (int i=0;i<SIZE/2;i++){
             for (int j=0;j<SIZE/2;j++){
                finalresult[i][j]=btm_image[i][j+SIZE/2];
             }
          }
    }else if (no_quar==2){
         for (int i=0;i<SIZE/2;i++){
             for (int j=128;j<SIZE;j++){
                finalresult[i][j]=btm_image[i][j];
             }
          }
    }else if (no_quar==3){
         for (int i=128;i<SIZE;i++){
             for (int j=0;j<SIZE/2;j++){
                finalresult[i][j]=btm_image[i-SIZE/2][j+SIZE/2];
             }
          }
    }else if (no_quar==4){
         for (int i=128;i<SIZE;i++){
             for (int j=128;j<SIZE;j++){
               finalresult[i][j]=btm_image[i-SIZE/2][j];
             }
          }
    }


}
void third_quarimage(){
     int no_quar;
    cout<<"enter quarter number which you want q3 : "<<endl;
    cin>>no_quar;
    if(no_quar==1){
          for (int i=0;i<SIZE/2;i++){
             for (int j=0;j<SIZE/2;j++){
                finalresult[i][j]=btm_image[i+SIZE/2][j];
             }
          }
    }else if(no_quar==2){
         for (int i=0;i<SIZE/2;i++){
             for (int j=128;j<SIZE;j++){
                finalresult[i][j]=btm_image[i+SIZE/2][j-SIZE/2];
             }
          }
    }else if(no_quar==3){
         for (int i=128;i<SIZE;i++){
             for (int j=0;j<SIZE/2;j++){
                finalresult[i][j]=btm_image[i][j];
             }
          }
    }else if(no_quar==4){
         for (int i=128;i<SIZE;i++){
             for (int j=128;j<SIZE;j++){
                finalresult[i][j]=btm_image[i][j-SIZE/2];
             }
          }
    }


}
void fourth_quarimage(){
      int no_quar;
    cout<<"enter quarter number which you want q4 : "<<endl;
    cin>>no_quar;
    if(no_quar==1){
          for (int i=0;i<SIZE/2;i++){
             for (int j=0;j<SIZE/2;j++){
                finalresult[i][j]=btm_image[i+SIZE/2][j+SIZE/2];
             }
          }
    }else if(no_quar==2){
         for (int i=0;i<SIZE/2;i++){
             for (int j=128;j<SIZE;j++){
                finalresult[i][j]=btm_image[i+SIZE/2][j];
             }
          }
    }else if(no_quar==3){
         for (int i=128;i<SIZE;i++){
             for (int j=0;j<SIZE/2;j++){
                finalresult[i][j]=btm_image[i][j+SIZE/2];
             }
          }
    }else if(no_quar==4){
         for (int i=128;i<SIZE;i++){
             for (int j=128;j<SIZE;j++){
               finalresult[i][j]=btm_image[i][j];
             }
          }
    }
}
void shuffle_image(){
     first_quarimage();
    second_quarimage();
    third_quarimage();
    fourth_quarimage();


}

void enlarge_image() {
    int choices;
    cout << "enter quarter number(1,2,3,4): " << endl;
    cin >> choices;
    if (choices == 1) {
        for (int row = 0; row < SIZE / 2; row++) {
            for (int colum = 0; colum < SIZE / 2; colum++) {
                btm_image[row][colum] = btm_image[row][colum];


            }
        }
        for (int row = 0; row < SIZE / 2; row++) {
            for (int colum = 0; colum < SIZE / 2; colum++) {
                zoom[row][colum] = btm_image[row][colum];
            }
        }
        for (int i = 0, row = 0; row < SIZE; row += 2, i++) {
            for (int n = 0, colum = 0; colum < SIZE; colum += 2, n++) {
                zoomimage[row][colum] = zoom[i][n];
                zoomimage[row + 1][colum] = zoom[i][n];
                zoomimage[row][colum + 1] = zoom[i][n];
                zoomimage[row + 1][colum + 1] = zoom[i][n];
            }
        }
    }
    if (choices == 2) {
        for (int row = 0; row < SIZE / 2; row++) {
            for (int colum = 0; colum < SIZE / 2; colum++) {
                btm_image[row][colum] = btm_image[row][colum];


            }
        }
        for (int row = 0; row < SIZE / 2; row++) {
            for (int colum = 0; colum < SIZE / 2; colum++) {
                zoom[row][colum] = btm_image[row][colum + SIZE / 2];
            }
        }
        for (int i = 0, row = 0; row < SIZE; row += 2, i++) {
            for (int n = 0, colum = 0; colum < SIZE; colum += 2, n++) {
                zoomimage[row][colum] = zoom[i][n];
                zoomimage[row + 1][colum] = zoom[i][n];
                zoomimage[row][colum + 1] = zoom[i][n];
                zoomimage[row + 1][colum + 1] = zoom[i][n];
            }
        }

    }
    if (choices == 3) {
        for (int row = 0; row < SIZE / 2; row++) {
            for (int colum = 0; colum < SIZE / 2; colum++) {
                btm_image[row][colum] = btm_image[row][colum];


            }
        }
        for (int row = 0; row < SIZE / 2; row++) {
            for (int colum = 0; colum < SIZE / 2; colum++) {
                zoom[row][colum] = btm_image[row + SIZE / 2][colum];
            }
        }
        for (int i = 0, row = 0; row < SIZE; row += 2, i++) {
            for (int n = 0, colum = 0; colum < SIZE; colum += 2, n++) {
                zoomimage[row][colum] = zoom[i][n];
                zoomimage[row + 1][colum] = zoom[i][n];
                zoomimage[row][colum + 1] = zoom[i][n];
                zoomimage[row + 1][colum + 1] = zoom[i][n];
            }
        }

    }
    if (choices == 4) {
        for (int row = 0; row < SIZE / 2; row++) {
            for (int colum = 0; colum < SIZE / 2; colum++) {
                btm_image[row][colum] = btm_image[row][colum];


            }
        }
        for (int row = 0; row < SIZE / 2; row++) {
            for (int colum = 0; colum < SIZE / 2; colum++) {
                zoom[row][colum] = btm_image[row + SIZE / 2][colum + SIZE / 2];
            }
        }
        for (int i = 0, row = 0; row < SIZE; row += 2, i++) {
            for (int n = 0, colum = 0; colum < SIZE; colum += 2, n++) {
                zoomimage[row][colum] = zoom[i][n];
                zoomimage[row + 1][colum] = zoom[i][n];
                zoomimage[row][colum + 1] = zoom[i][n];
                zoomimage[row + 1][colum + 1] = zoom[i][n];
            }
        }

    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            finalresult[i][j] = zoomimage[i][j];

        }

    }

}

void mirror(){
       int cho;
    cout<<"enter number from list-> \n1- right\n2- left\n3- upper\n4-down"<<endl;
    cin>>cho;
    if (cho==1){
            for(int i =0;i<SIZE;i++){
                for(int j=0;j<SIZE/2;j++){
                                btm_image[i][j]=btm_image[i][255-j];

                }
        }

    }else if(cho==2){
             for(int i =0;i<SIZE;i++){
                for(int j=0;j<SIZE/2;j++){

                                btm_image[i][255-j]=btm_image[i][j];

            }
        }
    }else if (cho==3){
         for(int i =0;i<SIZE/2;i++){
                for(int j=0;j<SIZE;j++){

                                btm_image[i][j]=btm_image[255-i][j];

                }
        }
    }else if (cho==4){
         for(int i =0;i<SIZE/2;i++){
                for(int j=0;j<SIZE;j++){

                                btm_image[255-i][j]=btm_image[i][j];

            }
        }
    }
for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            finalresult[i][j] = btm_image[i][j];

        }

    }

}



void saveimage()
{
	char third_image[100];
	cout << "Please enter the name of the target image :";
	cin >> third_image;
	//strcat_s(third_image,".bmp");
	strcat(third_image,".bmp");
	writeGSBMP(third_image, finalresult);

}
void rotate_image()
{
    int degree;
    cout<<"enter degree(90,180,270): ";
    cin>>degree;
    if (degree==90){
        for (int row = 0; row < SIZE; row++) {
            for (int colum= row; colum < SIZE; colum++){
                char   rot_image= btm_image[row][colum];
                // swap rows and columns image pixels columns
                btm_image[row][colum]=btm_image[colum][row];
                btm_image[colum][row]=rot_image;



    }//flip horizontal for rows and columns
}      for (int row = 0; row < SIZE; row++) {
            for (int colum= 0; colum < SIZE/2; colum++){
                    char   rot_image= btm_image[row][colum];
                    btm_image[row][colum]=btm_image[row][SIZE-1-colum];
                    btm_image[row][SIZE-1-colum]= rot_image;
            }}
    }else if (degree==180){

        for (int row = 0; row < SIZE; row++) {
            for (int colum = 0; colum < SIZE/2; colum++){
                    char   rot_image= btm_image[row][colum];
                    // moving pixels from up to down
                    btm_image[row][colum]=btm_image[SIZE-1-row][SIZE-1-colum];
                    btm_image[SIZE-1-row][SIZE-1-colum]= rot_image;
    }}
    }else if (degree==270){
        for (int row = 0; row< SIZE; row++) {
            for (int colum = 0; colum < SIZE/2; colum++){
                //make rotate as 180 degree
                    char   rot_image= btm_image[row][colum];
                    btm_image[row][colum]=btm_image[SIZE-1-row][SIZE-1-colum];
                    btm_image[SIZE-1-row][SIZE-1-colum]= rot_image;
    }
        }for (int row = 0; row < SIZE; row++) {
            for (int colum = row; colum < SIZE; colum++){
                    //make rotate as 90 degree
                char   rot_image= btm_image[row][colum];
                btm_image[row][colum]=btm_image[colum][row];
                btm_image[colum][row]=rot_image;
// flip the image from right to left
            }} for (int row = 0; row < SIZE; row++) {
                  for (int colum = 0; colum < SIZE/2; colum++){
                    char   rot_image= btm_image[row][colum];
                    btm_image[row][colum]=btm_image[row][SIZE-1-colum];
                    btm_image[row][SIZE-1-colum]= rot_image;
            }
            }


    }
    for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			finalresult[i][ j] =  btm_image[i][j] ;

		}

    }
    }

 void shrink_filter()

{   int choice;
    cout<<"please enter number (1)for 1/2 shrink  (2) for 1/4 shrink  (3) for 1/6 shrink";
    cin>>choice;


    int x=0;
    int y=0;
    for (int i = 0; i < SIZE; i=i+(choice*2))
    {
        for (int j = 0; j < SIZE; j=j+(choice*2))
        {
            finalresult[x][y]=first_image[i][j];
            y++;
        }
        y=0;
        x++;

    }
}


void choose_image(){
    // this function enable  to user choose any image who want it
    char image_name[150];
    cout<<"Enter your image name : ";
    cin>>image_name;
    strcat(image_name,".bmp");
    readGSBMP(image_name,btm_image);

}

int main()
{

 int choice;


    while (true)

    {


          cout<<"Please choose one from those filters or enter 0 to exit"<<endl;
          cout<<"(1) Merge filter"<<endl;
          cout<<"(2) Blur filter"<<endl;
          cout<<"(3) Black & white filter "<<endl;
          cout<<"(4) Flip image filter "<<endl;
          cout<<"(5) Invert filter "<<endl;
          cout<<"(6) Rotate image "<<endl;
          cout<<"(7) Darken image "<<endl;
          cout<<"(8) Light  images "<<endl;
          cout<<"(9) Edge detection images "<<endl;
          cout<<"(10) Shuffle images "<<endl;
          cout<<"(11) Enlarge images "<<endl;
          cout<<"(12) Shrink image "<<endl;
          cout<<"(13) mirror image "<<endl;
          cout<<"(0) Exit"<<endl;
          cin>>choice;
          if(choice==1)
          {
              load_image();
              load_twoimages();
              merge_filter();
              saveimage();
          }
          if(choice==2)
          {   load_image();
              blur_filter();
              saveimage();
          }
          else if (choice==3){
                load_image();
                bwimage();
                saveimage();
          }
          else if (choice==4){
              string cho;
              string input_cho;
              cout<<"Flip (h)orizontally or. (v)ertically ?"<<endl;
              cin>>cho;
              input_cho=cho;
              if (input_cho=="h"){
                load_image();
                flipimageh();
                saveimage();
               input_cho=" ";

              }else if (input_cho=="v"){

                  load_image();
                  flipimagev();
                  saveimage();
                  input_cho=" ";

              }else{
                  cout <<"Sorry invalid input "<<endl ;

              }


          }else if(choice==5){
              load_image();
              invert_image_filter();
              saveimage();
          }
          else if(choice==6){
              choose_image();
              rotate_image();
              saveimage();
          }



            else if(choice==7)
            {
              load_image();
              dark_image();
              saveimage();
            }
            else if(choice==8)
            {
              load_image();
              light_image();
              saveimage();
            }

            else if(choice==9)
            {
              load_image();
              edge_filter();
              saveimage();
            }
            else if(choice==10)
            {
              choose_image();
              shuffle_image();
              saveimage();
            }


            else if(choice==11)
            {
              choose_image();
              enlarge_image();
              saveimage();

            }
            else if(choice==12)
            {
              load_image();
              shrink_filter();
              saveimage();

            } else if(choice==13)
            {
              choose_image();
              mirror();
              saveimage();

            }

          else if(choice==0)
          {
              break;
          }else{
              cout<<"Sorry,invalid input"<<endl;
          }


    }

}






