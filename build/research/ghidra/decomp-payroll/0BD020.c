// image offset 0xBD020 address 7ff7a324d020

undefined8 FUN_7ff7a324d020(undefined4 param_1,longlong param_2,longlong param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined4 uVar6;
  longlong lVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined8 *puVar10;
  longlong lVar11;
  longlong lVar12;
  undefined8 local_48;
  undefined8 uStack_40;
  undefined8 local_38;
  undefined8 uStack_30;
  undefined1 local_28 [32];
  
  if (param_3 == 0) {
    return 0;
  }
  FUN_7ff7a39029b0(0xcd);
  DAT_7ff7a4695fa8 = DAT_7ff7a4695fa8 + 1;
  DAT_7ff7a595ec65 = FUN_7ff7a3804d60();
  DAT_7ff7a595ec66 = FUN_7ff7a3804df0();
  DAT_7ff7a595ec70 = param_2;
  uVar6 = FUN_7ff7a3630b80(param_1);
  lVar7 = FUN_7ff7a34a8760(uVar6);
  FUN_7ff7a34ab600(param_1);
  uVar4 = *(undefined8 *)(param_3 + 0x70);
  uVar5 = *(undefined8 *)(param_3 + 0x78);
  FUN_7ff7a3294620(param_3,&DAT_7ff7a3cc57e0,3);
  local_48 = *(undefined8 *)(*(longlong *)(param_3 + 0x48) + -0x10);
  uStack_40 = *(undefined8 *)(*(longlong *)(param_3 + 0x48) + -8);
  local_38 = uVar4;
  uStack_30 = uVar5;
  puVar8 = (undefined4 *)FUN_7ff7a3468580(local_28,param_3,&local_38,&local_48);
  uVar6 = puVar8[1];
  uVar1 = puVar8[2];
  uVar2 = puVar8[3];
  lVar11 = *(longlong *)(param_3 + 0x48);
  *(undefined4 *)(lVar11 + -0x10) = *puVar8;
  *(undefined4 *)(lVar11 + -0xc) = uVar6;
  *(undefined4 *)(lVar11 + -8) = uVar1;
  *(undefined4 *)(lVar11 + -4) = uVar2;
  *(longlong *)(param_3 + 0x48) = lVar11;
  uVar4 = *(undefined8 *)(lVar11 + -0x10);
  uVar5 = *(undefined8 *)(lVar11 + -8);
  FUN_7ff7a3294620(param_3,"roots",5);
  local_38 = *(undefined8 *)(*(longlong *)(param_3 + 0x48) + -0x10);
  uStack_30 = *(undefined8 *)(*(longlong *)(param_3 + 0x48) + -8);
  local_48 = uVar4;
  uStack_40 = uVar5;
  puVar9 = (undefined4 *)FUN_7ff7a3468580(local_28,param_3,&local_48,&local_38);
  lVar11 = -1;
  uVar6 = puVar9[1];
  uVar1 = puVar9[2];
  uVar2 = puVar9[3];
  puVar8 = *(undefined4 **)(param_3 + 0x48);
  puVar8[-4] = *puVar9;
  puVar8[-3] = uVar6;
  puVar8[-2] = uVar1;
  puVar8[-1] = uVar2;
  *(undefined4 **)(param_3 + 0x48) = puVar8;
  uVar4 = *(undefined8 *)(puVar8 + -4);
  uVar5 = *(undefined8 *)(puVar8 + -2);
  if (lVar7 == 0) {
    *puVar8 = 0;
    puVar8 = puVar8 + 4;
    *(undefined4 **)(param_3 + 0x48) = puVar8;
  }
  else {
    lVar12 = -1;
    do {
      lVar12 = lVar12 + 1;
    } while (*(char *)(lVar12 + lVar7) != '\0');
    FUN_7ff7a3294620(param_3,lVar7);
    puVar8 = *(undefined4 **)(param_3 + 0x48);
  }
  local_38 = *(undefined8 *)(puVar8 + -4);
  uStack_30 = *(undefined8 *)(puVar8 + -2);
  local_48 = uVar4;
  uStack_40 = uVar5;
  puVar8 = (undefined4 *)FUN_7ff7a3468580(local_28,param_3,&local_48,&local_38);
  uVar6 = puVar8[1];
  uVar1 = puVar8[2];
  uVar2 = puVar8[3];
  lVar7 = *(longlong *)(param_3 + 0x48);
  *(undefined4 *)(lVar7 + -0x10) = *puVar8;
  *(undefined4 *)(lVar7 + -0xc) = uVar6;
  *(undefined4 *)(lVar7 + -8) = uVar1;
  *(undefined4 *)(lVar7 + -4) = uVar2;
  *(longlong *)(param_3 + 0x48) = lVar7;
  uVar4 = *(undefined8 *)(lVar7 + -0x10);
  uVar5 = *(undefined8 *)(lVar7 + -8);
  FUN_7ff7a3294620(param_3,"processEvent",0xc);
  local_38 = *(undefined8 *)(*(longlong *)(param_3 + 0x48) + -0x10);
  uStack_30 = *(undefined8 *)(*(longlong *)(param_3 + 0x48) + -8);
  local_48 = uVar4;
  uStack_40 = uVar5;
  puVar10 = (undefined8 *)FUN_7ff7a3468580(local_28,param_3,&local_48,&local_38);
  uVar4 = puVar10[1];
  puVar8 = *(undefined4 **)(param_3 + 0x48);
  *(undefined8 *)(puVar8 + -4) = *puVar10;
  *(undefined8 *)(puVar8 + -2) = uVar4;
  *(undefined4 **)(param_3 + 0x48) = puVar8;
  *puVar8 = puVar8[-8];
  puVar8[1] = puVar8[-7];
  puVar8[2] = puVar8[-6];
  puVar8[3] = puVar8[-5];
  *(undefined4 **)(param_3 + 0x48) = puVar8 + 4;
  FUN_7ff7a3473c90(param_3,0,1);
  if (param_2 == 0) {
    puVar8 = *(undefined4 **)(param_3 + 0x48);
    *puVar8 = 0;
    puVar8 = puVar8 + 4;
    *(undefined4 **)(param_3 + 0x48) = puVar8;
  }
  else {
    do {
      lVar11 = lVar11 + 1;
    } while (*(char *)(param_2 + lVar11) != '\0');
    FUN_7ff7a3294620(param_3,param_2,lVar11);
    puVar8 = *(undefined4 **)(param_3 + 0x48);
  }
  if (*(undefined4 **)(param_3 + 0x58) < puVar8 + 8) {
    FUN_7ff7a3466cd0(param_3 + 0x18,param_3,2);
  }
  FUN_7ff7a3294620(param_3,&DAT_7ff7a3cc4b48,4);
  lVar11 = *(longlong *)(param_3 + 0x48);
  uVar6 = *(undefined4 *)(lVar11 + -0x10);
  uVar1 = *(undefined4 *)(lVar11 + -0xc);
  uVar2 = *(undefined4 *)(lVar11 + -8);
  uVar3 = *(undefined4 *)(lVar11 + -4);
  *(undefined4 *)(lVar11 + -0x10) = *(undefined4 *)(lVar11 + -0x20);
  *(undefined4 *)(lVar11 + -0xc) = *(undefined4 *)(lVar11 + -0x1c);
  *(undefined4 *)(lVar11 + -8) = *(undefined4 *)(lVar11 + -0x18);
  *(undefined4 *)(lVar11 + -4) = *(undefined4 *)(lVar11 + -0x14);
  *(undefined4 *)(lVar11 + -0x20) = uVar6;
  *(undefined4 *)(lVar11 + -0x1c) = uVar1;
  *(undefined4 *)(lVar11 + -0x18) = uVar2;
  *(undefined4 *)(lVar11 + -0x14) = uVar3;
  *(longlong *)(param_3 + 0x48) = lVar11;
  FUN_7ff7a34696b0(param_3,lVar11 + -0x30);
  *(longlong *)(param_3 + 0x48) = *(longlong *)(param_3 + 0x48) + -0x20;
  return 1;
}

