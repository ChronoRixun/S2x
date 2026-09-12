// image offset 0x8397E0 address 7ff7a39c97e0

void FUN_7ff7a39c97e0(undefined1 *param_1)

{
  char cVar1;

  *param_1 = 1;
  *(undefined4 *)(param_1 + 8) = 2;
  cVar1 = FUN_7ff7a3804d60();
  if (cVar1 != '\0') {
    FUN_7ff7a39c9810(param_1);
    return;
  }
  return;
}
