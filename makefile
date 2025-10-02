CC=gcc-15 

mysky: mysky.o lib/point.o lib/ray.o lib/sphere.o lib/hittable_list.o lib/interval.o lib/random.o lib/color.o
	$(CC) -fopenmp mysky.o lib/point.o lib/ray.o lib/interval.o lib/hittable_list.o lib/sphere.o lib/random.o lib/color.o -o mysky.out 

mysky.o: mysky.c lib/color.h lib/random.h lib/camera.h lib/point.h lib/hittable.h lib/sphere.h lib/interval.h lib/ray.h lib/materials.h
	$(CC) -fopenmp -c mysky.c -o mysky.o 

lib/sphere.o: lib/sphere.c lib/sphere.h lib/point.h lib/hittable.h lib/ray.h
	$(CC) lib/sphere.c -c -o lib/sphere.o

lib/hittable_list.o: lib/hittable_list.h lib/hittable_list.c lib/hittable.h lib/point.h lib/ray.h
	$(CC) lib/hittable_list.c -c -o lib/hittable_list.o

lib/color.o: lib/color.c lib/color.h lib/point.o
	$(CC) lib/color.c -c -o lib/color.o

lib/random.o: lib/point.o
	$(CC) -lm lib/random.c -c -o lib/random.o

lib/interval.o: lib/point.h lib/interval.c lib/interval.h
	$(CC) lib/interval.c -c -o lib/interval.o

lib/ray.o: lib/ray.c lib/point.h lib/ray.h
	$(CC) lib/ray.c -c -o lib/ray.o

lib/point.o: lib/point.c lib/point.h
	$(CC) lib/point.c -c -o lib/point.o

clean:
	rm *.o; rm lib/*.o
