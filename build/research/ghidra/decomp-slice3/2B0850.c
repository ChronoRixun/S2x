// image offset 0x2B0850 address 7ff7a3440850

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_7ff7a3440850(int param_1,uint param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  char *pcVar7;
  longlong lVar8;
  char *pcVar9;
  undefined4 uVar10;
  longlong lVar11;
  undefined *puVar12;
  undefined1 auStack_518 [32];
  undefined4 local_4f8;
  undefined8 local_4e8 [2];
  undefined1 local_4d8 [144];
  undefined1 local_448 [1024];
  ulonglong local_48;
  
  local_48 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_518;
  FUN_7ff7a38f34d0("mp/supplyDropTypes.csv",local_4e8);
  uVar6 = FUN_7ff7a38fa3d0(&DAT_7ff7a3cc2f5c,param_2);
  pcVar7 = (char *)FUN_7ff7a38f3560(local_4e8[0],1,uVar6);
  pcVar9 = pcVar7;
  if ((pcVar7 != (char *)0x0) && (*pcVar7 != '\0')) {
    uVar6 = FUN_7ff7a3919870(param_1);
    lVar8 = FUN_7ff7a33981b0(0,param_1,0x7f);
    pcVar9 = (char *)FUN_7ff7a39c9650(lVar8);
    if (((char)pcVar9 != '\0') && (pcVar9 = (char *)FUN_7ff7a39c9710(lVar8), (char)pcVar9 != '\0'))
    {
      memset(&DAT_7ff7ab973fa0,0,0x1800);
      iVar4 = FUN_7ff7a3b94cd0(&DAT_7ff7ab973fa0,0x1800,&DAT_7ff7a3cd06cc);
      iVar5 = FUN_7ff7a3b94cd0(&DAT_7ff7ab973fa0 + iVar4,0x1800 - iVar4,"\"Version\": %d",0);
      iVar4 = iVar4 + iVar5;
      iVar5 = FUN_7ff7a3b94cd0(&DAT_7ff7ab973fa0 + iVar4,0x1800 - iVar4,",\"Action\": \"%s\"",
                               "open_supply_drop");
      iVar4 = iVar4 + iVar5;
      iVar5 = FUN_7ff7a3b94cd0(&DAT_7ff7ab973fa0 + iVar4,0x1800 - iVar4,",\"ClientTx\": \"%s\"",
                               param_3);
      iVar4 = iVar4 + iVar5;
      iVar5 = FUN_7ff7a3b94cd0(&DAT_7ff7ab973fa0 + iVar4,0x1800 - iVar4,",\"SupplyDropID\": \"%s\"",
                               pcVar7);
      iVar4 = iVar4 + iVar5;
      local_4f8 = 0xffffffff;
      iVar5 = FUN_7ff7a3b94cd0(&DAT_7ff7ab973fa0 + iVar4,0x1800 - iVar4,
                               ",\"InventoryVersion\": [%d, %d]",0xffffffff);
      FUN_7ff7a3b94cd0(&DAT_7ff7ab973fa0 + (iVar4 + iVar5),0x1800 - (iVar4 + iVar5),
                       &DAT_7ff7a3cd0704);
      lVar11 = (longlong)param_1 * 0xf8;
      puVar12 = &DAT_7ff7ab971440 + lVar11;
      FUN_7ff7a3396000(puVar12);
      *(undefined8 *)(&DAT_7ff7ab971508 + lVar11) = uVar6;
      *(undefined4 *)(&DAT_7ff7ab971500 + lVar11) = 1;
      uVar10 = param_3[1];
      uVar1 = param_3[2];
      uVar2 = param_3[3];
      *(undefined4 *)(&DAT_7ff7ab971510 + lVar11) = *param_3;
      *(undefined4 *)(lVar11 + 0x7ff7ab971514) = uVar10;
      *(undefined4 *)(lVar11 + 0x7ff7ab971518) = uVar1;
      *(undefined4 *)(lVar11 + 0x7ff7ab97151c) = uVar2;
      *(undefined8 *)(&DAT_7ff7ab971520 + lVar11) = *(undefined8 *)(param_3 + 4);
      (&DAT_7ff7ab971528)[lVar11] = *(undefined1 *)(param_3 + 6);
      FUN_7ff7a3bcb8f0(puVar12,&DAT_7ff7ab973fa0);
      FUN_7ff7a39c9700(lVar8,puVar12);
      *(undefined1 *)(lVar8 + 2) = 1;
      *(code **)(lVar8 + 0x30) = thunk_FUN_7ff7a3be793b;
      *(code **)(lVar8 + 0x40) = FUN_7ff7a34402d0;
      *(code **)(lVar8 + 0x38) = FUN_7ff7a34403b0;
      FUN_7ff7a39c97e0(lVar8);
      uVar10 = 0;
      cVar3 = FUN_7ff7a3248cb0();
      if (cVar3 == '\0') {
        cVar3 = FUN_7ff7a324a660();
        if (cVar3 != '\0') {
          uVar10 = 1;
        }
      }
      else {
        uVar10 = 2;
      }
      FUN_7ff7a3384870(local_4d8,uVar6,local_448,0x400);
      FUN_7ff7a3382c30(local_4d8,"telemetry_open_sd_event");
      FUN_7ff7a3384560(local_4d8,"supply_drop");
      FUN_7ff7a3385510(local_4d8,&DAT_7ff7a3cd07fc,param_2 & 0xffff);
      FUN_7ff7a3385510(local_4d8,"hq_context",uVar10);
      FUN_7ff7a33861d0(local_4d8,"cl_transaction_id",param_3,0);
      FUN_7ff7a33849a0(local_4d8);
      FUN_7ff7a3385830(local_4d8);
      return 1;
    }
  }
  return (ulonglong)pcVar9 & 0xffffffffffffff00;
}

