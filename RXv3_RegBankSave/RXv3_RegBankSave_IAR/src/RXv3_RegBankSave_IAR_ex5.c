#include <stdio.h>
//#include <math.h>
#include <stdlib.h>
#include <ctype.h>

/* Special character code */
#define LF 0x0a                     /* Line feed       */

/* Flag */
#define FALSE 0x00
#define TRUE  0x01

//void main(void);
void sort_(long *a);
void change_(long *a);

static __interrupt __nested void i_hdr_5_1(void);

#pragma bank=0
static __interrupt __nested void i_hdr_5_1(void)
{
    long data[10];
    int i;
    char tmp[2];
    int ret;
    char isnuminput;

//    while(1){

        printf("### Data Input ###\n");

        for( i=0; i<10; i++ ){
            printf("data[%d]=",i);
            data[i]= 0;
            isnuminput = FALSE;
            while(1){
                ret = scanf("%c",&tmp);
                if(ret != EOF){
                    if( tmp[0] != LF ){
                        if( isdigit(tmp[0])!=0 ){
                            data[i] = data[i]*10 + atoi(tmp);
                            isnuminput = TRUE;
                        }else{
                            printf("\n+++You can input only the decimal number.+++\n");
                            data[i] = 0;
                            isnuminput = FALSE;
                            printf("data[%d]=",i);
                        }
                    }else{
                        if(isnuminput != FALSE){
                            break;
                        }else{
                            printf("\n+++You can input only the decimal number.+++\n");
                            data[i] = 0;
                            isnuminput = FALSE;
                            printf("data[%d]=",i);
                        }
                    }
                }else{
                    printf("\n+++You can input only the decimal number.+++\n");
                    data[i] = 0;
                    isnuminput = FALSE;
                    printf("data[%d]=",i);
                }
            }
        }

        sort_(data);

        printf("*** Sorting results ***\n");

        for( i=0; i<10; i++ ){
            printf("data[%d]=%ld\n",i,data[i]);
        }

        change_(data);

//    }
}

void sort_(long *data)
{
    long t;
    int i, j, k, gap;

    gap = 5;
    while( gap > 0 ){
        for( k=0; k<gap; k++){
            for( i=k+gap; i<10; i=i+gap ){
                for(j=i-gap; j>=k; j=j-gap){
                    if(data[j]>data[j+gap]){
                        t = data[j];
                        data[j] = data[j+gap];
                        data[j+gap] = t;
                    }
                    else
                        break;
                }
            }
        }
        gap = gap/2;
    }
}

void change_(long *data)
{
    long tmp[10];
    int i;

    for(i=0; i<10; i++){
        tmp[i] = data[i];
    }
    for(i=0; i<10; i++){
        data[i] = tmp[9 - i];
    }
}

void *i_debug_ex5_1 = (void *)i_hdr_5_1;



extern void i_fnc_4_2(void);
static __interrupt __nested void i_hdr_5_2(void);

#pragma bank=0
static __interrupt __nested void i_hdr_5_2(void)
{
   i_fnc_4_2();
}

void *i_debug_ex5_2 = (void *)i_hdr_5_2;



extern unsigned int cnt;
static __interrupt __nested void i_hdr_5_3(void);

#pragma bank=0
static __interrupt __nested void i_hdr_5_3(void)
{
    cnt = cnt * cnt;
}

void *i_debug_ex5_3 = (void *)i_hdr_5_3;



extern unsigned int cnt;
static __interrupt __nested void i_hdr_5_4(void);

#pragma bank=0
static __interrupt __nested void i_hdr_5_4(void)
{
   cnt++;
}

void *i_debug_ex5_4 = (void *)i_hdr_5_4;



#include <intrinsics.h>

static __interrupt __nested void i_hdr_5_5(void);

#pragma bank=0
static __interrupt __nested void i_hdr_5_5(void)
{
    __macl(0, 0, 2);
}

void *i_debug_ex5_5 = (void *)i_hdr_5_5;
