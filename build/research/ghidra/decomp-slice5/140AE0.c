// image offset 0x140AE0 address 7ff7a32d0ae0

void FUN_7ff7a32d0ae0(longlong param_1)

{
  int iVar1;
  
  FUN_7ff7a34737b0(param_1,"Engine",&PTR_s_PlaySound_7ff7a3cc7f30);
  iVar1 = (int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4);
  if (0 < iVar1) {
    iVar1 = 1;
  }
  *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + (longlong)iVar1 * -0x10;
  FUN_7ff7a3baf550(param_1);
  FUN_7ff7a34737b0(param_1,"Friends",&PTR_s_IsEliteClanAllowed_7ff7a3cca8c0);
  iVar1 = (int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4);
  if (0 < iVar1) {
    iVar1 = 1;
  }
  *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + (longlong)iVar1 * -0x10;
  FUN_7ff7a34ccfb0(param_1);
  FUN_7ff7a34cd000(param_1);
  FUN_7ff7a34d1890(param_1);
  FUN_7ff7a34be940(param_1);
  FUN_7ff7a34d3140(param_1);
  FUN_7ff7a3429ff0(param_1);
  FUN_7ff7a34d0910(param_1);
  FUN_7ff7a3412570(param_1);
  FUN_7ff7a33378d0(param_1);
  FUN_7ff7a3338bd0(param_1);
  FUN_7ff7a34a1030(param_1);
  FUN_7ff7a34737b0(param_1,"MatchRules",&PTR_s_SelectSaveDevice_7ff7a3ccae90);
  iVar1 = (int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4);
  if (0 < iVar1) {
    iVar1 = 1;
  }
  *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + (longlong)iVar1 * -0x10;
  FUN_7ff7a34b27b0(param_1);
  FUN_7ff7a34a54b0(param_1);
  FUN_7ff7a3500500(param_1);
  FUN_7ff7a34737b0(param_1,"DCache",&PTR_s_ClearDCache_7ff7a3cc7ea0);
  iVar1 = (int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4);
  if (0 < iVar1) {
    iVar1 = 1;
  }
  *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + (longlong)iVar1 * -0x10;
  FUN_7ff7a34737b0(param_1,"Patch",&PTR_s_PatchProgressPercent_7ff7a3cc7ee0);
  iVar1 = (int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4);
  if (0 < iVar1) {
    iVar1 = 1;
  }
  *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + (longlong)iVar1 * -0x10;
  FUN_7ff7a34fc250(param_1);
  FUN_7ff7a38cada0(param_1);
  return;
}

