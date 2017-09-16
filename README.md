# df-4motor-platform

TODO: migrate word doc to readme

sep 16, 2017
 - RF and electrical interference from DC motor is causing erratic behavior in the input to pin 3.
 - presence of RF inteference has been verified by chc via a simple test (varying the distance between the dc motor and the wire leading into pin 3). 
 - need to find some way to shield the EM inteference (aluminium foil, twisted pair, etc.). Or have DC motor as far as possible from other circuitry 
 - put a disc capacitor 10nf across the motor as close to the motor as possible to reduce RF noise off of the brushes
 - need to buy capacitors to reduce electrical noise
