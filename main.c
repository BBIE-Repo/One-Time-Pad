//
//  main.c
//  CipherLoc
//
//  Created by Earl Judge & Bradley Racey on 1/15/18.
//  Copyright © 2018 Earl Judge & Bradley Racey. All rights reserved.
//

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int timeOfLife = 0;

int numTables = 0;

int userIn;

int userInEncrypt;

unsigned key;

int NUMBITS = 8;

unsigned low8bits;

char array[5][5][127];

int DIMENSION = 5;

int getRand(int seed)
{
    key = rand();

    low8bits = key & 0xFF;

    printf("\nkey: %02x \n", low8bits);

    return low8bits;
}

//Decide if we want to skip elements that arent visible characters
void createLUC(int dimension)
{

    int value = 0;

    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            key = getRand(key);
            for(int k = 0; k < 127; k++)
            {
                value = low8bits ^ k;

                value %= 128;

                array[i][j][k] = value;
                printf("%d, ", array[i][j][k]);
                //printf("Memory Address: %p\n", &array[i][j][k]);
            }
        }
    }
}

int enncrypt(int charValue)
{
    int arrayItemI = getRand(array[DIMENSION][DIMENSION][126]);
    int arrayItemJ = getRand(arrayItemI);

    while(timeOfLife < 256)
    {
        charValue = array[arrayItemI][arrayItemJ][charValue];
        timeOfLife++;
    }
    arrayItemI = getRand(arrayItemI);
    arrayItemJ = getRand(arrayItemJ);
    timeOfLife = 0;
    return charValue;
}

char decrypt( int charValue )
{
    int arrayItemI = getRand(array[DIMENSION][DIMENSION][126]);
    int arrayItemJ = getRand(arrayItemI);

    while(timeOfLife < 256)
    {
        for(int i = 0; i < 127; i++)
        {
            if(array[arrayItemI][arrayItemJ][i] == charValue)
            {
                return i;
            }
        }
        timeOfLife++;
    }
    arrayItemI = getRand(arrayItemI);
    arrayItemJ = getRand(arrayItemJ);
    timeOfLife = 0;
    return charValue;
}

int main(int argc, const char * argv[])
{
    printf("What seed would you like to use?\n");
    scanf("%d", &userIn);
    printf("Would you like to e encrypt or d decrypt?\n");
    scanf("%d", &userInEncrypt);
    srand(userIn);
    key = getRand(userIn);
    createLUC(DIMENSION);

    //this should run while there is still data left to encrypt
    /*
    while(true)
    {
        //input = the character being encrypted.
        if(userInEncrypt == 'e')
        {
            enncrypt(charIN);
        }
        elif(userInEncrypt == 'd')
        {
            decrypt(charIN);
        }
        else
        {
            printf("Brad has a goat brain");
        }
    }
     */
    return 0;
}
