#define sw1   0x1
#define sw2   0x2
#define sw3   0x4
#define sw4   0x8
#define sw5   0x10
#define sw6   0x20
#define sw7   0x40
#define sw8   0x80

void PCF8574A_set(uint8_t sw);
uint8_t PCF8574A_get(void);
