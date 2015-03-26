//ExSorting.cpp

void ExSorting(){
	FILE *orderkeyfile, *custkeyfile;
	orderkeyfile = fopen("./bin/orderkey.bin", "rb");
	custkeyfile = fopen("./bin/custkey.bin", "rb");
	int counttemp = 0;
	int countlastpage = PAGESIZE*BUFFERSIZE;
	char path[20];
	int returnvalue;

	while(!feof(orderkeyfile)) {
		for(int i = 0; i < PAGESIZE*BUFFERSIZE; ++i) {
			returnvalue = fread(&orderCustBuffer[i].order_key, sizeof(int), 1, orderkeyfile);
			fread(&orderCustBuffer[i].cust_key, sizeof(int), 1, custkeyfile);
			if(returnvalue == 0) {
				countlastpage = i;
				break;
			}
		}

		quick_sort(orderCustBuffer, 0, countlastpage - 1);

		FILE * filetemp;
		itopath(path, counttemp);
		filetemp = fopen(path,"wb+");
		counttemp++;
		fwrite(orderCustBuffer, sizeof(struct orderCust)*countlastpage,1,filetemp);
		fclose(filetemp);
	}
  //the following codes will combine 12 tempfile into "sorted.bin"
	orderCust temp[TEMPSIZE];
	orderCust min;
	int index; //the index of the minimum data in the array temp

	FILE* tempfile[TEMPSIZE];
	FILE* sortedfile = fopen("./bin/sorted.bin", "wb+");
	bool flag = true;
  	int tempflag[12];
  	
	for(int i = 0; i < counttemp; ++i) {
    	tempflag[i] = 0;
		itopath(path, i);
		tempfile[i] =fopen(path, "rb");
	}

  while(flag) {
    for(int i = 0; i < counttemp; ++i) {
      if(tempflag[i] == 0) {
        returnvalue = fread(&temp[i], sizeof(struct orderCust), 1, tempfile[i]);
        if(returnvalue == 0)
          tempflag[i] = -1;
        else
          tempflag[i] = 1;
      }
    }

    min.cust_key = 2000000;
    for(int i = 0; i < counttemp; ++i) {
      if(temp[i].cust_key < min.cust_key && tempflag[i] == 1) {
        min = temp[i];
        index = i;
      }
    }

    if(min.cust_key == 2000000) {
      flag = false;
      continue;
    }
    fwrite(&min, sizeof(min), 1, sortedfile);
    tempflag[index] = 0;

  }

	for(int i = 0;i < counttemp; ++i) {
		itopath(path, i);
		fclose(tempfile[i]);
		remove(path);
	}
	fclose(sortedfile);
}