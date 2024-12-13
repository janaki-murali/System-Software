#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,m;
    int avail[25],max[25][25],alloc[25][25],need[25][25];
    int work[25],finish[25],sequence[25];
    int i,j,k,y,s=0,flag=1,safeflag=1;
    printf("How many processes ? : ");
    scanf("%d",&n);
    printf("How many resources ? : ");
    scanf("%d",&m);
    printf("Enter the Available Matrix\n");
    for(i=0;i<m;i++)
    {
        scanf("%d",&avail[i]);
    }
    printf("Enter the Max Matrix\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    printf("Enter the Allocation Matrix\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    printf("Need Matrix\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<m;i++)
    {
        work[i]=avail[i];
    }
    for(i=0;i<n;i++)
    {
        finish[i]=0;
    }
    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            if(finish[i] == 0)
            {
                flag=1;
                for(j=0;j<m;j++)
                {
                    if(need[i][j] > work[j])
                    {
                        flag=0;
                        break;
                    }
                }
                if(flag)
                {
                    sequence[s++]=i;
                    for(y=0;y<m;y++)
                    {
                        work[y]+=alloc[i][y];
                    }
                    finish[i]=1;
                }
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(finish[i]==0)
        {
            safeflag=0;
            break;
        }
    }
    if(safeflag == 1)
    {
        printf("SAFE SEQUENCE : ");
        for(i=0;i<n;i++)
        {
            printf("P%d ",sequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("UNSAFE SEQUENCE\n");
    }
    return 0;
}
