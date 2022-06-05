
#include <Ps3Controller.h>

#define in1 19
#define in2 18
#define in3 5
#define in4 17

const int cin1=0;
const int cin2=1;
const int cin3=2;
const int cin4=3;
const int fr = 5000;
const int re=8;
const byte hz=200;

void setup()
{
    ledcSetup(cin1,fr,re);
    ledcSetup(cin2,fr,re);
    ledcSetup(cin3,fr,re);
    ledcSetup(cin4,fr,re);
    ledcAttachPin(in1,cin1);
    ledcAttachPin(in2,cin2);
    ledcAttachPin(in3,cin3);
    ledcAttachPin(in4,cin4);
    Serial.begin(115200);
    Ps3.begin("2c:81:58:a2:3a:61");
}

void loop()
{
    if(Ps3.isConnected()){
        if(Ps3.data.analog.button.up){
            Serial.println("w");
            ledcWrite(cin2,200);
            ledcWrite(cin1,0);
            ledcWrite(cin4,200);
            ledcWrite(cin3,0);
        }
        if(Ps3.data.analog.button.left){
            Serial.println("a");
            ledcWrite(cin1,0);
            ledcWrite(cin2,200);
            ledcWrite(cin3,200);
            ledcWrite(cin4,0);
        }
        if(Ps3.data.analog.button.down){
            Serial.println("s");
            ledcWrite(cin2,0);
            ledcWrite(cin1,200);
            ledcWrite(cin4,0);
            ledcWrite(cin3,200);
        }
        if(Ps3.data.analog.button.right){
            Serial.println("d");
            ledcWrite(cin1,200);
            ledcWrite(cin2,0);
            ledcWrite(cin3,0);
            ledcWrite(cin4,200);
        }
        if(Ps3.data.analog.button.up==false&&Ps3.data.analog.button.left==false&&Ps3.data.analog.button.down==false&&Ps3.data.analog.button.right==false){
            ledcWrite(cin1,0);
            ledcWrite(cin2,0);
            ledcWrite(cin3,0);
            ledcWrite(cin4,0);
        }
    }
}
