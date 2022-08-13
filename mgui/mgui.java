package mgui;
import javax.swing.*;
import java.awt.Dimension;
import calcm_jni.*;

public class mgui { // extends JFrame {
  public String mtx1;  // public as this is a somewhat forced example of using JNI for this purpose
  public String mtx2;
  public String mtxR;
  private javax.swing.text.PlainDocument doc_mtx1;
  private javax.swing.text.PlainDocument doc_mtx2;
  private javax.swing.text.PlainDocument doc_mtxR;
  private JTextPane text_mtx1;
  private JTextPane text_mtx2;
  private JTextPane text_mtxR;

  private calcm_JNI calcm;  //class containig native calculating methods
  private mgui myself;  //replacement for 'this' in nested context
  
  public mgui() {    
    myself = this;

    text_mtx1 = new JTextPane();
    text_mtx1.setPreferredSize(new Dimension(200,200));
    //text_mtx1.setDocument(doc_mtx1, text_field_attribute);  //not for plainText
    //form_mgui.getContentPane().add(text_mtx1);

    text_mtx2 = new JTextPane();        
    text_mtx2.setPreferredSize(new Dimension(200,200));
    //text_mtx2.setDocument(doc_mtx2);

    text_mtxR = new JTextPane();     
    text_mtxR.setPreferredSize(new Dimension(200,200));
    //text_mtxR.setDocument(doc_mtxR);

    calcm = new calcm_JNI();

//DEBUG
    text_mtx1.setText("1 2 3\n4 5 6\n7 8 9");
    text_mtx2.setText("1 0 0\n0 1 0\n0 0 1");    
    mtxR = "result == empty";
//DEBUG
    
    fill_mtx();
  }

  private void fill_mtx(){
    mtx1 = text_mtx1.getText();
    mtx2 = text_mtx2.getText();
    text_mtxR.setText(mtxR);
    System.out.println(mtxR);
  }

  public void show(){    
    JFrame form_mgui = new JFrame("matrix gui");
    //JFrame form_mgui = this; //new JFrame("matrix gui");
    form_mgui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    form_mgui.setPreferredSize(new java.awt.Dimension(750,300));

    //location on the screen
    java.awt.GraphicsDevice[] gs = java.awt.GraphicsEnvironment.getLocalGraphicsEnvironment().getScreenDevices();
    java.awt.GraphicsConfiguration gc[] = gs[0].getConfigurations();
    java.awt.Rectangle bounds = gc[0].getBounds();
    form_mgui.setLocation( (int)(bounds.width/3) + bounds.x, (int)(bounds.height/3) + bounds.y);

    javax.swing.text.SimpleAttributeSet text_field_attribute = new javax.swing.text.SimpleAttributeSet();

    JLabel label_mtx1 = new JLabel("matrix 1");
    //form_mgui.getContentPane().add(label_mtx1);
    
    JLabel label_mtx2 = new JLabel("matrix 2");
    //form_mgui.getContentPane().add(label_mtx2);
    
    javax.swing.JButton button_mtx_dot = new javax.swing.JButton();
    button_mtx_dot.setText("mtx_dot");
    button_mtx_dot.addActionListener(
      new java.awt.event.ActionListener() {
        public void actionPerformed(java.awt.event.ActionEvent evnt){
          fill_mtx();        
          //calcm.set_mtxA_string_content(mtx1, mtx2);  //DEBUG
          calcm.mtx_dot(myself);  //myself--->this mgui
          //mtxR = calcm.get_mtxR_string_content();  //DEBUG
        }
      }
    );

    javax.swing.JButton button_mtx_mul = new javax.swing.JButton();
    button_mtx_mul.setText("mtx_mul");
    button_mtx_mul.addActionListener(
      new java.awt.event.ActionListener() {
        public void actionPerformed(java.awt.event.ActionEvent evnt){
          fill_mtx();
          //calcm.set_mtxA_string_content(mtx1, mtx2); //DEBUG
          calcm.mtx_mul(myself);  //myself--->this mgui
          //mtxR = calcm.get_mtxR_string_content(); //DEBUG      
          //text_mtx2.setText(text_mtx1.getText()); //DEBUG          
        }
      }
    );

    JLabel label_mtxR = new JLabel("matrix Result");    
    //form_mgui.getContentPane().add(label_mtxR);   


    javax.swing.GroupLayout glayout = new javax.swing.GroupLayout(form_mgui.getContentPane());
    glayout.setAutoCreateGaps(true);
    glayout.setAutoCreateContainerGaps(true);
    form_mgui.getContentPane().setLayout(glayout);

    glayout.setHorizontalGroup(

      glayout.createSequentialGroup()      
      .addGroup(
        glayout.createParallelGroup(javax.swing.GroupLayout.Alignment.CENTER)
        .addComponent(label_mtx1)
        .addComponent(text_mtx1,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE
        )        
      )
      .addGroup(
        glayout.createParallelGroup(javax.swing.GroupLayout.Alignment.CENTER)        
        .addComponent(label_mtx2)        
        .addComponent(text_mtx2,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE
        )
      )
      .addGroup(
        glayout.createParallelGroup(javax.swing.GroupLayout.Alignment.CENTER)        
        .addComponent(button_mtx_dot)        
        .addComponent(button_mtx_mul)
      )      
      .addGroup(
        glayout.createParallelGroup()        
        .addComponent(label_mtxR)        
        .addComponent(text_mtxR,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE
        )
      )
      
    );

    glayout.setVerticalGroup(

      glayout.createSequentialGroup()            
      .addGroup(
        glayout.createParallelGroup(javax.swing.GroupLayout.Alignment.CENTER)
        .addComponent(label_mtx1)
        .addComponent(label_mtx2)             
        .addComponent(label_mtxR)      
      )      
      .addGroup(
        glayout.createParallelGroup(javax.swing.GroupLayout.Alignment.CENTER)
        .addComponent(text_mtx1, 
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE
        )                
        .addComponent(text_mtx2,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE          
        )
        .addGroup(
          glayout.createSequentialGroup()
          .addComponent(button_mtx_dot)
          .addComponent(button_mtx_mul)        
        )
        .addComponent(text_mtxR,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE,
          javax.swing.GroupLayout.PREFERRED_SIZE          
        )
      )
    );     
    

    form_mgui.pack();
    form_mgui.setVisible(true);
  }

  // public static void main(String[] args){
  //   javax.swing.SwingUtilities.invokeLater(new Runnable() {
  //     public void run() {
  //       mgui mgui_obj = new mgui();
  //       mgui_obj.show();       
  //     }
  //   });
  // }
}
