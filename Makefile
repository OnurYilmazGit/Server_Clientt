all:
	gcc -o server server.c kitchen.c -pthread
	gcc -o client client.c
clean :
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 