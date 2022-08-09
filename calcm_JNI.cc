#include <vector>
#include <iostream>
#include "./include/calcm_jni_calcm_JNI.h"

using namespace std;

JNIEXPORT void JNICALL Java_calcm_1jni_calcm_1JNI_info
  (JNIEnv *, jobject)
{
  cout << "calcm library" << endl;
}