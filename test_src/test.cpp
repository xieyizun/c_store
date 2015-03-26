# include "../src/Define.cpp"

int main() {
  FILE* test = fopen("../bin/orderkey.bin", "rb");
  FILE* bug = fopen("../bin/orderkey.txt", "w+");
  int temp;
  int count = 0;

  while(!feof(test)) {
  	if(fread(&temp, sizeof(int), 1, test) != 0) {
  		count++;
  		fprintf(bug, "%d\n", temp);
  	}
  }
  printf("%d\n", count);
  return 0;
}
