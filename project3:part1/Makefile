

CC = gcc
CFLAGS = -g

OBJS = crawler.o indexPage.o

webSearch: webSearch.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@