/*
 * Demo code for driving a 12 digit 7 segment VFD using
 * an HV5812.
 */

#define LATCH_PIN B00100000
#define CLOCK_PIN B00000100
#define DATA_PIN  B00000001

#define SEGMENT_COUNT 12

byte buffer[] = {
  B11100110,
  B11111100, //0
  B11100110, //9
  B11111110, //8
  B11100000, //7
  B10111110, //6
  
  B10110110, //5
  B01100110, //4
  B11110010, //3
  B11011010, //2
  B01100000, //1
  B11111111  //-
};

void setup() {
  // Disable Timer0
  TCCR0B &= !(1 << CS00);

  // Set latch pin as output
  DDRH |= LATCH_PIN;

  // Clear latch pin
  PORTH &= !LATCH_PIN;
  
  // Set clock and data pins as output
  DDRB |= (CLOCK_PIN | DATA_PIN);

  // Clear clock and data pins
  PORTB &= !(CLOCK_PIN | DATA_PIN);
}

void loop() {
  for (byte i = 0; i < SEGMENT_COUNT; ++i) {
    writeSegments(buffer[i]);
    writeGrids(i);
    toggleLatch();
  }
}

void writeSegments(byte pattern) {
  for (byte i = 1; i != 0; i <<= 1) {
    if (pattern & i) {
      shiftOutBit(1);
    } else {
      shiftOutBit(0);
    }
  }
}

void writeGrids(byte activeGrid) {
  for(byte i = 0; i < SEGMENT_COUNT; ++i) {
    shiftOutBit(i==activeGrid);
  }
}

void toggleLatch() {
  PORTH |= LATCH_PIN;
  PORTH &= !LATCH_PIN;
}

void shiftOutBit(byte data) {
  // Toggle Data
  PORTB ^= data;

  // Set clock high
  PORTB |=  CLOCK_PIN;

  // Clear clock and data
  PORTB &= !(CLOCK_PIN | DATA_PIN);
}

