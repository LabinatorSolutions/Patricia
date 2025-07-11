#pragma once
#include "defs.h"
#include <cmath>
#include <iostream>
#include <vector>

MultiArray<int, MaxSearchDepth + 1, ListSize> LMRTable;


struct Parameter {
  std::string name;
  int &value;
  int min, max;
};

std::vector<Parameter> params;

// SPSA parameter code is based off Clover
// (https://github.com/lucametehau/CloverEngine)

struct CreateParam {
  int _value;
  CreateParam(std::string name, int value, int min, int max) : _value(value) {
    params.push_back({name, _value, min, max});
  }

  operator int() const { return _value; }
};


#define TUNE_PARAM(name, value, min, max)                                      \
  CreateParam name(#name, value, min, max);


TUNE_PARAM(NMPMinDepth, 3, 1, 5);
TUNE_PARAM(NMPBase, 4, 1, 5);
TUNE_PARAM(NMPDepthDiv, 5, 3, 9);
TUNE_PARAM(NMPEvalDiv, 175, 100, 300);
TUNE_PARAM(RFPMargin, 85, 50, 110);
TUNE_PARAM(RFPMaxDepth, 10, 6, 12);
TUNE_PARAM(ProbcutMargin, 250, 150, 400);
TUNE_PARAM(LMRBase, 4, 2, 8);
TUNE_PARAM(LMRRatio, 20, 15, 30);
TUNE_PARAM(LMPBase, 2, 1, 5);
TUNE_PARAM(LMPDepth, 6, 3, 7);
TUNE_PARAM(SEDepth, 5, 4, 10);
TUNE_PARAM(HistPruningDepth, 4, 2, 7);
TUNE_PARAM(SEDoubleExtMargin, 18, 10, 30);
TUNE_PARAM(SETripleExtMargin, 126, 75, 175);
TUNE_PARAM(FPDepth, 9, 5, 11);
TUNE_PARAM(FPMargin1, 98, 50, 150);
TUNE_PARAM(FPMargin2, 121, 75, 175);
TUNE_PARAM(IIRMinDepth, 2, 1, 5);
TUNE_PARAM(SeePruningDepth, 7, 5, 11);
TUNE_PARAM(SeePruningQuietMargin, -86, -110, -50);
TUNE_PARAM(SeePruningNoisyMargin, -94, -150, -50);
TUNE_PARAM(HistBonus, 291, 200, 400);
TUNE_PARAM(HistMax, 2476, 1500, 3500);
TUNE_PARAM(HistDiv, 9818, 5000, 15000);
TUNE_PARAM(AgeDiffDiv, 5, 2, 6);
TUNE_PARAM(CorrWeight, 25, 10, 40);
TUNE_PARAM(LMRMinDepth, 3, 2, 6);
TUNE_PARAM(AspStartWindow, 20, 10, 30);
TUNE_PARAM(NodeTmFactor1, 149, 100, 200);
TUNE_PARAM(NodeTmFactor2, 177, 125, 225);
TUNE_PARAM(BmFactor1, 152, 100, 200);


void print_params_for_ob() {
  for (auto &param : params) {
    std::cout << param.name << ", int, " << param.value << ", " << param.min
              << ", " << param.max << ", "
              << std::max(0.5, (param.max - param.min) / 20.0) << ", 0.002\n";
  }
}

void init_LMR() {
  for (int i = 0; i < MaxSearchDepth; i++) {
    for (int n = 0; n < ListSize; n++) {
      LMRTable[i][n] = LMRBase / 10.0 + log(i) * log(n) / (LMRRatio / 10.0);
    }
  }
}
