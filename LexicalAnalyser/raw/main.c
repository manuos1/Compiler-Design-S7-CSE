#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


#define n_operators 10
#define n_keywords 10
#define n_arithmeticOp 7
#define n_logicalOp 3
#define n_assignmentOp 7
#define n_comparisonOp 6

char operators[] = {'=', '+', '*', '/', '%', '<', '>', '!', '&', '|'};
char *keywords[] = {"void", "int", "float", "char", "return", "if", "for", "while", "do", "switch"};
char *arithmeticOp[] = {"+", "-", "*", "/", "%", "++", "--"};
char *logicalOp[] = {"&&", "||", "!"};
char *assignmentOp[] = {"=", "+=", "-=", "*=", "/=", "%=", "&="};
char *comparisonOp[] = {"==", "<=", ">=", "!=", ">", "<"};


int id=0;
char ident[20][10];

int getOperator(char *op) {
	int i;
	
	for(i=0; i<n_arithmeticOp; i++) {
		// printf("Comparing: %s and %s\n", op, arithmeticOp[i]);
		if(strcmp(arithmeticOp[i], op) == 0)
			return 1;
	}

	for(i=0; i<n_logicalOp; i++) {
		// printf("Comparing: %s and %s\n", op,logicalOp[i]);
		if(strcmp(logicalOp[i], op) == 0)
			return 2;
	}

	for(i=0; i<n_assignmentOp; i++) {
		// printf("Comparing: %s and %s\n", op,assignmentOp[i]);
		if(strcmp(assignmentOp[i], op) == 0)
			return 3;
	}

	for(i=0; i<n_comparisonOp; i++) {
		// printf("Comparing: %s and %s\n", op,comparisonOp[i]);
		if(strcmp(comparisonOp[i], op) == 0)
			return 4;
	}

	return 0;
}

int isOperator(char op) {
	int i;
	for (i=0;i<n_operators;i++) {
		if(operators[i] == op)
			return 1;
	}
	return 0;
}

int isKeyword(char *word)
{
	int j;
	for(j=0;j<n_keywords;j++)
	{
		if(strcmp(keywords[j],word)==0)
			return 1;
	}
	return 0;
}

int isIdentifier(char *word)
{
	int j;
	for(j=0;j<id;j++)
	{
		// printf("Comparing: %s and %s\n",ident[j],word);
		if(strcmp(ident[j],word)==0)
			return j+1;
	}
	strcpy(ident[id++],word);
	return id;
}


void main()
{
	FILE *input_file, *output_file;
	char ch,word[15],characters[10];
	int w=0,pos,c=0,i,flag=0,op;
	
	input_file=fopen("input.c","r");
	output_file=fopen("output.txt", "w");

	bzero(word,sizeof(word));
	bzero(characters,sizeof(characters));
	
	while(!feof(input_file))
	{
		ch=getc(input_file);
		// printf("Handling %c\n", ch);
		
		if (isspace(ch) || ch=='(' || ch==')' || ch=='{' || ch=='}' || ch==',' || ch==';')
			continue;
		else if(isalpha(ch) || ch=='_')
		{
			while(isalnum(ch) || ch=='_')
			{
				// printf("Char: %c\n",ch);
				word[w++]=ch;
				ch=getc(input_file);
			}
			ungetc(ch,input_file);
				
			// printf("Word: %s\tSize: %ld\n",word,strlen(word));
			
			if(isKeyword(word))
			{
				// printf("Keyword: %s\n",word);
				fprintf(output_file, "<%s\tkeyword >\n", word);
			}
			else
			{
				pos=isIdentifier(word);
				// printf("Identifier: %s\n",word);
				fprintf(output_file, "<%s\tidentifier\t%d >\n", word,pos);
			}
			
			bzero(word, sizeof(word));
			w=0;			
		}
		else if(ch=='"')
		{
			ch=getc(input_file);
			while(ch != '"')
			{
				characters[c++]=ch;
				ch=getc(input_file);
			}
			// printf("String Constant: %s\n",characters);
			fprintf(output_file, "<\"%s\"\tstring constant >\n",characters);
		}
		else if(ch=='\'')
		{
			ch=getc(input_file);
			// printf("Character Constant: %c\n",ch);
			fprintf(output_file, "<'%c'\tcharacter constant >\n", ch);
			getc(input_file);
		}
		else if(isdigit(ch))
		{
			while(isdigit(ch) || ch == '.')
			{
				characters[c++]=ch;
				ch=getc(input_file);
			}
			ungetc(ch,input_file);
			
			for(i=0;i<c;i++)
			{
				if(characters[i] == '.')
				{
					// printf("Real Constant: %s\n",characters);
					fprintf(output_file,"<%s\treal constant >\n",characters);
					flag=1;
					break;
				}
			}
			
			if(flag==0)
			{
				// printf("Integer Constant: %s\n",characters);
				fprintf(output_file,"<%s\tinteger constant >\n",characters);
			}
			else
				flag=0;
				
			bzero(characters,sizeof(characters));
			c=0;				
		}
		else // Operators
		{
			if (ch == -1) // EOF
				break;

			while(isOperator(ch))
			{
				// printf("Operator: %c\n", ch);
				characters[c++]=ch;
				ch=getc(input_file);
			}

			if (characters[0] != '\0') {
				op=getOperator(characters);

				if (op == 1) {
					// printf("Arithmetic Operator: %s\n",characters);
					fprintf(output_file,"<%s\tarithmetic operator >\n",characters);
				} else if (op == 2) {
					// printf("Logical Operator: %s\n",characters);
					fprintf(output_file,"<%s\tlogical operator >\n",characters);
				} else if (op == 3) {
					// printf("Assignment Operator: %s\n",characters);
					fprintf(output_file,"<%s\tassignment operator >\n",characters);
				} else if (op == 4) {
					// printf("Comparison Operator: %s\n",characters);
					fprintf(output_file,"<%s\tcomparison operator >\n",characters);
				} else {
					// printf("Unidentified Operator: %s\n",characters);
					fprintf(output_file,"<%s\tunidentified operator >\n",characters);
				} 

				bzero(characters,sizeof(characters));
				c=0;
			}

			ungetc(ch,input_file);
		}
	}

	fclose(input_file);
	fclose(output_file);
	
}