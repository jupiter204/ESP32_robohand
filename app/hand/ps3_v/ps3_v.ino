
#include <ESP32Servo.h> //載入函式庫，這是內建的，不用安裝
#include <Ps3Controller.h>

Servo myservo1;
Servo myservo2;
Servo myservo3; // 建立SERVO物件
Servo myservo4;

int a = 40, b = 65, c = 36, d = 180;

void servo_on(void){
    myservo1.attach(14); // 30,110
    myservo2.attach(12); // 10,140
    myservo3.attach(23); // 15,88
    myservo4.attach(13);
}

void servo_off(void){
    myservo1.detach();
    myservo2.detach();
    myservo3.detach();
    myservo4.detach();
}

void ps3control(void)
{
    if (Ps3.isConnected())
    {
        if (Ps3.data.analog.stick.lx > 50)
            b--;
        if (Ps3.data.analog.stick.lx < -50)
            b++;
        if (Ps3.data.analog.stick.ly > 50)
            c--;
        if (Ps3.data.analog.stick.ly < -50)
            c++;
        emergency_stop();
        if (Ps3.data.analog.stick.rx > 50)
            d++;
        if (Ps3.data.analog.stick.rx < -50)
            d--;
        if (Ps3.data.analog.stick.ry > 50)
            a--;
        if (Ps3.data.analog.stick.ry < -50)
            a++;
    }
    delay(20);
}

void angle(void)
{
    if (a < 30)
        a = 30;
    if (a > 110)
        a = 110;
    if (b < 10)
        b = 10;
    if (b > 139)
        b = 139;
    emergency_stop();
    if (c < 15)
        c = 15;
    if (c > 88)
        c = 88;
    if (d < 30)
        d = 30;
    if (d > 180)
        d = 180;
}

bool i = false;
void emergency_stop(void)
{
    if (Ps3.event.button_down.triangle)
    {
        servo_off();
        Serial.println("emgercy stop(kkk)");
        while (1)
        {
            delay(1000);
            digitalWrite(2, 1);
            for (int k = 0; k < 1000; k++)
            {
                if (Ps3.event.button_down.triangle)
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
    Serial.begin(115200);
    Ps3.begin("2c:81:58:a2:3a:61");
    Serial.println("Ready.");
}

void loop()
{
    emergency_stop();
    ps3control();
    angle();

    Serial.print(a);
    Serial.print(",");
    Serial.print(b);
    Serial.print(",");
    Serial.print(c);
    Serial.print(",");
    Serial.println(d);
    emergency_stop();
    myservo1.write(a);
    myservo2.write(b);
    myservo3.write(c);
    myservo4.write(d);
}
