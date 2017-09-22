# df-4motor-platform

TODO: migrate word doc to readme

sep 16, 2017
 - RF and electrical interference from DC motor is causing erratic behavior in the input to pin 3.
 - presence of RF inteference has been verified by chc via a simple test (varying the distance between the dc motor and the wire leading into pin 3). 
 - need to find some way to shield the EM inteference (aluminium foil, twisted pair, etc.). Or have DC motor as far as possible from other circuitry 
 - put a disc capacitor 10nf across the motor as close to the motor as possible to reduce RF noise off of the brushes
 - need to buy capacitors to reduce electrical noise

How to Set-Up OpenCV in Microsoft Visual Studio
https://docs.google.com/document/d/1GJKjPO__LdRvwhadMwhDU-g-vjULhmtshCOMC_yiCeM/edit?usp=sharing


sep 22, 2017 notes
 - motor brush produces sparks, producing noise. add ceramic capacitors (usually 100nF) directly to the terminals of the DC motor. for maximum noise suppression, add 3 caps (1 from terminal to terminal, 2 from each terminal to the motor casing).
  - when a motor is first turned on at dead stop, or when the motor stalls, the motor draws a higher current, which may pull down the battery power rail enough to reset some digital electronics in the circuit. To mitigate, add large electrolytic capacitors directly across the battery (or across the battery input to the PWM motor driver, or across the battery input to the digital electronics, or often capacitors in all three locations) -- these capacitors work better at supplying high currents for a few milliseconds than the battery does (decoupling caps).
  
   - keep motor and power leads as short possible
   
    - Place decoupling capacitors (also known as “bypass capacitors”) across power and ground near any electronics that you want to isolate from noise. The closer you can get them to the electronics, the more effective they will be, and generally speaking, the more capacitance you use, the better. Recommend electrolytic caps of several hundred microF
