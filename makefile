CC=gcc-15 -std=c99


main: main.c lib/camera.h lib/materials.o lib/random.o lib/sphere.o lib/hittable.o lib/color.o lib/ray.o lib/point.o 
	$(CC) -fopenmp main.c lib/materials.o lib/random.o lib/sphere.o lib/hittable.o lib/color.o lib/ray.o lib/point.o -lm -o main.out

test: test.c lib/color.o lib/point.o
	$(CC) test.c lib/color.o lib/point.o -o test.out

lib/materials.o: lib/materials.h lib/materials.c lib/point.o lib/ray.o lib/hittable.o lib/random.o
	$(CC) -c lib/materials.c -o lib/materials.o -lm

lib/random.o: lib/random.h lib/random.c lib/point.o
	$(CC) -c lib/random.c -o lib/random.o -lm

lib/sphere.o: lib/sphere.h lib/sphere.c lib/hittable.o
	$(CC) -c lib/sphere.c -o lib/sphere.o -lm

lib/hittable.o: lib/hittable.h lib/hittable.c lib/ray.o lib/point.o
	$(CC) -c lib/hittable.c -o lib/hittable.o

lib/color.o: lib/color.h lib/color.c lib/point.o
	$(CC) -c lib/color.c -o lib/color.o -lm

lib/ray.o: lib/ray.h lib/ray.c lib/point.o
	$(CC) -c lib/ray.c -o lib/ray.o

lib/point.o: lib/point.h lib/point.c
	$(CC) -c lib/point.c -o lib/point.o -lm

clean:
	rm *.o; rm lib/*.o
