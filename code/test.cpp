/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "se_defines.h"

SE_GLOBALS()

void test_case(std::string str) {
  std::istringstream stream(str);
  std::unordered_map<std::string, std::string> map;
  std::string line;
  while (std::getline(stream, line)) {
    std::istringstream lineStream(line);
    std::string key;
    std::string value;
    std::getline(lineStream, key, ':');
    std::getline(lineStream, value);
    if (key.size() == 0 || value.size() == 0) {
      return;
    }
    map[key] = value;
    SE_STEP(true /*if we made it here, we solved one problem*/);
  }
  if (map.size() == 0) {
    return;
  }
  SE_STEP(true /*if we made it here, we solved one problem*/);
  auto it = map.find("fnord");
  if (it != map.end()) {
    SE_STEP(true /*if we made it here, we solved one problem*/);
    SE_TARGET_STATE((it->second == "1337"));
  }
}

int main(int argc, char* argv[]) {
  std::istream* input;
  std::ifstream file;
  if (argc < 2) {
    input = &std::cin; // No file name provided, read from stdin
  } else {
    file.open(argv[1]);
    if (!file) {
      std::cerr << "Could not open the file.\n";
      return 1;
    }
    input = &file; // File opened successfully, read from file
  }
  std::string content(
      (std::istreambuf_iterator<char>(*input)),
      std::istreambuf_iterator<char>());
  test_case(content.c_str());
  return 0;
}