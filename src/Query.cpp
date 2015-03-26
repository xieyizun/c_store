//Query.cpp

void Query(int s_orderkey, int& s_custkey, double& s_totalprice, int& s_shippriority ) {
	FILE *orderkeyfile, *custkeyfile,*totalpricefile, *shippriorityfile, *indexfile;

	orderkeyfile = fopen("./bin/orderkey.bin", "rb");
	custkeyfile = fopen("./bin/custkey.bin", "rb");
	totalpricefile = fopen("./bin/totalprice.bin", "rb");
	shippriorityfile = fopen("./bin/shippriority.bin", "rb");
	indexfile = fopen("./bin/index.bin", "rb");

	int page = 0; //record the page when starting querying
	int targetrid = 0; //record the rid of the record
	bool flag = false; //if the record being queried exists,set true
	
	int pageid = 0;
	int pre_pageid = 0;
	bool pagefound_flag = false;
    int search_pageid = 0;
 
    //search the pageid of the target orderkey in the indexfile
    while (!feof(indexfile)) {
    	int count = fread(indexs, sizeof(Index),(PAGESIZE / 2) * BUFFERSIZE, indexfile);
    	for (int i = 0; i < count; i++) {
    		if (s_orderkey == indexs[i].headValue) {
    			pageid = indexs[i].pageid;
    			pagefound_flag = true;
    			break;
    		} else if (s_orderkey > indexs[i].headValue) {
    			pre_pageid = indexs[i].pageid;
    		} else if (s_orderkey < indexs[i].headValue) {
    			pageid = pre_pageid;
    			pagefound_flag = true;
    			break;
    		}
    	}
    }
    //when we have got the corresponding page or we didn't get and so we need to only search
    //the last page, search the orderkey in the page 
	if (pagefound_flag == true || (pagefound_flag == false && feof(indexfile) == true)) {
		if (pagefound_flag == true)
			search_pageid = pageid;
		else if (pagefound_flag == false && feof(indexfile) == true) {
			search_pageid = pre_pageid;
		}

		fseek(orderkeyfile, sizeof(int)*PAGESIZE*search_pageid, SEEK_SET);
	
	    //search the orderkey in the only page that may contains the orderkey
	    int *buffer = new int[PAGESIZE];
	    fread(buffer, sizeof(int)*PAGESIZE, 1, orderkeyfile);

		for(int i = 0; i < PAGESIZE; i++) {
			if(buffer[i] == s_orderkey) {
				flag = true;
				targetrid = i;
				break;
			}
		}

		if(flag == true) {
			fseek(custkeyfile, sizeof(int)*(PAGESIZE * search_pageid + targetrid), SEEK_SET);
			fread(&s_custkey, sizeof(int), 1, custkeyfile);

			fseek(totalpricefile, sizeof(double)*(PAGESIZE * search_pageid + targetrid), SEEK_SET);
			fread(&s_totalprice, sizeof(double), 1, totalpricefile);

			fseek(shippriorityfile, sizeof(int)*(PAGESIZE * search_pageid + targetrid), SEEK_SET);
			fread(&s_shippriority, sizeof(int), 1, shippriorityfile);
		} else if(flag == false) {
			s_custkey = s_totalprice = s_shippriority = -1;
		}

	}
	
	fclose(orderkeyfile);
	fclose(custkeyfile);
	fclose(totalpricefile);
	fclose(shippriorityfile);
}