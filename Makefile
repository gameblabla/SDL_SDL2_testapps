PRGNAME     = test.elf
CC			= gcc

OBJS		= main.o

CFLAGS		= -O0

CXXFLAGS = $(CFLAGS)

LDFLAGS     =  -lc -lgcc -lm -lSDL -lz -Wl,--as-needed -Wl,--gc-sections -s -flto


# Rules to make executable
$(PRGNAME): $(OBJS)  
	$(CC) $(CFLAGS)  -o $(PRGNAME) $^ $(LDFLAGS)

$(OBJ_C) : %.o : %.c
	$(CC) $(CFLAGS) -std=gnu99 -c -o $@ $<

clean:
	rm -f $(PRGNAME) *.o
