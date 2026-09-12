// image offset 0x3721A0 address 7ff7a35021a0

void FUN_7ff7a35021a0(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  
  if (*(int *)(DAT_7ff7ad79e9c0 + 0x10) != 0) {
    uVar1 = FUN_7ff7a35023b0(param_2,param_3);
    if (uVar1 != 0xffffffff) {
      *(undefined8 *)
       ((&DAT_7ff7abba5010)[(longlong)param_1 * 0x22] + 0x10 + (ulonglong)uVar1 * 0x1ca0) = 0;
    }
  }
  return;
}

