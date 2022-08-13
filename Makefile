JAVA_HOME="/usr/lib/jvm/jdk-18"

calculator_JNI : libcalc.so calculator_JNI.class libcalcm.so ./calcm_jni/calcm_JNI.class ./mgui/mgui.class
	$(JAVA_HOME)/bin/java -Djava.library.path="." calculator_JNI



calculator_JNI.class: calculator_JNI.java ./mgui/mgui.java
	$(JAVA_HOME)/bin/javac calculator_JNI.java

./include/calculator_JNI.h : calculator_JNI.java
	$(JAVA_HOME)/bin/javac calculator_JNI.java -h ./include

libcalc.so: ./include/calculator_JNI.h calculator_JNI.c
	gcc -o libcalc.so calculator_JNI.c -I"$(JAVA_HOME)/include" -I"$(JAVA_HOME)/include/linux" -shared -fPIC



./calcm_jni/calcm_JNI.class : ./calcm_jni/calcm_JNI.java ./mgui/mgui.java
	$(JAVA_HOME)/bin/javac ./calcm_jni/calcm_JNI.java

./include/calcm_jni_calcm_JNI.h: ./calcm_jni/calcm_JNI.java
	$(JAVA_HOME)/bin/javac ./calcm_jni/calcm_JNI.java -h ./include

libcalcm.so: calcm_JNI.cc ./include/calcm_jni_calcm_JNI.h
	g++ -o libcalcm.so calcm_JNI.cc -I"$(JAVA_HOME)/include" -I"$(JAVA_HOME)/include/linux" -shared -fPIC



./mgui/mgui.class : ./mgui/mgui.java ./calcm_jni/calcm_JNI.java
	$(JAVA_HOME)/bin/javac ./mgui/mgui.java

./include/mgui.h : ./mgui/mgui.java
	$(JAVA_HOME)/bin/javac ./mgui/mgui.java -h ./include


mgui: ./mgui/mgui.class
	$(JAVA_HOME)/bin/java -Djava.library.path="." mgui.mgui



.PHONY: clean


FILE_TO_DELETE=\
	calculator_JNI.class \
	./include/calculator_JNI.h \
	libcalc.so \
	\
	./calcm_jni/calcm_JNI.class \
	./include/calcm_jni_calcm_JNI.h	\
	libcalcm.so \
	\
	./mgui/mgui.class \


clean:	
	-for FILE in $(FILE_TO_DELETE); do	printf $$FILE; rm $$FILE ; done;


	
	
	