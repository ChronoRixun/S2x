// image offset 0xA4C6B0 address 7ff7a3bdc6b0

longlong FUN_7ff7a3bdc6b0(longlong param_1,uint param_2)

{
  FUN_7ff7a3bdc990(param_1 + -0x10,*(undefined8 *)(param_1 + -0x10),*(undefined4 *)(param_1 + -4));
  FUN_7ff7a3c05240(*(undefined8 *)(param_1 + -0x10));
  *(undefined8 *)(param_1 + -0x10) = 0;
  *(undefined8 *)(param_1 + -8) = 0;
  FUN_7ff7a3bdca10(param_1 + -0x20,*(undefined8 *)(param_1 + -0x20),*(undefined4 *)(param_1 + -0x14)
                  );
  FUN_7ff7a3c05240(*(undefined8 *)(param_1 + -0x20));
  *(undefined8 *)(param_1 + -0x20) = 0;
  *(undefined8 *)(param_1 + -0x18) = 0;
  FUN_7ff7a3bdc910(param_1 + -0x30,*(undefined8 *)(param_1 + -0x30),*(undefined4 *)(param_1 + -0x24)
                  );
  FUN_7ff7a3c05240(*(undefined8 *)(param_1 + -0x30));
  *(undefined8 *)(param_1 + -0x30) = 0;
  *(undefined8 *)(param_1 + -0x28) = 0;
  FUN_7ff7a3bcb470(param_1 + -0x180);
  FUN_7ff7a3c04d10(param_1 + -0x40);
  FUN_7ff7a3bcb470(param_1 + -0x1b8);
  FUN_7ff7a3c04d10(param_1);
  if ((param_2 & 1) != 0) {
    if ((param_2 & 4) == 0) {
      FUN_7ff7a3c05240(param_1 + -0x1c8);
    }
    else {
      FUN_7ff7a31a2b10(param_1 + -0x1c8,0x1d8);
    }
  }
  return param_1 + -0x1c8;
}

