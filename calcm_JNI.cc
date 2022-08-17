#include <vector>
#include <iostream>
#include <string>
#include <string_view>

#include "./include/calcm_jni_calcm_JNI.h"  //generated for c++  (for c diffrent headers are include inside)
/*
 (*env)->GetObjectClass(env, obj);  //c   "FieldAccess.h"
 env->GetObjectCalss(obj);          //c++ "???"
*/
using namespace std;

vector <vector <double> >& str2vvd_v2( string mtx, vector< vector<double> >& vvd);
vector <vector <double> >& str2vvd_v1( string mtx, vector< vector<double> >& vvd);

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
    string_mtxR = string_mtx1 + "\n MUL(.) \n" + string_mtx2;
    vector< vector<double> > vvd;
    vvd = str2vvd_v2(string_mtx1, vvd);


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

    string string_mtx1;    
    string string_mtx2;    
    string string_mtxR;    

    jclass gmui_class = env->GetObjectClass(gmui_obj);
    
    jfieldID mtx1_id = env->GetFieldID(gmui_class, "mtx1", "Ljava/lang/String;");
    jstring jstring_mtx1 = (jstring)env->GetObjectField( gmui_obj, mtx1_id);    
    c_str_mtx1 = env->GetStringUTFChars(jstring_mtx1, JNI_FALSE);
    string_mtx1 = c_str_mtx1;      
    
    jfieldID mtx2_id = env->GetFieldID(gmui_class, "mtx2", "Ljava/lang/String;");
    jstring jstring_mtx2 = (jstring)env->GetObjectField( gmui_obj, mtx2_id);
    c_str_mtx2 = env->GetStringUTFChars(jstring_mtx2, JNI_FALSE);
    string_mtx2 = c_str_mtx2;


    //math operations
    string_mtxR = string_mtx1 + "\n ADD(.) \n" + string_mtx2;


    jfieldID mtxR_id = env->GetFieldID(gmui_class, "mtxR", "Ljava/lang/String;");
    jstring jstring_mtxR = env->NewStringUTF( string_mtxR.c_str());
    env->SetObjectField( gmui_obj, mtxR_id, jstring_mtxR);

    env->ReleaseStringUTFChars(jstring_mtx1, c_str_mtx1);    
    env->ReleaseStringUTFChars(jstring_mtx2, c_str_mtx2);    
  }

  //-------------------------------------------------

vector <vector <double> >& str2vvd_v1(
  string mtx, vector< vector<double> >& vvd)
{
  #ifdef CALC_DEBUG
  cout << "str2vvd_v1" << endl;
  #endif

  string digit_dot_newLine = "0123456789.\n";
  string digit;
  vector<double> vd;  

  std::string::size_type i = 0;
  std::string::size_type prev_i = 0;
  //long int prev_i = -1;
  bool row_just_added = false;
  bool digit_just_added = false;

  while(
    std::string::npos != (i = mtx.find_first_of(digit_dot_newLine, i))
    && i < mtx.size()
  )
  {
    //cout << "i:" << i << ", prev_i:" << prev_i;
    //cout << " mtx[" << i << "]:" << mtx[i] << ", ";

    if(mtx[i] == '\n'){
      if( mtx[prev_i] != '\n'){
        vd.emplace_back(std::atof(digit.c_str()));
        digit_just_added = true;
        //cout << "+++ digit" << endl;
 
        vvd.emplace_back(vd);
        row_just_added = true;
        //cout << "___" << endl;
 
        vd.clear();
        digit.clear();
      }
      prev_i = i;
      i++;      
    }
    else {
      row_just_added = false;
      if(1 >= (i - prev_i) ) {
        digit_just_added = false;
        //cout << "(" << mtx[i] << "), ";  
        digit.append(1, mtx[i]);
        prev_i = i;
        i++;
      }        
      else {        
        //cout << " --- digit" << endl;
        vd.emplace_back(std::atof(digit.c_str()));
        digit_just_added = true;
        digit.clear();
        prev_i = i;
      }
    }  
  } //while
  if(!digit_just_added){
    vd.emplace_back(std::atof(digit.c_str()));
    //cout << "*** digit" << endl;
    digit.clear();
    digit_just_added = true;
  }
  if(!row_just_added){
    //cout << "_..._" << endl;
    vvd.emplace_back(vd);
    vd.clear();
    digit.clear();
    row_just_added = true;;
  }

  return vvd;
}


//---------------------------------------------------

bool is_digit(char c){
  string digits = "0123456789";
  for(int i = 0; i < digits.size(); i++){
    if(digits[i] == c) return true;
  }
  return false;
}

inline bool is_dot(char c){
  if(c == '.') return true;
  return false;
}
inline bool is_newLine(char c){
  if(c == '\n') return true;
  return false;
}

vector <vector <double> >& str2vvd_v2(
  string mtx, vector< vector<double> >& vvd)
{
  #ifdef CALC_DEBUG
  cout << "str2vvd_v2" << endl;
  #endif
  vector<double> vd;
  string digit;
  std::string::size_type i = 0;
  bool digit_state = false;
  bool row_state = false;
  bool digit_added = false;
  bool row_added = false;
  char prev_ch = mtx[0];

  for(i = 0; i < mtx.size(); i++){
    if( is_digit(mtx[i]) || is_dot(mtx[i])){
      digit.append(1, mtx[i]);
      digit_added = false;
      row_added = false;
    }
    else {
      if(is_digit(prev_ch) || is_dot(prev_ch)){
        vd.emplace_back(std::atof(digit.c_str()));
        digit.clear();
        digit_added = true;
      }
     
      if( is_newLine(mtx[i]) && !is_newLine(prev_ch) ){
        vvd.emplace_back(vd);
        vd.clear();
        row_added = true;
      }
    }//is_digit
    prev_ch = mtx[i];
  }//for
  if(!digit_added){
    vd.emplace_back(std::atof(digit.c_str()));
    digit.clear();
    digit_added = true;
  }
  if(!row_added){
    if(digit_added){
      vvd.emplace_back(vd);
      vd.clear();
      row_added = true;
    }
  }
  return vvd;
}