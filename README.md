# exam
// I renamed the picture, so I reupdated them then.
About:
We need to creat a square signal wave that rise to the peak(3V) in different of the period by using DAC. Also, shown the condition on uLCD. Then use ADC to detect it and sample it. Then plot out the ADC data points by Matplotlib.

Build with:
C++, Python

Inputs:
Three buttons as DigitalIn that can select the slew rate of the signal wave and confirm it, which have "up", "down", and "confirm".

Display:
Create a display on uLCD that can show the selection od the frequency.

Generate waveform:
Use DAC to generate a square signal wave of the selected slew rate.

Measure:
Use picoscope to measure the output signal wave.

Sample:
As the signal is generated, save the data points to a ADC matrix and save it.

Analysis:
Then plot the data points by Matplotlib and we can see the wave is different.


