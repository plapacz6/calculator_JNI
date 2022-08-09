package calcm_jni;

public class calcm_JNI {
  public calcm_JNI() {
    //System.load("../libcalcm.so"); //libcalcm.so
    System.loadLibrary("calcm"); //libcalcm.so
  }
  public native void info();  
}