//LoadOrders.cpp

void LoadOrders() {
	all_countpage = 0;

	FILE *infile, *orderkeyfile, *custkeyfile,*totalpricefile, *shippriorityfile, *indexfile;
	infile = fopen("orders.tbl", "rb");
	orderkeyfile = fopen("./bin/orderkey.bin", "wb+");
	custkeyfile = fopen("./bin/custkey.bin", "wb+");
	totalpricefile = fopen("./bin/totalprice.bin", "wb+");
	shippriorityfile = fopen("./bin/shippriority.bin", "wb+");
	indexfile = fopen("./bin/index.bin", "wb+");

	int pageindex = 0; 

	int orderkey;
	int custkey;
	double totalprice;
	int shippriority;

	char orderkeystatus;
	char orderdate[16], orderpriority[16], clerk[16], comment[80];

    //index 
    bool flag = true;//flag is to judge whether the orderkey is the first orderkey of each page
    int count = 0;
 
	while(fscanf(infile,"%d|%d|%c|%lf|%[^|]|%[^|]|%[^|]|%d|%[^|]|\n", &orderkey, &custkey, &orderkeystatus,
		&totalprice, orderdate, orderpriority, clerk, &shippriority, comment) != EOF) {
	
		if(pageindex >= PAGESIZE) {
			fwrite(all_orderkey, sizeof(all_orderkey), 1 ,orderkeyfile);
			fwrite(all_custkey, sizeof(all_custkey), 1 ,custkeyfile);
			fwrite(all_totalprice, sizeof(all_totalprice), 1 ,totalpricefile);
			fwrite(all_shippriority, sizeof(all_shippriority), 1 ,shippriorityfile);
			all_countpage++;
            count++;
			pageindex = 0;
			flag = true;
		}
		//index
		//create index table which stores the first orderkey of each page with the size of 4k, that is to
		//said each page contains 1024 orderkeys
        if (flag == true) {
           indexTable[count].headValue = orderkey;
           indexTable[count].pageid = all_countpage;        
           flag = false;
        }
        //index
        //if all the 128 pages that are read into the memory each time has been deal with
        //there is no space of indexTable, so we need to write it to the indexfile and
        //allocate another indexTable with the size of 128
        if ((count + 1) == PAGESIZE) {
        	fwrite(indexTable, sizeof(Index)*PAGESIZE, 1, indexfile);
            count = -1;
        }

		all_orderkey[pageindex] = orderkey;
		all_custkey[pageindex] = custkey;
		all_totalprice[pageindex] = totalprice;
		all_shippriority[pageindex] = shippriority;

		pageindex++;
	}

	if(pageindex <= PAGESIZE && pageindex != 0) {
		fwrite(all_orderkey, sizeof(int), pageindex, orderkeyfile);
		fwrite(all_custkey, sizeof(int), pageindex, custkeyfile);
		fwrite(all_totalprice, sizeof(double), pageindex, totalpricefile);
		fwrite(all_shippriority, sizeof(int), pageindex, shippriorityfile);
	}
	//index  
    if ((count + 1) != PAGESIZE)
    	fwrite(indexTable, sizeof(Index) * (count + 1), 1, indexfile);
    //test
    /*
    Index *test = new Index[1467];
    rewind(indexfile);
    fread(test, sizeof(Index), 1467, indexfile);
    for (int i = 0; i < 1467; i++) {
    	printf("pageid: %d headValue: %d\n", test[i].pageid, test[i].headValue);
    }
    */

    
	fclose(infile);
	fclose(orderkeyfile);
	fclose(custkeyfile);
	fclose(totalpricefile);
	fclose(shippriorityfile);	
	fclose(indexfile);
}