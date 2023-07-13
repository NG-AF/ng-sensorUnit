# NG-AF -- Sensor Unit Code
This code is written in order to gather data from all of the sensors in the NG RC Plane.

# For legal stuff -> [LICENSE](./LICENSE.md)

## Installation

This code is written using **[PlatformIO](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjf8JaWjYyAAxWaRvEDHYyaD2wQFnoECAoQAQ&url=https%3A%2F%2Fplatformio.org%2F&usg=AOvVaw0bbbRbV8IEdG0oFFV7AHHw&opi=89978449)**. Use of PIO is recommended.

```
git clone https://github.com/NG-AF/ng-sensorUnit.git
cd ng-sensorUnit/
```

## Notes
#### (Teleplot0)[https://marketplace.visualstudio.com/items?itemName=alexnesnes.teleplot] extension is used to plot the data. 
```
Serial.print(">{varName});
Serial.println({var});
```
Code above will plot the variable in Teleplot and ***not*** to the Serial Monitor.