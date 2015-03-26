//LoadCustomer.cpp

void LoadCustomer() {
	all_countpage = 0;

	FILE *infile, *custkeyfile;
	infile = fopen("customer.tbl", "rb");
	custkeyfile = fopen("./bin/customerCustkey.bin", "wb+");

	int pageindex = 0; 

	int custkey;
	char name[26];
	char address[41];
	int nationKey;
	char phone[16];
	double acctbal;
	char mktsegment[11];
	char comment[118];

	
	while(fscanf(infile,"%d|%[^|]|%[^|]|%d|%[^|]|%lf|%[^|]|%[^|]|\n", &custkey, name, address, &nationKey, phone,
		 &acctbal, mktsegment, comment) != EOF) {
		if(pageindex >= PAGESIZE) {
			fwrite(all_custkey, sizeof(all_custkey), 1 ,custkeyfile);
			all_countpage++;
			pageindex = 0;
		}

		all_custkey[pageindex] = custkey;
		pageindex++;
	}

	if(pageindex <= PAGESIZE && pageindex != 0) {
		fwrite(all_custkey, sizeof(int), pageindex, custkeyfile);
	}

	fclose(infile);
	fclose(custkeyfile);
}