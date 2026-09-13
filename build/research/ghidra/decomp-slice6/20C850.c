// image offset 0x20C850 address 7ff7a339c850

void FUN_7ff7a339c850(undefined4 *param_1,longlong param_2)

{
  *param_1 = *(undefined4 *)(param_2 + 0x68);
  param_1[1] = *(undefined4 *)(param_2 + 0x6c);
  *(undefined2 *)(param_1 + 6) = *(undefined2 *)(param_2 + 0xc0);
  *(undefined8 *)(param_1 + 4) = *(undefined8 *)(param_2 + 0xb8);
  param_1[2] = *(undefined4 *)(param_2 + 0xb4);
  return;
}

