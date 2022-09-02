import java.io.*; //Console
//import calcm_jni.*;
import mgui.*;

public class calculator_JNI {
  static {
    System.loadLibrary("calc");  //libcalc.so
  }

  //native method declarations
  private native double sum(double n1, double n2);
  private native double odd(double n1, double n2);
  private native double mul(double n1, double n2);
  private native double div(double n1, double n2);
  private native int integerDiv(int n1, int n2);
  private native int modulo(int n1, int n2);

  
  public static void main(String argsp[]){
    
    calculator_JNI calc = new calculator_JNI();
    //System.loadLibrary("calcm");
    //calcm_JNI calcm = new calcm_JNI();

    boolean endCalculator = false;
    String op = "";
    String s_arg1 = "";
    String s_arg2 = "";
    double arg1;
    double arg2;
    double calculationResult = 0;    
    int restPart = 0;
    Console console = System.console();
    if(console == null){
      System.out.println("console not available");
      return;
    }

    //calcm.info();

    do {          
      System.out.println("\n\nenter operator (+,-,*,/ , %(modulo), m(matrix calc))   x->end:");
      op = console.readLine(); 
      switch(op){
        case "x":{
          endCalculator = true;
          break;
        }
        case "m":{
          mgui mgui_obj = new mgui();
          mgui_obj.show();            
          break;
        }
        case "+":
        case "-":
        case "*":
        case "/":
        case "%":{
          System.out.println("enter arg1 :");
          arg1 = Double.valueOf(s_arg1 = console.readLine()); 
          
          System.out.println("enter arg2 :");
          arg2 = Double.valueOf(s_arg2 = console.readLine()); 
              
          switch(op) {
            case "+":{
              calculationResult = calc.sum(arg1, arg2);
              break;
            }
            case "-":{
              calculationResult = calc.odd(arg1, arg2);
              break;
            }
            case "*":{
              calculationResult = calc.mul(arg1, arg2);
              break;          
            }
            case "/":{
              calculationResult = calc.div(arg1, arg2);
              break;
            }
            case "%":{
              calculationResult = (double)calc.integerDiv((int)arg1, (int)arg2);
              restPart = calc.modulo((int)arg1, (int)arg2);
              break;
            }
            case "x":{
              endCalculator = true;
              break;
            }
            default :{          
              continue;          
            }        
          }
      
          System.out.println(        
            "result == " + 
            Double.toString(calculationResult) + (
            (op.equals("%")) 
              ? (", rest: " + Integer.toString(restPart)) 
              : ""));  
          break;    
        } 
        default :{
          System.out.println("Not supported operator.");      
        }
      }//switch
    } while(!endCalculator);
  }
}