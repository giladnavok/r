#include "Options.h"
#include <stdbool.h>

Options createOptions() {
	Options ret = {
		.opt = 0
	};
	return ret;
}

void setOption(Options* ops, int option) {
	ops->opt |= option;
}

void unsetOption(Options* ops, int option) {
	ops->opt = (ops->opt & ~option);
}

bool isOptionSet(Options* ops, int option) {
	return (ops->opt & option);
}
	

