#include "Lexer.h"
#include "Parser.h"
#include "Tree.h"
#include "Printer.h"

void createTree(Lexer* l, Parser* ps, FILE* src) {
	Token t = {0};
	t = lexerNextToken(l);
	while (t.type != TOKEN_END_OF_FILE) {
		parse(ps, src, &t);
		t = lexerNextToken(l);
	}
}

void createTest(FILE* src, FILE* dest) {
	Lexer l = createLexer(src);
	TestBlock root = createTestBlock(src); // src for now, should remake preproc since it should be able to come from different files, unlike headers
	root->data.name = malloc(1); // Should actually remake root to a tree
	root->data.name[0] = 0;
	Parser ps = createParser(root);
	
	createTree(&l, &ps, src);

	Printer pr = createPrinter(dest, src);
	printTest(&pr, root);

	destroyTestBlockRecursive(root);
	destroyLexer(&l);
	destroyParser(&ps);
	destroyPrinter(&pr);
}



int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "Intented use: tw <source-file> <dest-file>\n");
	} else {
		FILE* src = fopen(argv[1], "r");
		if (src == NULL) {
			fprintf(stderr, "Failed to open source file %s\n", argv[1]);
			return 1;
		}
		FILE* dest = fopen(argv[2], "w");
		if (dest == NULL) {
			fprintf(stderr, "Failed to open destination file %s\n", argv[2]);
			return 1;
		}
		createTest(src, dest);
		fclose(src);
		fclose(dest);
	}
	return 0;
}
		
			
		
		
		

 
