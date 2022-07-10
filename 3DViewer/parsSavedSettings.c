#include "parsSavedSettings.h"

void createDefaultSettings(FILE *settings) {
  const char *defSettings[] = DEFAULT;
  for (int i = 0; i < SETTINGSNUM; i++) {
    fprintf(settings, "%s\n", defSettings[i]);
  }
}

void translateHexInRgb(char *token, Color_t *settingsColor) {
  unsigned char *oneColor = &settingsColor->red;
  for (int i = 0; i < 3; i++) {
    sscanf(token + i * 2, "%2hhx", oneColor);
    oneColor = (unsigned char *)((unsigned long)oneColor) + sizeof(char);
  }
}

void settingsProjection(char *token, saveSettings *savedSettStruct) {
  char *crutch;
  token = strtok_r(token, " ", &crutch);
  if (!strncmp("central", token, (size_t)7)) {
    savedSettStruct->projection = CENTRAL;
  } else {
    savedSettStruct->projection = PARALLEL;
  }
}

void settingsEdgMethod(char *token, saveSettings *savedSettStruct) {
  char *crutch;
  token = strtok_r(token, " ", &crutch);
  if (!strncmp("dashed", token, (size_t)6)) {
    savedSettStruct->edgesMethod = DASHED;
  } else {
    savedSettStruct->edgesMethod = SOLID;
  }
}

void settingsColorEdg(char *token, saveSettings *savedSettStruct) {
  char *crutch;
  token = strtok_r(token, " ", &crutch);
  if (!strncmp("#", token, (size_t)1)) {
    token = strtok_r(token, "#", &crutch);
    translateHexInRgb(token, &savedSettStruct->colorEdges);
  } else {
    savedSettStruct->colorEdges.red = 0;
    savedSettStruct->colorEdges.green = 0;
    savedSettStruct->colorEdges.blue = 0;
  }
}

void settingsEdgThick(char *token, saveSettings *savedSettStruct) {
  char *crutch;
  token = strtok_r(token, " ", &crutch);
  if (atoi(token) == 0 || !token[0]) {
    savedSettStruct->edgesThickness = 1;
  } else {
    savedSettStruct->edgesThickness = atoi(token);
  }
}

void settingsVertType(char *token, saveSettings *savedSettStruct) {
  char *crutch;
  token = strtok_r(token, " ", &crutch);
  if (!strncmp("none", token, (size_t)4)) {
    savedSettStruct->vertType = 0;
  } else if (!strncmp("circle", token, (size_t)6)) {
    savedSettStruct->vertType = CIRCLE;
  } else {
    savedSettStruct->vertType = SQUARE;
  }
}

void settingsColorVert(char *token, saveSettings *savedSettStruct) {
  char *crutch;
  token = strtok_r(token, " ", &crutch);
  if (!strncmp("#", token, (size_t)1)) {
    token = strtok_r(token, "#", &crutch);
    translateHexInRgb(token, &(savedSettStruct->colorVert));
  } else {
    savedSettStruct->colorVert.red = 0;
    savedSettStruct->colorVert.green = 0;
    savedSettStruct->colorVert.blue = 0;
  }
}

void settingsSizeVert(char *token, saveSettings *savedSettStruct) {
  char *crutch;
  token = strtok_r(token, " ", &crutch);
  if (atoi(token) == 0) {
    savedSettStruct->sizeVert = 1;
  } else {
    savedSettStruct->sizeVert = atoi(token);
  }
}

void settingsColorBack(char *token, saveSettings *savedSettStruct) {
  char *crutch;
  token = strtok_r(token, " ", &crutch);
  if (!strncmp("#", token, (size_t)1)) {
    token = strtok_r(token, "#", &crutch);
    translateHexInRgb(token, &savedSettStruct->colorBack);
  } else {
    savedSettStruct->colorBack.red = 255;
    savedSettStruct->colorBack.green = 255;
    savedSettStruct->colorBack.blue = 255;
  }
}

void parsFileSavedSettings(FILE *objFile, saveSettings *savedSettStruct) {
  if (ftell(objFile)) {
    fseek(objFile, 0, SEEK_SET);
    char *arr = NULL;
    while (!feof(objFile)) {
      char *crutch;
      size_t len;
      getline(&arr, &len, objFile);
      strtok_r(arr, " ", &crutch);
      if (!strncmp("Projection", arr, (size_t)10)) {
        settingsProjection(crutch, savedSettStruct);
      } else if (!strncmp("VerticesType", arr, (size_t)12)) {
        settingsVertType(crutch, savedSettStruct);
      } else if (!strncmp("ColorEdges", arr, (size_t)10)) {
        settingsColorEdg(crutch, savedSettStruct);
      } else if (!strncmp("EdgesThickness", arr, (size_t)14)) {
        settingsEdgThick(crutch, savedSettStruct);
      } else if (!strncmp("EdgesMethod", arr, (size_t)11)) {
        settingsEdgMethod(crutch, savedSettStruct);
      } else if (!strncmp("ColorVertices", arr, (size_t)13)) {
        settingsColorVert(crutch, savedSettStruct);
      } else if (!strncmp("SizeVertices", arr, (size_t)12)) {
        settingsSizeVert(crutch, savedSettStruct);
      } else if (!strncmp("ColorBackground", arr, (size_t)15)) {
        settingsColorBack(crutch, savedSettStruct);
      }
    }
  } else {
    createDefaultSettings(objFile);
  }
}

void writingToFile(saveSettings *savedSettStruct, FILE *setFile) {
  if (!savedSettStruct->projection) {
    fprintf(setFile, "Projection: central\n");
  } else {
    fprintf(setFile, "Projection: parallel\n");
  }

  if (savedSettStruct->edgesMethod) {
    fprintf(setFile, "EdgesMethod: dashed\n");
  } else {
    fprintf(setFile, "EdgesMethod: solid\n");
  }

  if (savedSettStruct->edgesThickness) {
    fprintf(setFile, "EdgesThickness: %d\n", savedSettStruct->edgesThickness);
  } else {
    fprintf(setFile, "EdgesThickness: 1\n");
  }

  if (savedSettStruct->sizeVert) {
    fprintf(setFile, "SizeVertices: %d\n", savedSettStruct->sizeVert);
  } else {
    fprintf(setFile, "SizeVertices: 1\n");
  }

  if (savedSettStruct->vertType == SQUARE) {
    fprintf(setFile, "VerticesType: square\n");
  } else if (savedSettStruct->vertType == CIRCLE) {
    fprintf(setFile, "VerticesType: circle\n");
  } else {
    fprintf(setFile, "VerticesType: none\n");
  }

  fprintf(setFile, "ColorVertices: #%.2X%.2X%.2X\n",
          savedSettStruct->colorVert.red, savedSettStruct->colorVert.green,
          savedSettStruct->colorVert.blue);

  fprintf(setFile, "ColorEdges: #%.2X%.2X%.2X\n",
          savedSettStruct->colorEdges.red, savedSettStruct->colorEdges.green,
          savedSettStruct->colorEdges.blue);

  fprintf(setFile, "ColorBackground: #%.2X%.2X%.2X\n",
          savedSettStruct->colorBack.red, savedSettStruct->colorBack.green,
          savedSettStruct->colorBack.blue);
}
