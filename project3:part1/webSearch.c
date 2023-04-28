//add header guards
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "indexPage.h"
#include "crawler.h"


//arguments: file containing urls to index and # of hops, max # of pages to index, long for srand

int main(int argc, char** argv){

int MAX_N = atoi(argv[2]);//max number of pages to index
char url [MAX_ADDR_LENGTH]; 
char newUrl[MAX_ADDR_LENGTH];
int hopsLimit, hopNum, res;
int numberOfPagesIndexed = 0;
int hasNextUrl = 1;
struct listNode* urlList = malloc(sizeof(struct listNode));
struct TrieNode** trieList = malloc(sizeof(struct TrieNode*) * (MAX_N + 1));
FILE* fp;


//Not enough arguments given
if(argc <= 3) {
  printf("Not enough argumetns given");
  exit(-1);
}
srand(atol(argv[3]));
numberOfPagesIndexed = 0;

//sets up array of tries
for(int i = 0; i < MAX_N; i++){
    trieList[i] = malloc(sizeof(struct TrieNode));
    setupNode(trieList[i]);
}
fp = fopen(argv[1], "r");
if(fp == NULL){
    printf("The file could not be opened");
    exit(-1);
}
// hopsLimit = atoi(argv[1]);

//gets URLs and number of hops
printf("Indexing...\n");
while(hasNextUrl != 0 && numberOfPagesIndexed < MAX_N){
    //reads line from the file
    res = fscanf(fp, "%s%d",url,&hopsLimit);
    hopNum = 0;
    if (res != 2){
        //line could not be read
        hasNextUrl = 0;
    }
    if (res == EOF){
        //reached the end of URL file
        hasNextUrl = 0;
        break;
    }
    
    //checks if URL has been crawled
    while(!0){
        //crawl the url
        if(numberOfPagesIndexed == 0){
            strncpy(urlList->addr,url, MAX_ADDR_LENGTH);
            urlList->next = NULL;
            indexPage(url,trieList[numberOfPagesIndexed]);
            numberOfPagesIndexed++;
        }
        if (contains(urlList, url) == 0 ){
            insertBack(urlList, url);
            indexPage(url,trieList[numberOfPagesIndexed]);
            numberOfPagesIndexed++;
            
        }
        hopNum++;
        if(hopNum <= hopsLimit && numberOfPagesIndexed < MAX_N){
            //new_url one hop from url(according to getLink)
            int urlRes = getLink(url, newUrl, MAX_ADDR_LENGTH);
            if(urlRes == 0){
                break;
            }
            strncpy(url, newUrl, MAX_ADDR_LENGTH);
        }
        else{
            break;    
        }
    }//end while
}//end while


fclose(fp);
destroyList(urlList);
for(int i = 0; i < MAX_N +1; i++){
    free(trieList[i]);
}
free(trieList);

return 0;
}