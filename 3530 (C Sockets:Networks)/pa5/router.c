// Author: Scott Visser
// The function of this code is to model router activity and show how data would propogate between ends over a network.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

struct node
{
	char n;
	int neigbors[6];
	char list[6];
	char listLink[6];
	int listcount;
};
					// Router Index:
					// 0 : U
					// 1 : V
int main(void)				// 2 : W
{					// 3 : X
	int i, j, routers;		// 4 : Y
	int cost;			// 5 : Z
	char source, dest;
	int step;
	int nextCost[5];	
	char nextRouter[5];
	char nextLink[5];
	i = 0;
	j = 0;
	routers = 0;

	struct node router[6];
	
	router[0].n = 'u';
	router[0].listcount = 0;
	for (i = 0; i < 6; i++)
	 router[0].neigbors[i] = 999;
 
	router[1].n = 'v';
	router[1].listcount = 0;
	for (i = 0; i < 6; i++)
	 router[1].neigbors[i] = 999;

	router[2].n = 'w';
	router[2].listcount = 0;
	for (i = 0; i < 6; i++)
	 router[2].neigbors[i] = 999;
 
	router[3].n = 'x';
	router[3].listcount = 0;
	for (i = 0; i < 6; i++)
	 router[3].neigbors[i] = 999;

	router[4].n = 'y';
	router[4].listcount = 0;
	for (i = 0; i < 6; i++)
	 router[4].neigbors[i] = 999;

	router[5].n = 'z';
	router[5].listcount = 0;
	for (i = 0; i < 6; i++)
	 router[5].neigbors[i] = 999;
 
	FILE *fp;
	fp = fopen("router.txt", "r");
	printf("\n----------\n");

for (routers = 0; routers < 6; routers++)
{
	rewind(fp);
	step = 0;
	while (1) 
	{
		if (feof(fp))
		 break;
		fscanf(fp, "%c %c %d ", &source, &dest, &cost);
		
		if (source == router[routers].n)
		{
			router[routers].neigbors[router[routers].listcount] = cost;
			router[routers].list[router[routers].listcount] = dest;
			router[routers].listLink[router[routers].listcount] = dest; 
			router[routers].listcount++;		
		}
		else if (dest == router[routers].n)
		{
			router[routers].neigbors[router[routers].listcount] = cost;
			router[routers].list[router[routers].listcount] = source;  
			router[routers].listLink[router[routers].listcount] = source; 
			router[routers].listcount++;		
		}
	}

	nextRouter[0] = router[routers].list[0];
	nextCost[0] = router[routers].neigbors[0];

	for (i=1; i<router[routers].listcount; i++)
	{
		if (router[routers].neigbors[i] < nextCost[0])
		{
			nextCost[0] = router[routers].neigbors[i];
			nextRouter[0] = router[routers].list[i];
		}
	}

	step++;
	// reread file to find distances
	rewind(fp);
	while (1) // loop scans for distances between  
	{
		if (feof(fp))
		 break;

		fscanf(fp, "%c %c %d ", &source, &dest, &cost);

		if ((source == nextRouter[step-1]) && (dest != router[routers].n)) // find link between x and d from file
		{
			for (i = 0; i<router[routers].listcount; i++) // search for previous links (det cost)
			{ 
				if (router[routers].list[i] == dest)
			 	{ // if the dest already exist on the list and the sum cost with hop is lower...
					if (cost+nextCost[step-1] < router[routers].neigbors[i])
					{
						router[routers].neigbors[i] = cost + nextCost[step-1];
						router[routers].listLink[i] = source;
						break;
					}
					break;
				}
				else if ((i == router[routers].listcount-1) && 
					(router[routers].list[i] != dest))
				{
					router[routers].list[router[routers].listcount] = dest;
					router[routers].listLink[router[routers].listcount] = source;
					router[routers].neigbors[router[routers].listcount] = cost + nextCost[step-1];
					router[routers].listcount++;
					break;
				}
			}
		}
		else if ((dest == nextRouter[step-1]) && (source != router[routers].n)) // find link between x and d from file
		{
			for (i = 0; i<router[routers].listcount; i++) // search for previous links (det cost)
			{ 
				if (router[routers].list[i] == source)
			 	{ // if the dest already exist on the list and the sum cost with hop is lower...
					if (cost+nextCost[step-1] < router[routers].neigbors[i])
					{
						router[routers].neigbors[i] = cost + nextCost[step-1];
						router[routers].listLink[i] = dest;
						break;
					}
					break;
				}
				else if ((i == router[routers].listcount-1) && 
					(router[routers].list[i] != source))
				{
					router[routers].list[router[routers].listcount] = source;
					router[routers].listLink[router[routers].listcount] = dest;
					router[routers].neigbors[router[routers].listcount] = cost + nextCost[step-1];
					router[routers].listcount++;
					break;
				}
			}
		}
	}

	while (step < 6)
	{
		nextCost[step] = 555;
		for (i=0; i<router[routers].listcount; i++)
		{
			if (router[routers].neigbors[i] < nextCost[step]) 
			{ 
				for (j=0; j<step; j++)
				{
					if (router[routers].list[i] == nextRouter[j])
					 break;
					else if ((j == step-1) && (router[routers].list[i] != nextRouter[j]))
					{
						nextCost[step] = router[routers].neigbors[i];
						nextRouter[step] = router[routers].list[i];
						nextLink[step] = router[routers].listLink[i];
					}
				}
			}
		}
	
		step++;
		rewind(fp);

		while (1) // loop scans for distances between  
		{
			if (feof(fp))
			 break;

			fscanf(fp, "%c %c %d ", &source, &dest, &cost);

			if ((source == nextRouter[step-1])  && (dest != router[routers].n)) // find link between x and d from file
			{
				for (i = 0; i<router[routers].listcount; i++) // search for previous links (det cost)
				{ 
					if (router[routers].list[i] == dest)
				 	{ // if the dest already exist on the list and the sum cost with hop is lower...
						if (cost+nextCost[step-1] < router[routers].neigbors[i])
						{
							router[routers].neigbors[i] = cost + nextCost[step-1];
							router[routers].listLink[i] = nextLink[step-1];
							break;
						}
						break;
					}
					else if ((i == router[routers].listcount-1) && (router[routers].list[i] != dest))
					{
						router[routers].list[router[routers].listcount] = dest;
						router[routers].listLink[router[routers].listcount] = nextLink[step-1];
						router[routers].neigbors[router[routers].listcount] = cost + nextCost[step-1];
						router[routers].listcount++;
						break;
					}
				}
			}
			else if ((dest == nextRouter[step-1])  && (source != router[routers].n)) // find link between x and d from file
			{
				for (i = 0; i<router[routers].listcount; i++) // search for previous links (det cost)
				{ 
					if (router[routers].list[i] == source)
				 	{ // if the dest already exist on the list and the sum cost with hop is lower...
						if (cost+nextCost[step-1] < router[routers].neigbors[i])
						{
							router[routers].neigbors[i] = cost + nextCost[step-1];
							router[routers].listLink[i] = nextLink[step-1];
							break;
						}
						break;
					}
					else if ((i == router[routers].listcount-1) && (router[routers].list[i] != source))
					{
						router[routers].list[router[routers].listcount] = source;
						router[routers].listLink[router[routers].listcount] = nextLink[step-1];
						router[routers].neigbors[router[routers].listcount] = cost + nextCost[step-1];
						router[routers].listcount++;
						break;
					}
				}
			}

		}
	}

	printf("sourc\tdest\tlink\tcost\n");
	for (i=0; i<router[routers].listcount; i++)
	 printf(" %c\t %c\t %c\t %d\n", router[routers].n, router[routers].list[i], router[routers].listLink[i], router[routers].neigbors[i]);
//	 printf("%c (%c, %c)\n", router[routers].list[i], router[routers].n, router[routers].listLink[i]);
	printf("----------------------------\n");
	
}	
		
printf("\n");
return 0;
}


