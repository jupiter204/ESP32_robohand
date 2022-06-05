#include <Ps3Controller.h>
#include <ESP32Servo.h>

#define in1 19
#define in2 18
#define in3 5
#define in4 17

const int cin1 = 2;
const int cin2 = 3;
const int cin3 = 4;
const int cin4 = 5;
const int fr = 5000;
const int re = 8;
const byte hz = 200;

Servo myservo1;
Servo myservo2;
Servo myservo3; // 建立SERVO物件
Servo myservo4;

int aq = 40, bq = 65, cq = 36, dq = 180;

void servo_on(void)
{
    myservo1.attach(14); // 30,110
    myservo2.attach(12); // 10,140
    myservo3.attach(23); // 15,88
    myservo4.attach(13);
}

void servo_off(void)
{
    myservo1.detach();
    myservo2.detach();
    myservo3.detach();
    myservo4.detach();
}

void ps3control(void)
{
    if (Ps3.data.analog.stick.lx > 50)
        bq--;
    if (Ps3.data.analog.stick.lx < -50)
        bq++;
    if (Ps3.data.analog.stick.ly > 50)
        cq--;
    if (Ps3.data.analog.stick.ly < -50)
        cq++;
    if (Ps3.data.analog.stick.rx > 50)
        dq++;
    if (Ps3.data.analog.stick.rx < -50)
        dq--;
    if (Ps3.data.analog.stick.ry > 50)
        aq--;
    if (Ps3.data.analog.stick.ry < -50)
        aq++;

    delay(10);
}

void angle(void)
{
    if (aq < 30)
        aq = 30;
    if (aq > 110)
        aq = 110;
    if (bq < 10)
        bq = 10;
    if (bq > 139)
        bq = 139;
    emergency_stop();
    if (cq < 15)
        cq = 15;
    if (cq > 88)
        cq = 88;
    if (dq < 30)
        dq = 30;
    if (dq > 180)
        dq = 180;
}

void car(void)
{
    if (Ps3.data.analog.button.up)
    {
        Serial.println("w");
        ledcWrite(cin2, 230);
        ledcWrite(cin1, 0);
        ledcWrite(cin4, 230);
        ledcWrite(cin3, 0);
    }
    if (Ps3.data.analog.button.left)
    {
        Serial.println("a");
        ledcWrite(cin1, 0);
        ledcWrite(cin2, 230);
        ledcWrite(cin3, 230);
        ledcWrite(cin4, 0);
    }
    if (Ps3.data.analog.button.down)
    {
        Serial.println("s");
        ledcWrite(cin2, 0);
        ledcWrite(cin1, 230);
        ledcWrite(cin4, 0);
        ledcWrite(cin3, 230);
    }
    if (Ps3.data.analog.button.right)
    {
        Serial.println("d");
        ledcWrite(cin1, 230);
        ledcWrite(cin2, 0);
        ledcWrite(cin3, 0);
        ledcWrite(cin4, 230);
    }
    if (Ps3.data.analog.button.up == false && Ps3.data.analog.button.left == false && Ps3.data.analog.button.down == false && Ps3.data.analog.button.right == false)
    {
        ledcWrite(cin1, 0);
        ledcWrite(cin2, 0);
        ledcWrite(cin3, 0);
        ledcWrite(cin4, 0);
    }
}

bool i = false;
void emergency_stop(void)
{
    if (Ps3.data.analog.button.triangle)
    {
        servo_off();
        Serial.println("emgercy stop(kkk)");
        while (1)
        {
            delay(1000);
            digitalWrite(2, 1);
            for (int k = 0; k < 1000; k++)
            {
                if (Ps3.data.analog.button.triangle)
                {
                    i = true;
                }
                Serial.println(k);
            }
            digitalWrite(2, 0);
            if (i)
            {
                i = false;
                Serial.println("cancel(kkk)");
                delay(1000);
                servo_on();
                break;
            }
        }
    }
}

void setup()
{
    pinMode(2, OUTPUT);
    servo_on();
    ledcSetup(cin1, fr, re);
    ledcSetup(cin2, fr, re);
    ledcSetup(cin3, fr, re);
    ledcSetup(cin4, fr, re);
    ledcAttachPin(in1, cin1);
    ledcAttachPin(in2, cin2);
    ledcAttachPin(in3, cin3);
    ledcAttachPin(in4, cin4);
    Serial.begin(115200);
    Ps3.begin("2c:81:58:a2:3a:61");
}
void loop()
{
    emergency_stop();
        ps3control();
        angle();
        emergency_stop();
        car();
        myservo1.write(aq);
        myservo2.write(bq);
        myservo3.write(cq);
        myservo4.write(dq);
}
