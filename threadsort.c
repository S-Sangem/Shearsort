/*
@Sushanth Sangem 3/15/19
Implements ShearSort with threads
Reads input from file
*/

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

int i, j, m, n;
int **toSort;

//helper method for bubblesort
//Parameters: int x and y
void swap(int *x, int *y)
{
  int tempS = *x;
  *x = *y;
  *y = tempS;
}

//bubblesort, used in ordering sections of the array
//Parameters: arr[] and n
void bubblesort(int arr[], int n)
{
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

//sorts horizontal rows
//Parameter: long i
void *sortodd(void *i)
{
  int i2 = (long)i;
  int temp[n];
  for(j=0; j<n; j++)
  {
    temp[j] = toSort[i2][j]; //loads temps with values to be sorted
  }

  bubblesort(temp, n); //sorts a few elements

  if(i2%2 == 0) //puts even rows in correct position
  {
    for(j=0; j<n; j++)
    {
      toSort[i2][j] = temp[j]; //loads sorted elements back to array
    }
  }
  if(i2%2 == 1) //puts odd rows in correct position
  {
    int k = n-1;
    for(j=0; j<n; j++)
    {
      toSort[i2][k] = temp[j]; //loads sorted elements back to array
      k--;
    }
  }
  pthread_exit(NULL);
}

//sorts vertical rows
//Parameter: long j
void *sorteven(void *j)
{
    int j2 = (long)j;
    int temp[n];
    for(i=0; i<n; i++)
    {
      temp[i] = toSort[i][j2]; //loads temps with values to be sorted
    }

    bubblesort(temp, n); //sorts a few elements

    for(i=0; i<n; i++) //puts columns in correct position
    {
      toSort[i][j2] = temp[i]; //loads sorted elements back to array
    }
    pthread_exit(NULL);
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
   int logn;
   int phase;

   char c;
   char tempChar[9999];
   int tc = 0;
   //opens and reads file
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

   //log2 (n) + 1 phases
   logn = log2(n) + 1;

   //n now repersents the side length of the array
   n = sqrt(n);

   //global array we will store the input in
   toSort = malloc(n);
   for(i=0; i<n; i++)
   {
     toSort[i] = malloc(n);
   }

   //populates toSort with elements from input
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

  pthread_t threads[n];

  //shearsort algorithm threads
  for(phase = 1; phase <= logn; phase++)
  {
    if(phase%2 == 1) //Odd number phases
    {
      for(i=0; i<n; i++) //Sets up the threads
      {
        long i2 = i;
        pthread_create(&threads[i], NULL, sortodd, (void *)i2);
      }
    }

    if(phase%2 == 0) //Even number phases
    {
      for(j=0; j<n; j++) //Sets up the threads
      {
        long j2 = j;
        pthread_create(&threads[j], NULL, sorteven, (void *)j2);
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

  //free toSort mallac
  //free(*toSort);
  //free(toSort);
}
