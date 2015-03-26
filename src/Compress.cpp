//Compress.cpp

void Compress() {
	FILE* openfile = fopen("./bin/sorted.bin", "rb");
	FILE* compressedfile = fopen("./bin/compressed.bin", "wb+");

	orderCust tempcurrent, tempnext;
	int count = 1;
	int returnvalue = 1;
	fread(&tempcurrent, sizeof(struct orderCust), 1, openfile);

	while(!feof(openfile)) {
		returnvalue = fread(&tempnext, sizeof(orderCust), 1, openfile);
		
		if(returnvalue == 0) {
			fwrite(&(tempcurrent.cust_key), sizeof(int), 1, compressedfile);
			fwrite(&count, sizeof(count), 1, compressedfile);
		}
		
		if(tempcurrent.cust_key == tempnext.cust_key ) {
			count++;
		} else {
			fwrite(&(tempcurrent.cust_key), sizeof(int), 1, compressedfile);
			fwrite(&count, sizeof(count), 1, compressedfile);
			tempcurrent = tempnext;
			count = 1;
		}
	}
	fclose(openfile);
	fclose(compressedfile);
}