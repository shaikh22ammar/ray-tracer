
mysky: mysky.o lib/point.o lib/ray.o lib/sphere.o lib/hittable_list.o lib/interval.o lib/camera.h
	clang mysky.o lib/point.o lib/ray.o lib/interval.o lib/hittable_list.o lib/sphere.o -o mysky.out -lm

mysky.o: mysky.c lib/point.h lib/hittable.h lib/sphere.h lib/interval.h lib/ray.h lib/camera.h
	clang mysky.c -c

lib/hittable_list.o: lib/hittable_list.h lib/hittable_list.c lib/hittable.h lib/point.h lib/ray.h
	clang lib/hittable_list.c -c -o lib/hittable_list.o

lib/sphere.o: lib/sphere.c lib/sphere.h lib/point.h lib/hittable.h lib/ray.h
	clang lib/sphere.c -c -o lib/sphere.o

lib/ray.o: lib/ray.c lib/point.h lib/ray.h
	clang lib/ray.c -c -o lib/ray.o

lib/interval.o: lib/point.h lib/interval.c lib/interval.h
	clang lib/interval.c -c -o lib/interval.o

lib/point.o: lib/point.c lib/point.h
	clang lib/point.c -c -o lib/point.o

clear:
	rm *.o; rm lib/*.o
