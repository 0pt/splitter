/*
 * 拡張事項：
 * 複数の区切り文字を扱える同様な関数を作る done
 * 格納領域も同時に確保する同様な関数を作る done
 * 正規表現に対応する
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

void show(char **dar){
	for(int i=0; dar[i]!=0; i++){
		printf("%s\n",dar[i]);
	}
}

int split(int n, int w, char **dar, char *src, int del){
	for(int i=0; i<n; i++){
		for(int j=0; j<w+1; j++){
			// if n is small
			if((*src == del || j == w) && i == n-1){
				dar[i][j] = '\0';
				dar[i+1] = 0;
				return 0;
			}

			if(*src == del || j == w){
				dar[i][j] = '\0';
				while(*src != del && *src != '\0'){
					src++;
				}
				if(*src == '\0'){
					dar[i+1] = 0;
					return 0;
				}
				src++;
				break;
			}else if(*src == '\0'){
				dar[i][j] = '\0';
				dar[i+1] = 0;
				return 0;
			}else{
				dar[i][j] = *src;
				src++;
			}
		}
	}
	
	return -1;
}

int split_multi(int n, int w, char **dar, char *src, char *del){
	bool flag = false;
	for(int i=0; i<n; i++){
		for(int j=0; j<w+1; j++){
			// printf("%d %d",i,j);
			flag = false;
			for(int k=0; k<strlen(del); k++){
				if(del[k] == *src){
					flag = true;
				}
			}

			if((flag || j == w) && i == n-1){
				dar[i][j] = '\0';
				dar[i+1] = 0;
				return 0;
			}

			if(flag || j == w){
				dar[i][j] = '\0';
				while(true){
					flag = false;
					for(int k=0; k<strlen(del); k++){
						if(del[k] == *src || *src == '\0'){
							flag = true;
							break;
						}
					}
					if(flag) break;
					src++;
				}
				src++;
				break;
			}else if(*src == '\0'){
				dar[i+1] = 0;
				return 0;
			}else{
				dar[i][j] = *src;
				src++;
			}
		}
	}
	dar[n] = 0;
	return -1;
}

char **allocsplit(char *src, int del){
	int slen = strlen(src);
	char *tmp = (char *)malloc(sizeof(char)*(slen+1));
	int cnt = 0;
	for(int i=0; i<slen; i++){
		if(*(src+i) == del) cnt++;
	}
	char **dar = (char **)malloc(sizeof(char *)*(cnt+1));
	bool flag = true;
	while(*src != '\0'){
		if(flag){
			*dar = tmp;
			dar++;
			flag = false;
		}
		if(*src == del){
			*tmp = '\0';
			tmp++;
			flag = true;
		}else{
			*tmp = *src;
			tmp++;
		}
		src++;
	}
	*tmp = '\0';
	*dar = 0;
	return dar-cnt-1;
}

int main(){
   	char *s = "abc def geh qr tf-23wd jfsak;ldfj dfa,ads";
	printf("%s\n",s);
	printf("--- split ---\n");
	int n=7;
	char **d1 = (char **)malloc(sizeof(char *)*(n));
	char **d2 = (char **)malloc(sizeof(char *)*(n));
	char **d3 = (char **)malloc(sizeof(char *)*(n));
	
	for(int i=0; i<n; i++){
		d1[i] = (char *)malloc(sizeof(char)*BUFSIZ);
		d2[i] = (char *)malloc(sizeof(char)*BUFSIZ);
		d3[i] = (char *)malloc(sizeof(char)*BUFSIZ);
	}

	int diver = ' ';
    char *l = " =,;-";
	int w = 5;
	// printf("split=%d\n",split(n, BUFSIZ, d1, s, diver));
	split(n, w, d1, s, diver);
	show(d1);
	printf("--- split_multi ---\n");
	// printf("split_multi=%d\n",split_multi(n, BUFSIZ, d2, s, l));
	split_multi(n, w, d2, s, l);
	show(d2);
	printf("--- allocsplit ---\n");
	char **tmp = allocsplit(s, diver);
	show(tmp);
	return 0;
}
