/*
* This file is part of the BTCCollider distribution (https://github.com/JeanLucPons/Kangaroo).
* Copyright (c) 2020 Jean Luc PONS.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GPUENGINEH
#define GPUENGINEH

#include <vector>
#include "../SECPK1/SECP256k1.h"

#define ITEM_SIZE   72
#define ITEM_SIZE32 (ITEM_SIZE/4)

#define GPU_GRP_SIZE 128
#define NB_RUN 16

typedef struct {
  Int x;
  Int d;
  uint64_t kIdx;
} ITEM;

class GPUEngine {

public:

  GPUEngine(int nbThreadGroup,int nbThreadPerGroup,int gpuId,uint32_t maxFound);
  ~GPUEngine();
  void SetParams(uint64_t dpMask,uint64_t jumpModulo);
  void SetKangaroos(Int *px,Int *py,Int *d,bool freePinned = true);
  void GetKangaroos(Int *px,Int *py,Int *d);
  void SetKangaroo(uint64_t kIdx,Int *px,Int *py,Int *d);
  bool Launch(std::vector<ITEM> &hashFound,bool spinWait = false);
  int GetNbThread();
  int GetGroupSize();
  int GetMemory();
  static void GenerateCode(Secp256K1 *secp);
  bool callKernelAndWait();
  bool callKernel();

  std::string deviceName;

  static void *AllocatePinnedMemory(size_t size);
  static void FreePinnedMemory(void *buff);
  static void PrintCudaInfo();
  static bool GetGridSize(int gpuId,int *x,int *y);

private:


  int nbThread;
  int nbThreadPerGroup;
  int kangarooSize;
  uint64_t *inputKangaroo;
  uint64_t *inputKangarooPinned;
  uint64_t *inputKangarooSinglePinned;
  uint32_t *outputItem;
  uint32_t *outputItemPinned;
  bool initialised;
  bool lostWarning;
  uint32_t maxFound;
  uint32_t outputSize;
  uint64_t dpMask;
  uint64_t jumpModulo;

};

#endif // GPUENGINEH
