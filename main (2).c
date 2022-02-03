
#include <stdio.h>
int sw = 0; // switch
void house(int Hwidth, int Hheight);
void roof(int Rwidth);
int main()
{
    int width;
    int height;
    printf("sirka: ");
    scanf("%d", &width);
    if (width%2==0)
    {
        printf("sirka neni licha ");
        return 1;
    }
    printf("vyska: ");
    scanf("%d", &height);
    
    if (width < 3 || height < 3)
    {
        printf("moc nizke cislo");
        return 1;
    }
    
    roof(width);
    house(width,height);
     
     
     
     
    return 0;
}

void house(int Hwidth, int Hheight)
{
    for (int i = 1;i<=Hheight;i++)     
     {
         for (int j=1;j<=Hwidth;j++)
             {
                 if (i > 1 && i < Hheight && j>1 && j< Hwidth)
                    {
                        
                        
                        if (sw==1)
                          printf("*");  
                        else
                          printf(".");  
                        sw = !sw;
                    }
                else
                {
             printf("X");
                }
             }
         printf("\n");
     }
    
    
}

void roof(int Rwidth)
{
    int avrg = (Rwidth+1)/2;
   // printf("prumer: %d \n",avrg);
   for (int i = 0;i<avrg;i++)   //rows  
     {
         for (int j = 1;j<=Rwidth;j++)   //colum  
        {
             if (j == avrg-i)
             {
                printf("X");
             } 
            else if (j == avrg+i)
            {
              printf("X");  
            }
            else
            {
                printf(" ");
            }
         
     } 
     printf("\n");
     }
    
    
    
    
}