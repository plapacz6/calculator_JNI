#include <jni.h>  // JAVA_HOME/include
#include "calculator_JNI.h"

JNIEXPORT jdouble JNICALL Java_calculator_1JNI_sum
  (JNIEnv * ptr_jnie, jobject jobj, jdouble a1, jdouble a2)
{
  return a1 + a2;
}
JNIEXPORT jdouble JNICALL Java_calculator_1JNI_odd 
  (JNIEnv * ptr_jnie, jobject jobj, jdouble a1, jdouble a2)
{
  return a1 - a2;
}
JNIEXPORT jdouble JNICALL Java_calculator_1JNI_mul
  (JNIEnv * ptr_jnie, jobject jobj, jdouble a1, jdouble a2)
{
  return a1 * a2;
}
JNIEXPORT jdouble JNICALL Java_calculator_1JNI_div
  (JNIEnv * ptr_jnie, jobject jobj, jdouble a1, jdouble a2)
{
  return a1 / a2;
}
JNIEXPORT jint JNICALL Java_calculator_1JNI_integerDiv
  (JNIEnv * ptr_jnie, jobject jobj, jint a1, jint a2)
{
  return a1 / a2;
}
JNIEXPORT jint JNICALL Java_calculator_1JNI_modulo
  (JNIEnv * ptr_jnie, jobject jobj, jint a1, jint a2)
{
  return a1 % a2;
}