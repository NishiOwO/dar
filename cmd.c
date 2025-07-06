#include "common.h"

int zar_show_help = 1;
int zar_create = 0;
int zar_extract = 0;
int zar_test = 0;

static int count = 0;

int zar_cmd(const char* arg){
	int i;
	if(count == 0){
		int c = 0;
		for(i = 0; arg[i] != 0; i++){
			if(arg[i] == '-' && i == 0){
				continue;
			}else if(c == 0){
				zar_show_help = 0;
			}
		}
	}
	count++;
	return -1;
}
