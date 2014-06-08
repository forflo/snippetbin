call.c: 

hashing: hashing.c 
	gcc -c hashing.c 

db: db.c
	gcc -c db.c 


test_hashing: hashing.c hashing.test
	gcc -o hashing.test hashing.test.c -lcunit hashing.c -lcrypto ;\
	./hashing.test
