// image offset 0x36FD30 address 7ff7a34ffd30

undefined8 FUN_7ff7a34ffd30(longlong param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined1 local_68 [4];
  undefined4 local_64;
  undefined4 local_60;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined1 local_48 [48];
  
  local_60 = 0xffffffff;
  bVar2 = 0;
  local_68[0] = 0;
  local_64 = 0;
  local_58 = 0;
  uStack_50 = 0;
  cVar3 = FUN_7ff7a3401760();
  if ((cVar3 != '\0') && (cVar3 = FUN_7ff7a36309b0(), cVar3 == '\0')) {
    if ((int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4) != 0) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    iVar4 = FUN_7ff7a3402500();
    iVar7 = 0;
    do {
      cVar3 = FUN_7ff7a3631eb0(iVar7);
      if (cVar3 != '\0') {
        uVar5 = FUN_7ff7a3630a80(iVar7);
        cVar3 = FUN_7ff7a3401c90(uVar5);
        if (cVar3 != '\0') {
          cVar3 = FUN_7ff7a34017e0(uVar5,local_68,local_48,1);
          if ((cVar3 != '\0') && (FUN_7ff7a3401d30(uVar5,local_68,local_48), iVar6 = 0, 0 < iVar4))
          {
            do {
              cVar3 = FUN_7ff7a3401910(uVar5,iVar6,local_68,local_48);
              if (cVar3 != '\0') {
                bVar2 = 1;
                break;
              }
              iVar6 = iVar6 + 1;
            } while (iVar6 < iVar4);
          }
        }
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < 2);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar2;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

