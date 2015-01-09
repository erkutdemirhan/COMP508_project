all:
	g++ main.cpp enh.cpp harris.cpp -o cornerdet `pkg-config --libs --cflags opencv` 
	mkdir ./output_images

clean:
	rm -f cornerdet
	rm -rf ./output_images

test:
	g++ test.cpp enh.cpp harris.cpp -o cornerdet `pkg-config --libs --cflags opencv` 
	mkdir ./output_images
