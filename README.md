# menorah
Particle Photon Menorah

There are two versions of the Particle INO file: the digital version uses all digital pins (D0-D7) for the candles and A0 for the shammash (using DigitalWrite).

The JSON file contains the start datetime for each night of Chanukah for the current year. The PHP file reads the JSON and just echoes a single digit indicating which night of Chanukah it is.
