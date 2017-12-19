# Standard Use

0. $ ln -s /dev/ttyUSB0 USB0
1. Make the auto-zero
2. Turn on controller
3. Run: ./setMotorPK264_5cmPERmin
4. Run: ./FindZero (moving the sample holder all the way down)
5. Turn off the controller after the motor stops
6. Turn on the controller
7. Run: ./setMotorPK264_1mmPERsec
8. Put the crystal in
9. Start the data acquisition in the spectrometer (wait few seconds)
10. Run: ./MoveAll_1mmPERsec
11. Turn off the controller and return to (2)

* To move the motor to the center (for transverse transmittance), run: ./MoveMinus10cm
## To check three points

1. Zero stepper like above
2. ./MovePlus10cm
3. ./Move1cm three times -at 13 cm
4. ./Move2cm -at 8 cm
5. ./Move2cm -at 3 cm
6. ./MoveMinus1cm -resets back to 13 cm

NOTE: Move2cm means Move 5cm... 

* Originally written by Marco Carmignotto
