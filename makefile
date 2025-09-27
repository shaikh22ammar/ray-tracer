
mysky: mysky.o lib/point.o lib/ray.o lib/sphere.o
	clang mysky.o lib/point.o lib/ray.o lib/sphere.o -o mysky.out

mysky.o: lib/point.h mysky.c
	clang mysky.c -c

lib/sphere.o: lib/sphere.c lib/sphere.h lib/point.h lib/ray.h
	clang lib/sphere.c -c -o lib/sphere.o

lib/ray.o: lib/ray.c lib/point.h lib/ray.h
	clang lib/ray.c -c -o lib/ray.o

lib/point.o: lib/point.c lib/point.h
	clang lib/point.c -c -o lib/point.o

clear:
	rm *.o; rm lib/*.o
