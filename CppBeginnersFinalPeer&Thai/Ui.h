#pragma once
#include "Level.h"
#include "Unit.h"
#include <queue>
#include <string>

class Ui {
private:
    static std::queue<std::string> log;
    static const int MAX_LOG_SIZE = 6;

public:
    static void PrintFrame(Level& currentLevel, Map::mapType level, Unit& player);
    static void AddToLog(const std::string& message);
    static void PrintOpeningAndTutorials();
    static void RequireEnterPressToProgress();
private:
    static void PrintLog();
};

