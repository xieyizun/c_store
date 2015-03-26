//Cout.cpp
//Count is to count how many records there are in the orders.tbl
int Count() {
	int count = 0;
	FILE *infile = fopen("./bin/compressed.bin", "rb");
	int customer_order[2]; //customer[0] is the custkey of a customer and customer[1] is the number of his orders

	while (!feof(infile)) {
		fread(customer_order, sizeof(int), 2, infile);
		if(!feof(infile))
			count += customer_order[1];
	}
	return count;	
}