#include "Whistles.h"

size_t n = 0;
char buffer[4096] = "";

void setup()
{
    Serial.begin(115200);
    Whistles.eval("print(\"[INFO]: Hello, World!\");");
}

void loop()
{
    n = Serial.available();
    for (size_t i = 0; i < n; ++i)
    {
        buffer[i] = Serial.read();
    }
    buffer[n] = 0;
    Whistles.eval(buffer);
}
