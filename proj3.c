#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Item
{
  char name[150];
  int price;
  int value;
} Item;
int max(int num1, int num2);
void printVals(int values[5][101], int linecount);

int main(int argc, char* argv[])
{
  //Read in file
  FILE *data = fopen(argv[1], "r");
  if(data == NULL || argc-1 != 1)
  {
    printf("Error, file not found\n");
    return -1;
  }
  int linecount = 0; //number of items
  int lineSizeMax = 250;
  char line[250];
  while(fgets(line, lineSizeMax, data) != NULL)
  {
    linecount++;
  }
  linecount--; //Ignore first line
  rewind(data);
  int i = 0;
  Item items[linecount];
  while(fgets(line, lineSizeMax, data) != NULL)
  {
      fscanf(data, "%[^,],%d,%d", items[i].name, &items[i].price, &items[i].value);
      i++;
  }
  
  /*for(i = 0; i < linecount; i++)
  {
    printf("Item: %s || Price: %d || Value: %d\n", items[i].name, items[i].price, items[i].value);
  }*/
  
  //=========================================================================
  int budget = 100;
  int solution[linecount+1][budget+1];
  
  int values[linecount+1][budget+1]; //item count x amt of money
  
  //Fill in base cases
  int j;
  for(j = 0; j < budget+1; j++)
  {
    values[0][j] = 0;
  }
  for(i = 0; i < linecount+1; i++)
  {
    values[i][0] = 0;
  }
  
  //Build on the array
  for(i = 1; i < linecount+1; i++)
  {
    for(j = 1; j < budget+1; j++)
    {
      values[i][j] = values[i-1][j]; //Set current value to the one above it.
      
      //Check if the current item can be taken
      if(j >= items[i-1].price)
      {
        int temp = items[i-1].value;
        if(j-items[i-1].price >= 0)
        {
          //Add the value of the current item with the remaining leftover value from the previous row
          temp += values[i-1][j-items[i-1].price]; 
        }
        //Take the max between if the current item was taken and if it wasn't taken.
        values[i][j] = max(temp, values[i-1][j]);
      }
        
      
    } //End for2
  } //End for1
  
  //printVals(values, linecount);
  printf("Optimal value: %d\n", values[linecount][100]);
  
  //Perform traceback
  i = linecount;
  j = 100;
  int temp = 0;
  while(i > 0 && j > 0)
  {
    //Check if the current item was chosen.
    if(values[i][j] == values[i-1][j-items[i-1].price]+items[i-1].value)
    {
      //Item was chosen, print and then move up and left
      printf("%s\n", items[i-1].name);
      temp += items[i-1].value;
      j -= items[i-1].price;
    }
    i--;
  }
  //printf("Final val calculated from traceback: %d\n", temp);

  return 0;
}

int max(int num1, int num2)
{
  if (num1 > num2)
    return num1;
  return num2;
}

void printVals(int values[5][101], int linecount) //print the values array
{
  int i;
  int j;
  for(i = 1; i < linecount+1; i++)
  {
    for(j = 0; j < 101; j+=1)
    {
      printf("%d ", values[i][j]);
      if(j % 10 == 0)
        printf("|(%d)|", j);
    }
    printf("\n");
  }
}