method2time:
	g++ method2time.cpp -o method2time -pthread -std=c++11 `pkg-config --cflags --libs opencv` && ./method2time trafficvideo.mp4
method2utility:
	g++ method2utility.cpp -o method2utility -pthread -std=c++11 `pkg-config --cflags --libs opencv` && ./method2utility trafficvideo.mp4
method1utility:
	g++ method1utility.cpp -o method1utility -pthread -std=c++11 `pkg-config --cflags --libs opencv` && ./method1utility trafficvideo.mp4
method1time:
	g++ method1time.cpp -o method1time -pthread -std=c++11 `pkg-config --cflags --libs opencv` && ./method1time trafficvideo.mp4
method2:
	g++ method2time.cpp -o method2time -pthread -std=c++11 `pkg-config --cflags --libs opencv` && ./method2time trafficvideo.mp4 && g++ method2utility.cpp -o method2utility -pthread -std=c++11 `pkg-config --cflags --libs opencv` && ./method2utility trafficvideo.mp4
method1:
	g++ method1time.cpp -o method1time -pthread -std=c++11 `pkg-config --cflags --libs opencv` && ./method1time trafficvideo.mp4 && g++ method1utility.cpp -o method1utility -pthread -std=c++11 `pkg-config --cflags --libs opencv` && ./method1utility trafficvideo.mp4
compilemethod3and4:
	g++ method3.cpp -o m3.o -pthread -std=c++11 `pkg-config --cflags --libs opencv` && g++ m4.cpp -o m4.o -pthread -std=c++11 `pkg-config --cflags --libs opencv` && g++ single.cpp -o s.o -pthread -std=c++11 `pkg-config --cflags --libs opencv` && g++ util_calc.cpp -o util
exe_m3:
	time ./m3.o
exe_m4:
	time ./m4.o
exe_1thread:
	time ./s.o
m3util:
	./util m3.txt
m4util:
	./util m4.txt
s1util:
	./util one.txt
plot1txt:
	paste -d ',' <(cut -d ',' -f2 $'utility1.txt') <(cut -d ',' -f2 $'time1.txt') > gnuplot1.dat
plot2txt:
	paste -d ',' <(cut -d ',' -f3 $'utility2.txt') <(cut -d ',' -f3 $'time2.txt') > gnuplot2.dat

