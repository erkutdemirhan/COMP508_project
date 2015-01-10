all:
	g++ main.cpp enh.cpp harris.cpp -o cornerdet `pkg-config --libs --cflags opencv` 
	mkdir ./output_images

clean:
	rm -f cornerdet
	rm -rf ./output_images

test:
	g++ HashEntryModel.cpp HashKeyModel.cpp HashKeyScene.cpp enh.cpp harris.cpp helperMethods.cpp matching.cpp preprocessor.cpp test.cpp -o cornerdet `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -O0 -g3 -Wall
	mkdir ./output_images
	
#	echo "Building file: ./Comp508_Project.cpp"
#	g++ `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -O0 -g3 -Wall -c ./Comp508_Project.cpp -o ./Comp508_Project.o 
	 
#	echo "Building file: ./HashEntryModel.cpp"
#	g++ `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -O0 -g3 -Wall -c ./HashEntryModel.cpp -o ./HashEntryModel.o 
	 
#	echo "Building file: ./HashKeyModel.cpp"
#	g++ `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -O0 -g3 -Wall -c ./HashKeyModel.cpp -o ./HashKeyModel.o
	 
#	echo "Building file: ./HashKeyScene.cpp"
#	g++ `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -O0 -g3 -Wall -c ./HashKeyScene.cpp -o ./HashKeyScene.o
	 
#	echo "Building file: ./enh.cpp"
#	g++ `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -O0 -g3 -Wall -c ./enh.cpp -o ./enh.o
	 
#	echo "Building file: ./harris.cpp"
#	g++ `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -O0 -g3 -Wall -c ./harris.cpp -o ./harris.o
	 
#	echo "Building file: ./helperMethods.cpp"
#	g++ `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -g3 -Wall -c ./helperMethods.cpp -o ./helperMethods.o
	 
#	echo "Building file: ./matching.cpp"
#	g++ `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -O0 -g3 -Wall -c ./matching.cpp -o ./matching.o
	 
#	echo "Building file: ./preprocessor.cpp"
#	g++ `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -O0 -g3 -Wall -c ./preprocessor.cpp -o ./preprocessor.o
	 
#	echo "Building file: ./test.cpp"
#	g++ `pkg-config --libs --cflags opencv` -I./boost_1_57_0 -I./eigen_3_2_3 -O0 -g3 -Wall -c ./test.cpp -o ./test.o
	 
#	echo "Building target: Comp508_Project"
#	g++ `pkg-config --libs --cflags opencv` -o "Comp508_Project" ./HashEntryModel.o ./HashKeyModel.o ./HashKeyScene.o ./enh.o ./harris.o ./helperMethods.o ./matching.o ./preprocessor.o ./test.o
	
#	mkdir ./output_image
