all:
	g++ main.cpp -o cornerdet `pkg-config --libs --cflags opencv` 
	mkdir ./output_images
clean:
	rm -f cornerdet
	rm -rf ./output_images
