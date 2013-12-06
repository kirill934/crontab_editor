#include <stdio.h>
#include <string.h>

void print_help(void);
int create_file(char *name);
int delete_file(char *name);

int main(int argc, char *argv[])
{
	//FILE *file=fopen("testfile","w");
	if(argc!=3)
	{
		print_help();
		return 1;
	}

	++argv;
	if( strcmp(*argv,"-c")==0 || strcmp(*argv,"--create")==0 )
	{
		return create_file(*(++argv));
	}
	else if ( strcmp(*argv,"-d")==0 || strcmp(*argv,"--delete")==0 )
	{
		return delete_file(*(++argv));
	}
	else
		print_help();

	//fputc('c',file);
	//fprintf(file,"Hello, world\n");
	//fclose(file);
	return 0;
}
void print_help(void)
{
	printf("dofile [-c][--create][-d][--delete] filename \n");
	printf("-c, --create	create new file with name 'filename' \n");
	printf("-d, --delete	delete file with name 'filename' \n");

}
int create_file(char *name)
{
	//printf("You wanna create this file: %s \n",name);
	FILE *file;
	if( !(file=fopen(name,"r")) )
	{
		//file doesn't exist
		//let's create this file
		file=fopen(name,"w");
		printf("File %s has been created \n",name);
		fclose(file);
	}
	else
	{
		//file already exists
		//let's say about it
		char c;
		printf("File already exists \n");
		printf("Do you want to rewrite this file? (y\\n)...");
		c=getchar();
		if(c=='y')
		{
			fclose(file);
			file=fopen(name,"w");
			fclose(file);
		}
		else if(c=='n')
		{
			fclose(file);
			printf("Please run command again with other file name \n");
			return 0;
		}
		else
		{
			printf("Error: it's not 'y' or 'n' \n");
			return 1;
		}
	}
}
int delete_file(char *name)
{
	//printf("You wanna delete this file: %s \n",name);
	if( remove(name)!=0 )
	{
		printf("Error: can't delete this file \n");
		return 1;
	}
	else
	{
		printf("The file %s has been deleted \n",name);
		return 0;
	}
}
