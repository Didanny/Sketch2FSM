#pragma once

#include "stdafx.h"

#include "./../../SketchAnalyzer.h"

#ifdef SKETCH2FSM_EXPORTS
#define SKETCH2FSM_API __declspec(dllexport)
#else
#define SKETCH2FSM_API __declspec(dllimport)
#endif

extern SketchAnalyzer* sa;

extern "C" {
	SKETCH2FSM_API void Start();
	SKETCH2FSM_API void LoadSketch(const char* t_path, int t_length);
	SKETCH2FSM_API void FindConnectedComponents();
	SKETCH2FSM_API void FindContainers();
	SKETCH2FSM_API void FindCircles();
	SKETCH2FSM_API void FindCharacters();
	SKETCH2FSM_API void FindArrows();
	SKETCH2FSM_API void ParseLabels();
	SKETCH2FSM_API void CreateStates();
	SKETCH2FSM_API void CreateTransitions();
	SKETCH2FSM_API void OutputFile();
}