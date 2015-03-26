#include "Define.cpp"
#include "LoadOrders.cpp"
#include "Query.cpp"
#include "ExSorting.cpp"
#include "Compress.cpp"
#include "Join.cpp"
#include "LoadCustomer.cpp"
#include "Count.cpp"

int main(int argc, char *argv[]) {
	if((argc == 3) && (strcmp(argv[0], "./db") == 0) &&
		(strcmp(argv[1], "load") == 0) && (strcmp(argv[2], "orders") == 0)) {
		LoadOrders();
	} else if ((argc == 3) && (strcmp(argv[0], "./db") == 0) &&
		(strcmp(argv[1], "load") == 0) && (strcmp(argv[2], "customer") == 0)) {
		LoadCustomer(); 
	} else if((argc == 3) && (strcmp(argv[0], "./db") == 0) &&
		(strcmp(argv[1], "retrieve") == 0) && (strcmp(argv[2], "orders") == 0)) {
		int temp, cus, ship;
		double total;
		while(scanf("%d", &temp)) {
			Query(temp, cus, total, ship);
			if (cus != -1) {
				printf("%d %.2lf %d\n", cus, total, ship);
			} else {
				printf("no relevant record\n");
			}
		}
	} else if((argc == 4) && (strcmp(argv[0], "./db") == 0) && (strcmp(argv[1], "compress") == 0) && (strcmp(argv[2], "orders") == 0)
		      && (strcmp(argv[3], "1") == 0)) {
		ExSorting();
		Compress();
	} else if ((argc == 2) && (strcmp(argv[0], "./db") == 0) && (strcmp(argv[1], "join") == 0)) {
		Join();
	} else if ((argc == 2) && (strcmp(argv[0], "./db") == 0) && (strcmp(argv[1], "count") == 0)) {
		int count = Count();
		printf("Total number of orders: %d\n", count);
	} 
	else {
		printf("wrong command, please refer to readme\n");
	}

	return 0;
}