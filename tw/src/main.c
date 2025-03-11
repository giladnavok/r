#include "Lexer.h"
#include "Parser.h"
#include "Tree.h"
#include "Printer.h"

#include <unistd.h>
#include <assert.h>
#include <getopt.h>
#include <stdio.h>

void parseFile(Lexer* l, Parser* ps, FILE* src) {
	setLexerSourceFile(l, src);
	Token t = {0};
	t = lexerNextToken(l);
	while (t.type != TOKEN_END_OF_FILE) {
		parse(ps, src, &t);
		t = lexerNextToken(l);
	}
}

void createTest(FILE** sources, int sourcesCount, FILE* dest) {
	assert(sourcesCount > 0);
	Lexer l = createLexer();
	Tree t = createTree(sources[0]);
	t.root->data.name = malloc(1); // Should actually remake root to a tree
	t.root->data.name[0] = 0;
	Parser ps = createParser(&t);
	
	for (int i = 0; i < sourcesCount; i++) {
		parseFile(&l, &ps, sources[i]);
	}

	Printer pr = createPrinter(dest);
	printTree(&pr, &t);

	destroyTree(&t);
	destroyLexer(&l);
	destroyParser(&ps);
	destroyPrinter(&pr);
}


int main(int argc, char** argv) {
	int opt;
	FILE* dest = NULL;

	while((opt = getopt(argc, argv, "o:")) != -1) {
		switch(opt) {
			case 'o':
			dest = fopen(optarg, "w");
			if (dest == NULL) {
				fprintf(stderr, "Failed to open destination file %s\n", optarg);
				return 1;
			}
		}
	}
	if (dest == NULL) {
		fprintf(stderr, "Missing output file, use -o <filename>\n");
		return 1;
	}

	int sourceFileCount = argc - optind;
	if (sourceFileCount <= 0) {
		fprintf(stderr, "No source files\n");
	}
		
	FILE** sources = malloc(sizeof(*sources) * sourceFileCount);
	
	int currentFileIndex = 0;
	while (optind < argc) {
		sources[currentFileIndex] = fopen(argv[optind++], "r");
		if (sources[currentFileIndex] == NULL) {
			fprintf(stderr, "Failed to open %s\n", argv[optind - 1]);
			for (int i = 0; i < currentFileIndex - 1; i++) {
				fclose(sources[i]);
			}
			free(sources);
			return 1;
		}
		currentFileIndex++;
	}

	createTest(sources, sourceFileCount, dest);

	for (int i = 0; i < sourceFileCount; i++) {
		fclose(sources[i]);
	}
	fclose(dest);
	free(sources);
	return 0;
}
		


