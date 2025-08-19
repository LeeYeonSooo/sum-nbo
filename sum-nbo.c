#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>


uint32_t print_and_sum(const char *filename, int *printed){
        FILE *fp = fopen(filename, "rb");
        if (!fp) {
                fprintf(stderr, "can't open %s \n", filename);
                return 0;
        }

	uint32_t subtotal = 0;
	uint32_t value; //4 byte from file
	size_t n;
	int read_any = 0;

	while(1) {
		n = fread(&value, 1, 4, fp);
		if (n == 0) break;
                if (n != 4){
                        fprintf(stderr, "not 4 byte multiple, %s \n", filename);
                        fclose(fp);
                        return 0;
                }
	
		uint32_t val = ntohl(value);

		if (*printed) printf(" + ");
		printf("%u(0x%08x)", val, val);
		*printed = 1;

		subtotal += val;
		read_any = 1;
	}

	fclose(fp);

	if (!read_any){
		fprintf(stderr, "file %s is smaller than 4 bytes\n", filename);
                return 0;
	}

	return subtotal;
}

int main(int argc, char *argv[]){
	uint32_t total = 0;
	int printed = 0;

	for (int i = 1; i < argc; i++){
		total += print_and_sum(argv[i], &printed);
	}

	printf(" = %u(0x%08x)\n", total, total);

	return 0;
}
