#include <stdio.h>
#include <stdlib.h>

void show(char **s, int n){
	for(int i=0; i<n; i++){
		printf("%s\n",s[i]);
	}
	printf("------\n");
}

int join(int dlen, char *dst, int n, char **sar){
	char div = '-';
	for(int i=0; i<n; i++){
		for(int j=0; j<dlen+1; j++){
//			printf("%c\n",sar[i][j]);
			if(sar[i][j] != '\0'){
				*dst = sar[i][j];
				dst++;
			}else{
				if(i < n-1){
					*dst = div;
					dst++;
					break;
				}else{
					*dst = '\0';
					return 0;
				}
			}
		}
	}
	return -1;
}

int main(){
	char *s[6] = {"ABC", "CD", "EF","GHIJ","KLMNOPQRSTU","VW"};
	int num = 5;
	int len = BUFSIZ;
	show(s,6);
	char *d = (char *)malloc(sizeof(char)*(len*(num+1)));
//	printf("%d\n",join(len,d,num,s));
	join(len,d,num,s);
	printf("%s\n",d);
}
