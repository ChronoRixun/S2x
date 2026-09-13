// image offset 0xA48EB0 address 7ff7a3bd8eb0

void FUN_7ff7a3bd8eb0(longlong param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 *puVar2;
  byte bVar3;
  ulonglong uVar4;
  byte bVar5;
  bool bVar6;
  
  bVar5 = *(byte *)(param_1 + 0x1c);
  if (9 < bVar5) {
    bVar5 = 10;
  }
  cVar1 = FUN_7ff7a3c07870(param_2,bVar5);
  bVar6 = cVar1 != '\0';
  uVar4 = 0;
  if (bVar5 != 0) {
    do {
      if (bVar6) {
        puVar2 = (undefined8 *)(uVar4 * 0x38 + 0x78 + param_1);
        cVar1 = (**(code **)*puVar2)(puVar2,param_2);
        if (cVar1 == '\0') goto LAB_7ff7a3bd8f12;
        bVar6 = true;
      }
      else {
LAB_7ff7a3bd8f12:
        bVar6 = false;
      }
      bVar3 = (char)uVar4 + 1;
      uVar4 = (ulonglong)bVar3;
    } while (bVar3 < bVar5);
  }
  return;
}

