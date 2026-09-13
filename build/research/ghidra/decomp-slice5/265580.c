// image offset 0x265580 address 7ff7a33f5580

void FUN_7ff7a33f51e0(undefined4 *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar1 = (float)FUN_7ff7a3acc5d8(*param_1,0x3c4fcdac);
  fVar2 = (float)FUN_7ff7a3acc5d8(param_1[1],0x3c4fcdac);
  fVar3 = (float)FUN_7ff7a3acc5d8(param_1[2],0x3c4fcdac);
  fVar4 = fVar1 - 0.8359375;
  if (fVar4 <= 0.0) {
    fVar4 = 0.0;
  }
  fVar1 = (float)FUN_7ff7a3acc5d8(fVar4 / (18.851562 - fVar1 * 18.6875),0x40c8e06b);
  fVar4 = fVar2 - 0.8359375;
  if (fVar4 <= 0.0) {
    fVar4 = 0.0;
  }
  fVar8 = fVar1 * 10000.0 * 0.003;
  fVar1 = (float)FUN_7ff7a3acc5d8(fVar4 / (18.851562 - fVar2 * 18.6875),0x40c8e06b);
  fVar1 = fVar1 * 10000.0 * 0.003;
  fVar2 = fVar3 - 0.8359375;
  if (fVar2 <= 0.0) {
    fVar2 = 0.0;
  }
  fVar2 = (float)FUN_7ff7a3acc5d8(fVar2 / (18.851562 - fVar3 * 18.6875),0x40c8e06b);
  fVar3 = fVar2 * 10000.0 * 0.003;
  fVar2 = fVar8;
  if (fVar8 <= fVar1) {
    fVar2 = fVar1;
  }
  if (fVar2 <= fVar3) {
    fVar2 = fVar3;
  }
  fVar4 = (float)FUN_7ff7a33f55b0(fVar2,0x3ecccccd);
  if (fVar4 == 0.0) {
    fVar4 = 0.0;
  }
  else {
    fVar4 = fVar4 / fVar2;
  }
  fVar2 = (float)FUN_7ff7a33f55b0(fVar8,0x3ecccccd);
  fVar5 = (float)FUN_7ff7a33f55b0(fVar1,0x3ecccccd);
  fVar6 = (float)FUN_7ff7a33f55b0(fVar3,0x3ecccccd);
  fVar2 = (fVar8 * fVar4 - fVar2) + fVar2;
  fVar7 = 1.0 / DAT_7ff7a3f98430;
  fVar6 = (fVar3 * fVar4 - fVar6) + fVar6;
  fVar5 = (fVar1 * fVar4 - fVar5) + fVar5;
  fVar1 = (float)FUN_7ff7a3acc5d8(DAT_7ff7ab0bf700,fVar7);
  fVar3 = (float)FUN_7ff7a3acc5d8(DAT_7ff7a3f9842c,fVar7);
  fVar4 = (float)FUN_7ff7a3acc5d8(fVar3 - fVar1);
  fVar4 = 1.0 / fVar4;
  fVar8 = (fVar2 * 1.6605 - fVar5 * 0.5877) - fVar6 * 0.0728;
  fVar1 = -(fVar1 / (fVar3 - fVar1));
  if (1.0 <= fVar8) {
    fVar8 = 1.0;
  }
  fVar3 = 0.0;
  if (0.0 <= fVar8 * fVar4) {
    fVar3 = fVar8 * fVar4;
  }
  fVar3 = (float)FUN_7ff7a3acc5d8(fVar3,fVar7);
  *param_2 = fVar3 + fVar1;
  fVar3 = (fVar5 * 1.133 - fVar2 * 0.1246) - fVar6 * 0.0084;
  if (1.0 <= fVar3) {
    fVar3 = 1.0;
  }
  fVar8 = 0.0;
  if (0.0 <= fVar3 * fVar4) {
    fVar8 = fVar3 * fVar4;
  }
  fVar3 = (float)FUN_7ff7a3acc5d8(fVar8,fVar7);
  param_2[1] = fVar3 + fVar1;
  fVar2 = (fVar2 * -0.0182 - fVar5 * 0.1006) + fVar6 * 1.1187;
  if (1.0 <= fVar2) {
    fVar2 = 1.0;
  }
  fVar3 = 0.0;
  if (0.0 <= fVar2 * fVar4) {
    fVar3 = fVar2 * fVar4;
  }
  fVar2 = (float)FUN_7ff7a3acc5d8(fVar3,fVar7);
  param_2[2] = fVar2 + fVar1;
  return;
}

