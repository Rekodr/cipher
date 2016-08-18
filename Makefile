CC=gcc
CFLAGS= -I -W -lm
DEPENDENCIES= cipher.h
OBJ_en= cipher.o encryption.o
OBJ_dec= cipher.o decryption.o

%.o: %.c $(DEPENDENCIES)
	$(CC) -c -o $@ $< $(CFLAGS)

ALL: Encryption Decryption 	

Encryption: $(OBJ_en)
	$(CC) -o $@ $^ $(CFLAGS)

Decryption: $(OBJ_dec)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean: 
	rm -f $(OBJ_en) $(OBJ_dec)	