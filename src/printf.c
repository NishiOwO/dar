#include "common.h"

#define WIDTH 79

void dar_printf(FILE* out, const char* fmt, ...) {
	char	output[WIDTH + 1];
	char	save[WIDTH + 1];
	int	in_save = 0;
	va_list va;
	int	i;
	char*	current = &output[0];

	memset(output, 0, WIDTH + 1);

	va_start(va, fmt);
	for(i = 0; fmt[i] != 0; i++) {
		if(fmt[i] == '$') {
			char c = fmt[++i];
			if(c == fmt[i - 1]) {
				current[strlen(current)] = fmt[i];
			} else if(c == 'v') {
				strcat(current, va_arg(va, char*));
			} else if(c == 's') {
				memset(save, 0, WIDTH + 1);
				in_save = 1;
				current = &save[0];
			} else if(c == 'r' || c == 'c') {
				int j;
				int rep;
				if(c == 'r') {
					rep = WIDTH - strlen(output) - strlen(save);
				} else {
					rep = (WIDTH - strlen(save)) / 2 - strlen(output);
				}

				for(j = 0; j < rep; j++) output[strlen(output)] = ' ';
				strcat(output, save);
				in_save = 0;
				current = &output[0];
			} else if(c == 'a') {
				int aln = 0;
				int rep;
				int j;

				for(;;) {
					if('0' <= fmt[i + 1] && fmt[i + 1] <= '9') {
						aln *= 10;
						aln += fmt[++i] - '0';
					} else {
						break;
					}
				}

				rep = aln - strlen(current);
				if(rep < 0) rep = 0;
				for(j = 0; j < rep; j++) current[strlen(current)] = ' ';
			}
		} else {
			current[strlen(current)] = fmt[i];
		}
	}
	va_end(va);

	fprintf(out, "%s\n", output);
}
