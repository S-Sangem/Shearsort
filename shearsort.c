/*
@Sushanth Sangem 3/15/19
Implements ShearSort without threads
reads input from file
*/
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void bubblesort(int arr[], int n)
{
  int i;
  int j;
  for(i=0;i<n-1;i++)
  {
    for(j=0;j<n-i-1;j++)
    {
      if(arr[j] > arr[j + 1])
      {
        swap(&arr[j], &arr[j+1]);
      }
    }
  }
}

int main (int argc, char *argv[])
{
  /*
  int toSort[4][4] =
  {{3, 11, 6, 16},
   {8, 1, 5, 10},
   {14, 7, 12, 2},
   {4, 13, 9, 15}};
   */
   int temp[4] = {0, 0, 0, 0};
   int n = 0;
   int m = 0;

   int logn;
   int phase;

   int i;
   int j;

   char c;
   char tempChar[9999];
   int tc = 0;
   FILE *fp;
   fp = fopen("input.txt", "r");
   //sorts file into 1D array
   while ((c = getc(fp)) != EOF)
   {
     tempChar[tc] = c;
     tc++;
   }
   fclose(fp);

   //determines how many elements are in the array
   for(i=0;i<tc;i++)
   {
     if (tempChar[i] != ' ' && '\n')
     {
         if (tempChar[i+1] == ' ')
         {
           n++;
         }
         if (tempChar[i+1] == '\n')
         {
           n++;
         }
     }
   }
   //log2 (n) + 1
   logn = log2(n) + 1;
   //n now repersents the side length of the array
   n = sqrt(n);

   //array we will store the input in
   int toSort[n][n];

   //populates toSort
   for(i=0;i<n;i++)
   {
     for(j=0;j<n;j++)
     {
       char tempStr[9999] = {[0 ... 9998] = ' '};
       int tempC = 0;
       while(1)
       {
         if(!isdigit(tempChar[m]))
         {
           toSort[i][j] = atoi(tempStr);
           m++;
           break;
         }
         else
         {
         tempStr[tempC] = tempChar[m];
         tempC++;
         m++;
         }
       }
     }
   }

  for(phase = 1; phase <= logn; phase++)
  {
    if(phase%2 == 1) //Odd number phases
    {
      for(i=0; i<n; i++) //Sets up the temp array
      {
        for(j=0; j<n; j++)
        {
          temp[j] = toSort[i][j];
        }

        bubblesort(temp, n);

        if(i%2 == 0) //puts even rows in correct position
        {
          for(j=0; j<n; j++)
          {
            toSort[i][j] = temp[j];
          }
        }
        if(i%2 == 1) //puts odd rows in correct position
        {
          int k = n-1;
          for(j=0; j<n; j++)
          {
            toSort[i][k] = temp[j];
            k--;
          }
        }
      }
    }

    if(phase%2 == 0) //Even number phases
    {
      for(j=0; j<n; j++) //Sets up the temp array
      {
        for(i=0; i<n; i++)
        {
          temp[i] = toSort[i][j];
        }

        bubblesort(temp, n);

        for(i=0; i<n; i++) //puts columns in correct position
        {
          toSort[i][j] = temp[i];
        }
      }
    }

    //prints array as it is solved
    for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
      {
        printf("%d ", toSort[i][j]);
      }
      printf("\n");
    }
    printf("\n");
  }
}
