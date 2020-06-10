#include <Arduino.h>
#include <HardwareSerial.h>

#define CYCLES 2        // 2 yields a heartbeat effect
#define SHORT_DELAY 100 // 1/10 second
#define LONG_DELAY 1000 // 1 seco

// retarget the C library printf function to USART0
extern "C" int _put_char(int ch) // used by printf
{
  usart_data_transmit(USART0, (uint8_t)ch);
  while (usart_flag_get(USART0, USART_FLAG_TBE) == RESET)
  {
  }
  return ch;
}

static void init_uart0(void);

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  init_uart0();
  printf("\nSipeed Nano Blink\n");
  printf("=================\n");
  printf("Platform: Arduino\n");
  printf("LED_BUILTIN: %d\n", LED_BUILTIN);
  printf("\n");
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(100);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
  // wait for a second
  delay(100);
}

static void init_uart0(void)
{
  // enable GPIO clock
  rcu_periph_clock_enable(RCU_GPIOA);
  // enable USART0 clock
  rcu_periph_clock_enable(RCU_USART0);
  // configure USART0
  usart_deinit(USART0);
  usart_baudrate_set(USART0, 115200U);
  usart_word_length_set(USART0, USART_WL_8BIT);
  usart_stop_bit_set(USART0, USART_STB_1BIT);
  usart_parity_config(USART0, USART_PM_NONE);
  usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
  usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
  usart_receive_config(USART0, USART_RECEIVE_ENABLE);
  usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
  usart_enable(USART0);
}