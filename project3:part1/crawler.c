#include "crawler.h"
#include "indexPage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


/*
 * returns 1 if the list starting at pNode contains the address addr,
 *    and returns 0 otherwise
 */
int contains( struct listNode *pNode,  char *addr){
  // TODO: complete this
  //str compare
  if(strcmp(pNode->addr, addr) == 0){
    return 1;
  }
  else if(pNode->next != NULL){
    return contains(pNode->next, addr);
  }
  else{
    return 0;
  }
}
    

/*
 * inserts the address addr as a new listNode at the end of
 *    the list
 */
void insertBack(struct listNode *pNode,  char *addr){
  // TODO: complete this
  if(pNode->next != NULL){
    insertBack(pNode->next,addr);
  }
  else if (pNode->next == NULL)
  {
    struct listNode *newNode = NULL;
    newNode = malloc(sizeof(struct listNode));
    newNode->next = NULL;
    // copy addr to newNode->addr
    strcpy((newNode->addr), addr);
    pNode->next = newNode;
  }
  
}


/*
 * prints the addresses from pNode to the end of the list,
 *   one on each line
 */
void printAddresses(struct listNode *pNode,  struct TrieNode** root,int* trieNumber){
  char* word = malloc(sizeof(char) * 50);
  int* count = malloc(sizeof(int));
  *count = 0;
  printf("%s\n", pNode->addr);
  if(root[*trieNumber] != NULL){
  printTrieContents(root[*trieNumber],word,count);
  (*trieNumber)++;
  }
  if (pNode->next != NULL){
    printAddresses(pNode->next, root, trieNumber);
  }
  free(word);
  free(count);
}

/*
 * frees the memory associated with this node and all subsequent nodes
 */
void destroyList(struct listNode *pNode){
  
  if(pNode->next != NULL){
    destroyList(pNode->next);
  }
  free(pNode);
}
  


int getLink( char* srcAddr, char* link,  int maxLinkLength){
  const int bufSize = 1000;
  char buffer[bufSize];

  int numLinks = 0;

  FILE *pipe;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getLinks.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n", buffer);
    return 0;
  }

  fscanf(pipe, "%d\n", &numLinks);

  if(numLinks > 0){
    int linkNum;
    double r = (double)rand() / ((double)RAND_MAX + 1.0);

    for(linkNum=0; linkNum<numLinks; linkNum++){
      fgets(buffer, bufSize, pipe);
      
      if(r < (linkNum + 1.0) / numLinks){
		    break;
      }
    }

    /* copy the address from buffer to link */
    strncpy(link, buffer, maxLinkLength);
    link[maxLinkLength-1] = '\0';
    
    /* get rid of the newline */
    {
      char* pNewline = strchr(link, '\n');
      if(pNewline != NULL){
		    *pNewline = '\0';
      }
    }
  }

  pclose(pipe);

  if(numLinks > 0){
    return 1;
  }
  else{
    return 0;
  }
}
