// image offset 0x856640 address 7ff7a39e6640

uint FUN_7ff7a39e6640(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  uint uVar4;
  
  cVar1 = FUN_7ff7a3919d60();
  uVar4 = (uint)(cVar1 == '\0');
  iVar2 = FUN_7ff7a3919d80(param_1);
  if (iVar2 != 0) {
    uVar4 = uVar4 | 2;
  }
  cVar1 = FUN_7ff7a37defb0();
  if (cVar1 == '\0') {
    uVar4 = uVar4 | 8;
  }
  cVar1 = FUN_7ff7a32612b0();
  if (cVar1 == '\0') {
    uVar4 = uVar4 | 0x10;
  }
  cVar1 = FUN_7ff7a325ecd0();
  if (cVar1 == '\0') {
    uVar4 = uVar4 | 4;
  }
  iVar2 = FUN_7ff7a39c71b0();
  if (iVar2 != 0) {
    uVar4 = uVar4 | 0x200;
  }
  cVar1 = FUN_7ff7a32612c0(param_1);
  if (cVar1 != '\0') {
    uVar4 = uVar4 | 0x20;
  }
  cVar1 = FUN_7ff7a37defd0();
  if (cVar1 == '\0') {
    uVar4 = uVar4 | 0x2000;
  }
  cVar1 = FUN_7ff7a37e2760();
  if (cVar1 == '\0') {
    uVar4 = uVar4 | 0x40;
  }
  cVar1 = FUN_7ff7a376fa90();
  if (cVar1 == '\0') {
    uVar4 = uVar4 | 0x100;
  }
  cVar1 = FUN_7ff7a38b6b60(param_1);
  if (cVar1 == '\0') {
    uVar4 = uVar4 | 0x400;
  }
  cVar1 = FUN_7ff7a38f6630();
  if ((cVar1 == '\0') ||
     ((*(int *)(DAT_7ff7b13c6b60 + 0x10) == 0 && (cVar1 = FUN_7ff7a3334d10(param_1), cVar1 == '\0'))
     )) {
    uVar4 = uVar4 | 0x800;
  }
  cVar1 = FUN_7ff7a340a210(param_1);
  if (cVar1 == '\0') {
    uVar4 = uVar4 | 0x1000;
  }
  cVar1 = thunk_EXT_FUN_7ff734190070();
  if (cVar1 == '\0') {
    uVar4 = uVar4 | 0x8000;
  }
  uVar3 = FUN_7ff7a3422020();
  cVar1 = FUN_7ff7a3421150(uVar3);
  if (cVar1 == '\0') {
    uVar4 = uVar4 | 0x10000;
  }
  FUN_7ff7a39e7540(param_1,uVar4);
  return uVar4;
}

