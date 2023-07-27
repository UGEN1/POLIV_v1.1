#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <iarduino_RTC.h>
#include "DHT.h"
#define watersens A0
#define dht 4
#define DHTTYPE DHT11
#define pompa 11
#define ledder 12
#define culler 10

iarduino_RTC clock_ (RTC_DS1307);
LiquidCrystal_I2C lcd(0x3F,16,2);
SoftwareSerial BLUETOOTH (8,9); //rx, tx
DHT humi_temp (dht,DHTTYPE);
int tick, tickk;
int bt_signal;


class sensors {
  public:
  sensors ()
  {
  }
  void sens_init ()
  {
    humi_temp.begin();
    pinMode (watersens,INPUT);
  }
  
  int temp_read ()
  {
  
    int t=humi_temp.readTemperature();
    lcd.clear ();         
        
     
     lcd.setCursor (8,0);
     lcd.print ("T:");
     lcd.print ( t);
     lcd.println ("*C__");
    return t;
  }
  
    int hum_read ()
  {
    int h=humi_temp.readHumidity();
        lcd.clear ();         
        
     lcd.setCursor (0,0);
     lcd.print ("H:");
     lcd.print ( h);
     lcd.print ("%");
     
    return h;
  }
  
  
  
  protected:
  int t;
  int h;
  int water_level;
  
};

class load {
  public:
  load()
  {
    
  }
  void load_init()
  {
    pinMode(culler,OUTPUT);
    pinMode(pompa,OUTPUT);
    pinMode(ledder,OUTPUT);
    
  }
  void culler_status(bool stat_c,int delay_c)
  {
    switch(stat_c)
    {
      case(true):
      
      digitalWrite(culler,0);
      delay(delay_c);
      
      break;
      case (false):
      
      digitalWrite(culler,1);
       delay(delay_c);
      
      break;
      
    }
    
    
  }
  void pompa_set(bool stat_s)
  {
    switch(stat_s)
    {
      case(true):
      
      digitalWrite(pompa,0);
      
      break;
      
      case (false):
      digitalWrite(pompa,1);
      
      
      break;
      
    }
    
    
  }
  void led_set(bool stat_s2)
  {
    switch(stat_s2)
    {
      case(true):
      
      digitalWrite(ledder,0);
      
      break;
      
      case (false):
      digitalWrite(ledder,1);
      
      break;
      
    }
    
    
  }
  void culler_set(bool stat_s3)
  {
    switch(stat_s3)
    {
      case(true):
      
      digitalWrite(culler,0);
      
      break;
      
      case (false):
      digitalWrite(culler,1);
      
      break;
      
    }
    
    
  }
  void pompa_status(bool stat_p,int delay_p)
  {
    switch(stat_p)
    {
      case(true):
      
      digitalWrite(pompa,0);
      delay(delay_p);
      break;
      
      case (false):
      digitalWrite(pompa,1);
      delay(delay_p);
      
      break;
      
    }
    
    
  }
  void led_status(bool stat_l,int delay_l)
  {
    switch(stat_l)
    {
      case(true):
      
      digitalWrite(ledder,0);
      delay(delay_l);
      break;
      
      case (false):
      digitalWrite(ledder,1);
      delay(delay_l);
      
      break;
      
    }
    
    
  }
  
  protected:
  bool stat_c,stat_p,stat_l;
  int delay_c,delay_p,delay_l; 
  
};
class OUTDATE
{
  public:
  OUTDATE()
  {
    
  }
  void screen_init()
  {
    lcd.init();                       
    lcd.backlight();
    clock_.begin();
    lcd.setCursor (4,0);
    lcd.print("INIT SYSTEM");
    delay(2000);
  }
  void sens_out(int data_hum,int data_temp)
  {
     lcd.clear ();         
        
     lcd.setCursor (0,0);
     lcd.print ("H:");
     lcd.print ( data_hum);
     lcd.print ("%");
     lcd.setCursor (8,0);
     lcd.print ("T:");
     lcd.print ( data_temp);
     lcd.println ("*C__");
    
  }
  
};
class INDATE
{
  public:
  INDATE()
  {
    
  }
    void blutus_init()
  {
    BLUETOOTH.begin (9600);
    BLUETOOTH.println ("AT+NAMEWATERSYS");
  }
  int blutus_set_freq(int btt)
  {
      
          


int a=btt;


  if ((a>=2)&&(a<50))
  {
    
    int aa=map(bt_signal,2,50,0,24);
           lcd.clear ();         
           lcd.setCursor (0,0);
           lcd.print ("F:");
           lcd.print (aa);
           lcd.print ("h");
           
    return (aa);
  }


  
  }
    int blutus_set_del(int bttt)
  {

int a=bttt;

     Serial.print("a= ");
  Serial.println(a);
 if ((a>=51)&&(a<99))
  {
    int bb=map(bt_signal-51,0,48,0,61);
    lcd.clear ();         
           lcd.setCursor (8,0);
           lcd.print ("D:");
           lcd.print (bb);
           lcd.print ("s");
    return (bb);
  }
  
  }
    int blutus_set_Hmax(int btttt)
  {

int a=btttt;

     Serial.print("a= ");
  Serial.println(a);
     if ((a>=100)&&(a<150))
  {
    int cc=map(bt_signal-100,0,50,0,101);
    lcd.clear ();         
           lcd.setCursor (0,1);
           lcd.print ("Hma:");
           lcd.print (cc);
           lcd.print ("%");
    return (cc);
  }
  
  }
      int blutus_set_Hmin(int bttttt)
  {

int a=bttttt;

     Serial.print("a= ");
  Serial.println(a);
   if ((a>=151)&&(a<200))
  {
    int dd=map(bt_signal-151,0,49,0,102);
    lcd.clear ();         
           lcd.setCursor (9,1);
           lcd.print ("Hmi:");
           lcd.print (dd);
           lcd.print ("%");
    return (dd);
  
  }
  }
   
protected:
int a,b,c,d,aa,bb,cc,dd;
                
};

class Working :public  OUTDATE,load,sensors
{
  public:
  
  Working ()
  {
    load l1=l1;

  }
  

    bool level_read()
  {
    load l1;
    int water_level=analogRead (watersens)/3;

      
     

   if (water_level<=10)
    {
      lcd.clear();
      lcd.setCursor (0,1);
           lcd.print ("Low water");
      ll.led_status (true,500);
      ll.led_status (false,500);
      l1.pompa_set (false);
      
      return false;
    }
    else 

      led_set (true);
     return true;


  }

    bool humi_read(int hmin,int hmax)
  {
    sensors sens;
    load l1;
    int humi_level=humi_temp.readHumidity();
  

   if (humi_level<=hmin)
    {
      ll.pompa_status(true,3000);
      ll.culler_set(false);
      ll.pompa_set(false);
            lcd.clear ();         
           lcd.setCursor (0,1);
           lcd.print ("LOW HUM");
      return false;
    }
    else if (humi_level>=hmax)
    {
      ll.pompa_set(false);
      ll.culler_status(true,3000);
      ll.culler_set(false);
      lcd.clear ();         
           lcd.setCursor (0,1);
           lcd.print ("HIGHT HUM");
     return false;
    }
         else if ((humi_level<=hmax)&&(humi_level>=hmin))
    {
      ll.pompa_set(false);
      
      
     return true;
    }
  }


  int working_set_now ()
  {
    sensors S;
    OUTDATE screen;


    int aaa=S.temp_read();
    int bbb=S.hum_read();
    screen.sens_out(bbb,aaa);
    return bbb;
 

  }
  bool set_del(int del)
  {
    sensors sens;
    load l1;
    bool f1=false;

   do {
    if (millis()%1000==0)
    {
      del--;
      
           lcd.setCursor (8,1);
           lcd.print ("D:");
           lcd.print (del);
           lcd.print ("s");
           l1.pompa_set(true);

    }
   }while ((millis()-tik>=1)&&(del>=1));
    l1.pompa_set(false);

  }
     bool set_freq(int fre)
  {
    sensors sens;
    load l1;
    bool f2;
 lcd.setCursor (0,1);
           lcd.print ("F:");
           lcd.print (fre);
           lcd.print ("h");
   do {
    if (millis()%3600000==0)
    {

      fre--;
            lcd.setCursor (0,1);
           lcd.print ("F:");
           lcd.print (fre);
           lcd.print ("h");
        
    } 
   }while ((millis()-tik>=1)&&(fre>=1));


           
  }
  
  
  protected:
  load ll;
  sensors Sen;
  int tik;
  };

  class Setwork :public INDATE, OUTDATE,load,sensors,Working
  {
  public:
  Setwork()
  {
    
  }
   void begin_work ( )
   {
    S.sens_init();
  l.load_init();
  screen.screen_init();
  chanal.blutus_init();
           l.culler_set (false);
  l.pompa_set (false);
  l.led_set (false);
  
   }
   
   int workin_cicl ()
   {
          bt_signal=BLUETOOTH.read();
      Serial.println(bt_signal);
      
     if (bt_signal==49)
    {
     
        fre++;
        if (fre>23) fre=23;
      lcd.clear ();         
           lcd.setCursor (0,0);
           lcd.print ("F:");
           lcd.print (fre);
           lcd.print ("h");
    }

    
    else if (bt_signal==50)
    {
      fre--;
      if (fre<0) fre=1;
      
            lcd.clear ();         
           lcd.setCursor (0,0);
           lcd.print ("F:");
           lcd.print (fre);
           lcd.print ("h");
    }

    
        else if (bt_signal==51)
    {
      del++;
      if (del>59) del=59;
      
            lcd.clear ();         
           lcd.setCursor (8,0);
           lcd.print ("D:");
           lcd.print (del);
           lcd.print ("s");
    }

    
            else if (bt_signal==52)
    {
      del--;
      if (del<0) del=0;
      
            lcd.clear ();         
           lcd.setCursor (8,0);
           lcd.print ("D:");
           lcd.print (del);
           lcd.print ("s");
    }

    
    else if (bt_signal==53)
    {
      hma=hma+50;
      if (hma>99) hma=99;
      
            lcd.clear ();         
           lcd.setCursor (0,1);
           lcd.print ("Hma:");
           lcd.print (hma);
           lcd.print ("%");
    }
    else if (bt_signal==54)
    {
      hma--;
      if (hma<=1) hma=1;
      
            lcd.clear ();         
           lcd.setCursor (0,1);
           lcd.print ("Hma:");
           lcd.print (hma);
           lcd.print ("%");
    }

        else if (bt_signal==55)
    {
      hmi++;
      if (hmi>99) hmi=99;
      
            lcd.clear ();         
           lcd.setCursor (9,1);
           lcd.print ("Hmi:");
           lcd.print (hmi);
           lcd.print ("%");
    }
    else if (bt_signal==56)
    {
      hmi--;
      if (hmi<=1) hmi=1;
      
            lcd.clear ();         
           lcd.setCursor (9,1);
           lcd.print ("Hmi:");
           lcd.print (hmi);
           lcd.print ("%");
    }
    
    else if (bt_signal==57)
    {
      do{
        if (millis()%500==0)
{ 
  int ttt=WORK.working_set_now();
  WORK.humi_read( 20, 80);
  bool ff1=WORK.level_read();
  bool ff2=WORK.humi_read( hmi, hma);
  
  if ((ff1==true)&&(ff2==true))
  {
    if (bt_signal!=58)
    {
   WORK.set_freq (fre);
    
   WORK.set_del (del);
    }
    else if (bt_signal==58)
    {
      WORK.set_freq (1);
   WORK.set_del (20);
    }
   bt_signal=BLUETOOTH.read();
   bool ff2=WORK.humi_read( hmi, hma);
  }
  
  
}
      }while ((bt_signal!=49)&&(bt_signal!=50)&&(bt_signal!=51)&&(bt_signal!=52)&&(bt_signal!=53)&&(bt_signal!=54)&&(bt_signal!=55)&&(bt_signal!=56));
    
    }
    
   }
  

  
  
      
      
    
  
  private: 
  sensors S;
  load l;
  OUTDATE screen;
  INDATE chanal;
  Working WORK;
  int data,fre,del,hma,hmi;
};
