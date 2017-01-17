hmap.o: hmap.c hmap.h
	gcc -c hmap.c

pq.o: pq.c pq.h
	gcc -c pq.c

travel: hmap.o pq.o travel.c
	gcc travel.c hmap.o pq.o -o travel

clean: 
	rm -f *.o travel
