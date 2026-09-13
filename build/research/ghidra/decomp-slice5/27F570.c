// image offset 0x27F570 address 7ff7a340f570

undefined8
FUN_7ff7a340f570(longlong param_1,undefined8 param_2,undefined8 param_3,longlong *param_4)

{
  uint uVar1;
  undefined8 uVar2;
  uint uVar3;
  longlong lVar4;
  undefined8 local_res20;
  
  lVar4 = 0;
  *param_4 = 0;
  uVar2 = FUN_7ff7a340f430();
  if ((char)uVar2 == '\0') {
    return uVar2;
  }
  uVar1 = *local_res20 & 0xe0000000;
  if ((uVar1 == 0x40000000) && (uVar3 = *local_res20 & 0x1fffffff, uVar3 != 0x1fffffff)) {
    lVar4 = (ulonglong)uVar3 + *(longlong *)(param_1 + 0x100);
  }
  *param_4 = lVar4;
  return CONCAT71((uint7)(uint3)(uVar1 >> 8),1);
}

