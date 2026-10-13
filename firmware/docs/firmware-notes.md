# Lessons Learned

## Rotary switch startup

Observation:
The Gray-code band selector uses RP2040 internal pull-ups and
100 nF debounce capacitors on each GPIO input.

At power-up, the GPIO states may not immediately reflect the
physical switch position. A startup settling delay of 100 ms
eliminates false band selections.

Implementation:

```cpp
initRotary();
delay(100);
currentBand = readBandFromRotary();
```


## Rotary switch transitions

Observation: During band changes the Gray-code switch can briefly present valid intermediate states.

Solution: Two consecutive identical readings are required before a new band selection is accepted.

## MAX2870 startup

Observation: Programming the MAX2870 immediately after CE assertion does not reliably achieve lock.

A delay after CE enable is required.

Implementation:
digitalWrite(hw.cePin, HIGH);
delay(10);


Result: Reliable lock acquisition after power-up.