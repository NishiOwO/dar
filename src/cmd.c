#include "common.h"

int dar_show_help = 1;
int dar_create = 0;
int dar_extract = 0;
int dar_test = 0;
int dar_info = 0;
const char* dar_input = NULL;

static int count = 0;

int dar_cmd(int total, const char* arg){
	int i;
	if(total == 0){
		/* do nothing */
	}else if(total == 1 && count == 0){
		dar_show_help = 0;
		dar_info = 1;
		dar_input = arg;
	}else if(count == 0){
		int c = 0;
		for(i = 0; arg[i] != 0; i++){
			if(arg[i] == '-' && i == 0){
				continue;
			}else if(c == 0){
				dar_show_help = 0;
				if(arg[i] == 'c'){
					dar_create = 1;
				}else if(arg[i] == 'x'){
					dar_extract = 1;
				}else if(arg[i] == 't'){
					dar_test = 1;
				}else{
					fprintf(stderr, "invalid command: %c\n", arg[i]);
					return 1;
				}
			}
			c++;
		}
	}
	count++;
	return -1;
}
