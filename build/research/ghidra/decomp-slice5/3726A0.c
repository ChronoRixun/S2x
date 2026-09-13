// image offset 0x3726A0 address 7ff7a35026a0

void FUN_7ff7a35026a0(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = (longlong)*(int *)(param_1 + 4) * 0x110;
  *(undefined8 *)(&DAT_7ff7abba4f84 + (longlong)*(int *)(param_1 + 4) * 0x44) = 1;
  *(undefined8 *)(&DAT_7ff7abba4f68 + lVar1) = 0;
  *(undefined8 *)(lVar1 + 0x7ff7abba4f70) = 0;
  *(undefined8 *)(&DAT_7ff7abba4f78 + lVar1) = 0;
  (&DAT_7ff7abba4f80)[lVar1] = 0;
  return;
}

