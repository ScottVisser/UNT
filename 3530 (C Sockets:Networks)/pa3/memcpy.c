#include "server.h"


struct foo
{
	int a;
	char *b;
	short int c;
};


int main(void)
{

	struct foo crouton = {80085,"crouton",420};
	struct foo crouton2;

	char *buffer;
	buffer = malloc(sizeof(crouton));

	printf("%d %s %d\n", crouton.a, crouton.b, crouton.c);
	printf("sizeof(crouton) = %d\n", sizeof(crouton));

	memcpy(buffer, &crouton, sizeof(crouton));

	printf("buffer: %s\n", buffer);

	memcpy(&crouton2, buffer, sizeof(crouton));
	printf("%d %s %d\n", crouton2.a, crouton2.b, crouton2.c);
	

return 0;
}
