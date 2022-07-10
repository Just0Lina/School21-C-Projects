#ifndef PARSSAVEDSETTINGS_H_
#define PARSSAVEDSETTINGS_H_

#define SETTINGSNUM 8
#define DEFAULT                                                               \
  {                                                                           \
    "Projection: central", "VerticesType: solid", "EdgesColor: #000000",      \
        "EdgesThickness: 1", "EdgesMethod: circle", "VerticesColor: #000000", \
        "VerticesSize: 1", "BackgroundColor: #FAFAFA"                         \
  }
//#define SETTINGSNAME "savedSettings.txt"
#define CENTRAL 0
#define PARALLEL 1
#define SOLID 0
#define DASHED 1
#define CIRCLE 1
#define SQUARE 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Color_t {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} Color_t;

typedef struct saveSettings {
  int projection;   // 0-central, 1-parallel
  int vertType;     // 0-nan 1-circle 2-square
  int edgesMethod;  // 0-norm 1-dashed
  int edgesThickness;
  int sizeVert;
  Color_t colorBack;
  Color_t colorVert;
  Color_t colorEdges;
} saveSettings;

void createDefaultSettings(FILE *settings);
void translateHexInRgb(char *token, Color_t *settingsColor);
void settingsProjection(char *token, saveSettings *savedSettStruct);
void settingsVertType(char *token, saveSettings *savedSettStruct);
void settingsColorEdg(char *token, saveSettings *savedSettStruct);
void settingsEdgThick(char *token, saveSettings *savedSettStruct);
void settingsEdgMethod(char *token, saveSettings *savedSettStruct);
void settingsColorVert(char *token, saveSettings *savedSettStruct);
void settingsSizeVert(char *token, saveSettings *savedSettStruct);
void settingsColorBack(char *token, saveSettings *savedSettStruct);
void parsFileSavedSettings(FILE *objFile, saveSettings *savedSettStruct);
void writingToFile(saveSettings *savedSettStruct, FILE *setFile);

#endif  // PARSSAVEDSETTINGS_H_
