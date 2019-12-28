// This #include statement was automatically added by the Particle IDE.
#include <HttpClient.h>

http_header_t headers[] = {  
    { "Content-Type", "text/html" },  
    { NULL, NULL }   
};  
 
http_request_t request;  
http_response_t response;  
 
HttpClient http;  

Timer timer(60000, check_night_of_hanukkah);
   
SYSTEM_MODE(SEMI_AUTOMATIC);

// PWM pins D0, D1, D2, D3, A4, A5, WKP, RX and TX
int candle1 = D3; 
int candle2 = WKP; 
int candle3 = D0;
int candle4 = D1;
int candle5 = A5; 
int candle6 = TX; 
int candle7 = RX; 
int candle8 = D4; 
int shammash = D2;

int button = D6;
int indicator = D7;

int day = 0;
int manual = 0; //button press triggers manual mode, this will override the automatic candle-lighting

boolean connectToCloud = true;


// Cloud functions must return int and take one String
int setDay(String d) 
{
    manual = 1;
    day = d.toInt();
    clear_candles();
    light_candles();
  return 0;
}

void setup()
{
    pinMode(shammash, OUTPUT);
    pinMode(candle1, OUTPUT);
    pinMode(candle2, OUTPUT);
    pinMode(candle3, OUTPUT);
    pinMode(candle4, OUTPUT);
    pinMode(candle5, OUTPUT);
    pinMode(candle6, OUTPUT);
    pinMode(candle7, OUTPUT);
    pinMode(candle8, OUTPUT);
    
    pinMode(indicator, OUTPUT);
    pinMode(button, INPUT_PULLDOWN);
    
    request.hostname = "herstein.dyndns.org";
    request.path = "/hebcal/index.php";

bool success = Particle.function("setDay", setDay);

    timer.start();
}


void check_night_of_hanukkah()
{
    int newday;
    
    if(!manual)
    {
        http.get(request, response, headers);

        if(response.status==200)
        {
            newday = response.body.toInt();
        
            if(newday!=day)
            {
                day = newday;
                clear_candles();
            }
        }
        else // couldn't get to web site telling us what day it is, so set day to 0 and put into manual mode
        {
            day = 0;
            manual = 1;
        }
    }
}

void clear_candles()
{
    // turn all the candles off
    digitalWrite(shammash, LOW);
    analogWrite(candle1, 0);
    analogWrite(candle2, 0);
    analogWrite(candle3, 0);
    analogWrite(candle4, 0);
    analogWrite(candle5, 0);
    analogWrite(candle6, 0);
    analogWrite(candle7, 0);
    digitalWrite(candle8, LOW);
}

void light_candles()
{
    if(day==0)
    {
        // Just light the shamash
        digitalWrite( shammash, HIGH);
    }
    
    if(day>0)
    {
        digitalWrite( shammash, HIGH);
        analogWrite(candle1, random(155)+100);
    }
        
    if(day>1)
        analogWrite(candle2, random(155)+100);
    
    if(day>2)
        analogWrite(candle3, random(155)+100);

    if(day>3)
        analogWrite(candle4, random(155)+100);
        
    if(day>4)
        analogWrite(candle5, random(155)+100);
        
    if(day>5)
        analogWrite(candle6, random(155)+100);
        
    if(day>6)
        analogWrite(candle7, random(155)+100);
        
    if(day>7)
        digitalWrite(candle8, HIGH); //Moved to a digital pin, since there aren't enough analog pins!
}

void loop() 
{
    
    if(connectToCloud && Particle.connected() == false) {
        Particle.connect();
        connectToCloud = false;
    }
    
    //check if it's connected, if it is, turn on blue indicator LED
    if (Particle.connected()) 
        digitalWrite(indicator, HIGH);
    else
        digitalWrite(indicator, LOW);
    
    if(digitalRead(button) == HIGH)
    {
        manual = 1; //now in override mode!
        day++;
        if(day==9)
        {
            // reset day to zero; turn off menorah 
            day = 0;
            
            // reset all candles
            clear_candles();
        }
        
        delay(250);
    }

    light_candles();
    delay(random(100));
}

/*
void printResponse(http_response_t &response) {  
   Serial.println("HTTP Response: ");  
   Serial.println(response.status);  
   Serial.println(response.body);  
 }  
   
 void getRequest() {  
   
   request.path = "/photon/time";  
   request.body = "";  
   
   http.get(request, response, headers);  
   printResponse(response);  
 }  
   
 void putRequest() {  
   
   request.path = "/photon/measurements";  
   request.body = "{\"measurementType\":\"static\", \"value\": 1000}";  
   
   http.put(request, response, headers);  
   printResponse(response);  
 }  
   
 void postRequest() {  
   
   request.path = "/photon/measurements";  
   request.body = "{\"measurementType\":\"static\", \"value\": 2000}";  
   
   http.post(request, response, headers);  
   printResponse(response);  
 }  
   
 void deleteRequest() {  
   
   request.path = "/photon/measurements/123";  
   request.body = "";  
   
   http.del(request, response, headers);  
   printResponse(response);  
 }  
 */
