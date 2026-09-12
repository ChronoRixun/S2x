// image offset 0x2AF7A0 address 7ff7a343f7a0

void FUN_7ff7a343f7a0(int param_1,undefined8 param_2,undefined8 param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  char cVar3;
  undefined4 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  uint uVar7;
  int local_48 [2];
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  
  cVar3 = FUN_7ff7a340f430(param_2,param_3,"GrantedItems",&local_40);
  if (cVar3 != '\0') {
    uVar7 = 0;
    lVar5 = FUN_7ff7a340efe0(param_2,local_40);
    while ((lVar5 != 0 && (uVar7 < 0x32))) {
      local_48[0] = 0;
      cVar3 = FUN_7ff7a340f5f0(param_2,lVar5,&DAT_7ff7a3cd0d74,local_48);
      if ((cVar3 != '\0') && (local_48[0] != 0)) {
        uVar6 = (ulonglong)uVar7;
        uVar7 = uVar7 + 1;
        *(int *)(&DAT_7ff7ab973b4c + ((longlong)param_1 * 0x55 + uVar6) * 4) = local_48[0];
      }
      lVar5 = FUN_7ff7a340f240(param_2,lVar5);
    }
    lVar5 = (longlong)param_1 * 0x154;
    *(uint *)(&DAT_7ff7ab973c14 + lVar5) = uVar7;
    uVar4 = 0;
    cVar3 = FUN_7ff7a340f430(param_2,param_3,"GrantedCurrencies",&local_38);
    if (cVar3 != '\0') {
      uVar4 = FUN_7ff7a340c480(param_1,param_2,local_38,&DAT_7ff7ab973c18 + lVar5,0xd);
    }
    *(undefined4 *)(&DAT_7ff7ab973c80 + lVar5) = uVar4;
    uVar4 = param_4[1];
    uVar1 = param_4[2];
    uVar2 = param_4[3];
    *(undefined4 *)(&DAT_7ff7ab973b30 + lVar5) = *param_4;
    *(undefined4 *)(lVar5 + 0x7ff7ab973b34) = uVar4;
    *(undefined4 *)(lVar5 + 0x7ff7ab973b38) = uVar1;
    *(undefined4 *)(lVar5 + 0x7ff7ab973b3c) = uVar2;
    *(undefined8 *)(&DAT_7ff7ab973b40 + lVar5) = *(undefined8 *)(param_4 + 4);
    (&DAT_7ff7ab973b48)[lVar5] = *(undefined1 *)(param_4 + 6);
    FUN_7ff7a34052e0(param_1,3);
    cVar3 = FUN_7ff7a340f430(param_2,param_3,"DetailedInventory",&local_30);
    if (cVar3 != '\0') {
      FUN_7ff7a340c1d0(param_1,param_2,local_30,0,0);
      FUN_7ff7a343f560(param_1);
    }
  }
  return;
}

