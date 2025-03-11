#include "TestBlockTrace.h"
#include "Parser.h"
#include "common.h"
#include "ChildrenArray.h"
#include "Token.h"
#include "TestBlock.h"
#include "Tree.h"
#include "FilePositionOptions.h"

Parser createParser(Tree* t) {
	Parser ret = {
		.tree = t,
		.current = t->root,
		.currentCase = NULL,
		.trace = createTestBlockTrace(),
		.filePositionOptions = createFilePositionOptions()
	};
	return ret;
}

void destroyParser(Parser* p) {
	destroyTestBlockTrace(&p->trace);
}

void resetFilePositionOptionsNewBlock(Parser *p) {
	UNUSED();
	//unsetFilePositionOptionWrapAssert(&p->filePositionOptions);
	//unsetFilePositionOptionWrapExpect(&p->filePositionOptions);
}

void resetFilePositionOptionsNewCase(Parser *p) {
	UNUSED();
}

void setFilePositionOptionByTokenType(Parser *p, TokenType type) {
	switch(type) {
		case TOKEN_EXPECT_ALL:
			setFilePositionOptionWrapExpect(&p->filePositionOptions);
			break;
		case TOKEN_ASSERT_ALL:
			setFilePositionOptionWrapAssert(&p->filePositionOptions);
			break;
		case TOKEN_END_EXPECT_ALL:
			unsetFilePositionOptionWrapExpect(&p->filePositionOptions);
			break;
		case TOKEN_END_ASSERT_ALL:
			unsetFilePositionOptionWrapAssert(&p->filePositionOptions);
			break;
		case TOKEN_END_ALL:
			unsetFilePositionOptionWrapExpect(&p->filePositionOptions);
			unsetFilePositionOptionWrapAssert(&p->filePositionOptions);
		default:
			break;
	}
}
			
			

void parse(Parser* p, FILE* src, Token* token) {
	switch(token->type) {
		case TOKEN_NEWBLOCK:
			resetFilePositionOptionsNewBlock(p);
			if (getTestBlockType(p->current)
				== CHILDREN_CASE) {
				UNIMPLEMENTED("Syntax error: Test block inside a test cases block.");
				break;
			}
			char* newBlockName = 
				createStringFromFilePosition(src,token->filePosition);
			int existingTestBlockIndex =
				findNameInChildrenArray(&p->current->childrenArray, newBlockName);

			if (existingTestBlockIndex != -1) {
				pushTrace(&p->trace, p->current);
				p->current = 
					getTestBlockChildrenFromTestBlock(p->current, existingTestBlockIndex);
				free(newBlockName);
			} else {
				pushTrace(&p->trace, p->current);
				p->current = emplaceChildrenBlock(p->current, src); 
				p->current->data.name = newBlockName;
				p->currentCase = NULL;
			}
			break;
		case TOKEN_NEWCASE:
			resetFilePositionOptionsNewCase(p);
			if (getTestBlockType(p->current)
				!= CHILDREN_BLOCK) {
				p->currentCase = emplaceChildrenCase(p->current, src);
				p->currentCase->name =
					createStringFromFilePosition(src,token->filePosition);
			} else {
				UNIMPLEMENTED("Syntax error: Test case inside a test blocks block.");
			}
			break;
		case TOKEN_ENDBLOCK:
			if (p->tree->root == p->current) {
				UNIMPLEMENTED("Syntax error: END_BLOCK recieved at root");
			} else {
				p->current = popTrace(&p->trace);
			}
			break;
		case TOKEN_PREPROC:
			if (p->tree->root != p->current) {
				UNIMPLEMENTED("Syntax error, preproc after first block");
			} else {
				appendFilePositionArray(&p->tree->preproc,token->filePosition);
				appendFileArray(&p->tree->preprocSources, src);
			}
			break;
		case TOKEN_BEFORE_ALL:
			p->dataTarget = &p->current->data.beforeAll;
			break;
		case TOKEN_AFTER_ALL:
			p->dataTarget = &p->current->data.afterAll;
			break;
		case TOKEN_BEFORE_EACH:
			p->dataTarget = &p->current->data.beforeEach;
			break;
		case TOKEN_AFTER_EACH:
			p->dataTarget = &p->current->data.afterEach;
			break;
		case TOKEN_DATA:
		case TOKEN_DATA_NO_WRAP: // currently NO_WRAP is no options at all.
			if (p->tree->root == p->current) {
				appendFilePositionArray(&p->tree->preproc,token->filePosition);
				appendFileArray(&p->tree->preprocSources, src);
				break;
			}
			if (p->currentCase != NULL) {
				// Test here if data is part of C
				if (token->type != TOKEN_DATA_NO_WRAP) {
					token->filePosition.opt = p->filePositionOptions;
				}
				appendFilePositionArray(&p->currentCase->content,token->filePosition);
			}
			else {
				appendFilePositionArray(p->dataTarget,token->filePosition);
			}
			break;
		case TOKEN_END_OF_FILE:
			break;
		case TOKEN_EXPECT_ALL:
		case TOKEN_END_EXPECT_ALL:
		case TOKEN_ASSERT_ALL:
		case TOKEN_END_ASSERT_ALL:
		case TOKEN_END_ALL:
			setFilePositionOptionByTokenType(p, token->type);
			break;
		default:
			UNIMPLEMENTED("Unimplemented token type");
	}
}
			
		
			
			
			
			
		
	

	


