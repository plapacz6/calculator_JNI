JAVA_HOME="/usr/lib/jvm/jdk-18"

calculator_JNI : libcalc.so calculator_JNI.class libcalcm.so ./calcm_jni/calcm_JNI.class
	$(JAVA_HOME)/bin/java -Djava.library.path="." calculator_JNI



calculator_JNI.class: calculator_JNI.java
	$(JAVA_HOME)/bin/javac calculator_JNI.java

./include/calculator_JNI.h : calculator_JNI.java
	$(JAVA_HOME)/bin/javac calculator_JNI.java -h ./include

libcalc.so: ./include/calculator_JNI.h calculator_JNI.c
	gcc -o libcalc.so calculator_JNI.c -I"$(JAVA_HOME)/include" -I"$(JAVA_HOME)/include/linux" -shared -fPIC



./calcm_jni/calcm_JNI.class : ./calcm_jni/calcm_JNI.java
	$(JAVA_HOME)/bin/javac ./calcm_jni/calcm_JNI.java

./include/calcm_jni_calcm_JNI.h: ./calcm_jni/calcm_JNI.java
	$(JAVA_HOME)/bin/javac ./calcm_jni/calcm_JNI.java -h ./include

libcalcm.so: calcm_JNI.cc ./include/calcm_jni_calcm_JNI.h
	g++ -o libcalcm.so calcm_JNI.cc -I"$(JAVA_HOME)/include" -I"$(JAVA_HOME)/include/linux" -shared -fPIC




.PHONY: clean

clean:
	-rm calculator_JNI.class ./calcm_jni/calcm_JNI.class
	-rm libcalc.so libcalcm.so
	-rm ./include/calculator_JNI.h ./include/calcm_jni_calcm_JNI.h