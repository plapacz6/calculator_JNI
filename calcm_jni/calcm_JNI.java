package calcm_jni;
import mgui.*;

public class calcm_JNI {
  private String mtx1;
  private String mtx2;
  private String mtxR;

  public calcm_JNI() {
    //System.load("../libcalcm.so"); //libcalcm.so
    System.loadLibrary("calcm"); //libcalcm.so
  }

  public void set_mtxA_string_content(String mtx1_, String mtx2_){
    mtx1 = mtx1_;
    mtx2 = mtx2_;
  }

  public String get_mtxR_string_content(){
    return mtxR;
  }

  public native void info();  

  public native void mtx_dot(mgui mgui_obj);
  // public void mtx_dot(mgui mgui_obj){
  //   mgui_obj.mtxR = mgui_obj.mtx1 + "\n .(dot) \n" + mgui_obj.mtx2;
  // }

  public native void mtx_mul(mgui mgui_obj);
  // public void mtx_mul(mgui mgui_obj){
  //   mgui_obj.mtxR = mgui_obj.mtx1 + "\n *(mul) \n" + mgui_obj.mtx2;
  // }
  
}