// image offset 0x20D440 address 7ff7a339d440

void FUN_7ff7a339d440(longlong param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  *(undefined1 *)(param_1 + 0x234) = 0;
  *(undefined4 *)(param_1 + 0x230) = 0;
  do {
    FUN_7ff7a3bd8770((longlong)(int)uVar1 * 0x38 + param_1);
    uVar1 = uVar1 + 1;
  } while (uVar1 < 10);
  return;
}

