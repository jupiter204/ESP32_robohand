#include <ESP32Servo.h> //載入函式庫，這是內建的，不用安裝
#include <PS4Controller.h>

Servo myservo1;
Servo myservo2;
Servo myservo3; // 建立SERVO物件
Servo myservo4;

int a = 40, b = 65, c = 36, d = 180;

void setup()
{
    myservo1.attach(14); // 30,110
    myservo2.attach(12); // 10,140
    myservo3.attach(23); // 15,88
    myservo4.attach(13);
    Serial.begin(115200);
    PS4.begin("b8:9a:2a:1c:48:f9");
    Serial.println("Ready.");
}

void ps4control(void)
{
    if (PS4.isConnected())
    {
        if (PS4.LStickX() > 50)
            b--;
        if (PS4.LStickX() < -50)
            b++;
        if (PS4.LStickY() > 50)
            c++;
        if (PS4.LStickY() < -50)
            c--;
        if (PS4.RStickX() > 50)
            d++;
        if (PS4.RStickX() < -50)
            d--;
        if (PS4.RStickY() > 50)
            a--;
        if (PS4.RStickY() < -50)
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
    if (c < 15)
        c = 15;
    if (c > 88)
        c = 88;
    if (d < 30)
        d = 30;
    if (d > 180)
        d = 180;
}

int i;
void emergency_stop(void)
{
    if (PS4.Triangle())
    {
        while (1)
        {
            myservo1.detach();
            myservo2.detach();
            myservo3.detach();
            myservo4.detach();
            if (PS4.Triangle())
                break;
        }
    }
}

void loop()
{
    emergency_stop();
    ps4control();
    angle();

    Serial.print(a);
    Serial.print(",");
    Serial.print(b);
    Serial.print(",");
    Serial.print(c);
    Serial.print(",");
    Serial.println(d);

    myservo1.write(a);
    myservo2.write(b);
    myservo3.write(c);
    myservo4.write(d);
}
