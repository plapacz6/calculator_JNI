#include <vector>
#include <iostream>
#include "./include/calcm_jni_calcm_JNI.h"  //generated for c++  (for c diffrent headers are include inside)
/*
 (*env)->GetObjectClass(env, obj);  //c   "FieldAccess.h"
 env->GetObjectCalss(obj);          //c++ "???"
*/
using namespace std;

JNIEXPORT void JNICALL Java_calcm_1jni_calcm_1JNI_info
  (JNIEnv *, jobject)
{
  cout << "calcm library" << endl;
}

const int c_str_mtx_size = 1024;
/*
 * Class:     calcm_jni_calcm_JNI
 * Method:    mtx_dot
 * Signature: (Lmgui/mgui;)V
 */
JNIEXPORT void JNICALL Java_calcm_1jni_calcm_1JNI_mtx_1dot
  (JNIEnv * env, jobject calcm_obj, jobject gmui_obj){    
    const char* c_str_mtx1 = NULL;
    const char* c_str_mtx2 = NULL;
    const char* c_str_mtxR = NULL;

    string string_mtx1;    
    string string_mtx2;    
    string string_mtxR;    

    jclass gmui_class = env->GetObjectClass(gmui_obj);
    
    jfieldID mtx1_id = env->GetFieldID(gmui_class, "mtx1", "Ljava/lang/String;");   //!!! ; at the end of type signature 
    //jobject jobject_mtx1 = env->GetObjectField( gmui_obj, mtx1_id);
    jstring jstring_mtx1 = (jstring)env->GetObjectField( gmui_obj, mtx1_id);    
    c_str_mtx1 = env->GetStringUTFChars(jstring_mtx1, JNI_FALSE);
    string_mtx1 = c_str_mtx1;      
    //cout << "obtained mtx1 form object mgui: " << string_mtx1 << endl;

    jfieldID mtx2_id = env->GetFieldID(gmui_class, "mtx2", "Ljava/lang/String;");
    jstring jstring_mtx2 = (jstring)env->GetObjectField( gmui_obj, mtx2_id);
    c_str_mtx2 = env->GetStringUTFChars(jstring_mtx2, JNI_FALSE);
    string_mtx2 = c_str_mtx2;


    //math operations
    string_mtxR = string_mtx1 + "\n dot(.) \n" + string_mtx2;


    jfieldID mtxR_id = env->GetFieldID(gmui_class, "mtxR", "Ljava/lang/String;");
    jstring jstring_mtxR = env->NewStringUTF( string_mtxR.c_str());
    env->SetObjectField( gmui_obj, mtxR_id, jstring_mtxR);

    env->ReleaseStringUTFChars(jstring_mtx1, c_str_mtx1);    
    env->ReleaseStringUTFChars(jstring_mtx2, c_str_mtx2);    
  }

/*
 * Class:     calcm_jni_calcm_JNI
 * Method:    mtx_mul
 * Signature: (Lmgui/mgui;)V
 */
JNIEXPORT void JNICALL Java_calcm_1jni_calcm_1JNI_mtx_1mul
  (JNIEnv * env, jobject calcm_obj, jobject gmui_obj){
const char* c_str_mtx1 = NULL;
    const char* c_str_mtx2 = NULL;
    const char* c_str_mtxR = NULL;

    string string_mtx1;    
    string string_mtx2;    
    string string_mtxR;    

    jclass gmui_class = env->GetObjectClass(gmui_obj);
    
    jfieldID mtx1_id = env->GetFieldID(gmui_class, "mtx1", "Ljava/lang/String;");   //!!! ; at the end of type signature     
    jstring jstring_mtx1 = (jstring)env->GetObjectField( gmui_obj, mtx1_id);    
    c_str_mtx1 = env->GetStringUTFChars(jstring_mtx1, JNI_FALSE);
    string_mtx1 = c_str_mtx1;      
    
    jfieldID mtx2_id = env->GetFieldID(gmui_class, "mtx2", "Ljava/lang/String;");
    jstring jstring_mtx2 = (jstring)env->GetObjectField( gmui_obj, mtx2_id);
    c_str_mtx2 = env->GetStringUTFChars(jstring_mtx2, JNI_FALSE);
    string_mtx2 = c_str_mtx2;


    //math operations
    string_mtxR = string_mtx1 + "\n MUL(.) \n" + string_mtx2;


    jfieldID mtxR_id = env->GetFieldID(gmui_class, "mtxR", "Ljava/lang/String;");
    jstring jstring_mtxR = env->NewStringUTF( string_mtxR.c_str());
    env->SetObjectField( gmui_obj, mtxR_id, jstring_mtxR);

    env->ReleaseStringUTFChars(jstring_mtx1, c_str_mtx1);    
    env->ReleaseStringUTFChars(jstring_mtx2, c_str_mtx2);    
  }