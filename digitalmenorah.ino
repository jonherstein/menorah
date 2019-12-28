// This #include statement was automatically added by the Particle IDE.
#include <HttpClient.h>
http_header_t headers[] = {{ "Content-Type", "text/html" },{ NULL, NULL }};  
http_request_t request;  
http_response_t response;  
HttpClient http;  

Timer timer(60000, check_night_of_hanukkah);
   
SYSTEM_MODE(SEMI_AUTOMATIC);

// All Digital pins
int candle1 = D0; 
int candle2 = D1; 
int candle3 = D2;
int candle4 = D3;
int candle5 = D4; 
int candle6 = D5; 
int candle7 = D6; 
int candle8 = D7; 
int shammash = A0;

//int button = D6;
//int indicator = D7;

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
    // All Digital pins
    pinMode(shammash, OUTPUT);
    pinMode(candle1, OUTPUT);
    pinMode(candle2, OUTPUT);
    pinMode(candle3, OUTPUT);
    pinMode(candle4, OUTPUT);
    pinMode(candle5, OUTPUT);
    pinMode(candle6, OUTPUT);
    pinMode(candle7, OUTPUT);
    pinMode(candle8, OUTPUT);
    
//    pinMode(indicator, OUTPUT);
//    pinMode(button, INPUT_PULLDOWN);
    
    request.hostname = "herstein.dyndns.org";
    request.path = "/hebcal/index.php";

    // Publish the setDay function/API
    Particle.function("setDay", setDay);

    // Launch the timer to occasionally check the day
    timer.start();
}

void check_night_of_hanukkah()
{
    int newday;
    //String str = "The night is ";
    //Particle.publish("Checking night", PRIVATE);
    
    if(!manual)
    {
        http.get(request, response, headers);

        if(response.status==200)
        {

            newday = response.body.toInt();

            //str.concat(String(newday));
            //Particle.publish(str, PRIVATE);
        
            if(newday!=day)
            {
                day = newday;
                clear_candles();
                light_candles();
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
    digitalWrite(candle1, LOW);
    digitalWrite(candle2, LOW);
    digitalWrite(candle3, LOW);
    digitalWrite(candle4, LOW);
    digitalWrite(candle5, LOW);
    digitalWrite(candle6, LOW);
    digitalWrite(candle7, LOW);
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
        digitalWrite( candle1, HIGH);
    }
        
    if(day>1)
        digitalWrite( candle2, HIGH);
    
    if(day>2)
        digitalWrite( candle3, HIGH);

    if(day>3)
        digitalWrite( candle4, HIGH);
        
    if(day>4)
        digitalWrite( candle5, HIGH);
        
    if(day>5)
        digitalWrite( candle6, HIGH);
        
    if(day>6)
        digitalWrite( candle7, HIGH);
        
    if(day>7)
        digitalWrite( candle8, HIGH);
}

void loop() 
{
    // Attempt to connect to the cloud if we aren't already connected
    if(connectToCloud && Particle.connected() == false) {
        Particle.connect();
        connectToCloud = false;
    }

/*    
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
    */
    
    delay(100);
}
