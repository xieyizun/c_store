//Join the Customer tabel and Order tabel with the attribute custkey, where custkey is the main key of customer tabel and is the out key
//of the Order tabel. So custkey is sorted in the Customer tabel and we should load in the sorted.bin where Custkey is sorted and it contains
//the orderkey. If it is joined successfully, we should output the result in the order of custkey and next orderkey directed.
//here we use the sort-merge algorithm.

void Join() {
	
	FILE* sortedFile = fopen("./bin/sorted.bin", "rb");
	FILE* custKeyFile = fopen("./bin/customerCustkey.bin", "rb");
	
	int *customer_custkey = new int;
	orderCust *order = new orderCust;
    fread(customer_custkey, sizeof(int), 1, custKeyFile);
    fread(order, sizeof(orderCust), 1, sortedFile);
   
	while (!feof(sortedFile) && !feof(custKeyFile)) {
		while (*customer_custkey < order->cust_key && (!feof(sortedFile) && !feof(custKeyFile)))
			fread(customer_custkey, sizeof(int), 1, custKeyFile);
		while (*customer_custkey > order->cust_key && (!feof(sortedFile) && !feof(custKeyFile)))
			fread(order, sizeof(orderCust), 1, sortedFile);

		while (*customer_custkey == order->cust_key && (!feof(sortedFile) && !feof(custKeyFile))) {
			printf("custkey: %d  orderkey: %d\n", order->cust_key, order->order_key);
			fread(order, sizeof(orderCust), 1, sortedFile);
		}

		fread(customer_custkey, sizeof(int), 1, custKeyFile);
	}
    
    delete customer_custkey;
    delete order;
    
	fclose(sortedFile);
	fclose(custKeyFile);
	
}