// image offset 0xA4A990 address 7ff7a3bda990

undefined1 FUN_7ff7a3bda990(longlong param_1,undefined8 param_2)

{
  char cVar1;
  
  cVar1 = FUN_7ff7a3bda940();
  if (cVar1 != '\0') {
    cVar1 = FUN_7ff7a3c07870(param_2,*(undefined4 *)(param_1 + 0x348));
    if (cVar1 != '\0') {
      cVar1 = FUN_7ff7a3c072c0(param_2,*(undefined1 *)(param_1 + 0x34c));
      if (cVar1 != '\0') {
        return 1;
      }
    }
  }
  return 0;
}

