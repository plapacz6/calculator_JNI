JAVA_HOME="/usr/lib/jvm/jdk-18"

calculator_JNI : libcalc.so calculator_JNI.class
	$(JAVA_HOME)/bin/java -Djava.library.path="." calculator_JNI

calculator_JNI.class: calculator_JNI.java
	$(JAVA_HOME)/bin/javac calculator_JNI.java

calculator_JNI.h : calculator_JNI.java
	$(JAVA_HOME)/bin/javac calculator_JNI.java -h .

libcalc.so: calculator_JNI.h calculator_JNI.c
	gcc -o libcalc.so calculator_JNI.c -I"$(JAVA_HOME)/include" -I"$(JAVA_HOME)/include/linux" -shared -fPIC

.PHONY: clean

clean:
	-rm calculator_JNI.class
	-rm libcalc.so
	-rm calculator_JNI.h