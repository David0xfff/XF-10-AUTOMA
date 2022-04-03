#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27,20,4);


///////////////////////////////////////////////////////////////////////////////////////
//variables para el teclado matricial 4x5
const byte rowsCount = 5;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { 'F','G','#', '*' },//F= F1, G=F2, #=# *=*
   { '1','2','3', 'U' },// U= arriba
   { '4','5','6', 'A' },// A= abajo
   { '7','8','9', 'S' },// S= salir
   { 'D','0','I', 'E' } //D= derecha,  I=izquierda,  E=enter
};
 
const byte rowPins[rowsCount] = { 12, 11, 10, 9, 8 };
const byte columnPins[columsCount] = { 7, 6, 5, 4 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
///////////////////////////////////////////////////////////////////////////////////////


// #define T1  5

//menu principal
boolean arriba=0;
boolean abajo=0;
byte contselec=0;// Indica en que pocicion esta para imprimir en pantalla
byte seleccontt=0;
byte colgrados;//esta variable muestra el selector en la segunda colupna, es cuando hay mas de 8 selecciones  
byte limsup=3;//estos limites nos indican si el menu tiene cuatro opciones o ocho opciones 

boolean menu = true;//menu principal de seleccion y configuracion 
boolean menu1 = false;// menu de configurar grados
boolean menu2 = false;// menu de seleccion de grados para configurar 

boolean teclas1 = true;// teclado para solo flechas arriba y abajo
boolean teclas2 = false;// teclado para ingresar valores 

int cursorr;

/////////////////////////////////////////
//vectores para guardar los grados 
int grado0[9]={0};
unsigned int grado1[9]={0,0,0,0,0,0,0,0,0};
unsigned int grado2[9]={0,0,0,0,0,0,0,0,0};
unsigned int grado3[9]={0,0,0,0,0,0,0,0,0};
unsigned int grado4[9]={0,0,0,0,0,0,0,0,0};
////////////////////////////////////////


byte verpantalla1=0;

char key;

int colupnacolselec;

int unidades, u1, decenas, d2, centenas, c3;   
int cont0=0, var=0, numIngresado=0;


//menu principal numero 2////////////////////////////////////////////////////////////////
byte conf=0;
byte ConfTension;


# define camon1 3
# define camon2 2
# define camon3 1
# define camon4 0

#define ten1 A0
#define ten2 A1
#define ten3 A2
#define ten4 A3

    int tenactual;
    boolean pcamon1;
    boolean pcamon2;
    boolean pcamon3;
    boolean pcamon4;

    boolean pten1;
    boolean pten2;
    boolean pten3;
    boolean pten4;
    boolean pten5;
    boolean pten6;
    boolean pten7;
    boolean pten8;


void setup() 
{

  lcd.init();
  lcd.clear();
  lcd.setCursor (2, 2); 
  lcd.print("Cargando Programa");
  lcd.backlight(); // iniciamos lcd, prendemos luz de fondo, limpiamos pantalla


  pinMode(camon1, INPUT_PULLUP);
  pinMode(camon2, INPUT_PULLUP);
  pinMode(camon3, INPUT_PULLUP);
  pinMode(camon4, INPUT_PULLUP);

  pinMode(ten1, INPUT_PULLUP);
  pinMode(ten2, INPUT_PULLUP);
  pinMode(ten3, INPUT_PULLUP);
  pinMode(ten4, INPUT_PULLUP);


limpiarvar();
  for (byte i=1; i<9; i++)
   {
    
       unidades=EEPROM.read (( i*3 )-2);
       decenas=EEPROM.read (( i*3 )-1);
       centenas=EEPROM.read (( i*3 ));
       
       u1=unidades*1;
       d2=decenas*10;
       c3=centenas*100; 
       numIngresado=u1+d2+c3;
       
        grado1[i] = numIngresado;
        
   }


limpiarvar();
  for (byte k=9; k<17; k++)
   {
    
   unidades=EEPROM.read (( k*3 )-2);
   decenas=EEPROM.read  (( k*3 )-1);
   centenas=EEPROM.read (( k*3 ));
   
   u1=unidades*1;
   d2=decenas*10;
   c3=centenas*100; 
   numIngresado=u1+d2+c3;
   
   grado2[k-8] = numIngresado ;
     
   }


limpiarvar();
  for (byte i=17; i<25; i++){
      
   unidades=EEPROM.read (( i*3 )-2);
   decenas=EEPROM.read (( i*3 )-1);
   centenas=EEPROM.read (( i*3 ));
   
   u1=unidades*1;
   d2=decenas*10;
   c3=centenas*100; 
   numIngresado=u1+d2+c3;
   
    grado3[i-16] = numIngresado;
    
  
    }//tensiones1 guardadas


limpiarvar();    
  for (byte i=25; i<33; i++)
   {
      
   unidades=EEPROM.read (( i*3 )-2);
   decenas =EEPROM.read ((  i*3 )-1);
   centenas=EEPROM.read (( i*3 ));
   
   u1=unidades*1;
   d2=decenas*10;
   c3=centenas*100; 
   numIngresado=u1+d2+c3;
   
   grado4[i-24] = numIngresado;
    
   }//tensiones1 guardadas



 ConfTension=EEPROM.read (98);


  limpiarvar();
  lcd.clear();
  contselec=0;  conf=3;  MensajeGrados(); 
  
 //MensajeProgramas(); selector();
 // pinMode(2, INPUT_PULLUP);
}


void loop() 
{

if (conf<2){
             if (menu==true){teclado1();}
             if (menu1==true){teclado2();}
           }

if (conf==3){
              RunProgram ();
                        //lcd.clear();
                        //lcd.setCursor (12, 4); lcd.print F("si entro"); delay(4000);
               key = keypad.getKey();
             
               if (key) 
               {
                 if ( key == 'F' ){conf=0; LimpVariables(); limpiarvar(); MensajeProgramas(); selector();}
               }
             }
            
    
}


void RunProgram ()
  {
      
    pten1= digitalRead(ten1);
    if(pten1==1)
    { 
       pcamon1= digitalRead(camon1);
      if(pcamon1==1){ 
                     tenactual=grado0[1]; 
                     lcd.setCursor (9,0); lcd.print("A");
                    }
       
       pcamon2= digitalRead(camon2);
       if(pcamon2==1){
                      tenactual=grado0[1]; 
                      lcd.setCursor (9,0); lcd.print("B");
                     }

       pcamon3= digitalRead(camon3);
       if(pcamon3==1){
                      tenactual=grado0[1]; 
                      lcd.setCursor (9,0); lcd.print("C");
                     }

       pcamon4= digitalRead(camon4);
       if(pcamon4==1){
                      tenactual=grado0[1]; 
                      lcd.setCursor (9,0); lcd.print("D");  
                     }   
    }


    pten2= digitalRead(ten2);
    if(pten2==1)
    { 
       pcamon1= digitalRead(camon1);
      if(pcamon1==1){ 
                     tenactual=grado0[2]; 
                     lcd.setCursor (9,0); lcd.print("A");
                    }
       
       pcamon2= digitalRead(camon2);
        if(pcamon2==1){
                      tenactual=grado0[2]; 
                      lcd.setCursor (9,0); lcd.print("B");
                     }

       pcamon3= digitalRead(camon3);
       if(pcamon3==1){
                      tenactual=grado0[2]; 
                      lcd.setCursor (9,0); lcd.print("C");
                     }

       pcamon4= digitalRead(camon4);
       if(pcamon4==1){
                      tenactual=grado0[2]; 
                      lcd.setCursor (9,0); lcd.print("D");  
                     }   
    }


    pten3= digitalRead(ten3);
    if(pten3==1)
    { 
       pcamon1= digitalRead(camon1);
      if(pcamon1==1){ 
                     tenactual=grado0[3]; 
                     lcd.setCursor (9,0); lcd.print("A");
                    }
       
       pcamon2= digitalRead(camon2);
        if(pcamon2==1){
                      tenactual=grado0[3]; 
                      lcd.setCursor (9,0); lcd.print("B"); void loop();
                     }

       pcamon3= digitalRead(camon3);
        if(pcamon3==1){
                      tenactual=grado0[3]; 
                      lcd.setCursor (9,0); lcd.print("C");
                     }

       pcamon4= digitalRead(camon4);
        if(pcamon4==1){
                      tenactual=grado0[3]; 
                      lcd.setCursor (9,0); lcd.print("D");  
                     }   
    }




  }


void teclado1() 
{   
  key = keypad.getKey();
 
   if (key) 
   {
    if ( key == 'U' ){ if(seleccontt>0){
                                           if (conf==0)
                                            {
                                               arriba=1;
                                               seleccontt--; 
                                               if(menu2==false){ MensajeProgramas(); }                 
                                               else if(menu2==true){ SubmenuGrados(); }
                                               selector();
                                            }
  
                                            
                                         if (conf==1)
                                            {
                                              arriba=1;
                                              seleccontt--;
                                              selector();
                                            }
                                       }
                      }


      
    if ( key == 'A' ){ if(seleccontt<=2){ 
                                            if (conf==0)
                                            {
                                              abajo=1;
                                              seleccontt++; 
                                              if(menu2==false){  MensajeProgramas(); }                     
                                              else if(menu2==true) { SubmenuGrados();}
                                              selector();
                                            }
                                         
  
  
                                         else if (conf==1)
                                                {
                                                  abajo=1;
                                                  seleccontt++;
                                                  selector();
                                                }
                                        }
                                         
                       }



                                       
                     
      
    if ( key == 'E' ){ if(seleccontt<4){
                                          
                                             if(conf==0)
                                             {
                                               //contselec=0; 
                                               //seleccontt=0;
                                               if (menu2==false){ SelecccionarPrograma(); }
                                               else if (menu2==true){ menu=false; menu1=true; MensajeGrados(); selector(); void loop(); }
                                             }
    
                                              if(conf==1)
                                             {
                                                for (int i=0; i<4; i++){lcd.setCursor (12,i); lcd.print F(" ");}
                                                lcd.setCursor (12, seleccontt); lcd.print F("X");
                                                ConfTension = seleccontt;
                                                EEPROM.write (98, ConfTension);
                                             }
    
                                              if(seleccontt==1 && conf!=1)
                                             {
                                                 contselec=0; SelecccionarPrograma(); seleccontt=0;   conf=1;  
                                               lcd.setCursor (12, ConfTension); lcd.print F("X");
                                             }

                                             else if (seleccontt==3 && conf!=3)
                                             {
                                              contselec=0;  conf=3; SelecccionarPrograma(); MensajeGrados(); seleccontt=0; 
                                             }

                                        
                                         
                                       }
                                       
                                       
                       }
                      
   
   
   
   
   if ( key == 'S' ){ LimpVariables(); limpiarvar(); MensajeProgramas(); selector(); }
   
   
   } 
}


void teclado2() 
{   
  key = keypad.getKey();
  
 
    if(key)
 {

    if(teclas1==true && teclas2==false)
    {  
             if ( key == 'U' ){ if(seleccontt>0){ arriba=1; seleccontt--;  selector();}}
          
        else if ( key == 'A' ){ if(seleccontt<8){ abajo=1; seleccontt++; selector();}}
    } 
          
        if ( key == 'E' ){ if(seleccontt<8){
                                            
                                            composicion();limpiarvar();
                                            if     (teclas1==true && teclas2==false) {teclas2=true; teclas1=false; }
                                            else if(teclas2==true && teclas1==false) {teclas1=true; teclas2=false; }
                                           }
                          }



                          

       if ( key == 'S' ){ LimpVariables(); limpiarvar(); MensajeProgramas(); selector(); }

        
   
        if(teclas2==true && teclas1==false)
        {
          
             if ( key == '1' ){var=1; descomposicion();}
    
        else if ( key == '2' ){var=2; descomposicion();}
    
        else if ( key == '3' ){var=3; descomposicion();}
    
        else if ( key == '4' ){var=4; descomposicion();}
    
        else if ( key == '5' ){var=5; descomposicion();}
    
        else if ( key == '6' ){var=6; descomposicion();}
    
        else if ( key == '7' ){var=7; descomposicion();}
    
        else if ( key == '8' ){var=8; descomposicion();}
    
        else if ( key == '9' ){var=9; descomposicion();}
    
        else if ( key == '0' ){var=0; descomposicion();}
        
       }
 }
  
}


//1////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void descomposicion() 
       {
   if(cont0 < 3) {        
                 if(contselec<4) {cursorr = 7; colupnacolselec=contselec;}
                 if(contselec>=4){cursorr=17; colupnacolselec=contselec-4;}
                 
                 if (cont0 == 0){unidades=var;lcd.setCursor (cursorr-2, colupnacolselec);lcd.print("    "); lcd.setCursor (cursorr, colupnacolselec); lcd.print(unidades);} 
                 else if (cont0 == 1){decenas=unidades; unidades=var; lcd.setCursor (cursorr-1, colupnacolselec); lcd.print(decenas); lcd.setCursor (cursorr, colupnacolselec); lcd.print(unidades);}
                 else if (cont0 == 2){centenas=decenas; decenas=unidades; unidades=var;lcd.setCursor (cursorr-2, colupnacolselec); lcd.print(centenas);lcd.setCursor (cursorr-1, colupnacolselec); lcd.print(decenas); lcd.setCursor (cursorr, colupnacolselec); lcd.print(unidades);}
                 cont0++;       
               }
       }
//2////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//1////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void composicion()
      {
     
   u1=unidades*1;
   d2=decenas*10;
   c3=centenas*100; 
   numIngresado=u1+d2+c3;

   int grado0[9];

       byte f; byte c;
   for(byte i=0; i<8; i++){                        
                            if(i<4) { f=5; c=i; }
                            if(i>=4){ f=15; c=i-4; }

                            
                            if(contselec==i && verpantalla1==1 ){ 
                              
                            grado1[i+1]= numIngresado; lcd.setCursor (f,c); lcd.print("   "); lcd.setCursor (f,c); lcd.print(grado1[i+1]); lcd.print("X");

                              ////////////wow///////////////////
                            EEPROM.write (   (((i+1)*3)-2), unidades);
                            EEPROM.write (   (((i+1)*3)-1), decenas);
                            EEPROM.write (   ((i+1)*3), centenas);
                            
                            }

                            
                            else if(contselec==i && verpantalla1==2 )
                            { 
                              
                            grado2[i+1]= numIngresado; lcd.setCursor (f,c); lcd.print("   "); lcd.setCursor (f,c); lcd.print(grado2[i+1]); lcd.print("X");   
                           
                            EEPROM.write (   (((i+9)*3)-2), unidades);
                            EEPROM.write (   (((i+9)*3)-1), decenas);
                            EEPROM.write (   ( (i+9)*3), centenas);
                            
                            //EEPROM.write (i+8, grado2[i]);
                            
                            }

                            
                            else if(contselec==i && verpantalla1==3 )
                            {
                              
                              grado3[i+1]= numIngresado; lcd.setCursor (f,c); lcd.print("   "); lcd.setCursor (f,c); lcd.print(grado3[i+1]); lcd.print("X");

                              EEPROM.write (   (((i+17)*3)-2), unidades);
                              EEPROM.write (   (((i+17)*3)-1), decenas);
                              EEPROM.write (   ( (i+17)*3), centenas);
                                
                              }
                            else if(contselec==i && verpantalla1==4 )
                              {
                              grado4[i+1]= numIngresado; lcd.setCursor (f,c); lcd.print("   "); lcd.setCursor (f,c); lcd.print(grado4[i+1]); lcd.print("X");
                              
                              EEPROM.write (   (((i+25)*3)-2), unidades);
                              EEPROM.write (   (((i+25)*3)-1), decenas);
                              EEPROM.write (   ( (i+25)*3), centenas);
                              }
                          }
  

  
          
     }
//2////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///selectror menu principal
void selector()
{
      
       if (menu == true){limsup=3;}
       if (menu1 == true){limsup=7;}
       
       if (abajo == 1){ if(contselec<limsup){ contselec++; abajo=0; colgrados=contselec;}  }
       
       if(arriba == 1){if (contselec>0){contselec--;arriba=0; colgrados=contselec;} }
    
       if (contselec<4){ 
          for (int i=0; i<4; i++){lcd.setCursor (0,i); lcd.print F("  ");}}
       
       if (contselec>=4 || menu1 == true ){
                                              for (int i=0; i<4; i++){lcd.setCursor (0,i); lcd.print F("  ");}
                                              for (int i=0; i<4; i++){lcd.setCursor(10,i); lcd.print F("  ");}
                                          }
          
       if (contselec<4){  lcd.setCursor (0,contselec); lcd.print F("=>");}
    
       if (contselec>=4){  lcd.setCursor (10,contselec - 4); lcd.print F("=>");}

} 


void MensajeProgramas()
{
  
           if( seleccontt>=0 && seleccontt<4 )
                                  {
            lcd.clear();
            lcd.setCursor (0,0); lcd.print F("   Conf Grados");
            lcd.setCursor (0,1); lcd.print F("   Selec Grados");
            lcd.setCursor (0,2); lcd.print F("   Test");
            lcd.setCursor (0,3); lcd.print F("   Correr Prog");
            
                                  }    
           
} 


void SubmenuGrados()
{
            lcd.clear();
            for(int i=0; i<4; i++)  { lcd.setCursor (3, i);  lcd.print F("Tension "); lcd.print(i+1); }
}


void MensajeGrados()
{           
         
            
            byte bandera;
            if(conf==3){bandera=ConfTension; }
            else {bandera = seleccontt;}
            
            if(bandera==0)     {verpantalla1=1; for(int i=0; i<9; i++){ grado0[i]= grado1[i];  }}        
            else if(bandera==1){verpantalla1=2; for(int i=0; i<9; i++){ grado0[i]= grado2[i];  }} 
            else if(bandera==2){verpantalla1=3; for(int i=0; i<9; i++){ grado0[i]= grado3[i];  }} 
            else if(bandera==3){verpantalla1=4; for(int i=0; i<9; i++){ grado0[i]= grado4[i];  }}
            contselec=0;   seleccontt=0;
            lcd.clear();
            for(int i=0; i<4; i++){lcd.setCursor (2,i); lcd.print("#"); lcd.print(i+1);lcd.print(":");lcd.print(grado0[i+1]);}
            for(int i=0; i<4; i++){lcd.setCursor (12,i);lcd.print("#");lcd.print(i+5);lcd.print(":");lcd.print(grado0[i+5]);}
            
}


void SelecccionarPrograma()
   {

      if       (seleccontt==0){ menu2 = true;  SubmenuGrados(); selector();}
      else if  (seleccontt==1){ SubmenuGrados(); selector(); }
      else if  (seleccontt==2){while(1){lcd.clear();lcd.setCursor (3,3);  lcd.print("Sensor temp LM35");}}
      else if  (seleccontt==3){  }


   }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void limpiarvar(){  unidades=0; u1=0; decenas=0; d2=0; centenas=0; c3=0; cont0=0; var=0; numIngresado=0;   }


void LimpVariables()
  {
  
        arriba=0;
        abajo=0;
        contselec=0;// Indica en que pocicion esta para imprimir en pantalla
        seleccontt=0;
        colgrados;//esta variable muestra el selector en la segunda colupna, es cuando hay mas de 8 selecciones  
        limsup=3;//estos limites nos indican si el menu tiene cuatro opciones o ocho opciones 
      
        menu = true;//menu principal de seleccion y configuracion 
        menu1 = false;// menu de configurar grados
        menu2 = false;// menu de seleccion de grados para configurar 
      
        teclas1 = true;// teclado para solo flechas arriba y abajo
        teclas2 = false;// teclado para ingresar valores 
      
        verpantalla1=0;
      
        cont0=0;
        var=0;
        numIngresado=0;
      
        colupnacolselec=0;
      
        colgrados=0;

        conf=0;

  
  }
                                 




   
