// image offset 0x121E90 address 7ff7a32b1e90

undefined8 FUN_7ff7a32b1e90(longlong param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  float fVar4;
  
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 1)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar2 = FUN_7ff7a3468d90(param_1);
    if (iVar2 != 0) goto LAB_7ff7a32b1ed4;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b1ed4:
  puVar3 = *(undefined4 **)(param_1 + 0x48);
  if (*(undefined4 **)(param_1 + 0x50) < puVar3) {
    fVar4 = (float)FUN_7ff7a3469aa0(param_1,*(undefined4 **)(param_1 + 0x50));
    puVar3 = *(undefined4 **)(param_1 + 0x48);
    iVar2 = (int)fVar4;
  }
  else {
    iVar2 = 0;
  }
  cVar1 = (&DAT_7ff7a9234080)[(longlong)iVar2 * 0x13890];
  *puVar3 = 1;
  puVar3[2] = (uint)(cVar1 != '\0');
  *(undefined4 **)(param_1 + 0x48) = puVar3 + 4;
  return 1;
}

