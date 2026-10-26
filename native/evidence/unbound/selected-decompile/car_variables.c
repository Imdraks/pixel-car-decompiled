
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 *
_Z22gml_Script_scr_car_varP9CInstanceS0_R8YYRValueiPPS1_
          (int *param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined *puVar2;
  double *pdVar3;
  undefined4 *puVar4;
  double *pdVar5;
  longdouble lVar6;
  double dVar7;
  undefined4 uStack_e4;
  undefined *puStack_e0;
  undefined4 uStack_dc;
  undefined4 *puStack_d8;
  double dStack_d4;
  double dStack_cc;
  double dStack_c4;
  double dStack_bc;
  double dStack_b4;
  double dStack_ac;
  double dStack_a4;
  double dStack_9c;
  double dStack_94;
  double dStack_8c;
  double dStack_84;
  double dStack_7c;
  double dStack_74;
  double dStack_6c;
  double dStack_64;
  double dStack_5c;
  double dStack_54;
  double dStack_4c;
  double dStack_44;
  double dStack_3c;
  double dStack_34;
  double dStack_2c;
  double dStack_24;
  double dStack_1c;
  
  puStack_e0 = &UNK_00f7fc83;
  uStack_dc = 0;
  puStack_d8 = (undefined4 *)PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c;
  uStack_e4 = *(undefined4 *)PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c;
  *(undefined4 **)PTR__ZN13SYYStackTrace8s_pStartE_013c3e4c = &uStack_e4;
  if ((param_3[3] + 0xffffff & 0xfffffc) == 0) {
    func_0x0017e680(param_3);
  }
  param_3[3] = 0;
  param_3[1] = 0;
  *param_3 = 0;
  uStack_dc = 0;
  iVar1 = param_1[1];
  if (iVar1 == 0) {
    pdVar5 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
    if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) goto LAB_004a6d26;
LAB_004a6d05:
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_1c = dVar7;
  }
  else {
    pdVar5 = (double *)(iVar1 + 0x2180);
    if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) != 0) goto LAB_004a6d05;
LAB_004a6d26:
    dVar7 = *pdVar5;
  }
  puVar2 = PTR_g_GMLMathEpsilon_013c3408;
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)PTR_g_GMLMathEpsilon_013c3408 >> 0x20) ^
                       _UNK_00f75964,
                       (uint)*(undefined8 *)PTR_g_GMLMathEpsilon_013c3408 ^ _UNK_00f75960) <= dVar7)
  {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a6d5a;
LAB_004a6d97:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a6d97;
LAB_004a6d5a:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_24 = dVar7;
    }
    if (dVar7 + _UNK_00f75e90 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 1;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xbff00000;
      *puVar4 = 0;
      uStack_dc = 2;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0;
      *puVar4 = 0;
      uStack_dc = 3;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40584000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 5;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_2c = dVar7;
  }
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960) <= dVar7 + _UNK_00f75e90) {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a6f3c;
LAB_004a6f79:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a6f79;
LAB_004a6f3c:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_34 = dVar7;
    }
    if (dVar7 + _UNK_00f75e88 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 6;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40140000;
      *puVar4 = 0;
      uStack_dc = 7;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xc0240000;
      *puVar4 = 0;
      uStack_dc = 8;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40570000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 10;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_3c = dVar7;
  }
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960) <= dVar7 + _UNK_00f75e88) {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a711e;
LAB_004a715b:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a715b;
LAB_004a711e:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_44 = dVar7;
    }
    if (dVar7 + _UNK_00f75940 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 0xb;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xc0100000;
      *puVar4 = 0;
      uStack_dc = 0xc;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40260000;
      *puVar4 = 0;
      uStack_dc = 0xd;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40598000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 0xf;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_4c = dVar7;
  }
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960) <= dVar7 + _UNK_00f75940) {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a7300;
LAB_004a733d:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a733d;
LAB_004a7300:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_54 = dVar7;
    }
    if (dVar7 + _UNK_00f75e80 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 0x10;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0;
      *puVar4 = 0;
      uStack_dc = 0x11;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0;
      *puVar4 = 0;
      uStack_dc = 0x12;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40594000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 0x14;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_5c = dVar7;
  }
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960) <= dVar7 + _UNK_00f75e80) {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a74e2;
LAB_004a751f:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a751f;
LAB_004a74e2:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_64 = dVar7;
    }
    if (dVar7 + _UNK_00f75e78 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 0x15;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40180000;
      *puVar4 = 0;
      uStack_dc = 0x16;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xc0100000;
      *puVar4 = 0;
      uStack_dc = 0x17;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40594000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 0x19;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_6c = dVar7;
  }
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960) <= dVar7 + _UNK_00f75e78) {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a76c4;
LAB_004a76fb:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a76fb;
LAB_004a76c4:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_74 = dVar7;
    }
    if (dVar7 + _UNK_00f75e70 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 0x1a;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40180000;
      *puVar4 = 0;
      uStack_dc = 0x1b;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xc0100000;
      *puVar4 = 0;
      uStack_dc = 0x1c;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40564000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 0x1e;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_7c = dVar7;
  }
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960) <= dVar7 + _UNK_00f75e70) {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a789a;
LAB_004a78d1:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a78d1;
LAB_004a789a:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_84 = dVar7;
    }
    if (dVar7 + _UNK_00f75e68 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 0x1f;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40180000;
      *puVar4 = 0;
      uStack_dc = 0x20;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xc0100000;
      *puVar4 = 0;
      uStack_dc = 0x21;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40598000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 0x23;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_8c = dVar7;
  }
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960) <= dVar7 + _UNK_00f75e68) {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a7a70;
LAB_004a7aa7:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a7aa7;
LAB_004a7a70:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_94 = dVar7;
    }
    if (dVar7 + _UNK_00f75e60 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 0x24;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xbff00000;
      *puVar4 = 0;
      uStack_dc = 0x25;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xbff00000;
      *puVar4 = 0;
      uStack_dc = 0x26;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40570000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 0x28;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_9c = dVar7;
  }
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960) <= dVar7 + _UNK_00f75e60) {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a7c46;
LAB_004a7c7d:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a7c7d;
LAB_004a7c46:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_a4 = dVar7;
    }
    if (dVar7 + _UNK_00f75e58 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 0x29;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xbff00000;
      *puVar4 = 0;
      uStack_dc = 0x2a;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xbff00000;
      *puVar4 = 0;
      uStack_dc = 0x2b;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40570000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 0x2d;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_ac = dVar7;
  }
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960) <= dVar7 + _UNK_00f75e58) {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a7e1c;
LAB_004a7e53:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a7e53;
LAB_004a7e1c:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_b4 = dVar7;
    }
    if (dVar7 + _UNK_00f75e50 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 0x2e;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xbff00000;
      *puVar4 = 0;
      uStack_dc = 0x2f;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xbff00000;
      *puVar4 = 0;
      uStack_dc = 0x30;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x4054c000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 0x32;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_bc = dVar7;
  }
  if ((double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960) <= dVar7 + _UNK_00f75e50) {
    iVar1 = param_1[1];
    if (iVar1 == 0) {
      pdVar3 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
      if ((*(uint *)((int)pdVar3 + 0xc) & 0xffffff) != 0) goto LAB_004a7ff2;
LAB_004a8029:
      dVar7 = *pdVar3;
    }
    else {
      pdVar3 = (double *)(iVar1 + 0x2180);
      if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) == 0) goto LAB_004a8029;
LAB_004a7ff2:
      lVar6 = (longdouble)func_0x001785e0(pdVar3);
      dVar7 = (double)lVar6;
      dStack_c4 = dVar7;
    }
    if (dVar7 + _UNK_00f75e48 <
        (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                         (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
      uStack_dc = 0x33;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xbff00000;
      *puVar4 = 0;
      uStack_dc = 0x34;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0xbff00000;
      *puVar4 = 0;
      uStack_dc = 0x35;
      if (param_1[1] == 0) {
        puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
      }
      else {
        puVar4 = (undefined4 *)(param_1[1] + 0x2370);
      }
      if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
        func_0x0017e680(puVar4);
      }
      puVar4[3] = 0;
      puVar4[1] = 0x40550000;
      *puVar4 = 0;
    }
  }
  uStack_dc = 0x37;
  if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) {
    dVar7 = *pdVar5;
  }
  else {
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_cc = dVar7;
  }
  if (dVar7 + _UNK_00f75e48 <
      (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) goto LAB_004a8319;
  iVar1 = param_1[1];
  if (iVar1 == 0) {
    pdVar5 = (double *)(**(code **)(*param_1 + 8))(param_1,0x218);
    if ((*(uint *)((int)pdVar5 + 0xc) & 0xffffff) == 0) goto LAB_004a81f3;
LAB_004a81df:
    lVar6 = (longdouble)func_0x001785e0(pdVar5);
    dVar7 = (double)lVar6;
    dStack_d4 = dVar7;
  }
  else {
    pdVar5 = (double *)(iVar1 + 0x2180);
    if ((*(uint *)(iVar1 + 0x218c) & 0xffffff) != 0) goto LAB_004a81df;
LAB_004a81f3:
    dVar7 = *pdVar5;
  }
  if (dVar7 + _UNK_00f75e40 <
      (double)CONCAT44((uint)((ulonglong)*(undefined8 *)puVar2 >> 0x20) ^ _UNK_00f75964,
                       (uint)*(undefined8 *)puVar2 ^ _UNK_00f75960)) {
    uStack_dc = 0x38;
    if (param_1[1] == 0) {
      puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f7);
    }
    else {
      puVar4 = (undefined4 *)(param_1[1] + 0x4f70);
    }
    if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
      func_0x0017e680(puVar4);
    }
    puVar4[3] = 0;
    puVar4[1] = 0xbff00000;
    *puVar4 = 0;
    uStack_dc = 0x39;
    if (param_1[1] == 0) {
      puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x4f6);
    }
    else {
      puVar4 = (undefined4 *)(param_1[1] + 0x4f60);
    }
    if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
      func_0x0017e680(puVar4);
    }
    puVar4[3] = 0;
    puVar4[1] = 0xbff00000;
    *puVar4 = 0;
    uStack_dc = 0x3a;
    if (param_1[1] == 0) {
      puVar4 = (undefined4 *)(**(code **)(*param_1 + 8))(param_1,0x237);
    }
    else {
      puVar4 = (undefined4 *)(param_1[1] + 0x2370);
    }
    if ((puVar4[3] + 0xffffff & 0xfffffc) == 0) {
      func_0x0017e680(puVar4);
    }
    puVar4[3] = 0;
    puVar4[1] = 0x4058c000;
    *puVar4 = 0;
  }
LAB_004a8319:
  *puStack_d8 = uStack_e4;
  return param_3;
}

