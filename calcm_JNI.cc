#include <vector>
#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <cassert>

#include "./include/calcm_jni_calcm_JNI.h"  //generated for c++  (for c diffrent headers are include inside)
/*
 (*env)->GetObjectClass(env, obj);  //c   "FieldAccess.h"
 env->GetObjectCalss(obj);          //c++ "???"
*/
using namespace std;

vector <vector <double> >& str2vvd_v2( string mtx, vector< vector<double> >& vvd);
vector <vector <double> >& str2vvd_v1( string mtx, vector< vector<double> >& vvd);
string vvd2str(string& mtx, vector<vector<double> >& vvd);
vector<vector<double> > &matrix_mul(vector<vector<double> >& vvd1, vector<vector<double> >& vvd2, vector<vector<double> >& vvdR);
string to_string_f(double &val, int f);
#define PDEBUG(X)  cout << #X << ":\n" <<  X << endl << "----------\n";

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
    //string_mtxR = string_mtx1 + "\n MUL(.) \n" + string_mtx2;
    vector< vector<double> > vvd1, vvd2, vvdR;
    vvd1 = str2vvd_v2(string_mtx1, vvd1);
    vvd2 = str2vvd_v2(string_mtx2, vvd2);
    vvdR = matrix_mul(vvd1, vvd2, vvdR);
    string_mtxR = vvd2str(string_mtxR, vvdR);


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

/* str2vvd_v1() don't adds zeros for missing columns */
vector <vector <double> >& str2vvd_v1(
  string mtx, vector< vector<double> >& vvd)
{
  #ifdef TEST_CALCM_JNI
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
  #ifdef TEST_CALCM_JNI
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

  vector<int> digit_in_row_counter;
  int max_digit_in_row = 0;
  int row_counter = 0;

  for(int i = 0; i < vvd.size(); i++)
    vvd[i].clear();
  vvd.clear();

  cout << "++++++++++" << endl;
  PDEBUG(mtx);
  PDEBUG(vvd.size());
  cout << "++++++++++" << endl;


  digit_in_row_counter.push_back(0);
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

        digit_in_row_counter[row_counter]++;
        if(max_digit_in_row < digit_in_row_counter[row_counter]){
          max_digit_in_row = digit_in_row_counter[row_counter];
        }
      }
     
      if( is_newLine(mtx[i]) && !is_newLine(prev_ch) ){
        vvd.emplace_back(vd);
        vd.clear();
        row_added = true;    

        digit_in_row_counter.push_back(0);
        row_counter++;
      }
    }//is_digit
    prev_ch = mtx[i];
  }//for
  if(!digit_added){
    vd.emplace_back(std::atof(digit.c_str()));
    digit.clear();
    digit_added = true;

    digit_in_row_counter[row_counter]++;
    if(max_digit_in_row < digit_in_row_counter[row_counter]){
      max_digit_in_row = digit_in_row_counter[row_counter];
    }
  }
  if(!row_added){
    if(digit_added){
      vvd.emplace_back(vd);
      vd.clear();
      row_added = true;   

      digit_in_row_counter.push_back(0);
      row_counter++;
    }
  }
  //complementing missing zeros
  for(int i = 0; i < row_counter; i++){
    for(int j = 0; j < max_digit_in_row - digit_in_row_counter[i]; j++){
      cout << "max:" << max_digit_in_row << ", dirc[" << i << "]: " << digit_in_row_counter[i] << " diff: " << max_digit_in_row - digit_in_row_counter[i] << endl;
      vvd[i].emplace_back(0);
    }
  }

  return vvd;
}

//---------------------------------------------------
string vvd2str(string& mtx, vector<vector<double> >& vvd){
  for(int i = 0; i < vvd.size(); i++){
    for(int j = 0; j < vvd[i].size(); j++){\
      mtx.append(to_string_f(vvd[i][j], 2));
      mtx.append(", ");
    }
    mtx.append("\n");
  }
  return mtx;
}



string to_string_f(double &val, int f){
  ostringstream out_str;
  out_str.precision(2);
  out_str.setf(ios::fixed);
  out_str.setf(ios::showpoint);
  out_str << val;
  return out_str.str();
}

//---------------------------------------------------
#ifdef TEST_CALCM_JNI
void print_vvd(vector <vector <double> > &vvd, int clear = 0){
  for(int i = 0; i < vvd.size(); i++){
    for(int j = 0; j < vvd[i].size(); j++){
      cout << to_string_f(vvd[i][j], 2) << ",";
    }    
    cout << endl;      
    if(clear) vvd[i].clear();
  }
}

int main(){
  vector <vector <double> > vvd, vvd1, vvd2;
  string mtxX;
  #define TESTS_NUMBER (9)
  string string_mtx[TESTS_NUMBER] = {
    "1,2,3\n,5\n6",
    "0,\n1 2\n3",
    "1 2 3\n\n4\n5,6,7,8,",
    "1 2 3\n\n4\n5,6,7,8",
    "1 2 3\n\n4\n5,6,7,8\n",
    "1 2\n3 4\n5 9\n",
    "1 2\n3 4\n5 9",
    "1 2\n3 4\n5 9 ",
    "1 2\n3 4\n5 9,",
  };
  for(int z = 0; z < TESTS_NUMBER; z++){
    str2vvd_v2(string_mtx[z], vvd);  
    mtxX = vvd2str(mtxX, vvd);
    print_vvd(vvd, 1);    
    }    
  cout << "---" << endl << mtxX << endl << "---" << endl;
  PDEBUG(vvd.size());
  vvd.clear();    
  mtxX.clear();  
  
  #define TESTS_NUMBER_2 (4)
  struct {
    string a;
    string b;
  } 
  mtx_pair[TESTS_NUMBER_2] = {
    {"1 2 3\n4 5 6", "1 1\n1 1\n1 1"},    
    {"1 2\n 3 4\n 5 6", "1 1 1\n 1 1 1"},    
    {"1 2 3\n4 5 6\n", "1 1\n1 1\n1 1\n"},    
    {"1 2\n 3 4\n 5 6\n", "1 1 1\n 1 1 1\n"},    
  };
  for(int i = 0; i < TESTS_NUMBER_2; i++){
    str2vvd_v2(mtx_pair[i].a, vvd1);
    str2vvd_v2(mtx_pair[i].b, vvd2);
    print_vvd(vvd1);
    cout << endl;
    print_vvd(vvd2);
    cout << endl;
    vvd = matrix_mul(vvd1, vvd2, vvd);
    cout << endl;
    print_vvd(vvd, 1);
    cout << endl;
    vvd.clear();
  }
}
#endif // TEST_CALCM_JNI
//---------------------------------------------------

//---------------------------------------------------
/* TODO - MOCK*/
vector<vector<double> > &matrix_mul(vector<vector<double> >& vvd1, vector<vector<double> >& vvd2, vector<vector<double> >& vvdR){  
  cout << "matrix1 rows: " << vvd1.size() << ", matrix2 cols: " << vvd2[0].size() << endl;
  if(vvd2.size() == 0) {
    cout << "not enough columnt in 2 matrix" << endl;
    return vvdR;
  }
  if(vvd1.size() == 0) {
    cout << "not enough row in 1 matrix" << endl;
    return vvdR;
  }
  if( vvd1.size()  != vvd2[0].size() ){  
    cout << "number of rows in 1 matrix not equal number of columns in 2 matrix" << endl;    
    return vvdR;    
  }
  for(int i = 0; i < vvd1[0].size(); i++){      
    if(vvd2[i].size() != vvd1.size()){
      cout << "number of row " << i << " 1 matrix not equal number of columns in 2 matrix" << endl;      
      return vvdR;    
    }      
  }
  /* checking if matrices have correct shape */
  int max_size1, max_size2;  
  max_size1 = vvd1[0].size();  
  for(int i = 0; i < vvd1.size(); i++){    
    if(vvd1[i].size() != max_size1){
      cout << "1 matrix have not correct shape." << endl;
      return vvdR;        
    }    
  }  
  max_size2 = vvd2[0].size();
  for(int i = 0; i < vvd2.size(); i++){
    if(vvd2[i].size() != max_size2) {
      cout << "2 matrix have not correct shape." << endl;
      return vvdR;        
    }
  }

  /* matrix multiplication */  
  vvdR.clear();
  cout << "matrix multiplication" << endl;
  double val = 0;
  vvdR.resize(vvd1.size()); //rows mtx1
  cout << "row size changed: " << vvdR.size() << endl;
  for(int i = 0; i < vvd1.size(); i++){
    vvdR[i].resize(vvd2[0].size()); //cols mtx2
    cout << "cols in row " << i << " size changed: " << vvdR[i].size() << endl;
    for(int j = 0; j < vvd2[0].size(); j++){
      val = 0;      
      assert(vvd2.size() == vvd1[0].size()); //vvd1[0].size() : [0] because some matrix 2 have less rows than matrix 1 (matrix Result)
      for(int ii = 0, jj = 0; ii < vvd2.size() && jj < vvd1[i].size(); ii++, jj++){                        
        val += vvd1[i][jj] * vvd2[ii][j];        
        cout << "counting mtxR[" << i << "][" << j << "]:" << val << "->";
      }
      cout << "after summing: val == " << val << endl;
      vvdR[i][j] = val;
    }
  }
  return vvdR;
}
//---------------------------------------------------
