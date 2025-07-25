
#include "Console.h"
// #include "StreamStmUSB.h"
#include "main.h"

bool Console::recieveCommands()
{
  bool result = false;
  /*checks if 0 is overridden -> new message in buffer*/
  if (stream.isAvaliable())
  {
    // printf("Received data: %s\n", UserRxBufferFS);

    /*decode message*/
    char command[4] = {0};
    float param0 = -1, param1 = -1, param2 = -1, param3 = -1;

    int num_params = sscanf(stream.getBuffer(), "%s %f %f %f %f", command,
                            &param0, &param1, &param2, &param3);
    if (num_params)
    {

      // Print the command and the parameters
      printf("~rec:%s|%f|%f|%f|%f|\n", command, param0, param1, param2, param3);

      // printf("r:%i,n:%i\n",com_encoded, (int)('d' << 24 | 'f' << 16 | 'u' <<
      // 8 | 0));

      // encode command to int to use switch case
      int com_encoded =
          (int)((command[0] << 24) | (command[1] << 16) | (command[2] << 8) |
                command[3]); // encodes 4 char in one int to be compared by
                             // switch case
      switch (com_encoded)
      {
      /**here are the executions of all the commands */
      /*help*/
      case (int)('?' << 24 | 0):
      {
        printf("\n--help--\n");
        printf("-[str command]_[4x float param]\n");
        printf("-?|this help screen\n");
        printf("-dfu|Device Firmware Update\n");
        printf("-pa [freq] [dfu \\%]|Sets Phase A Freq\n");
        printf("\n");
        result = true;
        break;
      }

      case (int)('b' << 24 | 0):
      {
        printf(">Battery Voltage:69V");
        printf("\n");
        result = true;
        break;
      }

      /*dfu update*/
      case (int)('d' << 24 | 'f' << 16 | 'u' << 8 | 0):
      {
        printf("\n--DFU update--\n");
        stream.jumpToBootloader();
        result = false;
        break;
      }

      default:
      {
        printf("unknown commnad\n");
        break;
      }
      }
      stream.clearBuffer();
    }
  }
  return result;
}

void Console::startupMessage()
{
  printf("\033[35m");
  printf("  .-')    .-') _   _   .-')\n");
  printf(" ( OO ). (  OO) ) ( '.( OO )_\n");
  printf(" (_)---\\_)/     '._ ,--.   ,--.).-----.  .-----.  \n");
  printf("/    _ | |'--...__)|   `.'   |/  -.   \\/ ,-.   \\ \n");
  printf(" \\  :` `. '--.  .--'|         |'-' _'  |'-'  |  | \n");
  printf(" '..`''.)   |  |   |  |'.'|  |   |_  <    .'  /  \n");
  printf(" .-._)   \\   |  |   |  |   |  |.-.  |  | .'  /__  \n");
  printf("  \\       /   |  |   |  |   |  |\\ `-'   /|       | \n");
  printf(" `-----'    `--'   `--'   `--' `----'' `-------' \n");
  printf("\033[0m");
}

// extern USBD_HandleTypeDef hUsbDeviceFS;
// extern USBD_DescriptorsTypeDef FS_Desc;

// /**
//  * Trigger DFU bootloader via Software
//  */
// void Console::jumpToBootloader() {
//       // Disables CDC USB
//     USBD_Stop(&hUsbDeviceFS);
//     USBD_DeInit(&hUsbDeviceFS);

//     // Disable all interrupts
//     __disable_irq();

//     // Reset USB peripheral (optional, but good practice)
//     RCC->APB1ENR1 &= ~RCC_APB1ENR1_USBFSEN;
//     RCC->APB1ENR1 |= RCC_APB1ENR1_USBFSEN;

//     // Set the vector table MSP and jump to bootloader
//     uint32_t bootloader_address = 0x1FFF0000; // STM32L4 system memory

//     __set_MSP(*(volatile uint32_t *)bootloader_address);
//     void (*bootloader_jump)(void) = (void (*)(void))(*(volatile uint32_t *)(bootloader_address + 4));
//     bootloader_jump();
// }